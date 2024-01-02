# Configuration du style du graphique
set style data histograms
set style fill solid border -1

# Titres et légendes
set title "Top 10 Conducteurs - Distance Totale Parcourue"
set xlabel "Distance Totale Parcourue"
set ylabel "Conducteurs"
set ytics nomirror
set y2tics nomirror
set y2label "Distance"

# Paramètres pour l'affichage des noms de conducteurs sur l'axe y
set yrange [0.5:10.5]
set y2range [0:*]

# Utilisation des données provenant du fichier résultat_d2.txt
plot "temp/resultat_d2.txt" using 3:xticlabels(1) title "Distance" axes x1y2
