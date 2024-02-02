#!/bin/bash

#vérification des dossiers 'temp' et 'images'

dossier_temp="temp"
dossier_images="images"

#création des dossiers s'ils n'existent pas

[ -d "$dossier_temp" ] && rm -rf "$dossier_temp"/* || mkdir "$dossier_temp"
[ ! -d "$dossier_images" ] && mkdir "$dossier_images"

#éxécutables en langage C

executable_t="$dossier_progc/executable_t"
executable_s="$dossier_progc/executable_s"

#Message d'aide expliquant les options (option -h)

for arg in "$@" ; do
if [ "$arg" = "-h" ] ; then
echo "Format d'utilisation : $0 chemin_du_fichier_csv traitement1 traitement2..."
echo "Les différentes options de traitement :"
echo "-traitement [D1] -Récupérer les 10 conducteurs avec le plus de trajet et afficher le graphique correspondant."
echo "-traitement [D2] -Récupérer les 10 conducteurs avec les plus grandes distances parcourues et afficher le graphique correspondant."
echo "-traitement [L]  -Récupérer les 10 identifiants de route avec les plus grandes distances et afficher le graphique correspondant."
echo "-traitement [T]  -Récupérer les 10 villes avec le plus de trajets qui parcourent ces dernières et afficher le graphique correspondant"
echo "-traitement [S]  -Récupérer les identifiants de route avec les 50 plus grandes distances maximales, minimales et moyennes et afficher le graphique correspondant."
exit 0
fi
done

#Vérification du nombre d'arguments

if [ "$#" -lt 2 ] ; then
echo "Rappel du format d'usage : $0 chemin_du_fichier_csv traitement1 traitement2..."
exit 1
fi

#Début de la mesure du temps d'éxécution

temps_debut=$(date +%s)

#Compilation des programmes C s'ils ne sont pas

#Chemin du fichier CSV

chemin_fichier_csv="$1"

#Traitement en fonction du choix de l'utilisateur

case "$2" in

#Traitement [D1]

-D1)  
awk -F ';' '!seen[$1 FS $6]++ {print $1 FS $6}' data.csv | cut -d';' -f2 | sort | uniq -c | sort -rn | head -10 | awk '{print $2, $3, ";",$1}' | tac > "$dossier_temp/resultats_d1.txt"

awk '{print $1, $2}' "$dossier_temp/resultats_d1.txt" | cat  

gnuplot "graphique_d1.gp" ;;

#Traitement [D2]

-D2)
awk -F ';' '{somme_distance[$6]+=$5} END { for (personne in somme_distance) print personne, somme_distance[personne] }' data.csv | sort -rnt' ' -k3 | head -10 | awk '{print ""$1, $2"", ";", $3}' | tac > "$dossier_temp/resultats_d2.txt"

awk '{print $1, $2}' "$dossier_temp/resultats_d2.txt" | cat  
 
gnuplot "graphique_d2.gp" ;;

#Traitement [L]

-L)
awk -F ';' '{somme_etapes[$1]+=$5} END { for (trajet in somme_etapes) print trajet, somme_etapes[trajet] }' data.csv | sort -rnt' ' -k2 | head -n 10 | sort -n -k1 | awk '{print $1, ";", $2}' > "$dossier_temp/resultats_L.txt"

awk '{print $1}' "$dossier_temp/resultats_L.txt" | cat

gnuplot "graphique_l.gp" ;;

#Traitement [S]

-S)


awk -F";" ' FNR > 1 {print $1 ";" $5}' "$dossier_temp" > data_temp_s.csv
gcc -o traitement_s1 traitement_s1.c
gcc -o traitement_s2 traitement_s2.c
./traitement_s1
./traitement_s2
gnuplot "graphique_s.gp" ;;


#Traitement [T]

-T)
gcc -o traitement_t traitement_t.c
./traitement_t
gnuplot "graphique_t.gp"
esac

temps_fin=$(date +%s)
temps_execution=$((temps_fin - temps_debut))
echo "Temps d'éxécution : $temps_execution secondes"

