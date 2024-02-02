#GRAPHIQUE S
gnuplot << EOF
set terminal pngcairo size 1200,800 enhanced font 'Arial,12'
set output 'images/histogramme_s.png'
set title 'GRAPHIQUE TRAITEMENT S'
set xlabel 'STEP ID'
set ylabel 'DISTANCE'
set yrange [0:1000]
set xtics rotate by 45 right
set datafile separator ';'
plot 'demo/fichier_traite_opt_s.csv' using 0:3:5:xticlabel(2) with filledcurves lc rgb 'blue' lt 1 title "Distance Max/Min (en km)", \
'demo/fichier_traite_opt_s.csv' using 0:4 with lines linecolor 2 title "Distance moyenne (en km)"
EOF
gnuplot "graphique_s.gp" ;;