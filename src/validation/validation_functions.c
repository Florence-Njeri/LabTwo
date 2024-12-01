#include <stdio.h>
#include <string.h>

#include "validation_functions.h"

int fnchck(int a, int b) {
    int check;

    if (b == a) {
        puts("Valid access.");
        check = 0xf;
    } else {
        check = 0;
    }
    return check;
}

int validate(char * argv[]) {
    // Use malloc to dynamically allocate memory at runtime
    char *buffer = (char *)malloc(20);
     
    printf("You entered %s and %s. \nDo you agree ? (Y,n):\n", argv[1], argv[2]);
    // Use fgets to read the user input since it only writes upto the buffer size thus preventing buffer overflow
    fgets(buffer, 20, stdin)

    // Free the allocated memory
    free(buffer)
    // Return 0 if buffer == "Y" or buffer == "y"
    return (strcmp(buffer, "Y") == 0) || (strcmp(buffer, "y") == 0);
}