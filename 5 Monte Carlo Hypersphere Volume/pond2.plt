
# Gnuplot script file for plotting data
# This file is called pond2.plt
set title 'Monte Carlo Integration of Circle'
set xlabel 'X distance'
set ylabel 'Y distance'
set xr [-1.05:1.05]
set yr [-1.05:1.05]
set ticslevel  0
set origin 0,0
set size 1
set pointsize 0.95
set nokey 
plot "pond2.dat" index 0 using 1:2 with points,\
      "pond2.dat" index 1 using 1:2 with points
      
