#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node Node;

struct Node {
    int key;
    char *data;
    Node *right;
    Node *left;
};

Node *newNode(int key, char *data) {
    Node *node = malloc(sizeof(Node));

    if (!node) return NULL;

    node->key = key;
    node->data = malloc(strlen(data)+2);
    strcpy(node->data, data);
    node->right = NULL;
    node->left = NULL;

    return node;
}

Node *getNext(Node *node) {
    return node ? node->right : node;
}

Node *getPrevious(Node *node) {
    return node ? node->left : node;
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

char* getData(Node *node) {
    if (!node) {
        return NULL;
    }

    return node->data;
}

int getKey(Node *node) {
    if (!node) {
        return NULL;
    }

    return node->key;
}

Node *insertNode(Node *node, Node *nNode) {
    if(!node || node->key == nNode->key) {
        return nNode;
    }

    if(node->key > nNode->key) {
        node->left = insertNode(node->left, nNode);
    }

    if(node->key < nNode->key) {
        node->right = insertNode(node->right, nNode);
    }

    return node;
}

Node *insertData(Node *node, int key, char* data) {
    Node *nNode = newNode(key, data);

    insertNode(node, nNode);

    return nNode;
}

Node* searchBTree(Node* root, int key)
{
    if(root == NULL) return NULL;

    if(root->key == key) return root;

    if(root->key > key) {
        return searchBTree(root->left, key);
    }

    return searchBTree(root->right, key);
}

void displayBTree(Node* root) {
    if(root == NULL) return;

    displayBTree(root->left);
    printf("[%d -> %s]\n", root->key, root->data);
    displayBTree(root->right);
}