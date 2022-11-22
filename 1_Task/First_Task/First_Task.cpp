/*
	Петров Вадим ПС-22
	Вариант 14
	Задача:
		В некоторых строках текстового файла имеются выражения,
		состоящие   из   двух   целых   чисел, разделенных    знаком
		арифметической   операции('+', '-', '*', '/').Первое  из  чисел
		может быть отрицательным.В строке может содержаться несколько
		выражений.Перед  выражением  и  после него  могут  находиться
		произвольные символы.Требуется  выделить  строку, в  которой
		значение выражения максимально.Вывести найденное максимальное
		значение(7).
	Среда разработки: Microsoft Visual Studio 2017

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <cstring>
#include <istream>


#define operation(c)  ((c) == '+' || (c) == '-'  || (c) == '*' || (c) == '/')
#define digit(c)	  ((c) > '0' && (c) <= '9')

using namespace std;


int main()
{
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


	char currCh, prevCh, sign, signMax;
	int num1, num2, numMax1, numMax2, maxInt, i, len, totalNum;
	bool negative, nextNum;
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

	while (getline(fileInput, line))// Построчное чтение файла
	{
		i = 0;
		len = line.length();
		while ((i != len) && (i < len))// Обработка каждой строки
		{
			currCh = line[i], i++;// Чтение символа из строки
			negative = false;
			nextNum = false;

			if (digit(currCh)) // Чтение выражения
			{
				while (digit(currCh)) // Чтение первого число
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
				if (operation(currCh))
				{
					sign = currCh;
					currCh = line[i], i++;
					while (digit(currCh) || (nextNum == true))//Чтение второго числа
					{
						if (nextNum == true)
						{
							currCh = line[i], i++;
							if (!digit(currCh))
							{								
								break;
							}
							nextNum = false;
						}
						else
						{
							secondNum += currCh;
							num2 = stoi(secondNum);
							currCh = line[i], i++;
						}
						if (!digit(currCh)) // Складываем числа и находим максимальное
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
							if (operation(currCh))//Если есть дальше есть число, которое нужно посчитать
							{
								if (sign == '-')// Если было вычитание
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
									if (firstNum == "")// Два или более операторов подряд
									{
										break;
									}
									else
									{
										num1 = stoi(firstNum);
										secondNum = "";
										nextNum = true;
										sign = currCh;
									}									
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
