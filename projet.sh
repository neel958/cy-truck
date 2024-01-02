#!/bin/bash

# Dossiers à vérifier
dossier_temp="temp"
dossier_images="images"

# Création des dossiers 'temp' et 'images' si nécessaire
[ -d "$dossier_temp" ] && rm -rf "$dossier_temp"/* || mkdir "$dossier_temp"
[ ! -d "$dossier_images" ] && mkdir "$dossier_images"

# Emplacements des exécutables C
# executable_t="chemin/vers/executable_t"
# executable_s="chemin/vers/executable_s"

# Gestion de l'option d'aide (-h)
for arg in "$@"; do
    if [ "$arg" = "-h" ]; then
        echo "Usage: $0 chemin_du_fichier_csv traitement1 [traitement2 ...]"
        echo "Options de traitement :"
        echo "- traitement1 : Description du traitement1"
        echo "- traitement2 : Description du traitement2"
        exit 0
    fi
done

# Vérification des arguments
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 chemin_du_fichier_csv traitement1 [traitement2 ...]"
    exit 1
fi

# Début de la mesure du temps
start_time=$(date +%s)

# Implémentation des traitements
case "$2" in
  -d1)
    # Traitement D1 avec Shell
    awk -F ';' '{print $5, ";" , $6}' "$1" | sort -u | awk -F ';' '{print $2}' | sort | uniq -c | sort -nt " " -k1 | tail  -10 | awk '{print """$2, $3""", $1}' > "$dossier_temp/resultat_d1.txt"

    cut -d ' ' -f1,2 "$dossier_temp/resultat_d1.txt" | tac

    gnuplot "graph.gp"
    ;;

  -d2)
    # Vérification de l'existence du fichier CSV
    if [ ! -f "$1" ]; then
        echo "Le fichier CSV $1 n'existe pas."
        exit 1
    fi

    # Traitement D2 avec Shell
    awk -F ';' '{print $6, ";" , $5}' "$1" | sort | uniq -c | sort -nrk1 | head -n 10 | awk '{print """$2, $3""", $1}' > "$dossier_temp/resultat_d2.txt"

    # Affichage du résultat
    cut -d ' ' -f1,2 "$dossier_temp/resultat_d2.txt" | tac

    # Génération du graphique avec Gnuplot
    gnuplot "graph.gp"
    ;;

  *)
    echo "Option de traitement non reconnue."
    ;;

esac

# Fin de la mesure du temps
end_time=$(date +%s)
execution_time=$((end_time - start_time))
echo "Temps d'exécution total : $execution_time secondes."
