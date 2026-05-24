*This project has been created as part of the 42 curriculum by ynabti.*

# Philosophers

## Description

Philosophers is a simulation of the classic *Dining Philosophers Problem*,
first formulated by Edsger Dijkstra in 1965. It is an introduction to
concurrent programming: creating threads, synchronizing them with mutexes,
and avoiding the two classic pitfalls of concurrency — **deadlocks** and
**data races**.

A number of philosophers sit around a round table. Between each pair of
neighbours lies a single fork. To eat, a philosopher must hold the two forks
on either side of them. They spend their life alternating between three
states: **eating**, **sleeping**, and **thinking**. A philosopher who does
not start eating within `time_to_die` milliseconds dies, and the simulation
ends.

In this version, each philosopher is a separate **thread**, and each fork is
protected by a **mutex**.

## Instructions

### Build

```sh
make        # compiles the program, produces ./philo
make clean  # removes object files
make fclean # removes object files and the binary
make re     # rebuilds from scratch
```

### Run

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Meaning (all times in milliseconds) |
| --- | --- |
| `number_of_philosophers` | number of philosophers, and also the number of forks |
| `time_to_die` | a philosopher dies if they do not start eating within this delay since their last meal |
| `time_to_eat` | how long a philosopher takes to eat (holding two forks) |
| `time_to_sleep` | how long a philosopher sleeps |
| `[number_of_times_each_philosopher_must_eat]` | optional: the simulation stops once every philosopher has eaten this many times |

### Examples

```sh
./philo 5 800 200 200       # nobody should ever die
./philo 5 800 200 200 7     # stops once each philosopher has eaten 7 times
./philo 1 800 200 200       # a single philosopher dies (only one fork)
./philo 4 410 200 200       # tight timing, nobody should die
```

### Output

Each state change is logged as `timestamp_in_ms philosopher_id state`:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## Technical choices

- **One thread per philosopher**; the main thread acts as the monitor that
  watches for death and for the optional meal goal.
- **Deadlock avoidance**: even-numbered philosophers pick up their right fork
  first while odd-numbered philosophers pick up their left fork first, which
  breaks the circular wait. Even philosophers also wait briefly at the start
  to desynchronize the table.
- **Race-condition avoidance**: shared state is protected by mutexes — one per
  fork, one for printing (so messages never overlap), one for the stop flag,
  and one per philosopher for their `last_meal` / `meals_eaten` counters.
- A custom `ft_usleep` sleeps in short steps and re-checks the clock, because
  the standard `usleep` may oversleep on a busy system.

## Resources

- E. W. Dijkstra, *Hierarchical Ordering of Sequential Processes* (1971) — the
  origin of the dining philosophers problem.
- `man pthread_create`, `man pthread_mutex_init`, `man gettimeofday`,
  `man usleep`.
- [The Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Use of AI

AI was used as a tutor to explain the underlying concepts (processes vs.
threads, mutexes, deadlocks, race conditions) and to review the structure of
the implementation and the README. 