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

using namespace std;


struct treeNode {
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

void printNode(treeNode* tree)
{
	cout << endl << "Имя: " << tree->parent << endl;
	cout << "Дети: ";

	if (tree->child.size() > 0)
	{
		for (treeNode* node : tree->child)
			cout << node->parent << " ";
	}
	else
	{
		cout << "Дети отсутствуют";
	}
	if (tree->father != NULL)
	{
		cout << endl << "Отец: " << tree->father->parent;
	}
	if (tree->father->father != NULL)
	{
		cout << endl << "Дедушка: " << tree->father->father->parent;
	}

	cout << endl << endl;
}

void printTree(treeNode* tree)
{
	if (tree == NULL)
	{
		return;
	}
	printNode(tree);
	for (int i = 0; i < tree->child.size(); i++)
	{
		printTree(tree->child[i]);
	}
}

treeNode* searchNode(treeNode* root, string name)
{
	treeNode* element = new treeNode;
	if (!root)
	{
		return NULL;
	}
	if (root->parent == name)
	{
		printTree(root);
	}
	queue<treeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		int n = (int)q.size();
		while (n > 0)
		{
			treeNode* p = q.front();
			q.pop();

			if (p->parent == name)
			{
				printTree(p);
			}

			for (int i = 0; i < p->child.size(); i++)
			{
				q.push(p->child[i]);
			}

			n--;
		}
	}

	return element;
}


int getDepth(string line)
{
	int index = 0;

	while (line[index] == ' ')
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


ifstream openFile(string file_name)
{
	ifstream file;
	file.open(file_name);

	if (!file.is_open())
		cout << endl << "Ошибка при открытии файла: " << file_name << "!" << endl;

	return file;
}

void searchDriver(treeNode * root)
{
	bool flagInput = true;

	cout << "Добро пожаловать в программу поиска. Для выхода введите 'выход'" << endl << endl;
	while (flagInput)
	{
		string name;
		cout << "Введите имя: ";
		cin >> name;

		if (name == "выход")
			flagInput = false;
		if (name != "")
			searchNode(root, name);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream input;
	string line;
	treeNode* root;

	input = openFile("input.txt");

	getline(input, line);
	root = newNode(line);

	vector<treeNode*> nodes;
	nodes.push_back(root);

	while (getline(input, line))
	{
		int level = getDepth(line);
		string name = getName(line);
		treeNode* node = newNode(name);

		if (level == nodes.size())
		{
			nodes.push_back(node);
		}

		if (level < nodes.size())
		{
			node->father = nodes[level - 1];
			nodes[level - 1]->child.push_back(node);
			nodes.erase(nodes.begin() + level, nodes.end());
			nodes.push_back(node);
		}
	}

	searchDriver(root);
}

