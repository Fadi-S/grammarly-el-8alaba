g#ifndef BTREE_ELTEAM_ELGAMED_H
#define BTREE_ELTEAM_ELGAMED_H

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

#endif //BTREE_ELTEAM_ELGAMED_H
