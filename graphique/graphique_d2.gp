#GRAPHIQUE D2
set terminal pngcairo size 800,600
set output 'images/histogramme_d2.png'
set title 'LES CONDUCTEURS AVEC LA PLUS GRANDE DISTANCE PARCOURUE'
set ylabel 'PRENOM ET NOM DES CONDUCTEURS'
set xlabel 'DISTANCE'
set yrange [0:*]      
set style fill solid  
unset key            
set datafile separator ';'
myBoxWidth = 0.8
set offsets 0,0,0.5-myBoxWidth/2.,0.5

plot 'temp/resultats_d2.txt' using (0.5*$2):0:(0.5*$2):(myBoxWidth/2.):(2.6):ytic(1) with boxxy lc var