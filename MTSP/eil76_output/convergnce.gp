reset
set xlabel "x"
set ylabel "y"
set title "收斂圖"
set terminal svg
M = 2
ACO = 2
PSO = 500
file = sprintf('Result_M_%d_ACO_%d_PSO_%d.txt' , M , ACO , PSO)
keytitle = sprintf('M = %d ACO = %d PSO = %d' , M , ACO , PSO)
outputname = sprintf("收斂圖 M = %d.svg", M)
set output outputname
plot file with lines lw 5 title keytitle