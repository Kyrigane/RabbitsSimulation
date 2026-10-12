#include "./fibonacci.h"
#include "./rabbit.h"

int main(){
    printf("======================================================\n");
    printf("Bienvenue dans le simulateur de population de lapins!\n");
    printf("======================================================\n");

    month_simulation simulation_fibonacci;
    for (int i = 0; i <= 10; i++) {
        simulate_rabbit_fibonacci(&simulation_fibonacci, i);
        affiche_simulation(&simulation_fibonacci);
    }
    return 0;
}