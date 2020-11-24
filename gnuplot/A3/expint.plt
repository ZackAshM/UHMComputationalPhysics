# Gnuplot script file for expontential integration
#  Physics 305 spring 2013 --PG
set title "(Numerical value - true value), Integral of Exponential"
set xlabel "number of intervals"
set ylabel "magnitude of numerical error"
set xr [1:4002]
set yr [1e-7:1]
set logscale y  # set these in case they were set log from another time
set logscale x
set grid
# the plot command here uses arguments $1 $2 $3 for the column data in the file.
# It also overlays two plots by adding a 2nd line with another input sequence
plot 'integ.dat' using 1:(abs($2-(1.-exp(-6)))) title "Trapezoidal method"  with lines,\
 'integ.dat' using 1:(abs($3-(1.-exp(-6)))) title "Simpson's method"  with lines

