/*
	Петров Вадим ПС-22
	Вариант 7
	Задача:
		Перед открытием двух железнодорожных касс сформировались
		2 очереди пассажиров,  причем некоторые из них находятся сразу
		в  обеих очередях.  Для каждого пассажира известны его места в
		очередях и необходимое время обслуживания.  Если у какого-либо
		пассажира очереди подходят одновременно, то он обслуживается в
		первой   кассе.   Промоделировать   работу    касс,    выдавая
		последовательно информацию об обслуживании пассажиров (7).
	Среда разработки: Microsoft Visual Studio 2017
*/

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <cstring>



using namespace std;

int main()
{
	struct personsFirstQueue
	{
		string name;
		int time;
	};

	struct personsSecondQueue
	{
		string name;
		int time;
	};

	const int maxElements = 100;
	personsFirstQueue firstQueue[maxElements];
	personsSecondQueue secondQueue[maxElements];
	
	string line, name, temp;
	int lineNum, time, personNum1, personNum2;
	char currCh;

	personNum1 = 0;
	personNum2 = 0;
	time = 0;
	name = "";
	temp = "";
	currCh = ' ';
	lineNum = 0;


	setlocale(LC_ALL, "RUS");
	string fileName;
	cout << "Введите имя входного файла: ";
	cin >> fileName;
	ifstream fileInput(fileName);// Открываем файл
	if (!fileInput)
	{
		cout << "Файл не найден!" << endl;
		return 0;
	}
	cout << endl;


	while (getline(fileInput, line))// Построчное чтение файла
	{
		int i = 0;
		lineNum++;
		int len = line.length();
		while ((i != len) && (i < len))// Обработка каждой строки
		{
			if (lineNum == 2)// Переход на новую строку
			{
				cout << endl;
				lineNum = 10;
			}

			if (i == 0)// Пропуск обозначение номера очереди 
			{
				i = 3;
			}

			currCh = line[i], i++;
			if (currCh != '(')// Считывание имён и времени
			{
				while (currCh != '(')
				{
					if (currCh == ' ')
					{
						currCh = line[i], i++;
					}
					name += currCh;
					currCh = line[i], i++;
				}


				cout << "Имя: " << name;
				currCh = line[i], i++;

				while (currCh != ')')
				{
					temp += currCh;
					currCh = line[i], i++;
				}
				time = stoi(temp);
				


				if (lineNum == 1)
				{
					firstQueue[personNum1].name = name;
					firstQueue[personNum1].time = time;
					personNum1++;
				}
				if (lineNum == 10)
				{
					secondQueue[personNum2].name = name;
					secondQueue[personNum2].time = time;
					personNum2++;
				}

				cout << "  Время в очереди: "<< time << endl;
				temp = "";
				name = "";
				time = 0;
			}
		}
	}
	cout << endl;


	struct delitePersons
	{
		int firstId;
		int secondId;
	};

	delitePersons delitePerson[maxElements];
	string namePerson1, namePerson2;
	int personNum;
	personNum = 0;

	for (int i = 0; i < personNum1; i++)// Проверка на наличие человка в 2-ух очередях одновременно, и получение id в каждой из очереди
	{
		int a = 0;
		namePerson1 = firstQueue[i].name;
		namePerson2 = secondQueue[a].name;
		if (namePerson1 != namePerson2)
		{
			while (namePerson1 != namePerson2)
			{
				namePerson2 = secondQueue[a].name;
				if (namePerson1 == namePerson2)
				{
					delitePerson[personNum].firstId = i;
					delitePerson[personNum].secondId = a;
					personNum++;
					break;
				}
				a++;
				if (a == personNum2)
				{
					break;
				}
			}
		}
		else
		{
			delitePerson[personNum].firstId = i;
			delitePerson[personNum].secondId = a;
			personNum++;
		}
	}

	for (int i = 0; i < personNum; i++)// Вывод id человека в обоих очередях, если он находится в двух очередях одновременно 
	{
		int id1 = delitePerson[i].firstId;
		int id2 = delitePerson[i].secondId;
		cout << "ID " << i << "-го элемента ";
		cout << "[" <<  id1 << "]" << " - " << "[" << id2 << "]" << endl;
	}

	cout << endl;


	int timeFirstStart, timeFirstEnd;
	int timeSecondStart, timeSecondEnd;
	bool firstElement = true;
	timeFirstStart = 0;
	cout << "1: ";
	int i = 0;
	while (i < personNum1)// Вывод первой очереди
	{
		cout << firstQueue[i].name << "[";

		if (firstElement)
		{
			timeFirstEnd = firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			i++;
			timeFirstStart = timeFirstEnd;
			firstElement = false;
		}
		else
		{
			timeFirstEnd = timeFirstStart + firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			i++;
			timeFirstStart = timeFirstEnd;
		}
	}

	firstElement = true;
	timeSecondStart = 0;
	cout << endl << "2: ";
	i = 0;
	while (i < personNum2)// Вывод второй очереди
	{
		cout << secondQueue[i].name << "[";

		if (firstElement)
		{
			timeSecondEnd = secondQueue[i].time;
			cout << timeSecondStart << ", " << timeSecondEnd << "] ";
			i++;
			timeSecondStart = timeSecondEnd;
			firstElement = false;
		}
		else
		{
			timeSecondEnd = timeSecondStart + secondQueue[i].time;
			cout << timeSecondStart << ", " << timeSecondEnd << "] ";
			i++;
			timeSecondStart = timeSecondEnd;
		}
	}
}

