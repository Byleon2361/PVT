set terminal pdf color enhanced font 'Calibri,16' size 14cm,10cm
set output 'graph.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo

set xlabel "Threads" font 'Calibri,16'
set ylabel "Acceleration" font 'Calibri,16'

plot x title "Linear Acceleration" with lines lc rgb 'blue' lt 1 lw 2,\
     'v1.dat' using 1:2 title "v1" with linespoints ls 2,\
     'v2.dat' using 1:2 title "v2" with linespoints ls 3,\
     'v3.dat' using 1:2 title "v3" with linespoints ls 4, \
     'v4.dat' using 1:2 title "v4" with linespoints ls 5,\
     'v5.dat' using 1:2 title "v5" with linespoints ls 6