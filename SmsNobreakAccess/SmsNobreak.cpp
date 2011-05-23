/*
***************************************************************************
*    Copyright (C) 2008 by Roberto Cássio Silva do Nascimento Júnior      *
*    roberto.rcj@gmail.com                                                *
***************************************************************************
*    This file is part of MoLiNoS.                                        *
*                                                                         *
*    MoLiNoS is free software: you can redistribute it and/or modify      *
*    it under the terms of the GNU General Public License as published by *
*    the Free Software Foundation, either version 3 of the License, or    *
*    (at your option) any later version.                                  *
*                                                                         *
*    MoLiNoS is distributed in the hope that it will be useful,           *
*    but WITHOUT ANY WARRANTY; without even the implied warranty of       *
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
*    GNU General Public License for more details.                         *
*                                                                         *
*    You should have received a copy of the GNU General Public License    *
*    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
***************************************************************************
*/

using namespace std;
#include "Util.h"
#include "SerialAccesser.h"
#include "SmsNobreak.h"

///////////////////////
// Private functions //	
///////////////////////
SmsNobreak::SmsNobreak(std::string serialPort)
{
	_serial.SetPort(serialPort);
}

bool SmsNobreak::SendNobreakInitCommands()
{
	// first of all, open the communication port, of course
	if (!_serial.Open())
	{
		return false;
	}
	// send the bytes the nobreak expects at startup,
	// just as seen on the serial communication logs
	ByteBuffer buffer;
	buffer.push_back(0x49);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0xB7);
	buffer.push_back(0x0D);
	
	if (!_serial.SendData(buffer))
	{
		return false;
	}
	sleep_ms(200);
	buffer.clear();
	buffer.push_back(0x49);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0xB7);
	buffer.push_back(0x0D);
	if (!_serial.SendData(buffer))
	{
		return false;
	}
	sleep_ms(200);
	buffer.clear();
	buffer.push_back(0x46);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0xBA);
	buffer.push_back(0x0D);
	if (!_serial.SendData(buffer))
	{
		return false;
	}
	sleep_ms(200);	
	buffer.clear();
	if (_serial.ReadData(buffer, 2000))
	{
		if (buffer.size() == 0)
		{
			return false;
		}
		sleep_ms(2000);
	}
	return true;
}

bool SmsNobreak::QueryNobreakAndStoreData()
{
	ByteBuffer buffer;
	// initialize buffer with the nobreak's query string
	buffer.push_back(0x51);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0);
	buffer.push_back(0xAF);
	buffer.push_back(0x0D);
			
	// send string to nobreak asking for current status
	if (!_serial.SendData(buffer))
	{
		return false;
	}
	buffer.clear();
	// reuse the same buffer to get the answer
	if (!_serial.ReadData(buffer, 1000))
	{
		return false;
	}
	return ParseAndStoreData(buffer);
}

bool SmsNobreak::StartPollingThread()
{
	pthread_t thread;
	int errCode = pthread_create( &thread, NULL, 
		SmsNobreak::PollingThreadEntryPoint, this);
	return (errCode == 0);
}

void* SmsNobreak::PollingThreadEntryPoint(void* smsNobreak)
{
	SmsNobreak *runner = (SmsNobreak*) smsNobreak;
	runner->Polling();
	return NULL;
}

void SmsNobreak::Polling()
{
	while (_monitoringActive)
	{
		if (!QueryNobreakAndStoreData())
		{
			// some problem ocurred; since we currently don't know enough about
			// the protocol to handle it, just stop monitoring
			StopMonitoring();
		}
		sleep_ms(500);
	}	
}

bool SmsNobreak::ParseAndStoreData(const ByteBuffer& inputData)
{
	bool wellParsed = false;
	if (inputData.size() == 18)
	{
		// Byte #00 - Unknown
		// Byte #01 - Unknown
		// Byte #02 - Unknown
		// Byte #03 - Higher 8 bits of input voltage
		// Byte #04 - Lower 8 bits of input voltage
		// Byte #05 - Higher 8 bits of output voltage
		// Byte #06 - Lower 8 bits of output voltage
		// Byte #07 - Higher 8 bits of output power load
		// Byte #08 - Lower 8 bits of output power load
		// Byte #09 - Higher 8 bits of input frequency
		// Byte #10 - Lower 8 bits of input frequency
		// Byte #11 - Higher 8 bits of battery remaining load
		// Byte #12 - Lower 8 bits of battery remaining load
		// Byte #13 - Higher 8 bits of temperature
		// Byte #14 - Lower 8 bits of temperature
		// Byte #15 - Unknown
		// Byte #16 - Unknown
		// Byte #17 - Unknown 
		_inputVoltage = ((float) (((unsigned short) inputData[3] << 8) |
							((unsigned short) inputData[4])))/10.0f;
							
		_outputVoltage = ((float) (((unsigned short) inputData[5] << 8) |
							((unsigned short) inputData[6])))/10.0f;
							
		_outputPowerLoadRate = ((float) (((unsigned short) inputData[7] << 8) |
									((unsigned short) inputData[8])))/10.0f;
									
		_inputFrequency = ((float) (((unsigned short) inputData[9] << 8) |
							((unsigned short) inputData[10])))/10.0f;
							
		_remainingBatteryLevel = ((float) (((unsigned short) inputData[11] << 8) |
								((unsigned short) inputData[4])))/10.0f;
								
		_temperature = ((float) (((unsigned short) inputData[13] << 8) |
						((unsigned short) inputData[14])))/10.0f;
		
		wellParsed = true;
	}
	return wellParsed;
}

///////////////////////
// Public functions //	
///////////////////////

bool SmsNobreak::StartMonitoring()
{
	if (SendNobreakInitCommands())
	{
		_monitoringActive = true;
	}
	sleep_ms(1000);
	StartPollingThread();
	return _monitoringActive;
}

bool SmsNobreak::StopMonitoring()
{
	bool wasWorking = _monitoringActive;
	 
	_monitoringActive = false;
	if (wasWorking)
	{
		_serial.Close();
	}
	return wasWorking;
}

bool SmsNobreak::IsMonitoring()
{
	return _monitoringActive;
}

bool SmsNobreak::UsingAcPower()
{
	// TODO: see best way to do this
	return _inputVoltage > 10.0f;
}
	
float SmsNobreak::GetInputVoltage()
{
	return _inputVoltage;
}
	
float SmsNobreak::GetOutputVoltage()
{
	return _outputVoltage;
}
	
float SmsNobreak::GetBatteryRemainingLevel()
{
	return _remainingBatteryLevel;
}
	
float SmsNobreak::GetInputFrequency()
{
	return _inputFrequency;
}
	
float SmsNobreak::GetOutputPowerLoad()
{
	return _outputPowerLoadRate;
}

float SmsNobreak::GetTemperature()
{
	return _temperature;
}
