set term png;

set output 'graphique.png';
plot 'fichier.txt' using 1:2 title 'comparaisons' with lines, 'fichier.txt' using 1:3 title 'echanges' with lines;

set xrange [0:500000];
set yrange[0:200000000];
set output 'lin_aleaT.png';
plot 'cas0.txt' using 1:2 title 'aleaT' with lines, \
'cas0.txt' using 1:3 title '200 n' with lines, \
'cas0.txt' using 1:4 title '300 n' with lines, \
'cas0.txt' using 1:5 title '400 n' with lines, \
'cas0.txt' using 1:6 title '500 n' with lines, \
'cas0.txt' using 1:7 title '600 n' with lines ;

set xrange [0:500000];
set yrange[0:200000000];
set output 'lin_aleaTL.png';
plot 'cas1.txt' using 1:2 title 'aleaT_lowrep' with lines, \
'cas1.txt' using 1:3 title 'aleaL_lowrep' with lines, \
'cas1.txt' using 1:4 title 'aleaT_highrep' with lines, \
'cas1.txt' using 1:5 title 'aleaL_highrep' with lines;

set xrange [0:500000];
set yrange[0:20000000];
set output 'lin_rechercheTL.png';
plot 'cas2.txt' using 1:2 title 'rechercheT_lowrep' with lines, \
'cas2.txt' using 1:3 title 'rechercheL_lowrep' with lines, \
'cas2.txt' using 1:4 title 'rechercheT_highrep' with lines, \
'cas2.txt' using 1:5 title 'rechercheL_highrep' with lines;

set xrange [0:500000];
set yrange[0:20000000];
set output 'lin_minimumTL.png';
plot 'cas3.txt' using 1:2 title 'minimumSimpleT' with lines, \
'cas3.txt' using 1:3 title 'minimumSimpleL' with lines, \
'cas3.txt' using 1:4 title 'minimumTriT' with lines, \
'cas3.txt' using 1:5 title 'minimumTriL' with lines;

set xrange [0:20];
set yrange[0:200];
set output 'lin_ref.png';
plot 'cas4.txt' using 1:2 title 'log n' with lines, \
'cas4.txt' using 1:3 title 'npk' with lines, \
'cas4.txt' using 1:4 title 'n log n' with lines, \
'cas4.txt' using 1:5 title 'exp' with lines, \
'cas4.txt' using 1:6 title 'kpn' with lines;

set xrange [0:20];
set yrange[0:1];
set output 'lin_lognepsi.png';
plot 'cas5.txt' using 1:2 title '2' with lines, \
'cas5.txt' using 1:3 title '1' with lines, \
'cas5.txt' using 1:4 title '0.5' with lines, \
'cas5.txt' using 1:5 title '0.2' with lines, \
'cas5.txt' using 1:6 title '0.1' with lines;

set xrange [0:10];
set yrange[0:500];
set output 'lin_npk2pn.png';
plot 'cas6.txt' using 1:2 title 'k = 2' with lines, \
'cas6.txt' using 1:3 title 'k = 4' with lines, \
'cas6.txt' using 1:4 title 'k = 6' with lines, \
'cas6.txt' using 1:5 title 'k = 8' with lines, \
'cas6.txt' using 1:6 title 'k = 10' with lines;
