<h1 align="center">
	MINISHELL
</h1>

##  Summary

This program is the implementation of shell program referenced by [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

## How to compile the implemented program?

Given `Makefile` which provides the common rules (all, clean, fclean, re). After compiling all of the source codes, the program file will be generated.
> make all

## How to execute the implemented program?

Prompt of this shell is accordance with name of the binary file on the initial execution.
> ./minishell

##  Features

1. Several builtin commands have been implemented. (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
2. All other commands run by `execve` function in the child process.
3. Multi-Piping, Multi-Redirections.
4. Heredoc `<< [delimiter]`.
5. The exit status of the last executed command `$?` is implemented(It can be  with `echo` or `expr`).
6. Ctrl + C , Ctrl + D , Ctrl + \ are implemented as same as Bash.
7. Readline library has been used to produce a bash-like shell.
8. History management is based on the `add_histroy` function. Thus, arrow keys on the keyboard can be used.

## Peer Evaluation(Code Review)

### As a Interviewee

#### Fourth attempt
<img width="520" alt="스크린샷 2022-12-29 10 16 21" src="https://user-images.githubusercontent.com/50944735/209973250-a29cf996-772f-4cbb-b4fb-c871c6b4c9b4.png">

#### Third attempt
<img width="526" alt="스크린샷 2022-12-29 10 17 37" src="https://user-images.githubusercontent.com/50944735/209973402-087f5833-b990-4a3d-a6a7-af8241007d05.png">

#### Second attempt
<img width="521" alt="스크린샷 2022-12-29 10 17 43" src="https://user-images.githubusercontent.com/50944735/209973411-3f4b7947-5bbe-42b7-b016-7b1574771529.png">

#### First attempt
 <img width="520" alt="스크린샷 2022-12-29 10 17 50" src="https://user-images.githubusercontent.com/50944735/209973420-3424f856-15fc-475f-b9b1-1945d47d83bf.png">

### As a Interviewer
<img width="519" alt="스크린샷 2022-12-29 10 20 44" src="https://user-images.githubusercontent.com/50944735/209973752-fb5bc599-549b-4ca9-9799-d18b88ec432a.png">
