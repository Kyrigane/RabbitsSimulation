#include "./fibonacci.h"
#include "./population.h"
#include "time.h"

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
    clock_t startTime;
    clock_t endTime;
    double timeSpent=0;

    for (int iPopulation = 0; iPopulation < 10; iPopulation++) {
        Rabbit femelle;
        Rabbit male;
        initRabbit(&femelle);
        initRabbit(&male);
        // On force le genre pour avoir un couple de lapins
        femelle.is_female = true; 
        male.is_female = false;
        initRabbitPopulation(&population, 10);
        addRabbitToPopulation(&population, femelle);
        addRabbitToPopulation(&population, male);

        printf("===========================\n");
        printf("Simulation de la population de lapins %d:\n", iPopulation + 1);
        printf("===========================\n");

        startTime = clock();

        for (int month = 0; month < 120; month++) {
            printf("Mois %d: ", month);
            updateRabbitPopulation(&population);
            printf("Population de %zu lapins\n", population.count);
            //showRabbitPopulation(&population);
            if (population.count == 0) {
                printf("Tous les lapins sont morts.\n");
                break;
            }
        }

        endTime = clock();
        timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Temps écoulé pour la simulation : %.2f secondes\n", timeSpent);
    }
    return 0;
}