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

#include "StdIncludes.h"
#include "SerialAccesser.h"
#include "SmsNobreak.h"
#include <iostream>
#include <pthread.h>

void* nobreak_run(void* nobreak);

int main(void)
{
	SmsNobreak* noBreak = new SmsNobreak("/dev/ttyUSB0");
	noBreak->StartMonitoring();
	while (true)
	{
		std::cout << "----" << std::endl;
		std::cout << "Carga da bateria:      "
			<< noBreak->GetBatteryRemainingLevel();
		std::cout << std::endl;
		std::cout << "Tensão de entrada:     " << noBreak->GetInputVoltage();
		std::cout << std::endl;
		std::cout << "Tensão de saída:       " << noBreak->GetOutputVoltage();
		std::cout << std::endl;
		std::cout << "Temperatura:           " << noBreak->GetTemperature();
		std::cout << std::endl;
		std::cout << "Freqüência de entrada: " << noBreak->GetInputFrequency();
		std::cout << std::endl;
		std::cout << "Carga utilizada:       " << noBreak->GetOutputPowerLoad();
		std::cout << std::endl;
		sleep(1);
	}
}
