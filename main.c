#include <stdlib.h>
#include <stdio.h>
#include "binarytree.c"

int main()
{
	int a = 3, b[7] = { 8, 2, 7, 15, 0, -3, 4 };
	int *error = -1;
	binaryTree* _tree = createBinaryTree(a, error);
	for (int i = 0; i < 7; i++)
	{
		addTreeItem(b[i], _tree, error);
	}

	printPathToItem(b[3], _tree);

	printInOrder(_tree->top);

	removeTreeItem(7, _tree);

	printInOrder(_tree->top);

	removeTreeItem(3, _tree);

	printInOrder(_tree->top);

	removeTree(_tree);
}
