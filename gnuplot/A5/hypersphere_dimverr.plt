
# Gnuplot script file for plotting data
# This file is called hypersphere_dimverr.plt
set title 'Monte Carlo Integration of Sphere'
set xlabel 'Number of Trials'
set ylabel 'Fractional Error'
unset logscale y
set logscale x
set ticslevel  0
set origin 0,0
set pointsize 0.95
set key 
plot "hypersphere_dimverr.dat" index 0 using 2:4 title "Dim = 2" with linespoints lt 7,\
      "hypersphere_dimverr.dat" index 1 using 2:4 title "Dim = 3" with linespoints lt 6 lc "blue"
      
