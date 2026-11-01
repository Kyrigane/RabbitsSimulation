#include <stddef.h>
typedef struct month_simulation {
    int nb_month;
    size_t nb_rabbits;
} month_simulation;

void simulate_rabbit_fibonacci(month_simulation *simulation, size_t n);
void affiche_simulation(month_simulation *simulations);