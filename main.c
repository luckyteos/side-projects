#include <stdio.h>
#include <string.h>
/* Pointer Play
   Author: Jmteo
   Using Examples from Programiz
 */

void swapNumbers(int *n1, int *n2);

int main() {

    // Array initialization
    double marks[5] = {70.0, 84.0, 63.0, 45.0, 98.0};
    double * markP = &marks[0];
    printf("%lf\n\n", *(markP + 4));

    int n1, n2;

    // Initializing Number Values
    n1 = 10;
    n2 = 40;

    swapNumbers(&n1, &n2);

    printf("%d\n", n1);
    printf("%d\n\n\n", n2);

    // Strings
    char myString[50];

    printf("What's your favourite drink \n");

    // This gets string from user
    fgets(myString, sizeof(myString), stdin);

    //Normal way of Printing a string
    puts(myString);

    //Pointers Works on Strings too
    char * strPtr;
    strPtr = &myString[0];

    int i;

    //Printing a string with a pointer
    for (i = 0; i < strlen(myString); i++) {
        printf("%c", *(myString+i));
    }

    printf("\n");

    int pos;

    printf("Specify string position: ");

    scanf("%d", &pos);

    //Printing a single char from string, in this case its the second letter
    printf("Letter at %d is: %c\n", pos, *(strPtr+pos));
}

void swapNumbers(int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
