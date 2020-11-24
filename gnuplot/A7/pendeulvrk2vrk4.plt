# Gnuplot script file for plotting data
# 
set title "Pendulum: RK4, dt = 1 ms, {/Symbol q}_0 = 2.9rad"
set xlabel "time per period"
set ylabel "fractional energy difference per period, s^{-1}"
#set autoscale x
set xr [0:1]
set autoscale y
#set yr [-1:1]
set bar small
set key
set pointsize 0.75
set size 1,1
set origin 0,0
set key ins vert bottom right

set out "pendeulvrk2vrk4.png"

set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set multiplot
plot 'pendrk4.dat' u 8:7 title 'RK4' with lines lw 2 lc 'blue',\
   'pendrk2.dat' u 8:7 title 'RK2' with lines lw 2 lc 'red',\
   'pendeuler.dat' u 8:7 title 'Euler' with lines lw 2 lc 2
set size 0.47, 0.4
set origin 0.18, 0.45
unset key
unset ylabel
unset xlabel 
unset title 
set ytics scale 0.5
plot 'pendrk4.dat' u 8:7 with lines lw 2 lc 'blue',\
   'pendrk2.dat' u 8:7 with lines lw 2 lc 'red'
replot
unset multiplot

set size 1,1
set origin 0,0

set terminal wxt