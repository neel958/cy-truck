#GRAPHIQUE L
set terminal pngcairo size 800,600
set output 'images/histogramme_l.png'
set title 'LES 10 TRAJETS LES PLUS LONGS'
set ylabel 'DISTANCE'
set xlabel 'ROOT ID'
set yrange [0:*]      
set boxwidth 0.5      
unset key            
set style fill solid  
set colors podo
set datafile separator ';'
plot 'temp/resultats_L.txt' using 0:2:(3):xtic(1) with boxes lc variable