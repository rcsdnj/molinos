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
#include "StdIncludes.h"
#include "SerialAccesser.h"

SerialAccesser::SerialAccesser()
{	
	_serialPortName = "";
	_port = NULL;
}


bool SerialAccesser::Open()
{
	_port = new SerialPort(_serialPortName);
	_port->Open(SerialPort::BAUD_2400, SerialPort::CHAR_SIZE_8, 
		SerialPort::PARITY_NONE, SerialPort::STOP_BITS_1,
		SerialPort::FLOW_CONTROL_DEFAULT); 
	return _port->IsOpen();	
}

bool SerialAccesser::IsOpen()
{
	return _port->IsOpen();
}

void SerialAccesser::SetPort(std::string port)
{
	_serialPortName = port;
}

bool SerialAccesser::SendData(ByteBuffer buffer)
{
	bool writeOk = false;
	if (_port->IsOpen())
	{
		try
		{	
			_port->Write(buffer);
			writeOk = true;
		}
		catch(...)
		{
			
		}
	}
	else
	{
		
	}
	return writeOk;
}

bool SerialAccesser::ReadData(ByteBuffer& buffer, unsigned int msWaitTime)
{
	bool readOk = false;
	if (_port->IsOpen())
	{
		try
		{
			_port->Read(buffer, 0, msWaitTime);
			readOk = true;
		}
		catch(...)
		{
			
		}
	}
	else
	{
		
	}
	return readOk;
}

bool SerialAccesser::Close()
{
	bool closed = false;
	if (_port && _port->IsOpen())
	{
		_port->Close();
		closed = true;
	}
	return closed;
	
}
