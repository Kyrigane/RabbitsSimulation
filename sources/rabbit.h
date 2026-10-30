#include <stdbool.h>
#include "mt19937.h"
#include <stdint.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


typedef struct rabbit {
    uint8_t age_month;              // 8 bits : 0 à 255 (max 180 mois)
    uint8_t nb_litter_per_year : 4; // 4 bits : 0 à 15 (max 9 portées)
    uint8_t is_pregnant : 1;        // 1 bit
    uint8_t is_alive : 1;           // 1 bit
    uint8_t is_adult : 1;           // 1 bit
    uint8_t is_female : 1;          // 1 bit
} Rabbit;

void initRabbit(Rabbit * r); //Initialise un lapin
void chooseGender(Rabbit * r); //Genre d'un lapin, loi de Bernoulli avec p=0.5
void chooseNbLitterPerYear(Rabbit * r); //Nombre de portées par an d'une lapine, loi normale centrée sur 6 avec un écart type de 1.2
void choosePregnancy(Rabbit * r); //Si une lapine est enceinte ou non, Bernoulli avec p déterminé par le nombre de portées par an choisi précédemment
int chooseNbNewborns(Rabbit * r); //Nombre de lapereaux par portée, loi uniforme entre 3 et 6
void chooseMaturity(Rabbit * r); //Choisit si un lapin devient adulte, loi uniforme entre 5 et 8 (mois)
void chooseDeath(Rabbit * r); //Si un lapin meurt ou non, loi de Bernoulli avec p dépendant de l'âge du lapin
int updateRabbit(Rabbit * r,bool hasAdultMale); //Met à jour l'état d'un lapin (âge, maturité, grossesse, décès), renvoie le nombre de lapereaux nés
void showRabbit(Rabbit * r); //Affiche les informations d'un lapin
void freeRabbit(Rabbit * r); //Libère la mémoire allouée pour un lapin