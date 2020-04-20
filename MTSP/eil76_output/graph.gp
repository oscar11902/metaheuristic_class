reset
set xlabel "x"
set ylabel "y"
set title "路徑圖"
set terminal svg
set key  bot box out horiz
M = 2
ACO = 5
PSO = 200
file = sprintf('Path_M_%d_ACO_%d_PSO_%d.txt' , M , ACO , PSO)
outputname = sprintf("路徑圖 M = %d.svg", M)
set output outputname
plot file with linespoints title "Result = 662.32"