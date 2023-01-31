# IPC pipe in Unix

### RUN this command [**here**](https://replit.com/@MinsuKin/pipex#outfile)!

```./pipex infile "ls -al" "cat -e" outfile```

#### And have a look at the output in outfile.
```cat outfile```

This program will behave the same as

```< infile cmd1 | cmd2 > outfile```
# pipex : pipe를 통한 프로세스 간 통신

## 배우는 것

- 프로세스 간 통신(Inter-Process Communication, IPC), 이때 OS가 하는 일
- 파이프 동작 원리 이해 및 구현, STDIN - STDOUT 이해
- 부모 - 자식 프로세스, 좀비 프로세스, 고아 프로세스
- fork / exec 동작 이해
- 리다이렉션, 히어독
- 환경변수
- 파일 디스크립터
- 병렬 프로그래밍
