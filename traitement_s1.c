#include "main.h"
   



int main() {
    FILE *f1 = fopen("data.csv", "r");
    if (f1 == NULL) { 
        printf("Erreur lors de l'ouverture de <<data.csv>> \n");
        return 1;
    }
    
    FILE *f2 = fopen("data_temp_s.csv", "w+");
    if (f2 == NULL) {
        printf("Erreur lors de l'ouverture de <<data_temp_s.csv>> \n");
        fclose(f1);
        return 1;
    }

    int id_maximum = -1;
    struct trajet *trajet_1 = NULL;
    int z = 1; // nombre de ligne

    char line[100];
    while (fgets(line, sizeof(line), f1)) {
        if (z == 1) {
                z++;
                continue;
            }     
        int id; 
        float value;
        if (sscanf(line, "%d;%f", &id, &value) != 2) {
            printf("Impossible de lire la ligne : %s", line);
            continue; // continuer et ignorer si il y a un probleme
        }

        // Verifier si l'id est > 0
        if (id >= 0) {
            // Mettre à jour le + grand
            if (id > id_maximum) {
                id_maximum = id;
            }

            // Réallouer dynamiquement la mémoire si nécessaire
            trajet_1 = realloc(trajet_1, (id_maximum + 1) * sizeof(struct trajet));

            // Initialiser
            if (trajet_1[id].count == 0) {
                trajet_1[id].id = id;
                trajet_1[id].min = value;
                trajet_1[id].max = value;
                trajet_1[id].somme = value;
                trajet_1[id].count = 1;
            } 
            else {
                if (value < trajet_1[id].min) {
                    trajet_1[id].min = value;
                }
                if (value > trajet_1[id].max) {
                    trajet_1[id].max = value;
                }
                trajet_1[id].somme += value;
                trajet_1[id].count++;
            }
        }
    }

    for (int i = 0; i <= id_maximum; i++) {
        if (trajet_1[i].count > 0) {
            trajet_1[i].moyenne = trajet_1[i].somme / trajet_1[i].count;
            trajet_1[i].difference = trajet_1[i].max - trajet_1[i].min;
            fprintf(f2, "%d;%.3f;%.2f;%.3f;%.3f\n", trajet_1[i].id, trajet_1[i].min, trajet_1[i].moyenne, trajet_1[i].max, trajet_1[i].difference);
        }
    }

    // Libérer la mémoire allouée dynamiquement
    free(trajet_1);

    fclose(f1);
    fclose(f2);

   

    return 0;
}
