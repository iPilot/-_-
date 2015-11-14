#pragma once

//bool check_one(int i, char *c, int *br)
//{
//	if (c[i] == '(')
//	{
//		(*br)++;
//		if (c[i + 1] == '(' || names[c[i + 1]] || (operations[c[i + 1]] == -1)) return true;
//		else return false;
//	}
//	else
//		if (c[i] == ')')
//		{
//			(*br)--;
//			if (*br < 0) return false;
//			if (c[i + 1] == '\0' || c[i + 1] == ')' || (operations[c[i + 1]] > 0)) return true;
//			else return false;
//		}
//		else
//			if (operations[c[i]] == -1)
//			{
//				if ((operations[c[i + 1]] == -1) || names[c[i + 1]] || c[i + 1] == '(') return true;
//				else return false;
//			}
//			else
//				if (operations[c[i]] > 0)
//				{
//					if (i == 0) return false;
//					if (names[c[i + 1]] || c[i + 1] == '(' || (operations[c[i + 1]] == -1)) return true;
//					else return false;
//				}
//				else
//					if (names[c[i]])
//					{
//						if (c[i + 1] == ')' || c[i + 1] == '\0' || (operations[c[i + 1]] > 0)) return true;
//						else return false;
//					}
//					else return false;
//}

//void clear_space(char **input)
//{
//	char *tmp;
//	int l = strlen(*input), j = 0;
//	tmp = new char[l + 1];
//	for (int i = 0; i < l; i++)
//		if ((*input)[i] != ' ') tmp[j++] = (*input)[i];
//	tmp[j] = '\0';
//	delete *input;
//	*input = tmp;
//}

//bool check(char ** s)
//{
//	clear_space(s);
//	int _brackets = 0;
//	for (int i = 0; i < (int)strlen(*s); i++)
//	{
//		if (!check_one(i, *s, &_brackets))
//		{
//			cout << "String is not a formula\n";
//			return false;
//		}
//	}
//	if (_brackets == 0) return true;
//	else
//	{
//		cout << "String is not a formula\n";
//		return false;
//	}
//}
