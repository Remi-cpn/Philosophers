*This project has been created as part of the 42 curriculum by rcompain.*

# Philosophers (Bonus)

## Description

The bonus part reimagines the Philosophers problem using **processes instead of threads** and **semaphores instead of mutexes**. Each philosopher runs as a separate process, and all forks are placed in the middle of the table as a shared resource pool.

**Key differences from mandatory:**
- Each philosopher is a separate process (fork)
- Forks are represented by a single semaphore initialized to N
- The main process monitors deaths and meal completion
- No individual fork assignment (philosophers take any 2 forks from the pool)

## Instructions

### Compilation
```bash
make
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Parameters:** Same as mandatory version

**Example:**
```bash
./philo 5 800 200 200       # Runs indefinitely
./philo 5 800 200 200 7     # Stops when all have eaten 7 times
```

### Implementation Details

**Semaphores used:**
- `/forks`: Pool of N forks (init: N)
- `/print`: Mutex for printing (init: 1)
- `/meal_end`: Counter for completed philosophers (init: 0)
- `/ph_dead`: Signal for death detection (init: 0)
- `/end`: Global stop signal for cascade termination (init: 0)
- Per-philosopher semaphores for local thread synchronization

**Architecture:**
- Main process creates N child processes (philosophers)
- Two monitoring threads in main process:
  - `monitoring_meal`: Waits for all philosophers to finish eating
  - `monitoring_ph_dead`: Detects and handles philosopher deaths
- Each philosopher has two threads:
  - Main thread: eating/sleeping/thinking loop
  - Monitoring thread: detects death by starvation

## Resources

**Classic References:**
- [POSIX Semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [Doc 42]()

**AI Usage:**
This project was developed with extensive assistance from Claude for:
- Understanding sem_open/sem_close/sem_unlink semantics
- Discussion of architectural choices (processes vs threads, fork pools)