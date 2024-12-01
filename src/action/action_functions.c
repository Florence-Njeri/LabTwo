#include "action_functions.h"

#include <stdio.h>
#include <stdlib.h>
void fnr(void) {
    puts("The door is locked.");
    return;
}

void fngrt(void) {
    puts("Opened.");
    puts("No root.");
    return;
}
// To remove the vulnerability of the unused fnR function being in the executable, we will use the command Make sure it's not in the compiled code using the flag -DIGNORE_FUNCTION
#ifndef IGNORE_FUNCTION
void fnR(void) {
    puts("Opened.");
    puts("Be careful, you are ROOT !\n");
    int value = system("/usr/bin/env PS1=\"SUPPOSED ROOT SHELL > \" python3 -c 'import pty; pty.spawn([\"/bin/bash\", \"--norc\"])'");
    exit(value);
}
#endif