#include "rabbit.h"

static const float SURVIVAL_YOUNG = 0.91578f; // powf(0.35f, 1.0f/12.0f) précalculé pour optimisation
static const float SURVIVAL_ADULT = 0.95842f; // powf(0.60f, 1.0f/12.0f) précalculé pour optimisation

void initRabbit(Rabbit * r) {
    r->age_month = 0;
    r->is_pregnant = false;
    r->is_alive = true;
    r->is_adult = false;
    chooseNbLitterPerYear(r);
    chooseGender(r);
}

void chooseGender(Rabbit * r) {
    r->is_female = genrand_real1() < 0.5; 
}

// Méthode de Box-Muller pour générer un nombre aléatoire suivant une loi normale centrée réduite
void chooseNbLitterPerYear(Rabbit * r) {
    if (!r->is_female || !r->is_alive) {
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
    r->is_pregnant = false;
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
    if (!r->is_alive) {
        return; 
    }
    float monthlySurvivalRate;
    if (!r->is_adult) {
        monthlySurvivalRate = SURVIVAL_YOUNG;
    } else {
        int age_years = r->age_month / 12;
        if (age_years < 10) {
            monthlySurvivalRate = SURVIVAL_ADULT;
        } else if (age_years >= 15) {
            monthlySurvivalRate = 0.0f;
        } else {
            float annualSurvivalRate = 0.6f - 0.1f * (age_years - 9);
            monthlySurvivalRate = powf(annualSurvivalRate, 1.0f / 12.0f);
        }
    }
    
    r->is_alive = genrand_real1() < monthlySurvivalRate;
}

int updateRabbit(Rabbit * r, bool hasAdultMale) {
    int newborns = 0;
    if (!r->is_alive) {
        return 0; 
    }
    r->age_month++;
    chooseMaturity(r);
    chooseDeath(r);
    if (r->is_female && r->is_adult) {
        if (r->age_month % 12 == 0) {
            chooseNbLitterPerYear(r);
        }
        if (r->is_pregnant) {
            newborns = chooseNbNewborns(r);
        }
        if (hasAdultMale) {
            choosePregnancy(r);
        }
    }
    return newborns;
}

void showRabbit(Rabbit * r) {
    printf("Age (mois): %d | ", r->age_month);
    printf("Genre: %s | ", r->is_female ? "Femelle" : "Mâle");
    if (r->is_female) {
        printf("Enceinte: %s | ", r->is_pregnant ? "Oui" : "Non");
    }
    printf("Adulte: %s | ", r->is_adult ? "Oui" : "Non");
    printf("Vivant: %s\n", r->is_alive ? "Oui" : "Non");
}

void freeRabbit(Rabbit * r) {
    free(r);
}