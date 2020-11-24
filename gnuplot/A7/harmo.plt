# Gnuplot script file for plotting data
# 
set title "Harmonic oscillator: RK4 v RK2, dt = 10 ms"
set xlabel "time per period"
set ylabel "fractional energy difference per period, s^{-1}"
set xr [0:1]
set autoscale y
set bar small
set key
set key ins vert top right
plot 'rk4_300.dat' u 8:7 title 'rk4' lc 2,\
   'rk2_300.dat' u 8:7 title 'rk2' lc 'red'