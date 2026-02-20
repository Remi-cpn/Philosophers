*This project has been created as part of the 42 curriculum by rcompain.*

# Philosophers (Mandatory)

## Description

Philosophers is a classic synchronization problem in computer science. The goal is to simulate N philosophers sitting at a round table, alternating between eating, thinking, and sleeping. Each philosopher needs two forks to eat, but there are only N forks on the table (one between each pair of philosophers).

The challenge is to implement a solution that prevents deadlocks, ensures no philosopher starves, and uses proper synchronization mechanisms (threads and mutexes) to avoid data races.

**Key constraints:**
- Each philosopher is represented by a thread
- Forks are shared resources protected by mutexes
- A philosopher dies if they don't eat within `time_to_die` milliseconds
- Death must be detected within 10ms

## Instructions

### Compilation
```bash
make
```

### Execution
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Parameters:**
- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in ms before a philosopher dies without eating
- `time_to_eat`: Time in ms it takes to eat
- `time_to_sleep`: Time in ms spent sleeping
- `[number_of_times_each_philosopher_must_eat]` (optional): Program stops when all philosophers have eaten this many times

**Example:**
```bash
./philo 5 800 200 200       # Runs indefinitely
./philo 5 800 200 200 7     # Stops when all have eaten 7 times
./philo 4 310 200 100       # A philosopher should die
```

### Output Format
```
[timestamp_ms] philosopher_id action
```
Actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`

## Resources

**Classic References:**
- [Doc 42]()
- [Man pthread](https://www.man7.org/linux/man-pages/man3/pthread_create.3.html)

**AI Usage:**
This project was developed with assistance from Claude (Anthropic) for:
- Understanding pthread concepts