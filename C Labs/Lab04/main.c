#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 32

void linkList();

typedef struct node_struct {
    char * word;
    struct node_struct *next;
}Node;

int main() {
    linkList();
    return 0;
}

void linkList() {
    bool magicWord = false;
    // Create a Node pointer pointing to start of the linked list
    Node * listHead = NULL;

    loopStart:
    while (magicWord == false){
        char inputWord[MAX_WORD_LENGTH];
        printf("Please enter a word:");

        //Logic to remove \n from user input
        if (fgets(inputWord, MAX_WORD_LENGTH, stdin) != NULL){
            //Returns length of string
            size_t len = strlen(inputWord);
            if (len > 0 && inputWord[len-1] == '\n'){
                inputWord[--len] = '\0';
            }
        }
        printf("\n");

        //Break loop if input word is ***
        if (strcmp(inputWord, "***") == 0){
            magicWord = true;
            continue;
        }

        for (int i = 0; i < strlen(inputWord); i++){
            if (isalpha(inputWord[i]) || inputWord[i] == '\'' || inputWord[i] == '-'){
                inputWord[i] = tolower(inputWord[i]);
            } else {
                printf("That's an invalid input\n");
                goto loopStart;
            }
        }

        //Initialize the Node
        Node * wordNode = (Node *)malloc(sizeof(Node));
        if (wordNode == NULL){
            printf("Out of memory\n");
        }
        wordNode->word = (char *)malloc(sizeof(char) * MAX_WORD_LENGTH);
        if (wordNode->word == NULL){
            printf("Out of memory\n");
        }
        strcpy(wordNode->word, inputWord);

        if(listHead == NULL || strcmp(listHead->word, wordNode->word) >= 0){ // Character in left string greater than right string or both characters are the same
            wordNode->next = listHead;
            listHead = wordNode;
        } else {
            Node * iterHead = listHead;
            while(iterHead->next != NULL && strcmp(iterHead->next->word, wordNode->word) < 0){ // Character in right string greater than left string
                iterHead = iterHead->next;
            }
            wordNode->next = iterHead->next;
            iterHead->next = wordNode;
        }
    }

    //Logic to print items in linked list
    Node *temp = listHead;

    printf("All the entered words in order:\n");
    while (temp != NULL){
        printf("%s\n", temp->word);
        temp = temp->next;
    }

    // Logic to free the allocated memory
    Node * freeTemp = listHead;
    Node * freer;
    while (freeTemp != NULL){
        freer = freeTemp;
        freeTemp = freeTemp->next;
        free(freer->word);
        free(freer);
    }


}