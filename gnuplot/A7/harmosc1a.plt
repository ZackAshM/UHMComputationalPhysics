# Gnuplot script file for plotting data
# 
set title "Harmonic oscillator: Euler's solution"
set xlabel "time, s"
set ylabel "position or velocity"
set xr [0:50]
#set yr [-3:3]
set bar small
set key ins horizontal top right
w=1
p=1
m=1
d=1
#f(x) = cos(w*x + p)
#g(x) = -m*sin(m*x + d)
#fit f(x) "osc1.dat" using 1:2 via w, p
#fit g(x) "osc1.dat" using 1:3 via m, d
plot  "osc1.dat" using 1:2 title 'position' with lines,\
      "osc1.dat" using 1:3 title 'velocity' with lines
plot 'osc1.dat' u 1:2 title 'x(t), Euler' w l, \
	'osc1.dat' u 1:3 title 'v(t), Euler' w l, \
	'osc1.dat' u 1:4 title 'x(t), true' w l, \
	'osc1.dat' u 1:5title 'v(t), true'  w l


#Fit Results
#w = 0.999991 \pm 0.000005			-> T = 2*pi / w
#p = 0.0015 \pm 0.0001
#m = 0.999997 \pm 0.000005
#d = 0.0009 \pm 0.0001
