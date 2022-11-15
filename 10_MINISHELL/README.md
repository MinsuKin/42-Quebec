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

## Which are the allowed external functions?

* For the Mandatory
1. `open` on \<unistd.h>
2. `close` on \<unistd.h>
3. `read` on \<unistd.h>
4. `write` on \<unistd.h>
5. `unlink` on \<unistd.h>
6. `fork` on \<unistd.h>
7. `dup` on \<unistd.h>
8. `dup2` on \<unistd.h>
9. `pipe` on \<unistd.h>
10. `execve` on \<unistd.h>
11. `getcwd` on \<unistd.h>
12. `chdir` on \<unistd,h>
13. `isatty` on \<unistd.h>
14. `ttyname` on \<unistd.h>
15. `ttyslot` on \<unistd.h>
16. `errno` on \<errno.h>
17. `printf` on \<stdio.h>
18. `strerror` on \<string.h>
19. `malloc` on \<stdlib.h>
20. `free` on \<stdlib.h>
21. `getenv` on \<stdlib.h>
22. `exit` on \<stdlib.h>
23. `kill` on \<signal.h>
24. `signal` on \<signal.h>
25. `opendir` on \<dirent.h>
26. `closedir` on \<dirent.h>
27. `readdir` on \<dirent.h>
28. `tcgetattr` on \<term.h>
29. `tcsetattr` on \<term.h>
30. `tgetent` on \<term.h>
31. `tgetflag` on \<term.h>
32. `tgetnum` on \<term.h>
33. `tgetstr` on \<term.h>
34. `tgoto` on \<term.h>
35. `tputs` on \<term.h>
36. `ioctl` on \<sys/ioctl.h>
37. `wait3` on \<sys/wait.h>
38. `wait4` on \<sys/wait.h>
39. `wait` on \<sys/wait.h>
40. `waitpid` on \<sys/wait.h>
41. `stat` on \<sys/stat.h>
42. `lstat` on \<sys/stat.h>
43. `fstat` on \<sys/stat.h>
44. `readline` on \<readline/readline.h>
45. `rl_on_new_line` on \<readline/readline.h>
46. `rl_replace_line` on \<readline/readline.h>
47. `rl_redisplay` on \<readline/readline.h>
48. `add_history` on \<readlien/history.h>

# 5. Features

1. Several builtin commands have been implemented. (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
2. All other commands run by `execve` function in the child process.
3. Multi-Piping, Multi-Redirection is ok.
4. Heredoc `<< [delimiter]`.
5. The exit status of the last executed command `$?` is implemented(It can be used with `echo` or `expr`).
6. Ctrl + C , Ctrl + D , Ctrl + \ are implemented as same as Bash.
7. Readline library has been used to produce a bash-like shell.
8. History management is based on the `add_histroy` function. Thus, arrow keys on the keyboard can be used.

