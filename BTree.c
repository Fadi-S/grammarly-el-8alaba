#include <stdlib.h>
#include <string.h>
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

    node->data = malloc(strlen(data)+2);
    strcpy(node->data, data);
    node->right = NULL;
    node->left = NULL;

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
    if(!node || strcasecmp(node->data, nNode->data) == 0) {
        return nNode;
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
    Node *nNode = newNode(data);

    insertNode(node, nNode);

    return nNode;
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

void displayBTree(Node* root) {
    if(root == NULL) return;

    displayBTree(root->left);
    printf("[%s]\n", root->data);
    displayBTree(root->right);
}