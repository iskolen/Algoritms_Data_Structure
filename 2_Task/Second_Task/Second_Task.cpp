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

struct delitePersons
{
	int firstId;
	int secondId;
};


const int maxElements = 100;
const string separation = "     ";
const string absent = "              ";
personsFirstQueue firstQueue[maxElements];
personsSecondQueue secondQueue[maxElements];
delitePersons delitePerson[maxElements];

int timeCountFirst(int &i, int &timeFirstEnd, int &timeFirstStart, int &timeFirstSum)
{
	timeFirstStart = timeFirstEnd;
	timeFirstEnd = firstQueue[i].time + timeFirstStart;
	if (timeFirstEnd != 0)
	{
		timeFirstSum = timeFirstEnd;
	}
	return (timeFirstEnd, timeFirstStart, timeFirstSum);
}

int timeCountSecond(int &i, int &timeSecondEnd, int &timeSecondStart, int &timeSecondSum)
{
	timeSecondStart = timeSecondEnd;
	timeSecondEnd = secondQueue[i].time + timeSecondStart;
	if (timeSecondEnd != 0)
	{
		timeSecondSum = timeSecondEnd;
	}
	return (timeSecondEnd, timeSecondStart, timeSecondSum);
}

int deleteFromBoth(int &i, int &personNum1, int &personNum2)
{
	string currNameFirst = firstQueue[i].name;
	string currNameSecond = secondQueue[i].name;
	if (currNameFirst == currNameSecond)
	{
		secondQueue[i].name = "";
		secondQueue[i].time = 0;

		return(personNum1, personNum2);
	}

}

int deleteFromFirst(int i, int personNum1)
{
	string currName = secondQueue[i].name;
	for (int j = i; j < personNum1; j++)
	{
		if (currName == firstQueue[j].name)
		{
			for (int k = j; k < personNum1; k++)
			{
				firstQueue[k].name = firstQueue[k + 1].name;
				firstQueue[k].time = firstQueue[k + 1].time;
			}
			personNum1--;

			return personNum1;
		}
	}
	return personNum1;
}

int deleteFromSecond(int &i, int &personNum2)
{
	string currName = firstQueue[i].name;
	for (int j = i; j < personNum2; j++)
	{
		if (currName == secondQueue[j].name)
		{
			for (int k = j; k < personNum2; k++)
			{
				secondQueue[k].name = secondQueue[k + 1].name;
				secondQueue[k].time = secondQueue[k + 1].time;
			}
			personNum2--;

			return personNum2;
		}
	}
	return personNum2;
}

int deleteCurrFromFirst(int &i, int &personNum1)
{
	for (int j = i; j < personNum1; j++)
	{
		firstQueue[j].name = firstQueue[j + 1].name;
		firstQueue[j].time = firstQueue[j + 1].time;
	}
	personNum1--;

	return personNum1;
}

int deleteCurrFromSecond(int &i, int &personNum2)
{
	for (int j = i; j < personNum2; j++)
	{
		secondQueue[j].name = secondQueue[j + 1].name;
		secondQueue[j].time = secondQueue[j + 1].time;
	}
	personNum2--;

	return personNum2;
}


void printCurrFirst(int i, int timeFirstEnd, int timeFirstStart)
{
	cout << firstQueue[i].name << "(" << timeFirstStart << ", " << timeFirstEnd << ") [1] " << endl;
}

void printCurrSecond(int i, int timeSecondEnd, int timeSecondStart)
{
	cout << secondQueue[i].name << "(" << timeSecondStart << ", " << timeSecondEnd << ") [2] " << endl;
}

int transitionToSecond(int &i, int &personNum1, int &personNum2)
{
	for (int m = personNum2; m > i; m--)
	{
		secondQueue[m].name = secondQueue[m - 1].name;
		secondQueue[m].time = secondQueue[m - 1].time;
	}
	personNum2++;
	secondQueue[i].name = firstQueue[i].name;
	secondQueue[i].time = firstQueue[i].time;
	personNum1 = deleteCurrFromFirst(i, personNum1);

	return(personNum1, personNum2);
}


