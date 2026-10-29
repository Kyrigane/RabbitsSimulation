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
    int nbLitter;
    int countLitter[13]={0};
    for (int i=0; i <= 10000; i++) {
        nbLitter = chooseNbLitterPerYear();
        countLitter[nbLitter]++;
    }
    for (int i=0; i < 13; i++) {
        printf("Nombre de portées par an, %d: %d\n", i, countLitter[i]);
    }

    //test du choix de la grossesse d'une lapine
    Rabbit r;
    initRabbit(&r);
    bool pregnancy;
    int nbLitterReal=0;
    for (int i=0; i < 120; i++) {
        if (i % 12 == 0) {
            nbLitter = chooseNbLitterPerYear();
        }
        pregnancy = choosePregnancy(&r, nbLitter);
        if (pregnancy) {
            nbLitterReal++;
        }
        if (i % 12 == 11) {
            printf("Année %d: Portées par an attendues : %d (Portées réelles : %d)\n", i/12 + 1, nbLitter, nbLitterReal);
            nbLitterReal = 0;
        }
    }

    // test du choix du nombre de lapereaux par portée d'une lapine
    int countNewborns[4]={0};
    for (int i=0; i < 10000; i++) {
        initRabbit(&r);
        r.is_pregnant = true;
        int nbNewborns = chooseNbNewborns(&r);
        countNewborns[nbNewborns - 3]++;
    }
    for (int i=0; i < 4; i++) {
        printf("Nombre de lapereaux par portée, %d: %d\n", i+3, countNewborns[i]);
    }

    return 0;
}