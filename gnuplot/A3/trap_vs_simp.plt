# Gnuplot script file for chirp integration
set samples 100000	# For cos t5
set title "numerical integration of damped chirp function"
set xlabel "number of intervals"
set ylabel "integral of chirp function"
set xr [1:4002]
set yr [-1.9:1.9]
set nologscale y  # set these in case they were set log from another time
set logscale x
set grid
set key
plot 'integchirp1.dat' using 1:2 title "Trapezoidal method"  with lines,\
 'integchirp1.dat' using 1:3 title "Simpson's method"  with lines 

