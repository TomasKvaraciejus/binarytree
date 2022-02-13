#ifndef BINARYTREE_H
#define BINARYTREE_H

struct node
{
	int data, height;
	struct node* leftNode, * rightNode;
};
typedef struct node node;

struct binaryTree
{
	int size;
	node* top;
};
typedef struct binaryTree binaryTree;

binaryTree* createBinaryTree(int value);

node* createNode(int value);

node* addItem(int value, node* _n);
void addTreeItem(int value, binaryTree* _binaryTree);

node* balanceTree(int value, node* _n);

node* rotateLeft(node* _n);

node* rotateRight(node* _n);

node* removeItem(int value, node* _n);
void removeTreeItem(int value, binaryTree* _binaryTree);

void printPathToItem(int value, binaryTree* _binaryTree);

void printInOrder(node* _n);

int getMax(int a, int b);

int getHeight(node* _n);

#endif

