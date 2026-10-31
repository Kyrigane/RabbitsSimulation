#include "population.h"

void initRabbitPopulation(RabbitPopulation * population, size_t initial_capacity) {
    population->rabbits = (Rabbit *)malloc(initial_capacity * sizeof(Rabbit));
    population->count = 0;
    population->capacity = initial_capacity;
    population->adult_male_count = 0;
}

void addRabbitToPopulation(RabbitPopulation * population, Rabbit r) {
    if (population->count >= population->capacity) {
        size_t new_capacity = population->capacity * 2;
        Rabbit * new_rabbits = (Rabbit *)realloc(population->rabbits, new_capacity * sizeof(Rabbit));
        if (new_rabbits == NULL) {
            printf("Echec du realloc\n");
            exit(EXIT_FAILURE);
        }
        population->rabbits = new_rabbits;
        population->capacity = new_capacity;
    }
    population->rabbits[population->count] = r;
    population->count++;

    if (r.is_alive && !r.is_female && r.is_adult) {
        population->adult_male_count++;
    }
}

void updateRabbitPopulation(RabbitPopulation * population) {
    bool hasAdultMale = (population->adult_male_count > 0);
    population->adult_male_count = 0;

    size_t currentCount = population->count;
    size_t totalNewborns = 0;

    for (size_t i = 0; i < currentCount; i++) {
        int nbNewborns = updateRabbit(&population->rabbits[i], hasAdultMale);
        totalNewborns += nbNewborns;

        if (population->rabbits[i].is_alive) {
            if (!population->rabbits[i].is_female && population->rabbits[i].is_adult) {
                population->adult_male_count++;
            }
        } else {
            if (i < currentCount - 1) {
                population->rabbits[i] = population->rabbits[currentCount - 1];
                i--; 
            }
            currentCount--;
            population->count--;
        }
    }

    // Gestion des nouveaux-nés et redimensionnement du tableau (si nécessaire)
    if (totalNewborns > 0) {
        size_t new_total = population->count + totalNewborns;
        if (new_total > population->capacity) {
            size_t newCapacity = population->capacity * 2;
            
            // Dans le cas où c'est pas suffisant, on redouble
            if (newCapacity < new_total) {
                newCapacity = new_total * 2; 
            }

            Rabbit * newRabbits = (Rabbit *)realloc(population->rabbits, newCapacity * sizeof(Rabbit));
            if (newRabbits == NULL) {
                printf("Echec du realloc\n");
                exit(EXIT_FAILURE);
            }
            population->rabbits = newRabbits;
            population->capacity = newCapacity;
        }

        for (size_t i = 0; i < totalNewborns; i++) {
            initRabbit(&population->rabbits[population->count]);
            population->count++;
        }
    }
}


void showRabbitPopulation(RabbitPopulation * population) {
    printf("Population de lapins: %zu lapins\n", population->count);
    for (size_t i = 0; i < population->count; i++) {
        printf("Lapin %zu: ", i + 1);
        showRabbit(&population->rabbits[i]);
    }
}

void freeRabbitPopulation(RabbitPopulation * population) {
    free(population->rabbits);
    population->rabbits = NULL;
    population->count = 0;
    population->capacity = 0;
    population->adult_male_count = 0;
}