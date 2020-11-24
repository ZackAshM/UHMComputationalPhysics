
# Gnuplot script file for plotting data
# This file is called hypersphere.plt
set title 'Monte Carlo Integration of Sphere, Ntrials = 500000'
set xlabel 'Dimension'
set ylabel 'Hypersphere Volume'
unset logscale y
unset logscale x
set ticslevel  0
set origin 0,0
set pointsize 0.95
set key 
plot "hypersphere.dat" using 1:3 title "Vsphere" with linespoints lt 7 lw 1.5,\
      "hypersphere.dat" using 1:4 title "Vactual" with linespoints lt 6 lc "black"
      
