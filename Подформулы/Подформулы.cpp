#include "functions.h"

int main()
{
	cout << "Loading symbols from \"data.txt\"...\n";
	if (build_sets())
	{
		cout << "Loaded.\n";
		char *input;	
		input = new char[256];
		cout << "Enter a formula:\n";
		gets_s(input, 256);
		btree *root = NULL;
		if (buildbtree(&root, input))
		{
			cout << "Subformulas:\n";
			printsubformulas(root);
			for (auto it = subformulas.begin(); it != subformulas.end(); it++) cout << *it << endl;
		}
		else cout << "Not a formula.\n";
		system("pause");
	}
	else
	{
		system("pause");
		return 0;
	}
}