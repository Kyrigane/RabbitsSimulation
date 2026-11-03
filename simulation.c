#include "./fibonacci.h"
#include "./population.h"
#include <time.h>
#include <stdio.h>

void simulate_fibonacci(int months) {
    printf("Simulation avec la suite de Fibonacci:\n");

    month_simulation simulation_fibonacci;
    for (int month = 0; month <= months; month++) {
        simulate_rabbit_fibonacci(&simulation_fibonacci, month);
        affiche_simulation(&simulation_fibonacci);
    }
}

void better_simulation(int nb_simulations, int nb_couples, int years) {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    printf("======================================================\n");
    printf("Simulation avancée avec la population de lapins:\n");
    printf("======================================================\n");

    FILE *fichier_csv = fopen("resultats.csv", "w");
    FILE *fichier_stats = fopen("stats.csv", "w");
    if (fichier_csv == NULL || fichier_stats == NULL) {
        printf("Erreur lors de la création des fichiers CSV.\n");
        return;
    }
    fprintf(fichier_csv, "Mois,Population,Experience\n");
    fprintf(fichier_stats, "Experience,Survecu,Temps_s\n");

    RabbitPopulation population;
    clock_t startTime;
    clock_t endTime;
    double timeSpent=0;

    for (int iPopulation = 0; iPopulation < nb_simulations; iPopulation++) {
        initRabbitPopulation(&population, 100000000);
        for (int i = 0; i < nb_couples; i++) {
            Rabbit femelle = (Rabbit){12, 0, false, true, true, true}; // Lapine adulte
            chooseNbLitterPerYear(&femelle);
            Rabbit male = (Rabbit){12, 0, false, true, true, false}; // Lapin adulte
            addRabbitToPopulation(&population, femelle);
            addRabbitToPopulation(&population, male);
        }

        printf("===========================\n");
        printf("Simulation de la population de lapins %d:\n", iPopulation + 1);
        printf("===========================\n");

        startTime = clock();

        for (int month = 0; month <= years * 12; month++) {
            
            fprintf(fichier_csv, "%d,%zu,%d\n", month, population.count, iPopulation + 1);

            updateRabbitPopulation(&population);
            
            if (month % 12 == 0) {
                printf("Année %d: ", month / 12);
                printf("Population de %zu lapins\n", population.count);
            }
            
            if (population.count == 0) {
                printf("Tous les lapins sont morts.\n");
                break;
            }
        }

        endTime = clock();
        timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
        printf("Temps écoulé pour la simulation : %.2f secondes\n", timeSpent);

        int a_survecu = (population.count > 0) ? 1 : 0;
        fprintf(fichier_stats, "%d,%d,%f\n", iPopulation + 1, a_survecu, timeSpent);

        freeRabbitPopulation(&population); 
    }

    fclose(fichier_csv);
    fclose(fichier_stats);
    
    printf("===========================\n");
    printf("Les résultats ont été exportés dans 'resultats.csv' et 'stats.csv'.\n");
    printf("Simulations terminées.\n");

}


int main(){
    printf("======================================================\n");
    printf("Bienvenue dans le simulateur de population de lapins!\n");
    printf("======================================================\n");

    int choix;
    printf("Choisissez le type de simulation:\n");
    printf("1. Simulation avec la suite de Fibonacci\n");
    printf("2. Simulation avancée avec la population de lapins\n");
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            int months;
            printf("Entrez le nombre de mois pour la simulation Fibonacci (max 46): ");
            scanf("%d", &months);
            if (months < 0 || months > 46) {
                printf("Nombre de mois invalide.\n");
                return 1;
            }
            simulate_fibonacci(months);
            break;
        case 2:
            int nb_simulations, nb_couples, years;
            printf("Entrez le nombre de simulations à effectuer (max 40): ");
            scanf("%d", &nb_simulations);
            if (nb_simulations < 1 || nb_simulations > 40) {
                printf("Nombre de simulations invalide.\n");
                return 1;
            }
            printf("Entrez le nombre de couples initiaux de lapins (max 3): ");
            scanf("%d", &nb_couples);
            if (nb_couples < 1 || nb_couples > 3) {
                printf("Nombre de couples invalide.\n");
                return 1;
            }
            printf("Entrez le nombre d'années pour la simulation (max 10): ");
            scanf("%d", &years);
            if (years < 1 || years > 10) {
                printf("Nombre d'années invalide.\n");
                return 1;
            }
            better_simulation(nb_simulations, nb_couples, years);
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }


    return 0;
}