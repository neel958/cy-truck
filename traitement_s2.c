#include "main.h"

#define TAILLE_BUFFER 4096


typedef struct AVL {
    int id;
    float dist_min;
    float dist_max;
    float dist_moy;
    float diff;
    struct AVL *fg;
    struct AVL *fd;
    int h;
}*pArbre;

int max(int a, int b) {         // Retourne le maximum entre deux nombres passés en paramètres
  if (a > b) {
    return a;
  } 
  else {
    return b;
  }
}

int min(int a, int b) {         // Retourne le minimum entre deux nombres passés en paramètres
  if (a < b) {
    return a;
  } 
  else {
    return b;
  }
}


pArbre rotationGauche(pArbre a) {
    pArbre pivot = a->fd;
    a->fd = pivot->fg;
    pivot->fg = a;
    int eq_a = a->h;
    int eq_p = pivot->h;

    a->h = eq_a - max(eq_p, 0) - 1;
    pivot->h = min(eq_a - 2, min(eq_a + eq_p - 2, eq_p - 1));
    a = pivot;
    return a;
}



pArbre rotationDroite(pArbre a) {
    pArbre pivot = a->fg;
    a->fg = pivot->fd;
    pivot->fd = a;
    int eq_a = a->h;
    int eq_p = pivot->h;
    a->h = eq_a - min(eq_p, 0) + 1;
    pivot->h = max(eq_a + 2, max(eq_a + eq_p + 2, eq_p + 1));
    a = pivot;
    return a;
}



pArbre doubleRotationGauche(pArbre a) {
    a->fd = rotationDroite(a->fd); // Rotation droite du fils droit de a puis rotation gauche de a
    a = rotationGauche(a);
    return a;
}



pArbre doubleRotationDroite(pArbre a) {
    a->fg = rotationGauche(a->fg); // Rotation gauche du fils gauche de a
    a = rotationDroite(a); // Rotation droite de a
    return a;
}


pArbre equilibrerAVL(pArbre a) {
    if (a->h >= 2) {
        // Sous-arbre droit plus profond
        if (a->fd->h >= 0) {
            return rotationGauche(a);
        } 
        else {
            return doubleRotationGauche(a);
        }
    } 
    else if (a->h <= -2) {
        // Sous-arbre gauche plus profond
        if (a->fg->h <= 0) {
            return rotationDroite(a);
        }
        else {
            return doubleRotationDroite(a);
        }
    }


    return a;
}


pArbre creerNoeud(int id, float diff, float max, float min, float moy) {
    pArbre nouveau = malloc(sizeof(struct AVL));
    if (nouveau != NULL) {
        nouveau->id = id;
        nouveau->dist_max = max;
        nouveau->dist_min = min;
        nouveau->dist_moy = moy;
        nouveau->diff = diff;
        nouveau->h = 0; 
        nouveau->fg = NULL;
        nouveau->fd = NULL;
    } 
    else {
        fprintf(stderr, "Erreur d'allocation dynamique pour le nouveau nœud.\n");
    }
    return nouveau;
}



pArbre insertionAVL(pArbre x, int id, float diff, float max, float min, float moy, int *h) {
    if (x == NULL) {
        *h = 1;
        return creerNoeud(id, diff, max, min, moy);
    } 
    else if (diff < x->diff) {
        x->fg = insertionAVL(x->fg, id, diff, max, min, moy, h);
        *h = -*h;
    } 
    else if (diff > x->diff) {
        x->fd = insertionAVL(x->fd, id, diff, max, min, moy, h);
    } 
    else if (diff == 0) {
        return x;
    }

    if (*h != 0) {
        x->h = x->h + *h;
        x = equilibrerAVL(x);

        if (x->h == 0) {
            *h = 0;
        } else {
            *h = 1;
        }
    }

    return x;
}




//fonction pour extraire la 5 eme colonne du fichier data.csv et les inserer dans un avl

void extrairecol5(pArbre *a, FILE *fichier) {
    if (a == NULL || fichier == NULL) {
        printf("Erreur, pointeur nul \n");
        return;
    }

    char ligne[TAILLE_BUFFER];
    int h;
    int id;
    float mini, moy, maxi;
    int i = 0;

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        char *token = strtok(ligne, "\n");
        int colonne = 1;

        while (token != NULL) {
            char *token2 = strtok(token, ";");

            while (token2 != NULL) {
                if (colonne == 1) {
                    id = atoi(token2);
                } 
                else if (colonne == 2) {
                    mini = atof(token2);
                } 
                else if (colonne == 3) {
                    moy = atof(token2);
                } 
                else if (colonne == 4) {
                    maxi = atof(token2);
                } 
                else if (colonne == 5) {
                    float diff = atof(token2);
                    i++;
                    *a = insertionAVL(*a, id, diff, maxi, mini, moy, &h);
                }

                token2 = strtok(NULL, ";");
                colonne++;
            }

            token = strtok(NULL, "\n");
        }
    }
}





void parcoursDecroissant(pArbre a, FILE *fichierSortie, int *i, const int lim) {
    if (a == NULL || fichierSortie == NULL || i == NULL) {
        return;
    }

    if (*i <= lim) {
        parcoursDecroissant(a->fd, fichierSortie, i, lim);
        if (*i <= lim) {
            fprintf(fichierSortie, "%d;%d;%.3f;%.3f;%.3f;%.3f\n", *i, a->id, a->dist_min, a->dist_moy, a->dist_max, a->diff);
            (*i)++;
        }
        parcoursDecroissant(a->fg, fichierSortie, i, lim);
    }
}

void libererAVL(pArbre a) {
    if (a != NULL) {
        libererAVL(a->fg);
        libererAVL(a->fd);
        free(a);
    }
}

int main() {
    FILE *f1, *f2;
    pArbre a = NULL;

    f1 = fopen("data_temp_s.csv", "r");
    if (f1 == NULL) {
        printf("Erreur");
        return 1;
    }

    f2 = fopen("data_s.csv", "w");
    if (f2 == NULL) {
        printf("Erreur");
        fclose(f1);
        return 1;
    }

    extrairecol5(&a, f1);

    int compteur = 1;
    parcoursDecroissant(a, f2, &compteur, 50);

    fclose(f1);
    fclose(f2);

    libererAVL(a);

    return 0;
}