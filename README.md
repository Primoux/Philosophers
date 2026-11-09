# Philosophers

The dining philosophers problem, implemented with POSIX threads and mutexes. A 42 Common Core project about concurrency: every philosopher is a thread, every fork is a mutex, and nobody may starve.

## Build

```bash
cd philo && make
```

## Usage

```bash
./philo <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals_required]
```

```bash
./philo 5 800 200 200      # runs until a philosopher dies
./philo 5 800 200 200 7    # stops once everyone has eaten 7 times
```

All times are in milliseconds. The simulation logs every state change with a timestamp:

```
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
```

A death is reported within 10 ms of happening, and no message may be printed after it.

## The problem

Each philosopher alternates between eating, sleeping and thinking. Eating needs both neighbouring forks, so adjacent philosophers compete for the same mutex. Two failure modes have to be avoided:

- **deadlock** — everyone grabs their left fork and waits forever for the right one
- **starvation** — a philosopher never gets a turn and dies while others keep eating

Fork acquisition order therefore depends on the philosopher's position, which breaks the cycle of dependencies that causes the deadlock.

## Layout

```
philo/src/parsing/       argument validation
philo/src/init/          philosopher and simulation setup
philo/src/exec/          the thread routine, the monitor, timing helpers
philo/src/shared_state/  state guarded by mutexes
philo/src/debug/         simulation dump, for development
```

Shared state (meal counts, the death flag) is only ever read or written under its mutex — that discipline is the whole project.
