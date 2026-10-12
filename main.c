#include "./fibonacci.h"
#include "./rabbit.h"

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

    //test du choix du nombre de portées par an d'une lapine
    /*
    int test;
    int compteur[12]={0};
    for (int i=0; i <= 10000; i++) {
        test = chooseNbLitterPerYear();
        compteur[test]++;
    }
    for (int i=0; i < 12; i++) {
        printf("Nombre de portées de %d: %d\n", i, compteur[i]);
    }
    */
    return 0;
}