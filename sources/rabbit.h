#include <stdbool.h>
#include "mt19937.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

// Type bool est plus optimisé que int : utilise moins de mémoire et plus rapide à comparer

typedef struct rabbit{
    int age_month;
    bool is_pregnant;
    bool is_alive;
    bool is_adult;
    bool is_female;
} Rabbit;

void initRabbit(Rabbit * r); //Initialise un lapin
bool chooseGender(); //Genre d'un lapin, loi de Bernoulli avec p=0.5
int chooseNbLitterPerYear(); //Nombre de portées par an d'une lapine, loi normale centrée sur 6 avec un écart type de 1.2
bool choosePregnancy(Rabbit * r, int nbLitter); //Si une lapine est enceinte ou non, Bernoulli avec p déterminé par le nombre de portées par an choisi précédemment
int chooseNbNewborns(Rabbit * r); //Nombre de lapereaux par portée, loi uniforme entre 3 et 6
int getMonthsToMaturity(Rabbit * r); //Nombre de mois pour qu'un lapin devienne adulte, loi uniforme entre 5 et 8
bool isDead(Rabbit * r); //Si un lapin meurt ou non, loi de Bernoulli avec p dépendant de l'âge du lapin
void updateRabbit(Rabbit * r); //Met à jour l'état d'un lapin (âge, maturité, grossesse, décès)
void showRabbit(Rabbit * r); //Affiche les informations d'un lapin
void freeRabbit(Rabbit * r); //Libère la mémoire allouée pour un lapin