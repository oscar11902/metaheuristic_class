reset
set xlabel "x"
set ylabel "y"
set title "路徑圖"
set terminal svg
set key  out bot horiz box
M = 7
ACO = 10
PSO = 100
file = sprintf('Path_M_%d_ACO_%d_PSO_%d.txt' , M , ACO , PSO)
outputname = sprintf("路徑圖 M = %d.svg", M)
set output outputname
plot file with linespoints title "Result = 41.68"