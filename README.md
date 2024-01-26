<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/philosophers-light.png?raw=true#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/philosophers-dark.png?raw=true#gh-dark-mode-only" alt="Banner (oscuro)" />
    <br>
   In this project, you will learn the basics of threading a process.
You will see how to create threads and you will discover mutexes.
    <br>
    <a href='https://profile.intra.42.fr/users/alvega-g' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/>
    </a>
    <img src="https://img.shields.io/badge/score- WIP%20%2F%20100-success?color=%2312bab9&style=flat" />
    <img src="https://wakatime.com/badge/user/018cd069-7ab6-4658-9d62-78d9b3970dd2/project/018d45ac-78b5-473f-a3a8-a29d8650a45a.svg" alt="Tiempo" />
</div>

# Mandatory part

<table>
  <tr>
    <th>Program name</th>
    <td><em>philo</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, <code>*.h</code>, <code>*.c</code> in directory philo/</td>
  </tr>
  <tr>
	<th>Makefile</th>
	<td><em>NAME</em>, <em>all</em>, <em>clean</em>, <em>fclean</em>, <em>re</em></td>
  </tr>
  <tr>
    <th>Arguments</th>
    <td><code>number_of_philosophers</code> <code>time_to_die</code> <code>time_to_eat</code> <code>time_to_sleep</code> <code>[number_of_times_each_philospher_must_eat]</code></td>
  </tr>
  <tr>
    <th>External functions</th>
    <td> <code>memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock</code>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>No</td>
  </td>
  <tr>
    <th>Description</th>
    <td>Philosophers with threads and mutexes</td>
  </tr>
</table>

## Overview

Here are the things you need to know if you want to succeed this assignment:
- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively <b>eat</b>, <b>think</b>, or <b>sleep</b>.<br>
While they are eating, they are not thinking nor sleeping;<br>
while thinking, they are not eating nor sleeping;<br>
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are <b>as many forks as philosophers</b>.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

## Global rules

You have to write a program for the mandatory part and another one for the bonus part
(if you decide to do the bonus part). They both have to comply with the following rules:
- Global variables are forbidden!
- Your(s) program(s) should take the following arguments:
<code>number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]</code>
	- <code>number_of_philosophers</code>: The number of philosophers and also the number
of forks.
	- <code>time_to_die</code> (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
	- <code>time_to_eat</code> (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
	- <code>time_to_sleep</code> (in milliseconds): The time a philosopher will spend sleeping.
	- <code>number_of_times_each_philosopher_must_eat</code> (optional argument): If all
philosophers have eaten at least <code>number_of_times_each_philosopher_must_eat</code>
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.
- Each philosopher has a number ranging from 1 to <code>number_of_philosophers</code>.
- Philosopher number 1 sits next to philosopher number <code>number_of_philosophers</code>.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1

About the logs of your program:
- Any state change of a philosopher must be formatted as follows:
	- <code>timestamp_in_ms X has taken a fork</code>
	- <code>timestamp_in_ms X is eating</code>
	- <code>timestamp_in_ms X is sleeping</code>
	- <code>timestamp_in_ms X is thinking</code>
	- <code>timestamp_in_ms X died</code>

<em>Replace <code>timestamp_in_ms</code> with the current timestamp in milliseconds
and X with the philosopher number.</em>
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.
- Again, philosophers should avoid dying!

 ### Your program must not have any data races.

## Specific rules

The specific rules for the mandatory part are:
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.

# Bonus part

<table>
  <tr>
    <th>Program name</th>
    <td><em>philo_bonus</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, <code>*.h</code>, <code>*.c</code> in directory philo_bonus/</td>
  </tr>
  <tr>
	<th>Makefile</th>
	<td><em>NAME</em>, <em>all</em>, <em>clean</em>, <em>fclean</em>, <em>re</em></td>
  </tr>
  <tr>
    <th>Arguments</th>
    <td><code>number_of_philosophers</code> <code>time_to_die</code> <code>time_to_eat</code> <code>time_to_sleep</code> <code>[number_of_times_each_philospher_must_eat]</code></td>
  </tr>
  <tr>
    <th>External functions</th>
    <td> <code>memset, printf, malloc, free, write, fork, kill,
exit, pthread_create, pthread_detach, pthread_join,
usleep, gettimeofday, waitpid, sem_open, sem_close,
sem_post, sem_wait, sem_unlink</code>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>No</td>
  </td>
  <tr>
    <th>Description</th>
    <td>Philosophers with processes and semaphores</td>
  </tr>
</table>

## Specific rules

The program of the bonus part takes the same arguments as the mandatory program.
It has to comply with the requirements of the <em>Global rules</em> chapter.
The specific rules for the bonus part are:
- All the forks are put in the middle of the table.
- They have no states in memory but the number of available forks is represented by
a semaphore.
- Each philosopher should be a process. But the main process should not be a
philosopher.