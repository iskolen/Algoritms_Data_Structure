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

const int maxElements = 100;
personsFirstQueue firstQueue[maxElements];
personsSecondQueue secondQueue[maxElements];

void inputFormat()
{
	cout << endl << endl << "Формат входного файла:" << endl << endl;
	cout << "1: NAME(TIME) NAME(TIME) NAME(TIME)" << endl;
	cout << "2: NAME(TIME) NAME(TIME)" << endl << endl;

	cout << "Правила ввода:" << endl << endl;
	cout << "1) В одной очереди не может быть двух одинаковых человек" << endl;
	cout << "2) В конце строки не должно присутствовать пробелов" << endl;
	cout << "3) Время не может быть меньше 0";
}

bool dataValidation(int personNum1, int personNum2)
{
	bool error = false;
	for (int s = 0; s < personNum1; s++)// Проверка, на наличие в первой очереди одного и того же человека
	{
		string currFirstName = firstQueue[s].name;
		for (int i = s + 1; i < personNum1; i++)
		{
			string verifiableFirstName = firstQueue[i].name;
			if (currFirstName == verifiableFirstName)
			{
				system("cls");
				cout << "Ошибка: В первой очереди два одинаковых человека";
				inputFormat();
				cout << endl;

				error = true;
				return error;
			}
		}
	}

	for (int s = 0; s < personNum2; s++)// Проверка, на наличие во второй очереди одного и того же человека
	{
		string currSecondName = secondQueue[s].name;
		for (int i = s + 1; i < personNum2; i++)
		{
			string verifiableSecondName = secondQueue[i].name;
			if (currSecondName == verifiableSecondName)
			{
				system("cls");
				cout << "Ошибка: Во второй очереди два одинаковых человека";
				inputFormat();
				cout << endl;

				error = true;
				return error;
			}
		}
	}

	for (int s = 0; s < personNum1; s++)
	{
		if (firstQueue[s].time <= 0)
		{
			system("cls");
			cout << "Ошибка: У человека в первой очереди время меньше 0!";
			inputFormat();
			cout << endl;

			error = true;
			return error;
		}
		
	}

	for (int s = 0; s < personNum2; s++)
	{
		if (secondQueue[s].time <= 0)
		{
			system("cls");
			cout << "Ошибка: У человека в первой очереди время меньше 0!";
			inputFormat();
			cout << endl;

			error = true;
			return error;
		}

	}

	return error;
}

int timeCountFirst(int &iFirst, int &timeFirstEnd, int &timeFirstStart, int &timeFirstSum)
{
	timeFirstStart = timeFirstEnd;
	timeFirstEnd = firstQueue[iFirst].time + timeFirstStart;
	if (timeFirstEnd != 0)
	{
		timeFirstSum = timeFirstEnd;
	}
	return (timeFirstEnd, timeFirstStart, timeFirstSum);
}

int timeCountSecond(int &iSecond, int &timeSecondEnd, int &timeSecondStart, int &timeSecondSum)
{
	timeSecondStart = timeSecondEnd;
	timeSecondEnd = secondQueue[iSecond].time + timeSecondStart;
	if (timeSecondEnd != 0)
	{
		timeSecondSum = timeSecondEnd;
	}
	return (timeSecondEnd, timeSecondStart, timeSecondSum);
}

int deleteFromBoth(int &iFirst, int &iSecond, int &personNum1, int &personNum2)
{
	string currNameFirst = firstQueue[iFirst].name;
	string currNameSecond = secondQueue[iSecond].name;
	if (currNameFirst == currNameSecond)
	{
		for (int j = iSecond; j < personNum2; j++)
		{
			secondQueue[j].name = secondQueue[j + 1].name;
			secondQueue[j].time = secondQueue[j + 1].time;
		}
		personNum2--;

		return(personNum1, personNum2);
	}

}

