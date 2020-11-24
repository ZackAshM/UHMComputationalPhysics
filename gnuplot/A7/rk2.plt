# Gnuplot script file for plotting data
# 
set title "Harmonic oscillator: RK2, dt = 300 ms"
set xlabel "time per period"
set ylabel "fractional energy difference per period, s^{-1}"
#set autoscale x
set xr [0:1]
set autoscale y
set bar small
unset key
set pointsize 0.75
# set key ins top right
plot 'rk2_300.dat' u 8:7 lc 'red'