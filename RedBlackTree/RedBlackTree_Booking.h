// Description: Red black tree header file. It defines the Node and the
//              red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is a HotelBooking
struct Node
{
   string hotelName, arrivalDate;
   int confirmNum;

   Node *parent;
   Node *leftChild;
   Node *rightChild;
   string color;
};

class RedBlackTree
{
    private:
        Node *root;
    public:
        RedBlackTree();
        ~RedBlackTree();
        Node* getRoot();
        int deleteNode(Node *node);
        void insertNode(Node *node);
        void fixUp(Node *node);

        void preOrderTraversal(Node *node);
        void inorderTraversal(Node *node);
        void postOrderTraversal(Node *node);

        Node* findMinimumNode(Node *node);
        Node* findMaximumNode(Node *node);
        Node* treeSearch(string hotelName, string arrivalDate, int confirmNum);
        void leftRotate(Node *node);
        void rightRotate(Node *node);
        Node* findPredecessorNode(Node *node);
        Node* findSuccessorNode(Node *node);

        void treeMinimum();
        void treeMaximum();
        void treePreorder();
        void treeInorder();
        void treePostorder();
        void treePredecessor(string hotelName, string arrivalDate, int confirmNum);
        void treeSuccessor(string hotelName, string arrivalDate, int confirmNum);
        void treeInsert(string hotelName, string arrivalDate, int confirmNum);

        void print(Node *node);
        int compareNodes(Node *node, string key);
        Node* searchHelper(Node *node, string hotelName, string arrivalDate, int confirmNum);
};
#endif
