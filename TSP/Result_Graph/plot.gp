reset
set xlabel "Iteration"
set ylabel "Distance"
set yrange [400:560]
set xtics 0,50,1000
set ytics 20
set title "Q"


plot  'output_a_1.000000_b_2.000000_q_1.000000.txt' with linespoints pi 50 linewidth 2 title 'Q = 1',\
'output_a_1.000000_b_2.000000_q_0.950000.txt' with linespoints pi 50 linewidth 2 title 'Q = 0.95',\
'output_a_1.000000_b_2.000000_q_0.900000.txt' with linespoints pi 50 linewidth 2 title 'Q = 0.9',\
'output_a_1.000000_b_2.000000_q_0.800000.txt' with linespoints pi 50 linewidth 2 title 'Q = 0.8'