/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmetzger <jmetzger@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/29 13:20:37 by jmetzger      #+#    #+#                 */
/*   Updated: 2023/09/06 22:00:58 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//     system("leaks -q philo");

/* main();
 *	The function validates the command-line arguments,
 *	performs some initialization steps, and executes different actions 
 *	based on the arguments' validity.
 */
int	main(int argc, char **argv)
{
	t_arg		arg;
	t_philo		*philos;
	t_fork		*forks;

	philos = NULL;
	forks = NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (!ft_check_input(argv))
			ft_error_msg("Invalid Input");
		if (!init_arg(&arg, argc, argv))
			ft_error_msg("Something went wrong with the initialization");
		if (!ft_threads(&arg, philos, forks))
			ft_error_msg("Something went wrong with the threads");
	}
	else
	{
		printf("Error:\n"GREEN BOLD"Try: "RESET"./philo "RED BOLD "<"RESET
			"number of philosophers"RED BOLD"> "RESET RED BOLD"<"RESET"time " 
			"to die"RED BOLD"> "RESET RED BOLD"<"RESET"time to eat"RED BOLD"> "
			RESET RED BOLD"<"RESET"time to sleep"RED BOLD"> "RESET RED BOLD"<"
			RESET"number of times each philosopher must eat"RED BOLD">\n"RESET);
	}
	return (0);
}





//	-------------------------------------------------------------------
//	-------------------------------------------------------------------

