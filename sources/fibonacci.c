#include <stdio.h>
#include "fibonacci.h"

void simulate_rabbit_fibonacci(month_simulation *simulation, size_t n) {
    simulation->nb_month = n;
    if (n == 0) {
        simulation->nb_rabbits = 0;
        return;
    }
    if (n == 1) {
        simulation->nb_rabbits = 1;
        return;
    }
    int prev2 = 0;
    int prev1 = 1;
    int current = 1;

    for (size_t i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    simulation->nb_rabbits = current;
}

void affiche_simulation(month_simulation *simulation) {
    printf("Mois : %d | Nombre de couples de lapins : %zu\n", simulation->nb_month, simulation->nb_rabbits);
}