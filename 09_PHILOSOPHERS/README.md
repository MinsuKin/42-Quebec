<h1 align="center">
	PHILOSOPHERS
</h1>

##  Summary

Solution of classical synchronization problem about
[dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
where each philosopher is a thread and mutexes are used to prevent deadlocks.

External functions: `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`

Code written in accordance with **42 C** coding style.

##  Usage

Run `make` in the root of the projet and launch as follows:

    ./philo <philo_nb> <time_die> <time_eat> <time_slp> [ <must_eat> ]

- `philo_nb` -- the number of philosophers and forks.
- `time_die` -- A philosopher dies if he doesn't start to eat `time_die` ms
  after **the beginning of his last meal** (or the simulation).
- `time_eat` -- The time it takes for a philosopher to eat.
- `time_slp` -- The time it takes for a philosopher to sleep.
- `must_eat` -- (optional) simulation stops if all philosophers ate at least
  such amount of times.

- IF NOT `must_eat` THEN simulation stops at first death.
- CANNOT test `philo_nb > 200`.

Example of a dinner that should never stop:

    ./philo 4 410 200 200
            +-|---|---|-- philo_nb
              +---|---|-- time_die
                  +---|-- time_eat
                      +-- time_slp

***Makefile rules***

- `make` -- compiles philo.
- `make clean` -- deletes object files.
- `make fclean` -- deletes object files and philo.
- `make re` -- `fclean` + `make`.

## Peer Evaluation(Code Review)

### As a Interviewee

#### Second attempt
<img width="526" alt="스크린샷 2022-12-29 10 23 12" src="https://user-images.githubusercontent.com/50944735/209974043-70506da4-f076-4547-8d8d-d8d6a055f11e.png">

#### First attempt
<img width="521" alt="스크린샷 2022-12-29 10 22 53" src="https://user-images.githubusercontent.com/50944735/209974018-edbee21a-efae-46e4-a07c-b3a314c5ad48.png">

### As a Interviewer
<img width="530" alt="스크린샷 2022-12-29 10 24 09" src="https://user-images.githubusercontent.com/50944735/209974156-518b4f82-6aef-49cc-acfd-77a0e8f1e778.png">
<img width="535" alt="스크린샷 2022-12-29 10 25 11" src="https://user-images.githubusercontent.com/50944735/209974299-866f42bb-0120-4361-948a-1c43204648a2.png">
<img width="517" alt="스크린샷 2022-12-29 10 25 44" src="https://user-images.githubusercontent.com/50944735/209974339-7e832bd8-76fa-4063-a9f4-e9362f6e8467.png">
