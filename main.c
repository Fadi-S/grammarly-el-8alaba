#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "string.h"
void removeNewLine(char *string) {
    string[strcspn(string, "\r\n")] = 0;
}

Node *readFromFile(int *wordCount) {
    *wordCount = 0;
    FILE *file = fopen("EN-US-Dictionary.txt", "r");
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
        if (node) printf("%s - Correct.\n", node->data);
        else {
            printf("%s - Incorrect, did you mean: ", word);

            Node *inosuc = inorderSuccessor(dictionary, word);
            if (inosuc)
                printf("%s", inosuc->data);

            Node *inodec = inorderpredeccessor(dictionary, word);
            if (inodec)
                printf(", %s", inodec->data);
          preNull(dictionary, word);
        }

        word = strtok(NULL, " ");
    }
    return 0;
}
