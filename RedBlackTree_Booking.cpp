// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
	root = nullptr;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    int size  = deleteNode(root);
    cout << "The number of deleted nodes is: " << size << endl;
}

//Read the assignment description carefully and finish all functions definition here
//highly recommend that you follow the order defined in RedBlackTree.h
Node* RedBlackTree::getRoot()
{
    return root;
}

int RedBlackTree::deleteNode(Node *node)
{
    if(node == nullptr) {
        return 0;
    }
    int size = deleteNode(node->leftChild);
    size += deleteNode(node->rightChild);
    delete node;

    return size + 1;
}

//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.
//Note: duplicated node should not be added inside
void RedBlackTree::insertNode(Node *node)
{
    Node *parent = nullptr;
    Node *cur = root;
    while (cur != nullptr)      //Reach to a leaf node
    {
       parent = cur;
        if(compareNodes(node, (cur->hotelName + cur->arrivalDate + to_string(cur->confirmNum))) < 0)
        {
            cur = cur->leftChild;
        }else if (compareNodes(node, (cur->hotelName + cur->arrivalDate + to_string(cur->confirmNum))) > 0 )
        {
            cur = cur->rightChild;
        }else{
            cout << "Duplicated node. NOT added" << endl;
            return;
        }
    }
    node->parent = parent;      //Find node, insert node. Update node pointer
    if(parent == nullptr)
    {
        root = node;        //If node is empty
    }else if(compareNodes(node, (parent->hotelName + parent->arrivalDate + to_string(parent->confirmNum))) < 0)
    {
        parent->leftChild = node;
    }else if(compareNodes(node, (parent->hotelName + parent->arrivalDate + to_string(parent->confirmNum))) > 0)
    {
        parent->rightChild = node;
    }else{
        cout << "Duplicated node. NOT added" << endl;
    }
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->color = "RED";
    fixUp(node);
}

