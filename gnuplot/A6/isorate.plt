
# Gnuplot script file for plotting data
# This file is called iso1.plt
set title 'Carbon Isotope Decay'
set xlabel 'Time (s)'
set ylabel 'Decay Rate (decays/10sec)'
set xr [0:4000]
set yr [0.5:3000]
set logscale y
set ticslevel 0
set origin 0,0
set pointsize 0.95
set key
set key font ",8"
set size 1, 1
set origin 0, 0
set xtics auto
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

set out "isoC2.png"

set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set multiplot
plot "IsoC.dat" using 1:2:4 with yerrorbars title "Simulated Data" lt 1 lc 6,\
   f(x) title "fitted C^{11}: 2134 (68), 1085 (62); C^{10}: 7556 (66), 19.28 (.20)" lc "red",\
   10*(Nt*log(2)/tt)*exp(-x*log(2)/tt)+10*(Mt*log(2)/dt)*exp(-x*log(2)/dt) title "true C^{11}: 2500, 1221; C^{10}: 7500, 19.29" lc "black" 
set size 0.4, 0.35
set origin 0.15, 0.45
unset key
set logscale y
set yr [5:3000]
unset ylabel
unset xlabel 
unset title
set xtics 0,100,200
plot [0:200] "IsoC.dat" using 1:2:4 with yerrorbars lt 1 lc 6,\
   f(x) lc "red",\
   10*(Nt*log(2)/tt)*exp(-x*log(2)/tt)+10*(Mt*log(2)/dt)*exp(-x*log(2)/dt) lc "black" 
replot
unset multiplot

set terminal wxt
set size 1,1

