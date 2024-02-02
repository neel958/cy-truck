#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_VILLE 35
#define NOMBRES_MAX_VILLES 10



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//traitement t :
//stock les informations sur une ville
typedef struct ApparitionVILLE {
    char nom[TAILLE_VILLE];
    int totalVisites;
    struct ApparitionVILLE *gauche;
    struct ApparitionVILLE *droite;
    int hauteur;
} ApparitionVILLE;

// retourne le maximum entre deux entiers
int max(int a, int b);

//calcule la hauteur d'un noeud dans l'arbre
int hauteur(ApparitionVILLE *N);

// Crée un nouveau nœud pour une ville avec son nom et initialise les données 
ApparitionVILLE *nouvelleVille(char *nom);

// Rotations sur les AVL : 
ApparitionVILLE *rotationDroite(ApparitionVILLE *y);
ApparitionVILLE *rotationGauche(ApparitionVILLE *x);

// Retourne l'équilibre d'un noeud
int calculEQUILIBRE(ApparitionVILLE *N);

// Insére une ville dans l'arbre
ApparitionVILLE *insererVille(ApparitionVILLE *noeud, char *nom);

// Récupere les 10 villes avec le plus de visites
void parcoursPrefixe(ApparitionVILLE *racine, ApparitionVILLE *topVilles[], int *nbVilles);

int comparerVisites(const void *a, const void *b);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//traitement s : 
struct trajet {
    int id;
    float min;
    float max;
    float somme;
    int count;
    float moyenne;
    float difference;
}trajet;

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


// Retourne le maximum entre deux nombres
int max(int a, int b);



// Retourne le minimum entre deux nombres
int min(int a, int b);

// Rotations AVL : 
pArbre rotationgauche(pArbre a);
pArbre rotationdroite(pArbre a);
pArbre doubleRotationGauche(pArbre a);
pArbre doubleRotationDroite(pArbre a);


// Equilibre AVL
pArbre equilibrerAVL(pArbre a);

pArbre creerNoeud(int id, float diff, float max, float min, float moy);

pArbre insertionAVL(pArbre x, int id, float diff, float max, float min, float moy, int *h);

void extrairecol(pArbre *a, FILE *fichier);

void parcoursDecroissant(pArbre a, FILE *fichierSortie, int *i);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif