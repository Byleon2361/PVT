set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'graph.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo

set xlabel "Threads" font 'Calibri,16'
set ylabel "Acceleration" font 'Calibri,16'

plot x title "Linear Acceleration" with lines lc rgb 'blue' lt 1 lw 2,\
     '15mn.dat' using 1:2 title "N=15000" with linespoints ls 2,\
     '20mn.dat' using 1:2 title "N=20000" with linespoints ls 3,\
     '25mn.dat' using 1:2 title "N=25000" with linespoints ls 4