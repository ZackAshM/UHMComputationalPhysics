
# Gnuplot script file for plotting data
# This file is called iso1.plt
set title 'Isotope Lifetime'
set xlabel 'Time (s)'
set ylabel 'Decays per 10s time bin'
set xr [0:2000]
set yr [0.5:1000]
set logscale y
set ticslevel 0
set origin 0,0
set pointsize 0.95
set key
N = 10000
t = 250
#Nt = 10000
#tt = 250
f(x) = 10*(N*log(2)/t)*exp(-x*log(2)/t)
#g(x) = 10*(Nt*log(2)/tt)*exp(-x*log(2)/tt)
fit f(x) "Iso100.dat" using 1:2:4 via N, t
#plot "Iso5.dat" using 1:2:4 with yerrorbars title "simulated data" lc 6,\
#    f(x) title "fitted 9849 (90), 246 (3)s" lc "black",\
#	g(x) title "true 10000, 250s" lc "red"
