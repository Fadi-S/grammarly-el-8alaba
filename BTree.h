//
// Created by Fadi Sarwat on 10/05/2022.
//

#ifndef LECTURE_10_BTREE_H
#define LECTURE_10_BTREE_H

typedef struct Node Node;
struct Node{
    int key;
    char *data;
    Node *right;
    Node *left;
};
Node *newNode(int key, char *data);
Node *searchBTree(Node* node, int key);
Node* insertData(Node* node, int key, char* data);
Node* insertNode(Node* node, Node *nNode);
Node *getNext(Node* node);
char* getData(Node* node);
int getKey(Node* node);
Node *getPrevious(Node* node);
void deleteNode(Node* node);
void displayBTree(Node* root);

#endif //LECTURE_10_BTREE_H
