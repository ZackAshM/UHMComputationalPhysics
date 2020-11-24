
# Gnuplot script file for plotting data
# This file is called iso1.plt
set title 'Carbon Isotope Decay'
set xlabel 'Time (s)'
set ylabel 'Decay Rate (decays/10sec)'
set xr [0:3000]
set yr [0:1000]
set logscale y
set ticslevel 0
set origin 0,0
set pointsize 0.95
set key
set key font ",10"
Nt = 2250
tt = 1221
Mt = 5250
dt = 19.29
N = 2250
t = 1221
M = 5250
d = 19.29
f(x) = 10*(N*log(2)/t)*exp(-x*log(2)/t)+10*(M*log(2)/d)*exp(-x*log(2)/d)
fit f(x) "IsoC.dat" using 1:2:4 via N, t, M, d
plot "IsoC.dat" using 1:2:4 with yerrorbars title "Simulated Data" lt 1 lc 6,\
   f(x) title "fitted C^{11}: 2134 (68), 1085 (62); C^{12}: 7556 (66), 19.28 (.20)" lc "red",\
   10*(Nt*log(2)/tt)*exp(-x*log(2)/tt)+10*(Mt*log(2)/dt)*exp(-x*log(2)/dt) title "true C^{11}: 2500, 1221; C^{12}: 7500, 19.29" lc "black" 
      
