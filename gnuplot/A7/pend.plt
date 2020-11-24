# Gnuplot script file for plotting data
# 
set title "Pendulum: RK4, dt = 1 ms, {/Symbol q}_0 = 38{/Symbol \260}"
set xlabel "time per period"
set ylabel "{/Symbol q}, rad"
#set autoscale x
set xr [0:10]
set autoscale y
#set yr [-1:1]
set bar small
unset key
set pointsize 0.75
set key ins vert top right
plot 'pendrk4_38.dat' u 1:2 with lines lw 2,\
   'pendrk4_58.dat' u 1:2 with lines lw 2,\
   'pendrk4_78.dat' u 1:2 with lines lw 2,\
   'pendrk4_98.dat' u 1:2 with lines lw 2,\
   'pendrk4_118.dat' u 1:2 with lines lw 2,\
   'pendrk4_138.dat' u 1:2 with lines lw 2,\
   'pendrk4_158.dat' u 1:2 with lines lw 2,\
   'pendrk4_178.dat' u 1:2 with lines lw 2