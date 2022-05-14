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
Node *findMin(Node *n){
    if (n && n->left) return findMin(n->left);
    return n;}
    Node *findMax(Node*n)
    {
    if(n&&n->right)
        return findMax(n->right);
        return n;
    }
Node *inorderSuccessor(Node *root, char*key){
    if (!root) return NULL;
    Node *successor = NULL;
    Node *current  = root;
    while(current && strcasecmp(current->data , key)!=0){
        if(strcasecmp(current->data , key)<0){
            successor = current;
            current= current->left;
        }
        else current = current->right;
    }
    if (!current) return NULL;
    if(current && current->right)
        successor = findMin(current->right);
    return successor;
}
Node*inorderPredessor(Node*root)
{
    root = root->left;
    if(root == NULL)
        return NULL;
    while(root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
Node*findPredecessorRecursive(Node*root,Node*pred,char*key){

if(root == NULL){
return NULL;
}
if (strcasecmp(root->data , key)==0) {
if (root->left != NULL) {
return findMax(root->left);
}
}
else if (strcasecmp( root->data,key)>0) {
return findPredecessorRecursive(root->left, pred, key);
}
else {
pred = root;
return findPredecessorRecursive(root->right, pred, key);
}
return pred;
}