/*
Sure! I can explain what these functions do:

memset: This function is used to fill a block of memory with a particular value. It takes three arguments: a pointer to the memory block, the value to be set, and the number of bytes to be set.

printf: This function is used to print formatted output to the console or terminal. It takes a format string as its first argument, which can contain placeholders for variables, and additional arguments that correspond to the placeholders in the format string.

malloc: This function is used to dynamically allocate memory on the heap. It takes the number of bytes to allocate as its argument and returns a pointer to the allocated memory. It is commonly used to allocate memory for data structures such as arrays and structs.

free: This function is used to deallocate memory that was previously allocated using malloc or a related function. It takes a pointer to the memory block to be freed as its argument. Once memory is freed, it can no longer be accessed.

write: This function is used to write data to a file descriptor, typically used for writing to a file or a socket. It takes three arguments: the file descriptor to write to, a pointer to the data to be written, and the number of bytes to write.

usleep: This function is used to pause the execution of the program for a specified number of microseconds. It takes a single argument specifying the number of microseconds to sleep.

gettimeofday: This function is used to get the current time and date. It takes two arguments: a pointer to a timeval structure where the current time will be stored, and a timezone pointer (which is typically set to NULL).

pthread_create: This function is used to create a new thread of execution. It takes several arguments, including a pointer to a pthread_t variable to store the thread identifier, a pointer to a thread attribute structure (which can be NULL for default attributes), a start routine function that will be executed in the new thread, and an optional argument that can be passed to the start routine.

pthread_detach: This function is used to detach a thread, allowing it to run independently without being joined by another thread. It takes a single argument, the thread identifier.

pthread_join: This function is used to wait for a thread to terminate and retrieve its exit status. It takes two arguments: the thread identifier of the thread to join, and a pointer to a location where the exit status of the thread will be stored.

pthread_mutex_init: This function is used to initialize a mutex (short for mutual exclusion). A mutex is a synchronization primitive used to protect shared resources from simultaneous access by multiple threads. It takes a pointer to a mutex variable as its argument.

pthread_mutex_destroy: This function is used to destroy a mutex and release any associated resources. It takes a pointer to a mutex variable as its argument.

pthread_mutex_lock: This function is used to acquire a lock on a mutex. If the mutex is already locked by another thread, the calling thread will be blocked until the mutex becomes available.

pthread_mutex_unlock: This function is used to release a lock on a mutex, allowing other threads to acquire the lock. It takes a pointer to a mutex variable as its argument.

These functions are commonly used in C and C++ programming for various tasks, such as memory management, thread synchronization, and input/output operations.

Threads and mutexes are concepts related to concurrent programming and synchronization in multi-threaded environments. Let me explain each of them:

Threads:
Threads are the smallest units of execution within a program. They allow concurrent execution of different parts of a program, enabling multiple tasks to run simultaneously. Each thread has its own stack, program counter, and set of registers, but they share the same memory space with other threads within the same process.

Threads can be created, scheduled, and executed independently. They provide a way to achieve parallelism and utilize the capabilities of multi-core processors. By dividing a program's tasks into separate threads, different parts of the program can execute concurrently, potentially leading to improved performance and responsiveness.

Mutexes:
A mutex (short for mutual exclusion) is a synchronization primitive used to protect shared resources from simultaneous access by multiple threads. It provides a mechanism for mutual exclusion, ensuring that only one thread can access a critical section of code at a time.

When a thread wants to access a shared resource protected by a mutex, it first tries to acquire the mutex. If the mutex is not locked by another thread, it is successfully acquired by the current thread, which can then access the shared resource. If the mutex is already locked by another thread, the current thread will be blocked (put to sleep) until the mutex is released by the other thread.

Mutexes help prevent race conditions, where multiple threads access and modify shared data concurrently, leading to unpredictable and incorrect results. By enforcing exclusive access to critical sections of code, mutexes ensure thread-safe access to shared resources.

In the dining philosophers problem, mutexes are used to represent forks and protect them from concurrent access by neighboring philosophers. Each philosopher needs to acquire both the left and right forks (mutexes) to eat, and the use of mutexes ensures that only one philosopher can hold a fork at a time, avoiding conflicts and ensuring proper synchronization.

When the exit() function is called, it will terminate the program immediately without executing any further code or cleanup logic. In this case, the operating system will automatically reclaim the allocated memory and other system resources.

So, if you are calling exit() to terminate your program, you don't necessarily need to explicitly free the allocated memory using free(). However, it's generally considered good practice to free allocated memory and release resources before exiting, especially in larger programs or in cases where the program may be part of a larger system.

The expression (i + 1) % data->nb_philo calculates the index of the right fork for a philosopher with index i in a circular table of data->nb_philo philosophers.

In a circular table setting, each philosopher has a left fork and a right fork. The index of the right fork for a philosopher is calculated using the modulus operator %, which calculates the remainder of the division operation.

Here's a breakdown of how (i + 1) % data->nb_philo works:

i + 1: This expression increments the philosopher's index i by 1. It ensures that the right fork index is the next position clockwise from the philosopher's position.

% data->nb_philo: The modulus operator % calculates the remainder of the division of the value obtained in step 1 by data->nb_philo. This step ensures that the right fork index remains within the range of valid indices for the circular table.

For example, let's say data->nb_philo is 5, and we are calculating the right fork index for philosopher 2 (i = 2). The expression (2 + 1) % 5 would evaluate to (3) % 5, which results in 3. Therefore, in this case, the right fork index for philosopher 2 would be 3.

By using this expression, the code assigns the appropriate right fork position to each philosopher in a circular table, ensuring that the indices wrap around correctly.




// - One or more philosophers sit at a round table.
// There is a large bowl of spaghetti in the middle of the table.
// - The philosophers alternatively eat, think, or sleep.
// While they are eating, they are not thinking nor sleeping;
// while thinking, they are not eating nor sleeping;
// and, of course, while sleeping, they are not eating nor thinking.
// - There are also forks on the table. There are as many forks as philosophers.
// - Because serving and eating spaghetti with only one fork is very inconvenient, a
// philosopher takes their right and their left forks to eat, one in each hand.
// - When a philosopher has finished eating, they put their forks back on the table and
// start sleeping. Once awake, they start thinking again. The simulation stops when
// a philosopher dies of starvation.
// - Every philosopher needs to eat and should never starve.
// - Philosophers don’t speak with each other.
// - Philosophers don’t know if another philosopher is about to die.
// - No need to say that philosophers should avoid dying!

// - Global variables are forbidden!
// - Your(s) program(s) should take the following arguments:
// (number_of_philosophers), (time_to_die time_to_eat), (time_to_sleep),
// ([number_of_times_each_philosopher_must_eat])

//./philo 199 190 60 60 5 - die and print nothing after that
//./philo 4 200 20000 60 60 - has a 20second delay before exit
//./philo 3246784 190 60 60
//./philo 185 190 60 60
//./philo 199 185 60 60

In the printf format specifier %09ld, the 09 is a formatting directive that controls how the value of time_ms is displayed when it is printed.

Here's what each part of %09ld means:

%: This is the beginning of a format specifier in C and C++.
0: This is a flag that specifies that the value should be zero-padded.
9: This is the minimum field width, which means that the output should be at least 9 characters wide. If the value is less than 9 characters wide, it will be padded with leading zeros.
ld: This specifies that the argument to be printed is a long integer.
So, when you use printf("%09ld", time_ms), it will print the value of time_ms as a long integer with at least 9 characters, zero-padded if necessary. This can be useful for displaying fixed-width numbers, especially when working with time values or other numerical data where alignment and padding are important for readability.


/philo 5 800 200 200 7 | pbcopy

*/