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

#include "Util.h"
#include "SerialAccesser.h"
#include "SmsNobreak.h"
#include <iostream>
#include <pthread.h>
using namespace std;
void* nobreak_run(void* nobreak);

int main(void)
{
	SmsNobreak* noBreak = new SmsNobreak("/dev/ttyUSB0");


	while (true)
	{
		if (noBreak->StartMonitoring())
		{
			cout << "Monitoramento do no-break inicializado com sucesso." << endl;
		}
		else
		{
			cout << "Erro na inicialização do no-break!" << endl;
			break;
		}

		while (noBreak->IsMonitoring())
		{
			cout << "----" << endl;
			cout << "Carga da bateria:      "
				<< noBreak->GetBatteryRemainingLevel();
			cout << endl;
			cout << "Tensão de entrada:     " << noBreak->GetInputVoltage();
			cout << endl;
			cout << "Tensão de saída:       " << noBreak->GetOutputVoltage();
			cout << endl;
			cout << "Temperatura:           " << noBreak->GetTemperature();
			cout << endl;
			cout << "Freqüência de entrada: " << noBreak->GetInputFrequency();
			cout << endl;
			cout << "Carga utilizada:       " << noBreak->GetOutputPowerLoad();
			cout << endl;
			sleep(1);
		}
		char shouldRestart;
		cout << "----" << endl << "Monitoramento parou por algum problema inesperado. ";
		cout << "Reiniciar? (S/N)";
		cin >> shouldRestart;
		cout << endl;
		if (shouldRestart == 'S' || shouldRestart == 's')
		{
			continue;
		}
		else
		{
			break;
		}

	}
}
