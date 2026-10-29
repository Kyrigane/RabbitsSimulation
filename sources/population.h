#include "rabbit.h"

// Type size_t est plus adapté pour la taille et capacité : non signé et plus grand que int

typedef struct {
    Rabbit ** rabbits;
    size_t count;
    size_t capacity;
} RabbitPopulation;

void initRabbitPopulation(RabbitPopulation * population, size_t initial_capacity); //Initialise la population de lapins
void addRabbitToPopulation(RabbitPopulation * population, Rabbit * r); //Ajoute un lapin à la population
void updateRabbitPopulation(RabbitPopulation * population); //Met à jour l'état de la population de lapins
void showRabbitPopulation(RabbitPopulation * population); //Affiche les informations de la population de lapins
void freeRabbitPopulation(RabbitPopulation * population); //Libère la mémoire allouée pour la population de lapins
