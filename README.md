# The Bad Program

## Instructions

In this lab, you will have to use your knowledge of secure programming, of the C language, the information gathered during the first lab, and any tool you see fit.  
You will be given access to the source code of the program from Project Lab 1 (*The unknown program*).

None of the previous attacks should even crash the program.  
You should conceptualize, design, and at best, implement mechanisms preventing the same mistakes.  
For instance, the program should be resistant to fuzzing attack.  
Your tasks^[These tasks **are not** questions. The report should be structured.]:

- Explain your analysis protocol (Report the threats identified, ideas, assessment method...)
- Find the legacy options, i.e. begin by filling `LEGCFLAGS =`{.makefile} and `LEGLDFLAGS =`{.makefile} in the original Makefile
- Explain what are those options and what they do
- Explain which should be removed and how it will enhance security
- Find and report the problematic lines in the source code
- Patch the vulnerabilities in the code, and provide the patch with comments
- Report on future processes that may prevent such mistakes

On Moodle, you will find a TGZ archive named `door-locker.tar.gz`.  
This is the *"door locker"* project.  
You will have to extract the project somewhere with:

```bash
tar -xvzf door-locker.tar.gz
```

Then you can begin working on it.  
You must write a patch and a report addressing the points above.  
Again, to help you choose the level of language, a bit of context is given in the next section.

The report must be a PDF file type created using Markdown (like the current document^[Ignore fancy `<...>`{.html} and things related to `minted`{.html}, it is `\LaTeX{}`{=latex} type setting]) named `group_x_y_report.pdf`.  
You will find a presentation of Markdown [here](https://www.markdownguide.org/getting-started/), and explanations on the syntax [here](https://www.markdownguide.org/basic-syntax/).  
A very bare-bones template can be found [here](https://forgens.univ-ubs.fr/gitlab/moniere/template-markdown-pandoc)^[https://forgens.univ-ubs.fr/gitlab/moniere/template-markdown-pandoc] and should be renamed `group_x_y_report.md` (but you may use your own file as well).  
Then, use `pandoc` to convert the file, using:

```bash
pandoc --pdf-engine=pdflatex --standalone --to pdf \
    -o group_x_y_report.pdf group_x_y_report.md
```

The patch must be an all-in-one text file named `group_x_y_patch.txt`.  
To create it on Linux, if you have initialized a git repository in the project, you can do:

```bash
cd path/to/project
git diff --patch initialcommit > group_x_y_patch.txt
```

If you have not used git, you can still do a `diff` of the initial project with your modified version.  
Supposing you have both the modified project `mods` and the original one `orig` alongside, you can do:

```bash
cd path/to/parent/of/origNmods
diff --unified --recursive mods orig > group_x_y_patch.txt
```

On Moodle, you have access to a *Lab 2 assignment*, where you can provide the report alongside the patch to us.

This lab is graded. The clarity of the report and its structure are evaluated, as well as the content itself.  
The patch quality and the explanations about the fixes are both evaluated.

<!-- \clearpage -->

## The Lore

*Note that the lore **is not** directions and **shall not** be substituted to previous directions.*

You are a C developer in a company in the field of home automation, in the software security division.  
You have just completed the last task your manager gave you.

An e-mail arrives, from this manager:

> Dear \<insert your name\>,
>
> I received your report. I have not read it yet, but we have found the original project of the program.<br>
> Patch it as you see fit, and send me the patch.
> Oh, and we still need the legacy version of the program. So, you must find a way to replicate it, bugs included.
>
> Since it will be presented to the division director, I also need a formal report, introduction, context, and so on.
>
> I will need that as soon as possible, thank you.
>
> Professionally,<br>
> Ms. Agnes AGERSON, Senior Security Engineer

## Nota Bene

1. Markdown introduction: [https://www.markdownguide.org/getting-started/](https://www.markdownguide.org/getting-started/)
2. Markdown syntax: [https://www.markdownguide.org/basic-syntax/](https://www.markdownguide.org/basic-syntax/)

