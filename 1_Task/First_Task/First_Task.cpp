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
#include <cstring>


#define operation(c)  ((c) == '+' || (c) == '-'  || (c) == '*' || (c) == '/')
#define space(c)      ((c) == ' ' || (c) == '\t' || (c) == '\n')
#define digit(c)	  ((c) > '0' && (c) <= '9')

using namespace std;


int main()
{
	fstream fileInput;
	fileInput.open("input.txt");// открываем файл
	setlocale(LC_ALL, "Russian");

	char currCh, prevCh, sign, signMax;
	int convert, num1, num2, numMax1, numMax2, maxInt, i, len, totalNum;
	bool endFile, negative, nextNum;
	string firstNum, secondNum, line, lineMax;

	num1 = 0;
	num2 = 0;
	totalNum = 0;
	len = 0;
	maxInt = INT_MIN;
	currCh = ' ';
	prevCh = ' ';
	secondNum = "";
	firstNum = "";
	endFile = false;

	while (getline(fileInput, line))
	{
		i = 0;
		len = line.length();
		while ((i != len) && (i < len))
		{
			currCh = line[i], i++;
			negative = false;
			nextNum = false;

			if (digit(currCh)) // Читаем первое число
			{
				while (digit(currCh))
				{
					if (prevCh == '-')
					{
						negative = true;
					}
					firstNum += currCh;
					num1 = stoi(firstNum);
					currCh = line[i], i++;
					if ((i == len) || (i > len))
					{
						break;
					}
				}
				if (negative == true)
				{
					num1 = -num1;
					negative = false;
				}
				if (operation(currCh) && (negative == false))
				{
					sign = currCh;
					currCh = line[i], i++;
					while (digit(currCh) || (nextNum == true))
					{
						if (nextNum == true)
						{
							currCh = line[i], i++;
							nextNum = false;
						}
						else
						{
							secondNum += currCh;
							num2 = stoi(secondNum);
							currCh = line[i], i++;
						}
						if ((!digit(currCh)) || (space(currCh))) // Складываем числа и находим максимальное
						{
							switch (sign)
							{
							case '+':
								totalNum = num1 + num2;
								if (totalNum > maxInt)
								{
									maxInt = totalNum;
									numMax1 = num1;
									numMax2 = num2;
									signMax = sign;
									lineMax = line;
								}
								firstNum = "";
								cout << num1 << "+" << num2 << " Сумма двух чисел: " << totalNum << endl;
								cout << endl;
								break;

							case '-':
								totalNum = num1 - num2;
								if (totalNum > maxInt)
								{
									maxInt = totalNum;
									numMax1 = num1;
									numMax2 = num2;
									signMax = sign;
									lineMax = line;
								}
								firstNum = "";
								cout << num1 << "-" << num2 << " Разница двух чисел: " << totalNum << endl;
								cout << endl;
								break;

							case '*':
								totalNum = num1 * num2;
								if (totalNum > maxInt)
								{
									maxInt = totalNum;
									numMax1 = num1;
									numMax2 = num2;
									signMax = sign;
									lineMax = line;
								}
								firstNum = "";
								cout << num1 << "*" << num2 << " Произведение двух чисел: " << totalNum << endl;
								cout << endl;
								break;

							case '/':
								totalNum = num1 / num2;
								if (totalNum > maxInt)
								{
									maxInt = totalNum;
									numMax1 = num1;
									numMax2 = num2;
									signMax = sign;
									lineMax = line;
								}
								firstNum = "";
								cout << num1 << "/" << num2 << " Частное двух чисел: " << totalNum << endl;
								cout << endl;
								break;
							}
							if (operation(currCh))
							{
								if (sign == '-')
								{
									firstNum = secondNum;
									num1 = stoi(firstNum);
									num1 = -num1;
									secondNum = "";
									nextNum = true;
									sign = currCh;
								}
								else
								{	
									firstNum = secondNum;
									num1 = stoi(firstNum);
									secondNum = "";
									nextNum = true;
									sign = currCh;									
								}
							}
						}
					}
				}
				firstNum = "";
			}
			prevCh = currCh;
			secondNum = "";
		}
	}
	fileInput.close();
	if (maxInt == INT_MIN)
	{
		cout << "Максимальное число не найдено!" << endl;
	}
	else
	{
		cout << "Наибольшее число: " << maxInt << endl;
		cout << "Строка, в которой находится наибольшее число: " << lineMax << endl;

	}


	return 0;
}