void RedBlackTree::fixUp(Node *node)
{
    while(node != root && node->parent->color == "RED")
    {
        Node *grandParent = node->parent->parent;
        Node *uncle = nullptr;
        if(node->parent == node->parent->parent->leftChild)   //Insert Node's parent is a left child
        {
            uncle = node->parent->parent->rightChild;        //Locate Uncle Node
            if(uncle != nullptr && uncle->color == "RED")    //If node's parent and uncle both red
            {
                node->parent->color = "BLACK";               //Case 1A
                uncle->color = "BLACK";
                grandParent->color = "RED";
                node = grandParent;
            }else{
                if(node == node->parent->rightChild)        //Case 1B
                {
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->color = "BLACK";             //Case 2.2
                grandParent->color = "RED";
                rightRotate(grandParent);
            }
        } else{
            uncle = grandParent->leftChild;                //Case 2.1B
            if (uncle != nullptr && uncle->color == "RED")
            {
                node->parent->color = "BLACK";
                uncle->color = "BLACK";
                grandParent->color = "RED";
                node = grandParent;
            }else{
                if(node == node->parent->leftChild) {       //Case 2.2A
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->color = "BLACK";
                grandParent->color = "RED";
                leftRotate(grandParent);
            }
        }
    }
    root->color = "BLACK";
}

void RedBlackTree::preOrderTraversal(Node *node)
{
    if(node != nullptr)
    {
        print(node);
        preOrderTraversal(node->leftChild);
        preOrderTraversal(node->rightChild);
    }
}
void RedBlackTree::inorderTraversal(Node *node)
{
    if(node != nullptr)
    {
        inorderTraversal(node->leftChild);
        print(node);
        inorderTraversal(node->rightChild);
    }

}
void RedBlackTree::postOrderTraversal(Node *node)
{
    if(node != nullptr)
    {
        postOrderTraversal(node->leftChild);
        postOrderTraversal(node->rightChild);
        print(node);
    }
}

Node* RedBlackTree::findMinimumNode(Node *node)
{
    if(node == nullptr || node->leftChild == nullptr)
    {
        return node;
    }
    return findMinimumNode(node->leftChild);
}
Node* RedBlackTree::findMaximumNode(Node *node) {
    if(node == nullptr || node->rightChild == nullptr)
    {
        return node;
    }

    return findMaximumNode(node->rightChild);
}


Node* RedBlackTree::treeSearch(string hotelName, string arrivalDate, int confirmNum)
{
    Node *result = searchHelper(root, hotelName, arrivalDate, confirmNum);
    if(result == nullptr)
    {
        cout << left;
        cout << setw(18) << hotelName << "on "
             << setw(12) << arrivalDate << "confirmation No.: "
             << setw(8) << confirmNum << " is NOT found." << endl;
    }else{
        cout << left;
        cout << setw(18) << hotelName << "on "
             << setw(12) << arrivalDate << "confirmation No.: "
             << setw(8) << confirmNum << " is found." << endl;
    }
    return result;
}

void RedBlackTree::leftRotate(Node *node)
{
    Node *leftBaby = node->rightChild;      //Identify and relink the right child of the Node
    node->rightChild = leftBaby->leftChild;

    if(leftBaby->leftChild != nullptr)      //Identify and relink the right child of the Node
    {
        leftBaby->leftChild->parent = node;
    }

    leftBaby->parent = node->parent;        //Update left baby parent pointer

    if(node->parent == nullptr)             //Update parent node's child
    {
        root = leftBaby;
    }else if (node == node->parent->leftChild){
        node->parent->leftChild = leftBaby;
    } else{
        node->parent->rightChild = leftBaby;
    }

    leftBaby->leftChild = node;         //Update parent node's child
    node->parent = leftBaby;
}
void RedBlackTree::rightRotate(Node *node)
{
    Node *rightBaby = node->leftChild;          //Identify and relink the left child of the Node
    node->leftChild = rightBaby->rightChild;

    if(rightBaby->rightChild != nullptr)        //Update parent link of the moved Child
    {
        rightBaby->rightChild->parent = node;
    }
    rightBaby->parent = node->parent;           //Update right baby parent pointer

    if(node->parent == nullptr)                 //Update parent node's child
    {
        root = rightBaby;
    }else if (node == node->parent->leftChild){
        node->parent->leftChild = rightBaby;
    } else{
        node->parent->rightChild = rightBaby;
    }

    rightBaby->rightChild = node;               //Update parent node's child
    node->parent = rightBaby;
}

Node* RedBlackTree::findPredecessorNode(Node *node)
{
    if(node->leftChild != nullptr)
    {
        return findMaximumNode(node->leftChild);
    }
    if(node->parent != nullptr && node == node->parent->leftChild) {
        node = node->parent;        //if node is left node
    }
    return node->parent;
}

Node* RedBlackTree::findSuccessorNode(Node *node)
{
    if(node->rightChild != nullptr)
    {
        return findMaximumNode(node->rightChild);
    }

    if(node->parent != nullptr && node == node->parent->rightChild) {
        node = node->parent;        //if node is right node
    }
    return node->parent;
}

void RedBlackTree::treeMinimum()
{
    Node *getMin = findMinimumNode(root);
    if(getMin != nullptr)
    {
        cout<< "The MINIMUM is:" << endl;
        print(getMin);
    }else{
        cout << "Tree is empty" << endl;
    }
}

void RedBlackTree::treeMaximum()
{
    Node *getMax = findMaximumNode(root);
    if(getMax != nullptr)
    {
        cout<< "The MAXIMUM is:" << endl;
        print(getMax);
    }else{
        cout << "Tree is empty" << endl;
    }
}

void RedBlackTree::treePreorder()
{
    preOrderTraversal(root);
}

void RedBlackTree::treeInorder()
{
    inorderTraversal(root);
}

void RedBlackTree::treePostorder()
{
    postOrderTraversal(root);
}

void RedBlackTree::treePredecessor(string hotelName, string arrivalDate, int confirmNum)
{
    Node *preResult = treeSearch(hotelName, arrivalDate, confirmNum);       //Search if the target node is inside the tree

    if(preResult != nullptr) {
        Node* getPre = findPredecessorNode(preResult);      //Get predecessor of target node
        if(getPre != nullptr){
            cout << "Its Predecessor is: " << endl;
            print(getPre);
        }
    } else {
        cout << "Its Predecessor does NOT exist" << endl;
    }
}

void RedBlackTree::treeSuccessor(string hotelName, string arrivalDate, int confirmNum)
{
    Node *sucResult = treeSearch(hotelName, arrivalDate, confirmNum);       //Search if the target node is inside the tree

    if(sucResult != nullptr) {
        Node* getSuc = findSuccessorNode(sucResult);        //Get successor of target node
        if(getSuc != nullptr){
            cout << "Its Successor is: " << endl;
            print(getSuc);
        }
    } else {
        cout << "Its Successor does NOT exist" << endl;
    }
}

void RedBlackTree::treeInsert(string hotelName, string arrivalDate, int confirmNum)
{
    Node *newInsert = new Node();
    newInsert->hotelName = hotelName;
    newInsert->arrivalDate = arrivalDate;
    newInsert->confirmNum = confirmNum;

    insertNode(newInsert);
}
//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
      cout << left;
      cout << setw(18)  << node->hotelName
           << setw(12) << node->arrivalDate
           << setw(8) << node->confirmNum;
      cout << right << setw(7) << node->color << endl;
}

int RedBlackTree::compareNodes(Node *node, string key)
{
    string nodeInfo = node->hotelName + node->arrivalDate + to_string(node->confirmNum);

    return nodeInfo.compare(key);       //directly compare string by ASCII code
}

Node* RedBlackTree::searchHelper(Node *node, string hotelName, string arrivalDate, int confirmNum)
{
    string searchKey = hotelName + arrivalDate + to_string(confirmNum);

    if(node == nullptr || compareNodes(node, searchKey) == 0)
    {
        return node;            //if tree is empty or find node with same info
    }

    if(compareNodes(node, searchKey) < 0){
        return searchHelper(node->rightChild, hotelName, arrivalDate, confirmNum);
    }else{
        return searchHelper(node->leftChild, hotelName, arrivalDate,confirmNum);
    }
}