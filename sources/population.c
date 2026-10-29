#include "population.h"

void initRabbitPopulation(RabbitPopulation * population, size_t initial_capacity) {
    population->rabbits = (Rabbit **)malloc(initial_capacity * sizeof(Rabbit *));
    population->count = 0;
    population->capacity = initial_capacity;
}

void addRabbitToPopulation(RabbitPopulation * population, Rabbit * r) {
    if (population->count >= population->capacity) {
        size_t new_capacity = population->capacity * 2;
        Rabbit ** new_rabbits = (Rabbit **)realloc(population->rabbits, new_capacity * sizeof(Rabbit *));
        if (new_rabbits == NULL) {
            printf("Echec du realloc\n");
            exit(EXIT_FAILURE);
        }
        population->rabbits = new_rabbits;
        population->capacity = new_capacity;
    }
    population->rabbits[population->count] = r;
    population->count++;
}