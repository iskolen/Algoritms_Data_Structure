/*
	Петров Вадим ПС-22
	Вариант 1
	Задача:
		Имеется массив элементов,  отсортированный по некоторому
		полю. Методом бинарного поиска обеспечить:
		   1) нахождение заданного элемента;
		   2) вставку элемента;
		   3) удаление элемента (7).
	Среда разработки: Microsoft Visual Studio 2017
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void manage();
void addElement(int value);
void deleteElement(int value);
void printList();

string getUserAnswer()
{
	string fileName;
	cout << "Введите имя входного файла('0', если хотите выйти): ";
	cin >> fileName;
	return fileName;
}

vector<int> values;
pair<int, int> findElement(int value)
{
	bool flag = false;
	int l = 0;
	int valuesSize = values.size() - 1;
	int mid;

	while ((l <= valuesSize) && (!flag))
	{
		mid = (l + valuesSize) / 2;

		if (values[mid] == value)
		{
			flag = true;
		}

		if (values[mid] > value)
		{
			valuesSize = mid - 1;
		}
		else
		{
			l = mid + 1;
		}
	}
	if (flag) 
	{
		return make_pair(mid, l);
	}
	else 
	{
		return make_pair(-1, l);
	}
}

int main()
{
	string fileName;
	int value = 0;
	setlocale(LC_ALL, "RUS");
	fileName = getUserAnswer();
	while (fileName != "0")
	{
		fstream fileInput(fileName);
		if (fileInput.good())
		{
			while (fileInput >> value)
			{
				values.emplace_back(value);
			}
			while (1)
			{
				manage();
			}
		}
		else
		{
			cout << endl;
			cout << "Файл не существует!" << endl;
			cout << endl;
			fileName = getUserAnswer();
		}
	}

	return 0;
}

void manage()
{
	cout << "1. Найти элемент" << endl;
	cout << "2. Вставка элемента" << endl;
	cout << "3. Удаление элемента" << endl;
	cout << "4. Вывести массив" << endl;
	cout << "0. Выход из программы" << endl << endl;

	int value = 0;
	char ch = 10;

	while (ch != 0)
	{
		cout << "Выберите действие: ";
		cin >> ch;
		if (ch == '4')
		{
			printList();
			return;
		}
		if (ch == '0')
		{
			exit(0);
		}
		cout << "Введите число: ";
		cin >> value;
		if (ch == '1')
		{
			if (findElement(value).first + 1 > 0)
			{
				cout << "Число: ";
				cout << value << endl;
				cout << "Порядковый номер: ";
				cout << findElement(value).first + 1 << endl;
			}
			else
			{
				cout << "Число отсутсвует в массиве: ";
			}
			printList();
			cout << endl;
		}
		else if (ch == '2')
		{
			cout << "Число: ";
			cout << value << endl;
			cout << "Добавлено в массив: ";
			addElement(value);
			printList();
			cout << endl;
		}
		else if (ch == '3')
		{
			if (findElement(value).first + 1 > 0)
			{
				cout << "Число: ";
				cout << value;
				cout << " удалено из массива: ";

				deleteElement(value);
			}
			else
			{
				cout << "Число: ";
				cout << value << endl;
				cout << "Число отсутсвует в массиве: ";
			}

			printList();
			cout << endl;
		}
	}
}

void addElement(int value)
{
	values.insert(values.begin() + findElement(value).second, value);
}

void deleteElement(int value)
{
	int index = findElement(value).first;

	if (index >= 0)
	{
		values.erase(values.begin() + index);
	}
}

void printList()
{
	for (int i = 0; i < values.size(); i++) 
	{
		cout << values[i] << ' ';
	}
	cout << endl << endl;
}