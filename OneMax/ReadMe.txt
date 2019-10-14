使用 make
執行 OneMax

-a : ES HC TS SA

-l : string 長度 default 100
-i : iterator 次數 default 1000 
-r : run 次數 default 30 

//HC

./OneMax -a HC -l 80 -i 70 -r 50

//ES
-o : 0 1 是否timeout default false
-t : 執行時間(秒)) default 600

./OneMax -a ES -l 50 -o 0 -t 1000

//SA
-R : 退火的幅度 default 0.99
-s : 開始溫度 default 300
-e : 結束溫度 default 10

./OneMax -a SA -l 50 -s 900 -e 10 -R 0.999 -r 30

//TS
-A : 記憶長度 default 7

./OneMax -a TS -A 7 -r 10 -l 25 -i 100