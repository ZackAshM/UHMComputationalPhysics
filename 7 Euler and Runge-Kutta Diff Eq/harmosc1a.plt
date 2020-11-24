# Gnuplot script file for plotting data
# 
set title "Harmonic oscillator: Euler's solution"
set xlabel "time, s"
set ylabel "position or velocity"
set xr [0:50]
#set yr [-3:3]
set bar small
plot  "osc1.dat" using 1:2 title 'position' with lines,\
      "osc1.dat" using 1:3 title 'velocity' with lines
plot 'osc1.dat' u 1:2 title 'x(t), Euler' w l, \
	'osc1.dat' u 1:3 title 'v(t), Euler' w l, \
	'osc1.dat' u 1:4 title 'x(t), true' w l, \
	'osc1.dat' u 1:5title 'v(t), true'  w l
