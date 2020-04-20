reset
set xlabel "x"
set ylabel "y"
set title "收斂圖"
set terminal svg
M = 3
ACO = 2
PSO = 500
file = sprintf('Result_M_%d_ACO_%d_PSO_%d.txt' , M , ACO , PSO)
keytitle = sprintf('ACO = %d PSO = %d' , M , ACO , PSO)
outputname = sprintf("收斂圖 M = %d.svg", M)
filetitle = sprintf("收斂圖 M = %d" , M)
set title filetitle
set output outputname
set yrange [:485]

plot 'Result_M_3_ACO_2_PSO_500.txt' with linespoints lw 2 pi 50 title keytitle,\
'Result_M_3_ACO_5_PSO_200.txt'with linespoints lw 2 pi 50 title 'ACO = 5 PSO = 200',\
'Result_M_3_ACO_10_PSO_100.txt' with linespoints lw 2 pi 50 title 'ACO = 10 PSO = 100',\
'ACO_Result_M_3_ACO_2_PSO_500.txt'with linespoints lw 2 pi 50 title 'ACO only'
