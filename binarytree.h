#ifndef BINARYTREE_H
#define BINARYTREE_H

struct node // Individual nodes of AVL tree
{
	int data, height;
	struct node* leftNode, * rightNode;
};
typedef struct node node;

struct binaryTree // Tree
{
	int size;
	node* top;
};
typedef struct binaryTree binaryTree;

binaryTree* createBinaryTree(int value); // returns pointer to new binary tree with root of given value

node* createNode(int value); // returns pointer to node with given value

node* addItem(int value, node* _n); // recursive function that inserts item
void addTreeItem(int value, binaryTree* _binaryTree);

node* balanceTree(int value, node* _n); // function that adjusts tree to fit AVL type

node* rotateLeft(node* _n); // function used in balancing

node* rotateRight(node* _n); // function used in balancing

node* removeItem(int value, node* _n); // recursive function that removes item
void removeTreeItem(int value, binaryTree* _binaryTree);

void removeTree(binaryTree * _binaryTree); // function that removes entire tree
node* removeInOrder(node* _n, node* _parent);

void printPathToItem(int value, binaryTree* _binaryTree); // prints path to given value

void printInOrder(node* _n); // prints tree values in order

int getMax(int a, int b); // function used in balancing

int getHeight(node* _n // function used in balancing

#endif

