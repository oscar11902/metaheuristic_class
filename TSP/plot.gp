reset
set output 'output.png'
set title "ACO"
set xlabel "Iteration"
set ylabel "Distance"
set xrange [0:1000]
set yrange [400:800]
set xtics 50
set ytics 10

plot  'Output_1.txt' with linespoints