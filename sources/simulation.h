#include <stdbool.h>
#include <stdlib.h>

// Type bool est plus optimisé que int : utilise moins de mémoire et plus rapide à comparer
// Type size_t est plus adapté pour la taille et capacité : non signé et plus grand que int

#define MAX_RABBITS 10000

typedef struct rabbit{
    int age_month;
    bool is_pregnant;
    bool is_alive;
    bool is_adult;
    bool is_female;
} Rabbit;

typedef struct {
    Rabbit * rabbits;
    size_t count;
    size_t capacity;
} RabbitPopulation;

// Lapins :
bool chooseGender(Rabbit * r); //Genre d'un lapin, loi de Bernoulli avec p=0.5
int chooseNbLitterPerYear(Rabbit * r); //Nombre de portées par an d'une lapine, loi normale centrée sur 6 avec un écart type de 1.5
bool choosePregnancy(Rabbit * r, int nbLitter); //Si une lapine est enceinte ou non, p déterminé par le nombre de portées par an choisi précédemment
int chooseNbNewborns(Rabbit * r); //Nombre de lapereaux par portée, loi uniforme entre 3 et 6
int getMonthsToMaturity(Rabbit * r); //Nombre de mois pour qu'un lapin devienne adulte, loi uniforme entre 5 et 8
bool isDead(Rabbit * r); //Si un lapin meurt ou non, loi de Bernoulli avec p dépendant de l'âge du lapin
void updateRabbit(Rabbit * r); //Met à jour l'état d'un lapin (âge, maturité, grossesse, décès)
void showRabbit(Rabbit * r); //Affiche les informations d'un lapin
void freeRabbit(Rabbit * r); //Libère la mémoire allouée pour un lapin

// Population de lapins :
void initRabbitPopulation(RabbitPopulation * population, size_t initial_capacity); //Initialise la population de lapins
void updateRabbitPopulation(RabbitPopulation * population); //Met à jour l'état de la population de lapins
void showRabbitPopulation(RabbitPopulation * population); //Affiche les informations de la population de lapins
void freeRabbitPopulation(RabbitPopulation * population); //Libère la mémoire allouée pour la population de lapins
