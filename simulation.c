#include "./fibonacci.h"
#include "./population.h"

int main(){
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    printf("======================================================\n");
    printf("Bienvenue dans le simulateur de population de lapins!\n");
    printf("======================================================\n");

    printf("Simulation avec la suite de Fibonacci:\n");

    month_simulation simulation_fibonacci;
    for (int i = 0; i <= 10; i++) {
        simulate_rabbit_fibonacci(&simulation_fibonacci, i);
        affiche_simulation(&simulation_fibonacci);
    }

    
    printf("======================================================\n");

    printf("Simulation avec la population de lapins:\n");

    RabbitPopulation population;
    Rabbit femelle;
    Rabbit male;
    initRabbit(&femelle);
    initRabbit(&male);
    // On force le genre pour avoir un couple de lapins
    femelle.is_female = true; 
    male.is_female = false;
    initRabbitPopulation(&population, 10);
    addRabbitToPopulation(&population, &femelle);
    addRabbitToPopulation(&population, &male);

    return 0;
}