#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "string.h"

void removeNewLine(char *string) {
    string[strcspn(string, "\r\n")] = 0;
}

Node *getAdjacentNode(Node *current, char *key, int isSuccessor) {
    Node *successor;

    while (current) {
        char *first = isSuccessor ? current->data : key;
        char *second = !isSuccessor ? current->data : key;

        if (strcasecmp(first, second) > 0) {
            successor = current;
            current = isSuccessor ? current->left : current->right;
        } else {
            current = !isSuccessor ? current->left : current->right;
        }
    }

    return successor;
}

Node *inorderSuccessor(Node *root, char *key) {
    if (!root) return NULL;

    return getAdjacentNode(root, key, 1);
}

Node *inorderPredecessor(Node *root, char *key) {
    if (!root) return NULL;

    return getAdjacentNode(root, key, 0);
}

Node *findParent(Node *node, char *key, Node *parent) {
    if (!node)
        return NULL;

    if (strcasecmp(node->data, key) == 0)
        return parent;

    if (strcasecmp(node->data, key) > 0) {
        return findParent(node->left, key, node);
    }

    return findParent(node->right, key, node);
}

Node *previousBeforeNull(Node *root, char *key) {
    if (!root) return NULL;

    return findParent(root, inorderSuccessor(root, key)->data, NULL);
}

Node *readFromFile(int *wordCount) {
    *wordCount = 0;
    FILE *file = fopen("../EN-US-Dictionary.txt", "r");
    if (!file) {
        printf("File not found");
        exit(-1);
    }

    Node *root = newNode("-");
    while (!feof(file)) {
        char word[32];
        fgets(word, 31, file);
        removeNewLine(word);
        (*wordCount)++;
        insertData(root, word);
    }

    return root;
}

int main() {
    int wordCount = 0;
    Node *dictionary = readFromFile(&wordCount);
    printf("Dictionary loaded successfully\n");

    printf("Size = %d\n", wordCount);

    printf("Height = %d\n", getHeight(dictionary));
    char sentence[301];
    printf("Enter a sentence: \n");
    fgets(sentence, 300, stdin);
    char *word = strtok(sentence, " ");
    while (word) {
        removeNewLine(word);
        Node *node = searchBTree(dictionary, word);

        if (node) {
            printf("%s - Correct.", node->data);
        }else {
            printf("%s - Incorrect, did you mean: ", word);

            Node *inorderPre = inorderPredecessor(dictionary, word);
            Node *inorderSuc = inorderSuccessor(dictionary, word);
            Node *previousNode = previousBeforeNull(dictionary, word);

            if (previousNode)
                printf("%s", previousNode->data);

            if (inorderPre)
                printf(", %s", inorderPre->data);

            if (inorderSuc)
                printf(", %s", inorderSuc->data);

        }

        printf("\n");
        word = strtok(NULL, " ");
    }
    return 0;
}
