#include "./fibonacci.h"
#include "./rabbit.h"

int main(){
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    printf("======================================================\n");
    printf("Bienvenue dans le simulateur de population de lapins!\n");
    printf("======================================================\n");

    printf("Simulation avec la suite de Fibonacci:\n");

    month_simulation simulation_fibonacci;
    for (int i = 0; i <= 10; i++) {
        simulate_rabbit_fibonacci(&simulation_fibonacci, i);
        affiche_simulation(&simulation_fibonacci);
    }

    
    printf("======================================================\n");

    printf("Simulation avec la population de lapins:\n");

    //test du choix du nombre de portées par an d'une lapine
    Rabbit r;
    initRabbit(&r);
    r.is_female = true; // on force le genre pour tester les fonctions
    int countLitter[13]={0};
    for (int i=0; i <= 10000; i++) {
        chooseNbLitterPerYear(&r);
        countLitter[r.nb_litter_per_year]++;
    }
    for (int i=0; i < 13; i++) {
        printf("Nombre de portées par an, %d: %d\n", i, countLitter[i]);
    }

    //test du choix de la grossesse d'une lapine
    int nbLitterReal=0;
    for (int i=0; i < 120; i++) {
        if (i % 12 == 0) {
            chooseNbLitterPerYear(&r);
        }
        choosePregnancy(&r);
        if (r.is_pregnant) {
            nbLitterReal++;
        }
        r.is_pregnant = false; // on réinitialise pour le test
        if (i % 12 == 11) {
            printf("Année %d: Portées par an attendues : %d (Portées réelles : %d)\n", i/12 + 1, r.nb_litter_per_year, nbLitterReal);
            nbLitterReal = 0;
        }
    }

    // test du choix du nombre de lapereaux par portée d'une lapine
    int countNewborns[4]={0};
    for (int i=0; i < 10000; i++) {
        r.is_pregnant = true;
        int nbNewborns = chooseNbNewborns(&r);
        countNewborns[nbNewborns - 3]++;
    }
    for (int i=0; i < 4; i++) {
        printf("Nombre de lapereaux par portée, %d: %d\n", i+3, countNewborns[i]);
    }

    // test du choix de la maturité d'un lapin
    int countMaturity[4]={0};
    for (int i=0; i < 10000; i++) {
        r.is_adult = false;
        for (int month = 5; month < 9; month++) {
            r.age_month = month;
            chooseMaturity(&r);
            if (r.is_adult) {
                countMaturity[month - 5]++;
                break; 
            }
        }
    }
    printf("Nombre de lapins devenus adultes par mois:\n");
    for (int i=0; i < 4; i++) {
        printf("Mois %d: %d\n", i + 5, countMaturity[i]);
    }

    // test du choix de la mort d'un lapin au cours des années
    int countDeath[16]={0};
    for (int i=0; i < 100000; i++) {
        r.is_adult = false;
        r.is_alive = true;
        for (int month = 0; month < 16 * 12; month++) {
            r.age_month = month;
            if (!r.is_adult) {
                chooseMaturity(&r);
            }
            chooseDeath(&r);
            if (!r.is_alive) {
                countDeath[month / 12]++;
                break; 
            }
        }
    }
    for (int i=0; i < 16; i++) {
        printf("Lapins morts à l'âge de %d ans: %d\n", i, countDeath[i]);
    }

    // test de la mise à jour d'un lapin et de l'affichage de ses informations
    for (int i=0; i < 10; i++) {
        initRabbit(&r);
        for (int month = 0; month < 240; month++) {
            updateRabbit(&r);
            showRabbit(&r);
            if (!r.is_alive) {
                printf("Le lapin est mort à l'âge de %d mois.\n", r.age_month);
                break;
            }
        }
    }

    return 0;
}