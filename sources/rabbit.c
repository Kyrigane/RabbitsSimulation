#include "rabbit.h"

void initRabbit(Rabbit * r) {
    r->age_month = 0;
    r->is_pregnant = false;
    r->is_alive = true;
    r->is_adult = false;
    r->is_female = chooseGender();
}

bool chooseGender() {
    return genrand_real1() < 0.5; 
}

// Méthode de Box-Muller pour générer un nombre aléatoire suivant une loi normale centrée réduite
int chooseNbLitterPerYear(){
    double mean = 6; 
    double stddev = 1.2;
    double u1 = genrand_real1();
    double u2 = genrand_real1();
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    int nbLitter = (int)(round(mean + z0 * stddev));
    if (nbLitter < 1) nbLitter = 1; 
    return nbLitter;
}

bool choosePregnancy(Rabbit * r, int nbLitter) {
    if (r->is_pregnant) {
        return false; 
    }
    double p = nbLitter / 12.0;
    double random_value = genrand_real1();
    return random_value < p;
}

int chooseNbNewborns(Rabbit * r) {
    if (!r->is_pregnant) {
        return 0; 
    }
    return (int)(genrand_real1() * 4) + 3; 
}
