//14. В некоторых строках текстового файла имеются выражения,
//состоящие   из   двух   целых   чисел, разделенных    знаком
//арифметической   операции('+', '-', '*', '/').Первое  из  чисел
//может быть отрицательным.В строке может содержаться несколько
//выражений.Перед  выражением  и  после него  могут  находиться
//произвольные символы.Требуется  выделить  строку, в  которой
//значение выражения максимально.Вывести найденное максимальное
//значение(7).

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>


#define operation(c)  ((c) == '+' || (c) == '-'  || (c) == '*' || (c) == '/')
#define space(c)      ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define digit(c)	  ((c) > '0' && (c) <= '9')

using namespace std;


int main()
{
	fstream fileInput;
	fileInput.open("input.txt");// открываем файл
	setlocale(LC_ALL, "Russian");

	char currCh;
	char prevCh;
	int convert;
	int Num1;
	int Num2;
	int Num1Max;
	int Num2Max;
	int maxInt;
	char sign;
	char signMax;
	string firstNum;
	string secondNum;
	int totalNum;
	bool negative;
	bool next;
	string tempNum;
	string line;

	tempNum = "";
	Num1 = 0;
	Num2 = 0;
	maxInt = INT_MIN;
	prevCh = ' ';
	currCh = ' ';
	firstNum = "";
	secondNum = "";
	totalNum = 0;
	negative = false;

	while (!fileInput.eof())
	{
		currCh = fileInput.get();
		negative = false;
		next = false;
		if (fileInput.eof()) // Удаление последнего символа
		{
			break;
		}

		if (currCh == '-') // Определяем, отрицательное ли число
		{
			if (!digit(prevCh))
			{
				negative = true;
				firstNum += currCh;
			}
		}
		if (digit(currCh)) // Читаем первое число
		{
			firstNum += currCh;
			Num1 = stoi(firstNum);
		}
		else // Читаем второе число
		{
			if (operation(currCh) && (negative == false))
			{
				sign = currCh;
				currCh = fileInput.get();

				while (digit(currCh) || (next == true))
				{

					if (next == true)
					{
						currCh = fileInput.get();
						next = false;
					}
					else
					{
						secondNum += currCh;
						tempNum = secondNum;
						Num2 = stoi(secondNum);
						currCh = fileInput.get();
					}


					if ((!digit(currCh)) || (space(currCh))) // Складываем числа и находим максимальное
					{
						switch (sign)
						{
						case '+':
							totalNum = Num1 + Num2;
							if (totalNum > maxInt)
							{
								maxInt = totalNum;
								Num1Max = Num1;
								Num2Max = Num2;
								signMax = sign;
							}
							firstNum = "";
							tempNum = secondNum;
							cout << Num1 << "+" << Num2 << " Сумма двух чисел: " << totalNum << endl;
							cout << endl;
							break;

						case '-':
							totalNum = Num1 - Num2;
							if (totalNum > maxInt)
							{
								maxInt = totalNum;
								Num1Max = Num1;
								Num2Max = Num2;
								signMax = sign;
							}
							firstNum = "";
							tempNum = secondNum;
							cout << Num1 << "-" << Num2 << " Разница двух чисел: " << totalNum << endl;
							cout << endl;
							break;

						case '*':
							totalNum = Num1 * Num2;
							if (totalNum > maxInt)
							{
								maxInt = totalNum;
								Num1Max = Num1;
								Num2Max = Num2;
								signMax = sign;
							}
							firstNum = "";
							tempNum = secondNum;
							cout << Num1 << "*" << Num2 << " Произведение двух чисел: " << totalNum << endl;
							cout << endl;
							break;

						case '/':
							totalNum = Num1 / Num2;
							if (totalNum > maxInt)
							{
								maxInt = totalNum;
								Num1Max = Num1;
								Num2Max = Num2;
								signMax = sign;
							}
							firstNum = "";
							tempNum = secondNum;
							cout << Num1 << "/" << Num2 << " Частное двух чисел: " << totalNum << endl;
							cout << endl;
							break;
						}
					}
					if (operation(currCh) || space(currCh))
					{
						sign = currCh;
						firstNum = secondNum;
						Num1 = stoi(firstNum);
						secondNum = ' ';
						next = true;
					}
				}
			}
		}
		prevCh = currCh;
		firstNum = ' ';
		secondNum = ' ';
	}
	fileInput.close();

	cout << "Наибольшее число: " << maxInt << endl;
	cout << "Строка: " << Num1Max << ' ' << signMax << ' ' << Num2Max << endl;

	return 0;
}
