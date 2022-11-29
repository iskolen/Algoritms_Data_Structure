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
					if (currCh == '\0')
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
					if (!isdigit(currCh))
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

				cout << "  Время в очереди: "<< time << endl;
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

	const string separation = "     ";
	const string absent = "              ";

	int timeFirstSum, timeSecondSum;
	int timeFirstStart, timeFirstEnd;
	int timeSecondStart, timeSecondEnd;
	int largQueue;
	bool firstElement = true;
	timeFirstStart = 0;
	int i = 0;
	timeFirstSum = 0;
	timeSecondSum = 0;
	timeSecondStart = 0;
	if (personNum1 > personNum2)
	{
		largQueue = personNum1;
	}
	else
	{
		largQueue = personNum2;
	}

	cout << "1 очередь" << separation << "2 очередь" << endl;
	while (i < largQueue)
	{
		if (firstElement)
		{
			int deliteId1 = delitePerson[i].firstId;//Удаление элемента
			int deliteId2 = delitePerson[i].secondId;
			if (deliteId1 == i)
			{
				for (int j = deliteId2; j < personNum2; j++)
				{
					secondQueue[j].name = secondQueue[j + 1].name;
					secondQueue[j].time = secondQueue[j + 1].time;
				}
				personNum2--;
				for (int i = 0; i < personNum; i++)
				{
					delitePerson[i + 1].secondId--;
				}
			}


			cout << firstQueue[i].name << "[";
			timeFirstEnd = firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			timeFirstStart = timeFirstEnd;
			cout << separation;




			deliteId2 = delitePerson[i].secondId;//Удаление элемента
			deliteId1 = delitePerson[i].firstId;
			if (deliteId2 == i && deliteId1 != deliteId2)
			{
				for (int j = deliteId1; j < personNum1; j++)
				{
					firstQueue[j].name = firstQueue[j + 1].name;
					firstQueue[j].time = firstQueue[j + 1].time;
				}
				personNum1--;
				for (int i = 0; i < personNum; i++)
				{
					delitePerson[i + 1].firstId--;
				}
			}
			cout << secondQueue[i].name << "[";
			timeSecondEnd = secondQueue[i].time;
			cout << timeSecondStart << ", " << timeSecondEnd << "] ";
			timeSecondStart = timeSecondEnd;



			firstElement = false;
			i++;
			cout << endl;
		}

		if (i < personNum1)
		{
			int deliteId1 = delitePerson[i].firstId;//Удаление элемента
			int deliteId2 = delitePerson[i].secondId;
			if (deliteId1 == i)
			{
				for (int j = deliteId2; j < personNum2; j++)
				{
					secondQueue[j].name = secondQueue[j + 1].name;
					secondQueue[j].time = secondQueue[j + 1].time;
				}
				personNum2--;
				for (int i = 0; i < personNum; i++)
				{
					delitePerson[i + 1].secondId--;
				}
			}


			cout << firstQueue[i].name << "[";
			timeFirstEnd = timeFirstStart + firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			timeFirstStart = timeFirstEnd;
			cout << separation;
		}
		else
		{
			cout << absent;
		}

		if (i < personNum2)
		{
			int deliteId2 = delitePerson[i].secondId;//Удаление элемента
			int deliteId1 = delitePerson[i].firstId;
			if (deliteId2 == i && deliteId1 != deliteId2)
			{
				for (int j = deliteId1; j < personNum1; j++)
				{
					firstQueue[j].name = firstQueue[j + 1].name;
					firstQueue[j].time = firstQueue[j + 1].time;
				}
				personNum1--;
				for (int i = 0; i < personNum; i++)
				{
					delitePerson[i + 1].firstId--;
				}
			}

			cout << secondQueue[i].name << "[";
			timeSecondEnd = secondQueue[i].time;
			cout << timeSecondStart << ", " << timeSecondEnd << "] ";
			timeSecondStart = timeSecondEnd;

			i++;
			cout << endl;
		}
		else
		{
			i++;
			cout << endl;
		}
	}

	cout << endl;



	/*int deliteId1 = delitePerson[i].firstId;//Удаление элемента
	int deliteId2 = delitePerson[i].secondId;
	if (deliteId1 == i)
	{
		for (int j = deliteId2; j < personNum2; j++)
		{
			secondQueue[j].name = secondQueue[j + 1].name;
			secondQueue[j].time = secondQueue[j + 1].time;
		}
		personNum2--;
		for (int i = 0; i < personNum; i++)
		{
			delitePerson[i + 1].secondId--;
		}
	}*/



	/*int timeFirstSum, timeSecondSum;
	int timeFirstStart, timeFirstEnd;
	int timeSecondStart, timeSecondEnd;
	bool firstElement = true;
	timeFirstStart = 0;
	cout << "1: ";
	int i = 0;
	timeFirstSum = 0;
	timeSecondSum = 0;
	while (i < personNum1)// Вывод первой очереди
	{
		cout << firstQueue[i].name << "[";

		if (firstElement)
		{
			timeFirstEnd = firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			if (i < personNum1)
			{
				timeFirstSum += firstQueue[i].time;
			}
			if (i < personNum2)
			{
				timeSecondSum += secondQueue[i].time;
			}
			i++;
			timeFirstStart = timeFirstEnd;
			firstElement = false;
		}
		else
		{
			timeFirstEnd = timeFirstStart + firstQueue[i].time;
			cout << timeFirstStart << ", " << timeFirstEnd << "] ";
			if (i < personNum1)
			{
				timeFirstSum += firstQueue[i].time;
			}
			if (i < personNum2)
			{
				timeSecondSum += secondQueue[i].time;
			}
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

	cout << endl << endl;
	cout << "Сумма времени первой очереди: " << timeFirstSum << endl;
	cout << "Сумма времени второй очереди: " << timeSecondSum << endl;*/
}

/*int deliteId1 = delitePerson[i].firstId;
if (deliteId1 == i)
{
	int deliteId2 = delitePerson[i].secondId;
	for (int j = deliteId2; j < personNum2; j++)
	{
		secondQueue[j].name = secondQueue[j + 1].name;
		secondQueue[j].time = secondQueue[j + 1].time;
	}
	personNum2--;
}*/