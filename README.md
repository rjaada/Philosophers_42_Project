# 🍽️ Philosophers 🧠

## 🌟 Overview
This is an implementation of the classic Dining Philosophers problem in C using threads and mutexes. The project simulates philosophers sitting at a round table with forks between them, each philosopher needing two forks to eat. It demonstrates concurrent programming concepts and resource sharing challenges in computer science.

## 🤔 The Problem
The Dining Philosophers problem, conceived by Edsger Dijkstra, illustrates synchronization issues and techniques for solving them:

- N philosophers sit at a round table with N forks placed between them
- Each philosopher alternates between thinking 🤔 and eating 🍝
- To eat, a philosopher needs to pick up both the fork on their left and the fork on their right 🍴
- A fork can only be held by one philosopher at a time
- After eating, philosophers put down both forks and resume thinking
- If a philosopher doesn't eat for too long, they die of starvation 💀

The challenge is to design a solution that avoids deadlock (where all philosophers hold one fork and wait indefinitely for another) and starvation (where philosophers never get a chance to eat).

## ✨ Features
- 👥 Simulates any number of philosophers specified by the user
- 🧵 Each philosopher has their own thread
- 🔒 Forks are represented by mutexes
- 🔄 Philosophers follow a cycle of thinking, eating, and sleeping
- ⏱️ Program ends when a philosopher dies of starvation or all philosophers have eaten enough times
- 📊 Status messages are printed showing the activities of each philosopher
- 🛡️ Deadlock prevention through even/odd ID-based fork acquisition timing
- ⏰ Custom precise sleep function to ensure accurate timing

## 📋 Requirements
- C compiler (gcc recommended)
- POSIX threads library (pthread)
- UNIX/Linux environment (for gettimeofday)

## 🛠️ Compilation
Use the provided Makefile to compile the program:

```bash
make
```

This will create the executable `philo`.

## 🚀 Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters:
1. `number_of_philosophers`: The number of philosophers and forks
2. `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
3. `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
4. `time_to_sleep`: Time in milliseconds it takes for a philosopher to sleep
5. `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times

### Example:
```bash
./philo 5 800 200 200 5
```
This runs the simulation with:
- 5 philosophers 👥👥👥👥👥
- 800ms time to die ⏱️
- 200ms time to eat 🍝
- 200ms time to sleep 😴
- Simulation ends when all philosophers have eaten at least 5 times 🔄✅

## 📁 Project Structure

### Files
- `main.c`: Entry point, argument parsing and program orchestration 🚪
- `init.c`: Data structures and mutexes initialization 🏗️
- `philosophers.c`: Philosopher thread routines and lifecycle functions 🧵
- `monitoring.c`: Death monitoring and meal counting 👀
- `utils.c`: Utility functions (time, sleep, string conversion) 🛠️
- `Philosophers.h`: Header file with structure definitions and function prototypes 📝
- `Makefile`: Compilation instructions 🔨
- `.gitignore`: Files to be ignored by git 🙈

### Detailed File Structure 📂
```
philosophers/
├── Makefile           # Compilation rules
├── Philosophers.h     # Main header file with all prototypes
├── init.c             # Initialization functions
├── main.c             # Program entry point
├── monitoring.c       # Monitors philosophers for death/completion
├── philosophers.c     # Core philosopher logic and routines
├── utils.c            # Utility functions
└── .gitignore         # Git ignore rules
```

### Data Structures
#### `t_philosopher` struct 👤
```c
typedef struct s_philosopher
{
    int             id;              // Philosopher's ID number
    int             left_fork;       // Index of left fork
    int             right_fork;      // Index of right fork
    int             meals_eaten;     // Counter of meals eaten
    long long       last_meal_time;  // Timestamp of last meal
    pthread_t       thread;          // Philosopher's thread
    struct s_data   *data;           // Pointer to shared data
}                   t_philosopher;
```

#### `t_data` struct 🌐
```c
typedef struct s_data
{
    int             num_philosophers; // Number of philosophers
    int             time_to_die;      // Time until starvation in ms
    int             time_to_eat;      // Time it takes to eat in ms
    int             time_to_sleep;    // Time it takes to sleep in ms
    int             num_meals;        // Number of times to eat (-1 = infinite)
    long long       start_time;       // Simulation start time
    int             someone_died;     // Flag for death event
    pthread_mutex_t *forks;           // Array of fork mutexes
    pthread_mutex_t write_mutex;      // Mutex for console output
    t_philosopher   *philosophers;    // Array of philosopher structures
}                   t_data;
```

## 🔍 Implementation Details

### Thread Management
- Each philosopher runs in their own thread 🧵
- A monitoring function checks for deaths or meal completion 👮
- Mutexes protect shared resources (forks and status printing) 🔒

### Deadlock Prevention
The simulation uses an even/odd strategy to prevent deadlocks:
- Even-numbered philosophers wait briefly before starting their routine ⏲️
- This introduces asymmetry that breaks potential circular wait conditions 🔄

### Custom Sleep
A custom `ft_usleep` function ensures accurate timing by:
- Getting the starting time ⏱️
- Periodically checking the elapsed time ⏳
- Using small usleep intervals to minimize CPU usage while maintaining precision ✨

## 🧹 Cleaning Up
To remove object files:
```bash
make clean
```

To remove object files and the executable:
```bash
make fclean
```

To rebuild the project:
```bash
make re
```

## 🎭 Life of a Philosopher
```
1. Think 🧠
2. Get hungry 🍔
3. Pick up forks 🍴
4. Eat 🍝
5. Put down forks ⬇️
6. Sleep 😴
7. Repeat ♻️
```

## ⚠️ Beware of Deadlocks!
When philosophers pick up forks in the same order, they can deadlock - with each holding one fork and waiting forever for another! Our implementation cleverly avoids this pitfall. 🧠💡

## 🎮 Enjoy the Simulation!
Watch as philosophers think, eat, sleep, and compete for resources in this classic computer science problem come to life! 🎬
