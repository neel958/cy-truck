#include "main.h"
   

struct trajet {
    int id;
    float min;
    float max;
    float somme;
    int count;
    float moyenne;
    float difference;
};

int main() {
    FILE *input = fopen("data.csv", "r");
    if (input == NULL) { 
        fprintf(stderr, "Impossible d'ouvrir <<data.csv>> \n");
        return 1;
    }
    
    FILE *output = fopen("data_temp_s.csv", "w+");
    if (output == NULL) {
        fprintf(stderr, "Impossible d'ouvrir <<data_temp_.csv>> \n");
        fclose(input);
        return 1;
    }

    // Variables pour gérer dynamiquement la mémoire
    int max_id = -1;
    struct trajet *stats = NULL;
    int lineNumber = 1;

    char line[100];
    while (fgets(line, sizeof(line), input)) {
        if (lineNumber == 1) {
                lineNumber++;
                continue;
            }     
        int id; 
        float value;
        if (sscanf(line, "%d;%f", &id, &value) != 2) {
            fprintf(stderr, "Erreur lors de la lecture de la ligne : %s", line);
            continue; // Ignorer la ligne incorrecte et passer à la suivante
        }

        // Vérifier si l'identifiant est dans la plage attendue
        if (id >= 0) {
            // Mettre à jour le plus grand identifiant rencontré
            if (id > max_id) {
                max_id = id;
            }

            // Réallouer dynamiquement la mémoire si nécessaire
            stats = realloc(stats, (max_id + 1) * sizeof(struct trajet));

            // Initialiser à zéro si l'élément est nouvellement alloué
            if (stats[id].count == 0) {
                stats[id].id = id;
                stats[id].min = value;
                stats[id].max = value;
                stats[id].somme = value;
                stats[id].count = 1;
            } 
            else {
                // Mettre à jour les statistiques
                if (value < stats[id].min) {
                    stats[id].min = value;
                }
                if (value > stats[id].max) {
                    stats[id].max = value;
                }
                stats[id].somme += value;
                stats[id].count++;
            }
        }
    }

    for (int i = 0; i <= max_id; i++) {
        if (stats[i].count > 0) {
            stats[i].moyenne = (float)stats[i].somme / stats[i].count;
            stats[i].difference = (float)stats[i].max - (float)stats[i].min;
            fprintf(output, "%d;%.3f;%.2f;%.3f;%.3f\n", stats[i].id, stats[i].min, stats[i].moyenne, stats[i].max, stats[i].difference);
        }
    }

    // Libérer la mémoire allouée dynamiquement
    free(stats);

    fclose(input);
    fclose(output);

   

    return 0;
}