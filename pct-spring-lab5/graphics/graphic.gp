set terminal pdf color enhanced font 'Calibri,16' size 15cm,10cm
set output 'graph.pdf'
set key inside left top font 'Calibri,16'
set colorsequence podo

set xlabel "Threads" font 'Calibri,16'
set ylabel "Acceleration" font 'Calibri,16'

plot '1000.dat' using 1:($2) with linespoints title 'quickSort(threadshold =1000)', \
     'line.dat' using 1:($2) with linespoints title 'Linear Acceleration',\

plot '10000.dat' using 1:($2) with linespoints title 'quickSort(threadshold =10000)',\
     'line.dat' using 1:($2) with linespoints title 'Linear Acceleration',\

plot '100000.dat' using 1:($2) with linespoints title 'quickSort(threadshold =100000)',\
     'line.dat' using 1:($2) with linespoints title 'Linear Acceleration',\
