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

#ifndef SERIALACCESSER_H_
#define SERIALACCESSER_H_

typedef std::vector<unsigned char> ByteBuffer;

class SerialAccesser
{
private:
	std::string _serialPortName;
	SerialPort* _port;
	
public:
	SerialAccesser();
	
	bool Open();
	
	bool Close();
	
	bool IsOpen();
	
	void SetPort(std::string port);
	
	bool SendData(ByteBuffer buffer);
	
	bool ReadData(ByteBuffer& buffer, unsigned int msWaitTime);
	
};

#endif /*SERIALACCESSER_H_*/
