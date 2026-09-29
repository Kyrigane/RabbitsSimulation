#include <stdio.h>
#include "fibonacci.h"

void simulate_rabbit_fibonacci(month_simulation *simulation, int n) {
    if (n == 0) {
        simulation->nb_month = 0;
        simulation->nb_rabbits = 0;
    } else if (n == 1) {
        simulation->nb_month = 1;
        simulation->nb_rabbits = 1;
    }
    else {
        month_simulation prev1, prev2;
        simulate_rabbit_fibonacci(&prev1, n - 1);
        simulate_rabbit_fibonacci(&prev2, n - 2);
        simulation->nb_month = n;
        simulation->nb_rabbits = prev1.nb_rabbits + prev2.nb_rabbits;
    }
}

void affiche_simulation(month_simulation *simulation) {
    printf("Mois : %d | Nombre de couples de lapins : %d\n", simulation->nb_month, simulation->nb_rabbits);
}