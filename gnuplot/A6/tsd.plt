
# Gnuplot script file for plotting data
# This file is called tsd.plt
set title 'Time Series of Decay'
set xlabel 'Time (s)'
set ylabel 'Decay'
set xr [0:180]
set ticslevel  0
set origin 0,0
set pointsize 0.95
set nokey 
plot "timeseriesdecay.dat" using 2:4 with linespoints lc "black"
      
