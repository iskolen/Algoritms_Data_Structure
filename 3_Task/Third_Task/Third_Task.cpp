/*
	Петров Вадим ПС-22
	Вариант 5
	Задача:
		Имеется дерево, корень которого соответствует основателю
		рода.  Сыновья  каждой  вершины  задают  сыновей   и   дочерей
		соответствующего    человека.   Указывается   имя   некоторого
		человека.  Требуется выдать имена его детей,  внуков, сестер и
		братьев, одного из родителей, дедушки или бабушки (9).
	Среда разработки: Microsoft Visual Studio 2017
*/

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <stdlib.h>

using namespace std;


struct treeNode 
{
	string parent;
	vector<treeNode*> child;
	treeNode* father;
};

treeNode* newNode(string name)
{
	treeNode* temp = new treeNode();
	temp->parent = name;
	return temp;
}

void printNode(treeNode* tree, string name)
{
	cout << endl << "Имя: " << tree->parent << endl << endl;
	cout << "Дети: ";

	if (tree->child.size() > 0)
	{
		for (treeNode* node : tree->child)
		{
			cout << node->parent << " ";
		}

		bool haveGrandsons = false;
		cout << endl << "Внуки: ";
		for (int i = 0; i < tree->child.size(); i++)
		{
			for (treeNode* node : tree->child[i]->child)
			{
				if (tree->child[i]->child.size() > 0)
				{
					cout << node->parent << " ";
					haveGrandsons = true;
				}
			}
		}
		if (haveGrandsons == false)
		{
			cout << "Внуки не указаны";
		}
	}
	else
	{
		cout << "Дети не указаны" << endl;
		cout << "Внуки: Внуки не указаны";
	}

	if (tree->father != NULL && tree->father->child.size() > 1)
	{
		cout << endl << "Братья/Сёстры: ";

		for (treeNode* node : tree->father->child)
		{
			if (node->parent != name)
			{
				cout << node->parent << " ";
			}
		}

	}
	else
	{
		cout << endl << "Братья/Сёстры: Братья не указаны";
	}


	if (tree->father != NULL)
	{
		cout << endl << "Отец: " << tree->father->parent;
		if (tree->father->father != NULL)
		{
			cout << endl << "Дедушка: " << tree->father->father->parent;
		}
		else
		{
			cout << endl << "Дедушка: Дедушка не указан";
		}
	}
	else
	{
		cout << endl << "Отец: Отец не указан";
		cout << endl << "Дедушка: Дедушка не указан";
	}

	cout << endl << endl;
}

void printTree(treeNode* tree, string name)
{
	if (tree == NULL)
	{
		return;
	}
	printNode(tree, name);
}

treeNode* searchNode(treeNode* root, string name)
{
	int size;
	bool haveName = false;
	queue<treeNode*> Queue;
	treeNode* element = new treeNode;
	if (!root)
	{
		return NULL;
	}

	Queue.push(root);
	while (!Queue.empty())
	{
		size = (int)Queue.size();
		while (size > 0)
		{
			treeNode* first = Queue.front();
			Queue.pop();

			if (first->parent == name)
			{
				printTree(first, name);
				haveName = true;
			}

			for (int i = 0; i < first->child.size(); i++)
			{
				Queue.push(first->child[i]);
			}

			size--;
		}
	}
	if (haveName == false)
	{
		cout << endl << "Имя введено неверно!" << endl << endl;
	}

	return element;
}


int getDepth(string line)
{
	int index = 0;

	while (line[index] == '.')
	{
		index++;
	}

	return index;
}

string getName(string line)
{
	string name = "";

	int depth = getDepth(line);
	size_t len = line.length();

	name = line.substr(depth, len);

	return name;
}


void search(treeNode * root, string fileName)
{
	bool flagInput = true;
	int action;
	string line;

	cout << "1. Нахождение родственников определённого человека" << endl;
	cout << "2. Вывод семейного дерева" << endl;
	cout << "0. Выход из программы" << endl << endl;
	cout << "Выберите дейсвтие: ";

	cin >> action;

	if (action == 0)
	{
		exit(0);
	}

	if (action == 1)
	{
		while (flagInput)
		{
			string name, absent;
			cout << endl << "Введите имя: ";
			cin >> name;

			if (name != "")
			{
				searchNode(root, name);
			}
			flagInput = false;
		}
	}

	if (action == 2)
	{
		fstream fileInput(fileName);
		cout << endl;
		while (getline(fileInput, line))
		{
			cout << line << endl;
		}
		cout << endl;
	}

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
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string line, fileName;
	treeNode* root;

	fileName = getUserAnswer();
	while (fileName != "0")
	{
		fstream fileInput(fileName);
		if (fileInput.good())
		{
			getline(fileInput, line);
			root = newNode(line);

			vector<treeNode*> nodes;
			nodes.push_back(root);

			while (getline(fileInput, line))
			{
				int level = getDepth(line);
				string name = getName(line);
				treeNode* node = newNode(name);

				nodes.push_back(node);
				node->father = nodes[level - 1];
				nodes[level - 1]->child.push_back(node);
				nodes.erase(nodes.begin() + level, nodes.end());
				nodes.push_back(node);
			}

			search(root, fileName);
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

