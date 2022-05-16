//
// Created by Fadi Sarwat on 10/05/2022.
//

#ifndef LECTURE_10_BTREE_H
#define LECTURE_10_BTREE_H

typedef struct Node Node;
struct Node{
    char *data;
    Node *right;
    Node *left;
};
Node *newNode(char *data);
Node *searchBTree(Node* node, char* key);
Node* insertData(Node* node, char* data);
Node* insertNode(Node* node, Node *nNode);
int getHeight(Node* root);
void displayBTree(Node* node);
Node *findMin(Node *n);


#endif //LECTURE_10_BTREE_H
