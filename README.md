<h1 align="center">School 42 Philosophers</h1>

This repository contains my implementation of the Philosophers project from the 42 cursus. The goal is to solve the classic dining philosophers problem, learning about threads, mutexes, processes and semaphores.

<h2 align="center">
    <a href="#about">About</a>
    <span> · </span>
    <a href="#structure">Structure</a>
    <span> · </span>
<a href="#bonus">Bonus</a>
    <span> · </span>
    <a href="#requirements">Requirements</a>
    <span> · </span>
    <a href="#instructions">Instructions</a>
</h2>

## About

The Dining Philosophers problem is a classic synchronization challenge in computer science. It illustrates the issues of deadlock and resource starvation. The simulation involves several philosophers sitting at a round table who do nothing but think, eat, and sleep.

To eat, a philosopher needs two forks: the one on their left and the one on their right. The main challenge is to design a system where philosophers can eat without deadlocking (a situation where everyone is holding one fork and waiting for the other, so no one can eat) and without any philosopher starving.

The simulation ends if a philosopher dies of hunger or, optionally, if all philosophers have eaten a specified number of times.

You can find more details in the official project subject.

## Structure

The project is divided into two parts: a mandatory version using threads and mutexes, and a bonus version using processes and semaphores.

### Mandatory Part (Threads & Mutexes)

**Threads:** Each philosopher is represented by a separate thread (pthread_create).

**Forks as Mutexes:** Each fork is a mutex (pthread_mutex_t). To eat, a philosopher must lock both the mutex for their left fork and the mutex for their right fork.

**Deadlock Prevention:** A common deadlock scenario is when every philosopher picks up their left fork simultaneously and then waits indefinitely for the right one. My solution prevents this by making even-indexed philosophers pick up their left fork first, while odd-indexed philosophers pick up their right fork first. This breaks the circular dependency.

**Checker Thread:** A separate thread, the "checker," constantly monitors the state of all philosophers. It checks if any philosopher has died from starvation (time_to_die) or if the optional meal count has been reached. If a simulation-ending condition is met, it sets a flag to stop all philosopher threads gracefully.

**Data Race Protection:** All shared data, such as the last meal time or the meal counter, is protected by additional mutexes to prevent data races.

### Bonus Part (Processes & Semaphores)

**Processes:** Each philosopher is a separate process created with fork().

**Forks as a Semaphore:** All forks are represented by a single named semaphore (sem_t). The semaphore is initialized with the total number of forks. To eat, a philosopher must perform a sem_wait() operation twice to acquire two forks. When finished, they release them with two sem_post() calls.

**Synchronization:** Semaphores are used to protect shared resources and critical sections, such as printing to the console or accessing meal counters. Each philosopher process has its own checker thread to monitor its state.

**Process Management:** The main process is responsible for creating all philosopher processes and waiting for them to terminate. If one philosopher dies, the main process kills all other child processes to end the simulation.

## Requirements

To compile and run this project, you will need:

* A C compiler, such as gcc.

* The make utility.

* A system that supports POSIX threads (pthreads) and semaphores.

## Instructions
#### 1. Compile the Project

To compile the mandatory philo program:
```$ make```

To compile the philo_bonus program:
```$ make bonus```

#### 2. Clean Files

To remove the object files (.o):
```$ make clean```

To remove object files and the executables:
```$ make fclean```

To clean and recompile everything:
```$ make re```

#### 3. How to Run

Run the program with the required arguments:

```$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals_to_eat]```

Example:

```$ ./philo 5 800 200 200```

This will start a simulation with 5 philosophers, who will die if they don't eat within 800ms, and who take 200ms to eat and 200ms to sleep.

**Optional 5th Argument**
The fifth argument, [meals_to_eat], is optional. If it's provided, the simulation will stop once every philosopher has eaten at least that many times. If it's omitted, the simulation only stops when a philosopher dies.

Example with 5th argument:
```
$ ./philo 5 800 200 200 7
```
In this case, the simulation will end after each of the 5 philosophers has eaten 7 times.

#### 4. Checking for Data Races with Helgrind

To ensure the program is free of data races and other synchronization issues, you can use Helgrind, a tool from the Valgrind suite.

Run the program with Helgrind using the following command:
```
$ valgrind --tool=helgrind ./philo <args>
```
If the output shows no errors, your program is likely free of data races.
