reset
set xlabel "Iteration"
set ylabel "Distance"
set yrange [400:800]
set xtics 0,50,1000
set ytics 20
set title "Alpha"


plot  'output_a_4.000000_b_2.000000_q_0.900000.txt' with lines linewidth 2 title 'Alpha = 4',\
'output_a_2.000000_b_2.000000_q_0.900000.txt' with lines linewidth 2 title 'Alpha = 2',\
'output_a_1.000000_b_2.000000_q_0.900000.txt' with lines linewidth 2 title 'Alpha = 1',\
'output_a_0.500000_b_2.000000_q_0.900000.txt' with lines linewidth 2 title 'Alpha = 0.5'