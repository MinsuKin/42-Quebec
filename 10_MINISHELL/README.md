<h1 align="center">
	MINISHELL
</h1>

##  Summary

This program is the implementation of shell program referenced by [Bash](https://en.wikipedia.org/wiki/Bash_(Unix_shell)).

## To compile

Given `Makefile` which provides the common rules (all, clean, fclean, re). After compiling all of the source codes, the program file will be generated.
> make all

## To execute

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
<img width="515" alt="Screen Shot 2023-03-16 at 5 45 07 PM" src="https://user-images.githubusercontent.com/50944735/225759733-9356cbcc-82dd-4c40-85f3-788372371f8b.png">
<img width="511" alt="Screen Shot 2023-03-16 at 5 45 35 PM" src="https://user-images.githubusercontent.com/50944735/225759736-e01a8b8c-0b89-4dac-829b-d174fbc40050.png">
<img width="508" alt="Screen Shot 2023-03-16 at 5 45 50 PM" src="https://user-images.githubusercontent.com/50944735/225759739-4a53ebf7-24ad-4abb-a3ef-7ad717182506.png">
<img width="519" alt="스크린샷 2022-12-29 10 20 44" src="https://user-images.githubusercontent.com/50944735/209973752-fb5bc599-549b-4ca9-9799-d18b88ec432a.png">

# minishell : 나만의 쉘 만들어보기(첫 팀프로젝트)

## 배우는 것

> 자신이 맡은 파트가 아니어도 충분히 설명할 수 있을 정도로 팀원과 같이 고민하고 공부해봅시다.
파싱과 실행 모두 공부할 수 있는 부분이 많습니다.
> 
- 팀프로젝트 일정 관리
- 팀워크(커뮤니케이션, 의견 조율, 설득 및 이해)
- 프로젝트를 어느 정도 깊이까지 할지 설정하기
- git 을 통한 팀 작업
- 쉘 분석 및 고찰
- 복잡한 문자열 파싱 (LALR)
- 멀티프로세싱
- 파일 디스크립터 관리
- 파이프, 리다이렉션, 환경변수, 시그널 활용 (2서클의 pipex, minitalk 활용)
- 컴파일러 또는 인터프리터 동작 방식

##
