---
title: The Bad Program
subtitle: Lab Two
author: Lydiah Florence Njeri and Chinya Tsai
date: 27 November 2024
geometry: top=1.5cm,left=2cm,right=2cm,bottom=2cm
license: CC0 1.0
numbersections: true
highlightstyle: pygments
header-includes:
    - \usepackage{package_deps/comment}
    - \usepackage{multicol}
    - \usepackage{lmodern}
    - \newcommand{\hideFromPandoc}[1]{#1}
    - \hideFromPandoc{
        \let\Begin\begin
        \let\End\end
      }
colorlinks: true
lang: en-GB
---

<!-- Remplacer 'en-GB' par 'fr' pour un document en français -->

<!-- 
	Markdown is a minimalistic HTML-based language
	
	The restricted set of functionalities is BY DESIGN,
	It is useful in any course context to restrict report formatting.
	You SHALL NOT try to circumvent how it works. You must CONFORM to the format. 
	Any text editor will work, since Markdown is just plain text.
	
	Visual Studio Code has nice basic support and previewing capabilities,
	and support several extensions that enhance the writing experience.
	You are stroongly advised to use them.

	The template is commented to guide you through the format,
	but you should *read* the comments to understand.

	Note that line breaks do not exist. You cannot skip a line, 
-->

<!-- Sections are denoted with a "#" at the very beginning of the line. Do not number the sections! Pandoc will handle that part -->
# Introduction

# Context

## Analysis Protocol (Report the threats identified, ideas, assessment method…),
1. Manually analyze the source code
I manually analyzed te code in `action_functions.c`, `validations_functions.c` to try and identify what the vulnerabilities in the code are. 
2. Manually analyze the Makefile
I then manually analyzed the `Makefile` to try and identify what the compiler flags and linking options were used during the compilation of the program that we did in Lab 1.
## Legacy Options [, i.e. begin by filling “ LEGCFLAGS = ” and “ LEGLDFLAGS = ” in the original Makefile,]
## Explain what are those options and what they do,
## Explain which should be removed and how it will enhance security,
## Find et report the problematic lines in the source code,

## How to patch the vulnerabilities above

The source code below is the patched code of `validation_functions.c`

```C
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

```

The code above does the following:
1. `char *buffer = (char *)malloc(20);` will dynamically assign memory to our buffer at run time. This allows memory to be allocated at random addresses
 when ASLR is active.
2. `fgets(buffer, 20, stdin)`. `fgets` is more secure compared to `scanf`.  The `fgets` function ensures that no more than 19 characters are read, preventing buffer overflow when saving the input to `buffer` and leaving space for the null terminator.
3. `return (strcmp(buffer, "Y") == 0) || (strcmp(buffer, "y") == 0)`. The initial return function had two issues. First, it used the && comparator, which meant that if the user inputs "Y", the comparison strcmp(buffer, "y") would always evaluate to 1, causing the return to fail. This bug was fixed by changing the comparator to ||. Second, we didn't evaluate the return value of strcmp(buffer, "Y"), so we introduced the expected result into the evaluation.

The source code below in `validation_functions.c` is is vulnerable because we have the `fnR` function that give the users system root access on the terminal which is a priviledge escalation. The solution to this problem would be to either delete the code as its unused or excempt it from the executabe file during compilation. 

```C
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

```

The code snippet above shows the solution which adds the `ifdef IGNORE_FUNCTION` where `IGNORE_FUNCTION` is the flag we will pass to the compiler using the `-D` flag. This is the complete compilation command to use `-DIGNORE_FUNCTION`

In the `main.c` function, the `atoi()` function, which converts user input to an integer, has been deprecated. It also does not check for errors before converting the string to an integer. In the `door-locker` program, if the user inputs two different strings as input, the door would open. This vulnerability exists because we are using `atoi()`. To fix this vulnerability, we replaced the `atoi()` function with the `strtol()` function, which will throw an error if the input isn't a valid number, as shown in the patched code below.

```C
#include <stdio.h>
#include <stdlib.h>

#include "action_functions.h"
#include "validation_functions.h"

int main(int argc, char * argv[]) {
    int check;
    int in0;
    int in1;

    if (argc == 3) {
        check = validate(argv);
        if (check == 0) {
            puts("\nChecking values");
            // Use strtol with error checking since atoi is deprecatted
            in0   = strol(argv[2]);
            in1   = strol(argv[1]);
            check = fnchck(in1, in0);
            if (check == 0xf) {
                fngrt();
            } else {
                fnr();
            }
        } else {
            fnr();
        }
        check = 0;
    } else {
        puts("Usage : client <chiffre0> <chiffre1>");
        check = 1;
    }
    return check;
}
```

## How to avoid these mistakes in future.
The vulnerabilities identified and addressed in the source code highlight some of the security concerns we can introduce to our code. Below is a detailed plan of future the software development process to mitigate such mistakes before the code is released:
**Use Secure Coding Practices**

- Always validate and sanitize user input to prevent unexpected behavior.
- Use safer alternatives like fgets instead of gets or scanf to avoid buffer overflows.
- Dynamically allocate memory using `malloc` only when necessary.
- Always check for successful allocation using malloc or calloc and free the memory after use to prevent memory leaks in the code.

**Ensure Code Review and Auditing**

- Peer review all new code for adherence to security guidelines.
- Use static analysis tools (e.g., SonarQube, Coverity) to identify vulnerabilities such as buffer overflows or use of unsafe functions.
- Periodically review older code to find unused functions, insecure patterns, and deprecated APIs, functions and dependencies and update them to the recommended functions.
- Remove unused functions or ensure they are excluded from compilation (e.g., through macros using `ifdef`).

**Enable Compiler Flags for Security**

- Use flags like `-D_FORTIFY_SOURCE=2` to add runtime checks for common string format vulnerabilities.
- Employ `-DIGNORE_FUNCTION` to exclude unused functions from the build.
- Use `-fstack-protector-all` flag to enables stack protection, including shadow
 stacks, for all functions.

**Use Linker Flags**
- To ensure the stack is non-executable (a key part of preventing exploit execution), you should also link with the `-z noexecstack` flag to mark the stack as non-executable using `gcc −o my_program my_program.c −fstack−protector−all −fcf−protection − D`

# Conclusion

```{=latex}
\end{verbatim}
\end{comment}
```

