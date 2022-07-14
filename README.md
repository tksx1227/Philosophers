# Philosophers
This program implements the [Dining Philosophers Problem](https://ja.wikipedia.org/wiki/%E9%A3%9F%E4%BA%8B%E3%81%99%E3%82%8B%E5%93%B2%E5%AD%A6%E8%80%85%E3%81%AE%E5%95%8F%E9%A1%8C).

In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

## Description
This program implements the "Dining Philosophers Problem" in two different ways.

One is to represent the philosophers as threads and use mutexes for exclusion control.

The other is to represent each philosopher as a process and use semaphores for exclusion control.

Each philosopher repeats the three actions of "eat," "sleep," and "think," and the program terminates when any one philosopher dies or when all philosophers have met a certain number of meals.

Programs implemented in threads: `philo/`

Programs implemented in processes: `philo_bonus/`

## Usage

After generating the binary file with make, the program is executed.

```bash
$ make
```

This program take the following arguments:

- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die (in milliseconds)`: If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat (in milliseconds)`: The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep (in milliseconds)`: The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat (optional argument)`: If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

Arguments are specified according to this format.

```bash
$ ./bin/philo <NUMBER_OF_PHILOSOPHERS> <TIME_TO_DIE> <TIME_TO_EAT> <TIME_TO_SLEEP> [NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT]
```

## Example

An example of program execution is shown below.

In this example, the philosopher does not die, and the program ends when everyone's meal count has met 10.

```bash
$ ./bin/philo 4 800 200 200 10

1657758799657 3 has taken a fork
1657758799657 3 has taken a fork
1657758799657 3 is eating
1657758799657 1 has taken a fork
1657758799657 1 has taken a fork
1657758799657 1 is eating
1657758799857 3 is sleeping
1657758799857 2 has taken a fork
1657758799857 2 has taken a fork
1657758799857 2 is eating
1657758799857 4 has taken a fork
1657758799857 4 has taken a fork
1657758799857 4 is eating
1657758799857 1 is sleeping
1657758800057 3 is thinking
1657758800057 4 is sleeping
1657758800057 1 is thinking
...
```

In this example, one philosopher dies, at which point the program ends.

```bash
$ ./bin/philo 5 500 250 250

1657759158958 1 has taken a fork
1657759158958 1 has taken a fork
1657759158958 1 is eating
1657759158958 3 has taken a fork
1657759158958 3 has taken a fork
1657759158958 3 is eating
1657759158958 5 has taken a fork
1657759159208 3 is sleeping
1657759159208 4 has taken a fork
1657759159208 1 is sleeping
1657759159208 5 has taken a fork
1657759159209 5 is eating
1657759159209 2 has taken a fork
1657759159209 2 has taken a fork
1657759159209 2 is eating
1657759159458 2 died
```

A simple test case is defined in the Makefile, which can also be used.

```bash
$ make test1
$ make test2
$ make test3
$ make test4
$ make test5
```
