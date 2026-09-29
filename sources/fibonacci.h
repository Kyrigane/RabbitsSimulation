typedef struct month_simulation {
    int nb_month;
    int nb_rabbits;
} month_simulation;

void simulate_rabbit_fibonacci(month_simulation *simulation, int n);
void affiche_simulation(month_simulation *simulations);