#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#define sz(a) (int)a.size()

using namespace std;
bool names[300];
int operations[300], group[300];

struct btree
{
	char *data;
	int length;
	btree *prev;
	btree *left;
	btree *right;
};

void newsubtree(btree **tree, btree *left, btree *right, btree *prev, char * data, int length)
{
	*tree = new btree;
	(*tree)->data = data;
	(*tree)->left = left;
	(*tree)->right = right;
	(*tree)->prev = prev;
	(*tree)->length = length;
}

bool buildbtree(btree **root, char * input)
{
	newsubtree(root, NULL, NULL, NULL, NULL, 0);
	btree *cur;
	cur = *root;
	int i = 0, l = strlen(input);
	for (; i < l; i++)
	{
		if (group[input[i]]) 
		{
			if (group[input[i]] > 0) //открывающая скобка
			{
				if (cur->data == NULL) //пустой узел
				{
					cur->data = input + i;
					cur->length = 1;
					newsubtree(&cur->right, NULL, NULL, cur, NULL, 0);
					cur = cur->right;
				}
				else break;
			}
			else 
			{
				if (cur->data != NULL)
				{
					char stop = -group[input[i]];
					while (cur->prev != NULL && operations[cur->data[0]]) cur = cur->prev;
					if (cur->data[0] == stop && cur->right != NULL)
					{
						if (cur->prev == NULL)
						{
							btree *tmp;
							newsubtree(&tmp, cur, NULL, cur->prev, NULL, 0);
							cur->prev = tmp;
							*root = tmp;
							cur = cur->prev;
						}
						else cur = cur->prev;
					}
					else break;
				}
				else break;
			}
		}
		else
		if (names[input[i]])  
		{
			if (cur->data == NULL)   
			{
				int q = 0;
				while (names[input[i+q]]) q++;
				cur->data = input + i;
				cur->length = q;
				i += q - 1;
				if (cur->prev != NULL)
				{
					cur = cur->prev;
					while (cur->prev != NULL && operations[cur->data[0]] < 0) cur = cur->prev;
				}
				else
				{
					btree *tmp;
					newsubtree(&tmp, cur, NULL, cur->prev, NULL, 0);
					*root = cur = cur->prev = tmp;
				}
			}
			else break;
		}
		else
		if (operations[input[i]])
		{
			if (operations[input[i]] < 0)
			{
				if (cur->data == NULL && cur->left == NULL)
				{
					cur->length = 1;
					cur->data = new char[cur->length];
					cur->data = input + i;
					newsubtree(&cur->right, NULL, NULL, cur, NULL, 0);
					cur = cur->right;
				}
				else break;
			}
			else
			{
				if (cur->data == NULL && cur->left != NULL)
				{
					cur->data = input + i;
					cur->length = 1;
					newsubtree(&cur->right, NULL, NULL, cur, NULL, 0);
					cur = cur->right;
				}
				else
				if (cur->data != NULL)
				{					
					while (cur->prev != NULL && operations[cur->data[0]] <= operations[input[i]] && !group[cur->data[0]]) cur = cur->prev;
					btree *tmp;
					if (group[cur->data[0]] || operations[cur->data[0]] > operations[input[i]])
					{
						newsubtree(&tmp, cur->right, NULL, cur, input+i, 1);
						cur->right = cur->right->prev = tmp;
					}
					else
					{
						newsubtree(&tmp, cur, NULL, cur->prev, input+i, 1);
					    *root = cur->prev = tmp;
					}
					newsubtree(&tmp->right, NULL, NULL, tmp, NULL, 0);
					cur = tmp->right;
				}
				else break;
			}
		}
		else
		if (input[i] != ' ') break;
	}
	if (i < l) return false;
	else
	{
		while (cur->prev != NULL && operations[cur->data[0]]) cur = cur->prev;
		if (cur != *root) return false;
		else
			if (cur->data == NULL && cur->left != NULL && cur->right == NULL ||
				operations[cur->data[0]] < 0 && cur->left == NULL && cur->right != NULL ||
				operations[cur->data[0]] > 0 && cur->left != NULL && cur->right != NULL) return true;
			else return false;
	}
}

btree *clearbtree(btree *node)
{
	if (node->left != NULL)
		node->left = clearbtree(node->left);
	if (node->right != NULL)
		node->right = clearbtree(node->right);
	delete node->data;
	delete node;
	return NULL;
}

string printsubformulas(btree *tree)
{
	string l = "";
	if (tree->left != NULL) l += printsubformulas(tree->left);
	if (tree->data != NULL)
	{
		for (int i = 0; i < tree->length; i++) l += tree->data[i];
		if (tree->right != NULL) l += printsubformulas(tree->right);
		if (group[tree->data[0]]) l += (char)group[tree->data[0]];
		else cout << l << endl;
	}
	return l;
}

bool build_sets()
{
	FILE *f = NULL;
	fopen_s(&f, "data.txt", "r");
	if (f != NULL)
	{
		char buf;
		int prior = 1;
		for (fscanf_s(f, "%c", &buf, 1); buf != '\n'; fscanf_s(f, "%c", &buf, 1)) names[buf] = true;
		for (fscanf_s(f, "%c", &buf, 1); buf != '\n'; fscanf_s(f, "%c", &buf, 1))
		{
			if (buf == ' ') prior++;
			else
				if (!names[buf]) operations[buf] = prior;
				else
				{
					cout << "Invalid data: found character \'" << buf << "\' already assigned as \"name symbol\".\n";
					return false;
				}
		}
		for (fscanf_s(f, "%c", &buf, 1); buf != '\n'; fscanf_s(f, "%c", &buf, 1))
		{
			if (!names[buf] && !operations[buf]) operations[buf] = -1;
			else
			{
				cout << "Invalid data: found character \'" << buf << "\' already assigned as \"name symbol\" or \"binary operation symbol\".\n";
				return false;
			}
			buf = -1;
		}
		char buf2 = -1; 
		for (fscanf_s(f, "%c%c", &buf, 1, &buf2, 1); buf != EOF; buf = -1, buf2 = -1, fscanf_s(f, "%c%c", &buf, 1, &buf2, 1))
		{
			if (buf2 != EOF)
			{
				if (!names[buf] && !operations[buf])
				{
					if (!names[buf2] && !operations[buf2])
					{
						if (buf != buf2)
						{
							group[buf] = buf2;
							group[buf2] = -buf;
						}
						else
						{
							cout << "Group-open symbol is equal to group-close symbol.\n";
							return false;
						}
					}
					else
					{
						cout << "Invalid data: found character \'" << buf2 << "\' already assigned as \"name symbol\" or \"operation symbol\".\n";
						return false;
					}
				}
				else
				{
					cout << "Invalid data: found character \'" << buf << "\' already assigned as \"name symbol\" or \"operation symbol\".\n";
					return false;
				}
			}
			else
			{
				cout << "Group-close symbol not found.\n";
				return false;
			}
		}
		fclose(f);
		return true;
	}
	else
	{
		cout << "File \"data.txt\" not found.\n";
		return false;
	}
}