#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "string.h"

void removeNewLine(char *string)
{
    while ((string = strstr(string, "\n")) != NULL)
    {
        *string = '\0';
    }
}

Node *createBalancedTree(char* data[], int start, int end) {
    int middle = (start + end) / 2;
    Node *root;

    if(start >= end) return newNode("a");

    root = newNode(data[middle]);
    root->left = createBalancedTree(data, start, middle - 1);
    root->right = createBalancedTree(data, middle + 1, end);

    return root;
}

Node* readFromFile(int *wordCount) {
    FILE *file = fopen("words.txt", "r");
    if(!file) {
        printf("File not found");
        exit(-1);
    }

    char* data[9000];
    int i = 0;
    while(!feof(file)) {
        char word[32];
        fgets(word, 31, file);
        removeNewLine(word);
        (*wordCount)++;
        data[i] = word;
        i++;
    }

    return createBalancedTree(data, 0, *wordCount);
}

int main() {
    int wordCount = 0;
    Node* dictionary = readFromFile(&wordCount);
    printf("Dictionary loaded successfully\n");

    printf("Size = %d\n", wordCount);

    printf("Height = %d\n", getHeight(dictionary));



    return 0;
}
