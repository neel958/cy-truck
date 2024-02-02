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
    struct trajet *trajet = NULL;
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
            trajet = realloc(trajet, (id_maximum + 1) * sizeof(struct trajet));

            // Initialiser
            if (trajet[id].count == 0) {
                trajet[id].id = id;
                trajet[id].min = value;
                trajet[id].max = value;
                trajet[id].somme = value;
                trajet[id].count = 1;
            } 
            else {
                if (value < trajet[id].min) {
                    trajet[id].min = value;
                }
                if (value > trajet[id].max) {
                    trajet[id].max = value;
                }
                trajet[id].somme += value;
                trajet[id].count++;
            }
        }
    }

    for (int i = 0; i <= id_maximum; i++) {
        if (trajet[i].count > 0) {
            trajet[i].moyenne = trajet[i].somme / trajet[i].count;
            trajet[i].difference = trajet[i].max - trajet[i].min;
            fprintf(f2, "%d;%.3f;%.2f;%.3f;%.3f\n", trajet[i].id, trajet[i].min, trajet[i].moyenne, trajet[i].max, trajet[i].difference);
        }
    }

    // Libérer la mémoire allouée dynamiquement
    free(trajet);

    fclose(f1);
    fclose(f2);

   

    return 0;
}
