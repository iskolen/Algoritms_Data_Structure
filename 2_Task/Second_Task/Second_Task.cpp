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
	string line, name;
	int lineNum, time;
	char currCh;

	time = 0;
	name = "";
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


	struct person
	{
		string name;
		int time;
	};


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
				lineNum = 0;
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
				name = "";
				currCh = line[i], i++;

				while (currCh != ')')
				{
					time += currCh - '0';
					currCh = line[i], i++;
				}
				cout << "  Время в очереди: "<< time << endl;
				time = 0;
			}


		}
	}
}

