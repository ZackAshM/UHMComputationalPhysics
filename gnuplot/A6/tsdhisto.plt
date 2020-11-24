
# Gnuplot script file for plotting data
# This file is called tsd.plt
set title 'Time Series Decay Count'
set xlabel 'Possible counts'
set ylabel 'Times Decay Count was Observed'
set auto x
set ticslevel  0
set origin 0,0
set pointsize 0.95
set nokey 
set style data histogram
set style fill solid border -1
set boxwidth 2
plot "tsd_mb.dat" using 2:xtic(1) lc "blue"

