/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svikornv <svikornv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:21:58 by svikornv          #+#    #+#             */
/*   Updated: 2023/12/20 14:12:20 by svikornv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>
// #include <sys/time.h>

// #define MAX_NAME_LENGTH 20

// typedef struct {
//     int id;
//     pthread_mutex_t *left_fork;
//     pthread_mutex_t *right_fork;
//     int time_to_die;
//     int time_to_eat;
//     int time_to_sleep;
//     int num_eat;
//     struct timeval last_meal_time;
//     struct timeval start_time;
// } Philosopher;

// void initialize_philosopher(Philosopher *philosopher, int id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int time_to_die, int time_to_eat, int time_to_sleep, int num_eat) {
//     philosopher->id = id;
//     philosopher->left_fork = left_fork;
//     philosopher->right_fork = right_fork;
//     philosopher->time_to_die = time_to_die;
//     philosopher->time_to_eat = time_to_eat;
//     philosopher->time_to_sleep = time_to_sleep;
//     philosopher->num_eat = 0;
//     gettimeofday(&philosopher->last_meal_time, NULL);
//     gettimeofday(&philosopher->start_time, NULL);
//     philosopher->num_eat = num_eat;
// }

// void print_state(Philosopher *philosopher, const char *state) {
//     struct timeval current_time;
//     gettimeofday(&current_time, NULL);
//     long timestamp = (current_time.tv_sec - philosopher->start_time.tv_sec) * 1000 +
//                      (current_time.tv_usec - philosopher->start_time.tv_usec) / 1000;
//     printf("%ld %d %s\n", timestamp, philosopher->id, state);
// }

// void take_forks(Philosopher *philosopher) {
//     if (philosopher->id % 2 == 0) {
//         pthread_mutex_lock(philosopher->right_fork);
//         pthread_mutex_lock(philosopher->left_fork);
//     } else {
//         pthread_mutex_lock(philosopher->left_fork);
//         pthread_mutex_lock(philosopher->right_fork);
//     }

//     print_state(philosopher, "has taken a fork");
//     print_state(philosopher, "has taken a fork");
// }

// void put_forks(Philosopher *philosopher) {
//     pthread_mutex_unlock(philosopher->left_fork);
//     pthread_mutex_unlock(philosopher->right_fork);
// }

// void eat(Philosopher *philosopher) {
//     print_state(philosopher, "is eating");
//     usleep(philosopher->time_to_eat * 1000);
//     philosopher->num_eat++;
//     gettimeofday(&philosopher->last_meal_time, NULL);
// }

// void sleep_(Philosopher *philosopher) {
//     print_state(philosopher, "is sleeping");
//     usleep(philosopher->time_to_sleep * 1000);
// }

// void think(Philosopher *philosopher) {
//     print_state(philosopher, "is thinking");
// }

// void* philosopher_thread(void *arg) {
//     Philosopher *philosopher = (Philosopher*) arg;
//     int num_eat = philosopher->num_eat;

//     while (1) {
//         take_forks(philosopher);
//         eat(philosopher);
//         put_forks(philosopher);
//         sleep_(philosopher);
//         think(philosopher);

//         struct timeval current_time;
//         gettimeofday(&current_time, NULL);
//         long time_diff = (current_time.tv_sec - philosopher->last_meal_time.tv_sec) * 1000
//                        + (current_time.tv_usec - philosopher->last_meal_time.tv_usec) / 1000;

//         if (time_diff >= philosopher->time_to_die) {
//             print_state(philosopher, "died");
//             break;
//         }

//         if (num_eat > 0 && philosopher->num_eat >= num_eat) {
//             break;
//         }
//     }

//     return NULL;
// }

// int main(int argc, char *argv[]) {
//     if (argc < 5 || argc > 6) {
//         printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
//         return 1;
//     }

//     int num_philosophers = atoi(argv[1]);
//     int time_to_die = atoi(argv[2]);
//     int time_to_eat = atoi(argv[3]);
//     int time_to_sleep = atoi(argv[4]);
//     int num_eat = (argc == 6) ? atoi(argv[5]) : -1;

//     pthread_t philosophers[num_philosophers];
//     pthread_mutex_t forks[num_philosophers];

//     Philosopher philosophers_data[num_philosophers];

//     // Initialize forks
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_mutex_init(&forks[i], NULL);
//     }

//     // Initialize philosophers
//     for (int i = 0; i < num_philosophers; i++) {
//         initialize_philosopher(&philosophers_data[i], i + 1, &forks[i], &forks[(i + 1) % num_philosophers], time_to_die, time_to_eat,time_to_sleep, num_eat);
//     }
//     // Create philosopher threads
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_create(&philosophers[i], NULL, philosopher_thread, &philosophers_data[i]);
//     }

//     // Wait for philosopher threads to finish
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_join(philosophers[i], NULL);
//     }

//     // Destroy forks
//     for (int i = 0; i < num_philosophers; i++) {
//         pthread_mutex_destroy(&forks[i]);
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define MAX_NAME_LENGTH 20

typedef struct {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_eat;
    struct timeval last_meal_time;
    struct timeval start_time;
} Philosopher;

void initialize_philosopher(Philosopher *philosopher, int id, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork, int time_to_die, int time_to_eat, int time_to_sleep, int num_eat) {
    philosopher->id = id;
    philosopher->left_fork = left_fork;
    philosopher->right_fork = right_fork;
    philosopher->time_to_die = time_to_die;
    philosopher->time_to_eat = time_to_eat;
    philosopher->time_to_sleep = time_to_sleep;
    philosopher->num_eat = num_eat;
    gettimeofday(&philosopher->last_meal_time, NULL);
    gettimeofday(&philosopher->start_time, NULL);
}

void print_state(Philosopher *philosopher, const char *state) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long timestamp = (current_time.tv_sec - philosopher->start_time.tv_sec) * 1000 +
                     (current_time.tv_usec - philosopher->start_time.tv_usec) / 1000;
    printf("%ld %d %s\n", timestamp, philosopher->id, state);
}

void take_forks(Philosopher *philosopher) {
    if (philosopher->id % 2 == 0) {
        pthread_mutex_lock(philosopher->right_fork);
        pthread_mutex_lock(philosopher->left_fork);
    } else {
        pthread_mutex_lock(philosopher->left_fork);
        pthread_mutex_lock(philosopher->right_fork);
    }

    print_state(philosopher, "has taken a fork");
    print_state(philosopher, "has taken a fork");
}

void put_forks(Philosopher *philosopher) {
    pthread_mutex_unlock(philosopher->left_fork);
    pthread_mutex_unlock(philosopher->right_fork);
}

void eat(Philosopher *philosopher) {
    print_state(philosopher, "is eating");
    usleep(philosopher->time_to_eat * 1000);
    philosopher->num_eat++;
    gettimeofday(&philosopher->last_meal_time, NULL);
}

void sleep_(Philosopher *philosopher) {
    print_state(philosopher, "is sleeping");
    usleep(philosopher->time_to_sleep * 1000);
}

void think(Philosopher *philosopher) {
    print_state(philosopher, "is thinking");
}

void* philosopher_thread(void *arg) {
    Philosopher *philosopher = (Philosopher*) arg;
    int num_eat = philosopher->num_eat;

    while (1) {
        take_forks(philosopher);
        eat(philosopher);
        put_forks(philosopher);
        sleep_(philosopher);
        think(philosopher);

        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        long time_diff = (current_time.tv_sec - philosopher->last_meal_time.tv_sec) * 1000
                       + (current_time.tv_usec - philosopher->last_meal_time.tv_usec) / 1000;

        if (time_diff >= philosopher->time_to_die) {
            print_state(philosopher, "died");
            break;
        }

        if (num_eat > 0 && philosopher->num_eat >= num_eat) {
            break;
        }
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 5 || argc > 6) {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return 1;
    }

    int num_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);
    int num_eat = (argc == 6) ? atoi(argv[5]) : -1;

    pthread_t philosophers[num_philosophers];
    pthread_mutex_t forks[num_philosophers];

    Philosopher philosophers_data[num_philosophers];

    // Initialize forks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Initialize philosophers
    for (int i = 0; i < num_philosophers; i++) {
        initialize_philosopher(&philosophers_data[i], i + 1, &forks[i], &forks[(i + 1) % num_philosophers], time_to_die, time_to_eat, time_to_sleep, num_eat);
    }
    // Create philosopher threads
    for (int i = 0; i < num_philosophers; i++) {
        pthread_create(&philosophers[i], NULL, philosopher_thread, &philosophers_data[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy forks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}