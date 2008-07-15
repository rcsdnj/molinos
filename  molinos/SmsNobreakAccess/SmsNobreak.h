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

#ifndef SMSNOBREAK_H_
#define SMSNOBREAK_H_

class SmsNobreak
{
	
public:

	SmsNobreak(std::string serialPort);

	bool StartMonitoring();

	bool StopMonitoring();
	
	bool UsingAcPower();
	
	float GetInputVoltage();
	
	float GetOutputVoltage();
	
	float GetBatteryRemainingLevel();
	
	float GetInputFrequency();
	
	float GetOutputPowerLoad();
	
	float GetTemperature();

private:
	bool SendNobreakInitCommands();
	bool InitializeNobreakPolling();
	bool ParseAndStoreData(const ByteBuffer& inputData);
	bool QueryNobreakAndStoreData();

	bool StartPollingThread();
	static void* PollingThreadEntryPoint(void* smsNobreak);
	
	void Polling();
	
	bool _monitoringActive;
	float _inputVoltage;
	float _outputVoltage;
	float _outputPowerLoadRate;
	float _inputFrequency;
	float _remainingBatteryLevel;
	float _temperature;
	SerialAccesser _serial;
	
	
};

#endif /*SMSNOBREAK_H_*/
