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

void updateRabbitPopulation(RabbitPopulation * population) {
    bool hasAdultMale = false;
    for (size_t i = 0; i < population->count; i++) {
        Rabbit *r = population->rabbits[i];
        if (r->is_alive && !r->is_female && r->is_adult) {
            hasAdultMale = true;
            break;
        }
    }
    for (size_t i = 0; i < population->count; i++) {
        int nbNewborns = updateRabbit(population->rabbits[i], hasAdultMale);
        if (nbNewborns > 0) {
            for (int j = 0; j < nbNewborns; j++) {
                Rabbit * new_rabbit = (Rabbit *)malloc(sizeof(Rabbit));
                initRabbit(new_rabbit);
                addRabbitToPopulation(population, new_rabbit);
            }
        }
        if (!population->rabbits[i]->is_alive) {
            freeRabbit(population->rabbits[i]);
            if (i < population->count - 1) {
                population->rabbits[i] = population->rabbits[population->count - 1];
                population->rabbits[population->count - 1] = NULL;
                i--; 
            };
            population->count--;
        }
    }
}


void showRabbitPopulation(RabbitPopulation * population) {
    printf("Population de lapins: %zu lapins\n", population->count);
    for (size_t i = 0; i < population->count; i++) {
        printf("Lapin %zu: ", i + 1);
        showRabbit(population->rabbits[i]);
    }
}