#GRAPHIQUE D1
set terminal pngcairo size 800,600
set output 'images/histogramme_d1.png'
set title 'LES CONDUCTEURS AVEC LE PLUS GRAND NOMBRE DE TRAJETS'
set ylabel 'PRENOM ET NOM DES CONDUCTEURS'
set xlabel 'NOMBRE DE TRAJETS'
set yrange [0:*]      
set style fill solid  
unset key            
set datafile separator ';'
myBoxWidth = 0.8
set offsets 0,0,0.5-myBoxWidth/2.,0.5

plot 'temp/resultats_d1.txt' using (0.5*$2):0:(0.5*$2):(myBoxWidth/2.):(2.6):ytic(1) with boxxy lc var