int deleteFromFirst(int &iFirst, int &iSecond, int personNum1)
{
	string currName = secondQueue[iSecond].name;
	for (int j = iFirst; j < personNum1; j++)
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

int deleteFromSecond(int &iFirst, int &iSecond, int &personNum2)
{
	string currName = firstQueue[iFirst].name;
	for (int j = iSecond; j < personNum2; j++)
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

int deleteCurrFromFirst(int &iFirst, int &personNum1)
{
	for (int j = iFirst; j < personNum1; j++)
	{
		firstQueue[j].name = firstQueue[j + 1].name;
		firstQueue[j].time = firstQueue[j + 1].time;
	}
	personNum1--;

	return personNum1;
}

int deleteCurrFromSecond(int &iSecond, int &personNum2)
{
	for (int j = iSecond; j < personNum2; j++)
	{
		secondQueue[j].name = secondQueue[j + 1].name;
		secondQueue[j].time = secondQueue[j + 1].time;
	}
	personNum2--;

	return personNum2;
}

void printCurrFirst(int iFirst, int timeFirstEnd, int timeFirstStart)
{
	cout << firstQueue[iFirst].name << "(" << timeFirstStart << ", " << timeFirstEnd << ") [1] " << endl;
}

void printCurrSecond(int iSecond, int timeSecondEnd, int timeSecondStart)
{
	cout << secondQueue[iSecond].name << "(" << timeSecondStart << ", " << timeSecondEnd << ") [2] " << endl;
}

int transitionToSecond(int &iFirst, int &iSecond, int &personNum1, int &personNum2)
{
	for (int m = personNum2; m > iSecond; m--)
	{
		secondQueue[m].name = secondQueue[m - 1].name;
		secondQueue[m].time = secondQueue[m - 1].time;
	}
	personNum2++;
	secondQueue[iSecond].name = firstQueue[iFirst].name;
	secondQueue[iSecond].time = firstQueue[iFirst].time;
	personNum1 = deleteCurrFromFirst(iFirst, personNum1);

	return(personNum1, personNum2);
}

int transitionToFirst(int &iFirst, int &iSecond, int &personNum1, int &personNum2)
{
	for (int m = personNum1; m > iFirst; m--)
	{
		firstQueue[m].name = firstQueue[m - 1].name;
		firstQueue[m].time = firstQueue[m - 1].time;
	}
	personNum1++;
	firstQueue[iFirst].name = secondQueue[iSecond].name;
	firstQueue[iFirst].time = secondQueue[iSecond].time;
	personNum2 = deleteCurrFromSecond(iSecond, personNum2);

	return(personNum1, personNum2);
}

string getUserAnswer()
{
	string fileName;
	cout << "Введите имя входного файла('0', если хотите выйти): ";
	cin >> fileName;
	return fileName;
}

int main()
{
	string line, name, temp, fileName;
	int lineNum, time, personNum1, personNum2;
	char currCh;
	setlocale(LC_ALL, "RUS");

	fileName = getUserAnswer();
	while (fileName != "0")
	{
		fstream fileInput(fileName);
		if (fileInput.good())
		{
			personNum1 = 0, personNum2 = 0, time = 0, lineNum = 0;
			name, temp = "";
			currCh = ' ';
			while (getline(fileInput, line))// Построчное чтение файла
			{
				int i = 0;
				lineNum++;
				int len = line.length();
				if (len == 3)
				{
					system("cls");
					cout << "Ошибка: Очередь пуста!";
					inputFormat();
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
								inputFormat();
								cout << endl;
								return 0;
							}
							if (currCh == ' ')
							{
								currCh = line[i], i++;
								if (currCh == '\0')
								{
									system("cls");
									cout << "Ошибка: В конце строки лишний символ!";
									inputFormat();
									cout << endl;
									return 0;
								}
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
								inputFormat();
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
			if (line == "" && lineNum == 0) // Если файл пустой
			{
				system("cls");
				cout << "Ошибка: Файл пустой";
				inputFormat();
				cout << endl;
				return 0;
			}
			if (line == "" && lineNum == 1) // Если вторая очередь отсутствует
			{
				system("cls");
				cout << "Ошибка: Вторая очередь отсутствует";
				inputFormat();
				cout << endl;
				return 0;
			}


			bool error = dataValidation(personNum1, personNum2); // Валидация полученных очередей
			if (error)
			{
				return 0;
			}
			cout << endl;


			int timeFirstSum = 0, timeSecondSum = 0, timeFirstStart = 0, timeFirstEnd = 0, timeSecondStart = 0, timeSecondEnd = 0, difference = 0;
			int largQueue;
			bool firstElement = true;
			bool firstBusy, secondBusy;
			int iFirst = 0;
			int iSecond = 0;
			firstBusy = false; secondBusy = false;

			if (personNum1 > personNum2)
			{
				largQueue = personNum1;
			}
			else
			{
				largQueue = personNum2;
			}

			while (firstQueue[iFirst].name != "" || secondQueue[iSecond].name != "")
			{
				if (firstElement)
				{
					if (firstQueue[iFirst].name == secondQueue[iSecond].name)
					{
						(personNum1, personNum2) = deleteFromBoth(iFirst, iSecond, personNum1, personNum2);
						(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);
						iFirst++;
					}
					else
					{
						personNum2 = deleteFromSecond(iFirst, iSecond, personNum2);
						(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);

						personNum1 = deleteFromFirst(iFirst, iSecond, personNum1);
						(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(iSecond, timeSecondEnd, timeSecondStart, timeSecondSum);
						iFirst++;
						iSecond++;
					}
					firstElement = false;
				}

				if (iFirst < personNum1) // Первая очередь
				{

					if (firstQueue[iFirst].name == secondQueue[iSecond].name && firstQueue[iFirst].name != "")
					{
						(personNum1, personNum2) = deleteFromBoth(iFirst, iSecond, personNum1, personNum2);
						(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);
						iFirst++;
					}
					else
					{
						/*if (timeFirstSum > timeSecondSum)
						{
							while (timeFirstSum > timeSecondSum && firstQueue[iFirst].time != 0)
							{
								(personNum1, personNum2) = transitionToSecond(iFirst, iSecond, personNum1, personNum2);
								(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(iSecond, timeSecondEnd, timeSecondStart, timeSecondSum);
								iSecond++;
							}
							iFirst++;
						}
						else*/
						{
							personNum2 = deleteFromSecond(iFirst, iSecond, personNum2);
							(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);
							iFirst++;
						}

					}
				}
				if (iSecond <= personNum2) // Вторая очередь
				{

					if (firstQueue[iFirst].name == secondQueue[iSecond].name && firstQueue[iFirst].name != "")
					{
						(personNum1, personNum2) = deleteFromBoth(iFirst, iSecond, personNum1, personNum2);
						(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);
						iFirst++;
					}
					else
					{
						/*if (timeSecondSum > timeFirstSum)
						{
							while (timeSecondSum > timeFirstSum && secondQueue[iSecond].time != 0)
							{
								(personNum1, personNum2) = transitionToFirst(iFirst, iSecond, personNum1, personNum2);
								(timeFirstEnd, timeFirstStart, timeFirstSum) = timeCountFirst(iFirst, timeFirstEnd, timeFirstStart, timeFirstSum);
								iFirst++;
							}
						}
						else*/
						{
							personNum1 = deleteFromFirst(iFirst, iSecond, personNum1);
							(timeSecondEnd, timeSecondStart, timeSecondSum) = timeCountSecond(iSecond, timeSecondEnd, timeSecondStart, timeSecondSum);
							iSecond++;
						}
					}
				}
			}


			timeFirstStart = 0; timeFirstEnd = 0; timeSecondStart = 0; timeSecondEnd = 0;
			cout << endl;
			cout << "1: ";
			for (int i = 0; i < personNum1; i++)
			{
				timeFirstStart = timeFirstEnd;
				timeFirstEnd = firstQueue[i].time + timeFirstStart;
				if (firstQueue[i].name == "")
				{
					continue;
				}
				cout << firstQueue[i].name << "[" << timeFirstStart << ", " << timeFirstEnd << "]";
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
			cout << endl << endl;
			fileName = getUserAnswer();
		}
		else
		{
			cout << endl;
			cout << "Файл не существует!" << endl;
			cout << endl;
			fileName = getUserAnswer();
		}
	
	}
}