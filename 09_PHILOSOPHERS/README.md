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

