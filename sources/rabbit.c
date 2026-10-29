#include "rabbit.h"

void initRabbit(Rabbit * r) {
    r->age_month = 0;
    r->is_pregnant = false;
    r->is_alive = true;
    r->is_adult = false;
    chooseGender(r);
}

void chooseGender(Rabbit * r) {
    r->is_female = genrand_real1() < 0.5; 
}

// Méthode de Box-Muller pour générer un nombre aléatoire suivant une loi normale centrée réduite
void chooseNbLitterPerYear(Rabbit * r) {
    if (!r->is_female || !r->is_alive || r->age_month % 12 != 0) {
        return; 
    }
    double mean = 6; 
    double stddev = 1.2;
    double u1 = genrand_real1();
    double u2 = genrand_real1();
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    int nbLitter = (int)(round(mean + z0 * stddev));
    r->nb_litter_per_year = nbLitter;
}

void choosePregnancy(Rabbit * r) {
    if (r->is_pregnant || !r->is_female || !r->is_alive) {
        return; 
    }
    double p = r->nb_litter_per_year / 12.0;
    double random_value = genrand_real1();
    r->is_pregnant = random_value < p;
}

int chooseNbNewborns(Rabbit * r) {
    if (!r->is_pregnant || !r->is_female || !r->is_alive) {
        return 0; 
    }
    return (int)(genrand_real1() * 4) + 3; 
}

// On passe par une loi de Bernouilli avec p qui dépend du mois (âge) du lapin.
void chooseMaturity(Rabbit * r) {
    if (r->is_adult || !r->is_alive) {
        return; 
    }
    switch (r->age_month) {
        case 5:
            r->is_adult = genrand_real1() < 0.25;
            break;
        case 6:
            r->is_adult = genrand_real1() < 0.33;
            break;
        case 7:
            r->is_adult = genrand_real1() < 0.5;
            break;
        case 8:
            r->is_adult = true;
            break;
        default:
            break;
    }
}

void chooseDeath(Rabbit * r) {
    float annualSurvivalRate=0.6; // Valeur par défaut pour les lapins adultes
    if (!r->is_alive) {
        return; 
    }
    if (!r->is_adult) {
        annualSurvivalRate = 0.35;
    } else if ((r->age_month / 12) >= 15){
        annualSurvivalRate = 0;
    } 
    else if ((r->age_month / 12) >= 10) {
        annualSurvivalRate -= 0.1 * ((r->age_month / 12) - 9);
    }
    float monthlySurvivalRate = powf(annualSurvivalRate, 1.0 / 12.0);
    r->is_alive = genrand_real1() < monthlySurvivalRate;
}
