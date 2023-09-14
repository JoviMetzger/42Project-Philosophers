# 🍴 Philosophers 🍴

## 🍝 Problem Statement
Imagine a round table with several philosophers, each with a bowl of spaghetti in front of them. These philosophers alternate between eating, thinking, and sleeping, with a set of rules governing their behavior:

- While a philosopher is eating, they cannot think or sleep.
- While thinking, they cannot eat or sleep.
- While sleeping, they cannot eat or think.
- Philosophers need to eat regularly and should never starve.
- They don't communicate with each other or know when another philosopher is about to die.
- Additionally, there are forks on the table, one for each philosopher. <br>
  To eat, a philosopher must use both their left and right forks.

**Problem Solving** <br>
To solve the Dining Philosophers problem, philosophers use forks as a shared resource. They must acquire the mutex associated with each fork before picking them up to avoid conflicts with other philosophers. If a philosopher can't acquire both forks, they must release any acquired forks and retry later. This ensures that each philosopher can eat without interfering with others.

## 🍝 Understanding Key Concepts
Before we delve into the solution, let's clarify some key concepts:

**Fork**: <br>
In Unix-like operating systems, a fork is a system call that creates a new process by duplicating an existing one. The new process is referred to as the child process, while the original process is the parent process. This allows multiple processes to run independently, sharing code and memory space.

**Thread**: <br>
A thread is the smallest unit of execution within a process. Threads share the same memory space and can communicate efficiently, making them suitable for concurrent tasks within a single program.

**Mutex (Mutex Lock)**: <br>
A mutex (short for "mutual exclusion") is a synchronization mechanism used to ensure that only one thread can access a shared resource or critical section of code at a time. It prevents data races and maintains data integrity by allowing threads to take turns accessing shared resources.

![image](<img width="1222" alt="Screen Shot 2023-09-14 at 4 08 41 PM" src="https://github.com/JoviMetzger/42Project-Philosophers/assets/117259075/4154dedb-d487-496b-a841-fc66cb9aedf4">
)

## 🍝 Helpful Tips and Tricks

### Printf Format Specifier %09ld.
In C programming, you can use the format specifier %09ld to format output. Here's what each part of %09ld signifies:

`%`: Marks the beginning of a format specifier in C. <br>
`0`: This flag specifies zero-padding for the value. <br>
`9`: The minimum field width, ensuring the output is at least 9 characters wide. If the value is shorter, it will be filled with leading zeros. <br>
`ld`: This denotes that the argument to be printed is a long integer. <br>

For example, when you use **printf("%09ld", time_ms)**, it will print the time_ms value as a long integer with at least 9 characters, zero-padded if needed. This is particularly useful when dealing with time values or other numerical data where alignment and padding enhance readability.

### Quick Copy-Paste Shortcut
To copy and paste content without manually highlighting it, you can use the following command:

`./philo 5 800 200 200 7 | pbcopy`

This command efficiently copies the output directly into your clipboard buffer, making it a convenient way to capture and paste content.

## 🍝 Installation

To execute the program, follow the steps below:

1. Compile the game by running the following command:
```C
$ make
```
2. Finally, execute the program using the following command: <br>
./philo **<**number_of_philosophers**>** **<**time_to_die**>** **<**time_to_eat**>** **<**time_to_sleep**>** *[number_of_times_each_philosopher_must_eat]*; <br>
*(number_of_times_each_philosopher_must_eat) is optinal* / *time is im ms*;
```C
$ ./philo  5 800 200 200
```
OR
```C
$ ./philo  5 800 200 200 7
```

## 🍝 Some Test
✅ `./philo  5 800 200 200`    No one should die. <br>
✅ `./philo  5 800 200 200 7`  No one should die, and simulation should stop after 7 eats. <br>
✅ `./philo  4 410 200 200`    No one should die. <br>
✅ `./philo  4 310 200 100`    One philo should die. <br>
✅ `./philo  1 800 200 200`    Philo should die. <br>
✅ `./philo  1 800 20000 200`  Philo should die, NO 20s delay before exit. <br>
✅ `./philo  5 800 0 200`      Should error. <br>
✅ `./philo  5 800 200 200 0`  Should error. <br>
✅ `./philo  5 800 -200 200`   Should error. <br>
✅ `./philo  5 800 2i0 200`    Should error. <br>

## 🍝 Resources

- [The Dining Philosopher's Problem](https://medium.com/swlh/the-dining-philosophers-problem-bbdb92e6b788)
- [Mutexes and fork()ing](https://brauner.io/2018/03/04/locking-in-shared-libraries.html)
- [Threads, Mutexes and Concurrent Programming in C](https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/)
- [Visualizer](https://nafuka11.github.io/philosophers-visualizer/)
