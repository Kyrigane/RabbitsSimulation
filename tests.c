#include "./rabbit.h"
#include <stdio.h>

void export_litter_distribution_to_csv() {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    FILE *fichier_csv = fopen("portees.csv", "w");
    if (fichier_csv == NULL) {
        printf("Erreur de création du fichier CSV.\n");
        return;
    }
    
    fprintf(fichier_csv, "Nb_Portees,Occurrences\n");

    Rabbit r;
    initRabbit(&r);
    r.is_female = true; 
    r.is_alive = true;

    int countLitter[15] = {0};
    int nb_tests = 100000;

    for (int i = 0; i < nb_tests; i++) {
        chooseNbLitterPerYear(&r);
        if (r.nb_litter_per_year >= 0 && r.nb_litter_per_year < 15) {
            countLitter[r.nb_litter_per_year]++;
        }
    }

    for (int i = 2; i <= 10; i++) {
        fprintf(fichier_csv, "%d,%d\n", i, countLitter[i]);
    }

    fclose(fichier_csv);
}

void export_pregnancy_distribution_to_csv() {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    FILE *fichier_csv = fopen("grossesses.csv", "w");
    if (fichier_csv == NULL) {
        printf("Erreur de création du fichier CSV.\n");
        return;
    }

    fprintf(fichier_csv, "Nb_Portees,Attendues,Reelles\n");

    Rabbit r;
    initRabbit(&r);
    r.is_female = true;
    r.is_alive = true;

    int countExpected[15] = {0};
    int countReal[15] = {0};
    int nb_annees = 100000;

    for (int annee = 0; annee < nb_annees; annee++) {
        chooseNbLitterPerYear(&r);
        int expected = r.nb_litter_per_year;
        
        if (expected >= 0 && expected <= 14) {
            countExpected[expected]++;
        }

        int nbLitterReal = 0;
        for (int mois = 0; mois < 12; mois++) {
            choosePregnancy(&r);
            if (r.is_pregnant) {
                nbLitterReal++;
            }
            r.is_pregnant = false;
        }
        
        if (nbLitterReal >= 0 && nbLitterReal <= 14) {
            countReal[nbLitterReal]++;
        }
    }

    for (int i = 1; i <= 12; i++) {
        fprintf(fichier_csv, "%d,%d,%d\n", i, countExpected[i], countReal[i]);
    }

    fclose(fichier_csv);
}

void export_newborn_distribution_to_csv() {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    FILE *fichier_csv = fopen("lapereaux.csv", "w");
    if (fichier_csv == NULL) {
        printf("Erreur de création du fichier CSV.\n");
        return;
    }
    
    fprintf(fichier_csv, "Lapereaux,Occurrences\n");

    Rabbit r;
    initRabbit(&r);
    r.is_female = true;
    r.is_alive = true;

    int countNewborns[7] = {0};
    int nb_tests = 100000;

    for (int i = 0; i < nb_tests; i++) {
        r.is_pregnant = true; 
        
        int nb = chooseNbNewborns(&r);
        
        if (nb >= 3 && nb <= 6) {
            countNewborns[nb]++;
        }
    }
    for (int i = 3; i <= 6; i++) {
        fprintf(fichier_csv, "%d,%d\n", i, countNewborns[i]);
    }

    fclose(fichier_csv);
}

void export_maturity_distribution_to_csv() {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    FILE *fichier_csv = fopen("maturite.csv", "w");
    if (fichier_csv == NULL) {
        printf("Erreur de création du fichier CSV.\n");
        return;
    }
    
    fprintf(fichier_csv, "Mois_Maturite,Occurrences\n");

    int countMaturity[9] = {0}; 
    int nb_tests = 100000;

    for (int i = 0; i < nb_tests; i++) {
        Rabbit r;
        initRabbit(&r);
        r.is_adult = false;
        r.is_alive = true;

        for (int month = 5; month <= 8; month++) {
            r.age_month = month;
            chooseMaturity(&r);
            
            if (r.is_adult) {
                countMaturity[month]++;
                break;
            }
        }
    }
    for (int month = 5; month <= 8; month++) {
        fprintf(fichier_csv, "%d,%d\n", month, countMaturity[month]);
    }

    fclose(fichier_csv);
}

void export_death_distribution_to_csv() {
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);

    FILE *fichier_csv = fopen("mortalite_mois.csv", "w");
    if (fichier_csv == NULL) {
        printf("Erreur de création du fichier CSV.\n");
        return;
    }
    
    fprintf(fichier_csv, "Age_Deces_Mois,Occurrences\n");

    int countDeath[181] = {0};
    int nb_tests = 100000;

    for (int i = 0; i < nb_tests; i++) {
        Rabbit r;
        initRabbit(&r);
        r.is_adult = false;
        r.is_alive = true;

        for (int month = 0; month <= 180; month++) {
            r.age_month = month;
            if (!r.is_adult) {
                chooseMaturity(&r);
            }
            
            chooseDeath(&r);
            
            if (!r.is_alive) {
                countDeath[month]++;
                break; 
            }
        }
    }

    for (int i = 0; i <= 180; i++) {
        fprintf(fichier_csv, "%d,%d\n", i, countDeath[i]);
    }

    fclose(fichier_csv);
}

int main() {
    printf("Quelles données voulez-vous exporter ?\n");
    printf("1. Distribution du nombre de portées par an (Loi normale)\n");
    printf("2. Distribution du nombre de portées par an après Bernoulli\n");
    printf("3. Distribution du nombre de lapereaux par portée (Loi uniforme)\n");
    printf("4. Distribution de la maturité (Loi uniforme)\n");
    printf("5. Distribution de la mortalité par mois (Loi de Bernoulli)\n");
    int choix;
    scanf("%d", &choix);
    switch (choix) {
        case 1:
            export_litter_distribution_to_csv();
            break;
        case 2:
            export_pregnancy_distribution_to_csv();
            break;
        case 3:
            export_newborn_distribution_to_csv();
            break;
        case 4:
            export_maturity_distribution_to_csv();
            break;
        case 5:
            export_death_distribution_to_csv();
            break;
        default:
            printf("Choix invalide.\n");
    }
    return 0;
}