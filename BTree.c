#include <stdlib.h>
#include "string.h"
#include <stdio.h>

typedef struct Node Node;

struct Node {
    char *data;
    Node *right;
    Node *left;
};

Node *newNode(char *data) {
    Node *node = malloc(sizeof(Node));

    if (!node) return NULL;

    node->data = malloc(strlen(data) + 1);
    node->right = NULL;
    node->left = NULL;
    strcpy(node->data, data);

    return node;
}

void deleteNode(Node *node) {
    if (!node)
        return;

    Node* prev = node->left, *right=node->right;

    if(right)
        right->left = prev;

    if(prev)
        prev->right = right;

    free(node);
}

int getHeight(Node *root){
    int leftHeight, rightHeight;
    if(root == NULL)
        return 0;

    leftHeight = getHeight(root->left);
    rightHeight = getHeight(root->right);

    return ((leftHeight >= rightHeight) ? leftHeight : rightHeight) + 1;
}

Node *insertNode(Node *node, Node *nNode) {
    if(!node) {
        return nNode;
    }

    if(strcasecmp(node->data, nNode->data) == 0) {
        return node;
    }

    if(strcasecmp(node->data, nNode->data) > 0) {
        node->left = insertNode(node->left, nNode);
    }

    if(strcasecmp(node->data, nNode->data) < 0) {
        node->right = insertNode(node->right, nNode);
    }

    return node;
}

Node *insertData(Node *node, char* data) {
    return insertNode(node, newNode(data));
}

Node* searchBTree(Node* root, char* key)
{
    if(root == NULL) return NULL;

    if(strcasecmp(root->data, key) == 0) return root;

    if(strcasecmp(root->data, key) > 0) {
        return searchBTree(root->left, key);
    }

    return searchBTree(root->right, key);
}

void displayBTree(Node* node) {
    if(node == NULL) return;

    displayBTree(node->left);
    printf("%s\n", node->data);
    displayBTree(node->right);
}