#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binarytree.h"

binaryTree* createBinaryTree(int value)
{
	binaryTree * _newBinaryTree = malloc(sizeof(binaryTree));
	if (_newBinaryTree != NULL)
	{
		_newBinaryTree->size = 1;

		node* _newNode = createNode(value);
		_newBinaryTree->top = _newNode;
	}
	else
	{
		printf("err: could not allocate memory\n");
	}

	return _newBinaryTree;
}

node* createNode(int value)
{
	node* _newNode = malloc(sizeof(node));
	if (_newNode != NULL)
	{
		_newNode->data = value;
		_newNode->leftNode = NULL;
		_newNode->rightNode = NULL;
		_newNode->height = 1;

		return _newNode;
	}
	else
	{
		printf("err: could not allocate memory\n");
		return NULL;
	}
}

node * addItem(int value, node * _n)
{
	if (_n == NULL)
	{
		return createNode(value);
	}

	if (value > _n->data)
	{
		_n->leftNode = addItem(value, _n->leftNode);
	}
	else if (value < _n->data)
	{
		_n->rightNode = addItem(value, _n->rightNode);
	}
	else
	{
		return _n;
	}

	_n->height = getMax(getHeight(_n->leftNode), getHeight(_n->rightNode)) + 1;

	_n = balanceTree(value, _n);

	return _n;
}

void addTreeItem(int value, binaryTree * _binaryTree)
{
	_binaryTree->top = addItem(value, _binaryTree->top);
	++_binaryTree->size;
}

node* balanceTree(int value, node * _n)
{
	int balance = getHeight(_n->rightNode) - getHeight(_n->leftNode);

	if (balance > 1 && value < _n->rightNode->data)
	{
		return rotateRight(_n);
	}

	if (balance < -1 && value > _n->leftNode->data)
	{
		return rotateLeft(_n);
	}

	if (balance > 1 && value > _n->rightNode->data)
	{
		_n->rightNode = rotateLeft(_n->rightNode);
		return rotateRight(_n);
	}

	if (balance < -1 && value < _n->leftNode->data)
	{
		_n->leftNode = rotateRight(_n->leftNode);
		return rotateLeft(_n);
	}

	return _n;
}

node* rotateRight(node* _n)
{
	node* rightChild = _n->rightNode, * rightChildLeftChild = rightChild->leftNode;

	rightChild->leftNode = _n;
	_n->rightNode = rightChildLeftChild;

	_n->height = getMax(getHeight(_n->leftNode), getHeight(_n->rightNode)) + 1;
	rightChild->height = getMax(getHeight(rightChild->leftNode), getHeight(rightChild->rightNode)) + 1;

	return rightChild;
}

node* rotateLeft(node* _n)
{
	node* leftChild = _n->leftNode, * leftChildRightChild = leftChild->rightNode;

	leftChild->rightNode = _n;
	_n->leftNode = leftChildRightChild;

	_n->height = getMax(getHeight(_n->leftNode), getHeight(_n->rightNode)) + 1;
	leftChild->height = getMax(getHeight(leftChild ->leftNode), getHeight(leftChild->rightNode)) + 1;

	return leftChild;
}

node * removeItem(int value, node * _n)
{
	if (_n == NULL)
	{
		return _n;
	}

	if (value > _n->data)
	{
		_n->leftNode = removeItem(value, _n->leftNode);
	}
	else if (value < _n->data)
	{
		_n->rightNode = removeItem(value, _n->rightNode);
	}
	else
	{
		if (_n->leftNode == NULL || _n->rightNode == NULL)
		{
			if (_n->leftNode != NULL)
			{
				*_n = *(_n->leftNode);
				free(_n->leftNode);
			}
			else if(_n->rightNode != NULL)
			{
				*_n = *(_n->rightNode);
				free(_n->rightNode);
			}
			else
			{
				free(_n);
				_n = NULL;
			}
		}
		else
		{
			node* _tempNode = _n->leftNode;

			char endFlag = 0;
			while (!endFlag)
			{
				if (_tempNode->rightNode != NULL)
				{
					_tempNode = _tempNode->rightNode;
				}
				else
				{
					endFlag = 1;
				}
			}

			_n->data = _tempNode->data;

			_n->leftNode = removeItem(_n->data, _n->leftNode);
		}
	}

	if (_n == NULL)
	{
		return _n;
	}

	_n->height = getMax(getHeight(_n->leftNode), getHeight(_n->rightNode)) + 1;

	_n = balanceTree(value, _n);
	
	return _n;
}

void removeTreeItem(int value, binaryTree * _binaryTree)
{
	_binaryTree->top = removeItem(value, _binaryTree->top);
	--_binaryTree->size;
}

void removeTree(binaryTree* _binaryTree)
{
	removeInOrder(_binaryTree->top, _binaryTree->top);
	_binaryTree->top = NULL;
}

node* removeInOrder(node * _n, node * _parent)
{
	if (_n == NULL)
	{
		return _n;
	}

	if (_n->rightNode != NULL)
	{
		removeInOrder(_n->rightNode, _n);
	}

	if (_n->leftNode != NULL)
	{
		removeInOrder(_n->leftNode, _n);
	}

	free(_n);
	return _parent;
}

void printPathToItem(int value, binaryTree * _binaryTree)
{
	node* _n = _binaryTree->top;

	char endFlag = 0;
	while (!endFlag)
	{
		if (value > _n->data)
		{
			if (_n->leftNode != NULL)
			{
				printf("%d\n", _n->data);
				_n = _n->leftNode;
			}
			else
			{
				printf("err: value does not exist in binary tree\n");
				endFlag = 1;
			}
		}
		else if (value < _n->data)
		{
			if (_n->rightNode != NULL)
			{
				printf("%d\n", _n->data);
				_n = _n->rightNode;
			}
			else
			{
				printf("err: value does not exist in binary tree\n");
				endFlag = 1;
			}
		}
		else
		{
			printf("%d\n", _n->data);
			endFlag = 1;
		}
	}
}

void printInOrder(node * _n)
{
	if (_n == NULL)
	{
		return;
	}

	printInOrder(_n->rightNode);

	printf("%d\n", _n->data);

	printInOrder(_n->leftNode);
}

int getMax(int a, int b)
{
	return ((a > b) ? a : b);
}

int getHeight(node * _n)
{
	if (_n == NULL)
	{
		return 0;
	}
	return _n->height;
}