int main()
{
	string line, name, temp, fileName;
	int lineNum, time, personNum1, personNum2;
	char currCh;

	personNum1 = 0, personNum2 = 0, time = 0, lineNum = 0;
	name, temp = "";
	currCh = ' ';


	setlocale(LC_ALL, "RUS");
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
		if (len == 3)
		{
			system("cls");
			cout << "Ошибка: Очередь пуста";
			cout << endl;
			return 0;
		}
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
					if (currCh == '\0')// Если время отсутсвтует
					{
						system("cls");
						cout << "Ошибка: Время задано неправильно (отсутсвует)";
						cout << endl;
						return 0;
					}
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
					if (!isdigit(currCh))// Если время не число
					{
						system("cls");
						cout << "Ошибка: Время задано неправильно (не число)";
						cout << endl;
						return 0;
					}
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

				cout << "  Время в очереди: " << time << endl;
				temp = "";
				name = "";
				time = 0;
			}
		}
	}
	if (line == "" && lineNum == 0)
	{
		system("cls");
		cout << "Ошибка: Файл пустой";
		cout << endl;
		return 0;
	}
	if (line == "" && lineNum == 1)
	{
		system("cls");
		cout << "Ошибка: Вторая очередь отсутствует";
		cout << endl;
		return 0;
	}

	cout << endl;

	int timeFirstSum, timeSecondSum, timeFirstStart, timeFirstEnd, timeSecondStart, timeSecondEnd;
	int largQueue;
	bool firstElement = true;
	bool firstBusy, secondBusy;
	int i = 0;
	firstBusy = false; secondBusy = false;
	timeFirstEnd = 0; timeFirstStart = 0; timeSecondEnd = 0; timeSecondStart = 0; timeFirstSum = 0; timeSecondSum = 0;

	if (personNum1 > personNum2)
	{
		largQueue = personNum1;
	}
	else
	{
		largQueue = personNum2;
	}

	while (i < largQueue)
	{
		if (firstElement)
		{
			if (firstQueue[i].name == secondQueue[i].name)
			{
				(personNum1, personNum2) = deleteFromBoth(i, personNum1, personNum2);
			}
			else
			{
				personNum2 = deleteFromSecond(i, personNum2);
				(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(i, timeFirstEnd, timeFirstStart, timeFirstSum);

				personNum1 = deleteFromFirst(i, personNum1);
				(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(i, timeSecondEnd, timeSecondStart, timeSecondSum);
			}
			firstElement = false;
			i++;
		}

		if (i < personNum1)
		{
			timeSecondSum += secondQueue[i].time;
			if (timeFirstSum > timeSecondSum)
			{
				firstBusy = true;
			}

			if (firstQueue[i].name == secondQueue[i].name)
			{
				(personNum1, personNum2) = deleteFromBoth(i, personNum1, personNum2);
			}
			else
			{
				if (firstBusy)
				{
					(personNum1, personNum2) = transitionToSecond(i, personNum1, personNum2);
					(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(i, timeSecondEnd, timeSecondStart, timeSecondSum);
					firstBusy = false;
				}
				else
				{
					personNum2 = deleteFromSecond(i, personNum2);
					(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(i, timeFirstEnd, timeFirstStart, timeFirstSum);
				}
			}
		}

		if (i < personNum2)
		{
			if (timeSecondSum > timeFirstSum)
			{
				secondBusy = true;
			}

			if (firstQueue[i].name == secondQueue[i].name)
			{
				(personNum1, personNum2) = deleteFromBoth(i, personNum1, personNum2);
			}
			else
			{
				personNum1 = deleteFromFirst(i, personNum1);
				(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(i, timeSecondEnd, timeSecondStart, timeSecondSum);
			}
			
			i++;
		}
		else
		{
			i++;
		}
	}


	timeFirstStart = 0; timeFirstEnd = 0; timeSecondStart = 0; timeSecondEnd = 0;
	cout << endl;
	cout << "1: ";
	for (int i = 0; i < personNum1; i++)
	{
		timeFirstStart = timeFirstEnd;
		timeFirstEnd = firstQueue[i].time + timeFirstStart;

		cout << firstQueue[i].name << "[" << timeFirstStart << ", " << timeFirstEnd << "]" ;
		if (i == personNum1 - 1)
		{
			break;
		}
		cout << ", ";
	}
	cout << endl;
	cout << "2: ";
	for (int i = 0; i < personNum2; i++)
	{
		timeSecondStart = timeSecondEnd;
		timeSecondEnd = secondQueue[i].time + timeSecondStart;
		if (secondQueue[i].name == "")
		{
			continue;
		}
		cout << secondQueue[i].name << "[" << timeSecondStart << ", " << timeSecondEnd << "]";
		if (i == personNum2 - 1)
		{
			break;
		}
		cout << ", ";
	}

}