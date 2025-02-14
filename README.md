# philosophers
Philosophers Project

Introduction

The Philosophers project is part of the 42 curriculum, designed to introduce students to concurrency, threading, and synchronization. It is based on the classic "Dining Philosophers" problem, which demonstrates resource sharing and deadlock scenarios in concurrent programming.

Objectives

Implement the Dining Philosophers problem using multithreading.

Manage shared resources using mutexes or semaphores.

Avoid deadlocks and race conditions.

Gain a deeper understanding of process synchronization.

Project Structure

📂 philosophers/
 ├── src/
 │   ├── main.c
 │   ├── utils.c
 │   ├── philosopher.c
 │   ├── simulation.c
 │
 ├── includes/
 │   ├── philosophers.h
 │
 ├── Makefile
 ├── README.md

Compilation

To compile the project, simply run:

make

This will generate the philosophers executable.

Usage

Run the program with:

./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

number_of_philosophers: Total number of philosophers (and forks).

time_to_die: Time (in ms) a philosopher can live without eating.

time_to_eat: Time (in ms) a philosopher takes to eat.

time_to_sleep: Time (in ms) a philosopher takes to sleep.

[number_of_times_each_philosopher_must_eat]: (Optional) Simulation stops when each philosopher has eaten this many times.

Example:

./philosophers 5 800 200 200

Key Features

Thread management: Each philosopher runs as a separate thread.

Mutex synchronization: Forks (chopsticks) are protected with mutexes to avoid race conditions.

Avoiding deadlocks: Implemented using proper locking order or a monitoring system.

Logging: Real-time logging of philosopher actions (eating, sleeping, thinking, death).

Rules

Each philosopher can only pick up the forks next to them.

They must eat before time_to_die expires.

After eating, they put down the forks and sleep.

The simulation ends when all philosophers have eaten the required times (if specified) or one dies.

Handling Edge Cases

Philosophers should not interfere with each other's operations.

All memory allocations and thread creations are managed properly to prevent leaks.

If only 1 philosopher is present, the program should handle it correctly.

Additional Notes

The program follows 42's Norminette coding style.

Works on macOS and Linux environments.

Requires pthread library for threading support.

Author

Habip Yalçınkaya
