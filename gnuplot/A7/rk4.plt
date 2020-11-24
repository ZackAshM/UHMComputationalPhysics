# Gnuplot script file for plotting data
# 
set title "Harmonic oscillator: RK4, dt = 10 ms"
set xlabel "time per period"
set ylabel "fractional energy difference per period, s^{-1}"
#set autoscale x
set xr [0:1]
set autoscale y
set bar small
set key
set pointsize 0.75
# set key ins top right
plot 'rk4_10.dat' u 8:7 title 'rk4' lc 'blue'