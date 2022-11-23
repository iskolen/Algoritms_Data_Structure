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
			if (lineNum == 2)
			{
				cout << endl;
				lineNum = 0;
			}

			if (i == 0)
			{
				i = 3;
			}

			currCh = line[i], i++;
			while (currCh == '(')
			{
				name = line[i], i++;
			}

			cout << currCh;
		}
	}
}

