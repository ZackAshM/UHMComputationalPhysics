
# Gnuplot script file for plotting data
# This file is called tsd.plt
set title 'Time Series Decay Count'
set xlabel 'Possible counts'
set ylabel 'Times Decay Count was Observed'
set xr [:16]
set ticslevel  0
set origin 0,0
set pointsize 1.25
set bar small
set key top right
set key font ",10"
f(x) = N*(m**x)*(exp(-m)/gamma(x+1))
N=166
fit f(x) "tsd_mb.dat" using 1:2:(1+sqrt($2+0.75)) via m, N
plot "tsd_mb.dat" using 1:2:(1+sqrt($2+0.75)) with yerrorbars title 'Decay Data' lt 7 lc "blue", \
   f(x) title 'Poisson Fit, m = 6.052 (0.241), N = 152.6 (13.0)' lc "blue"

