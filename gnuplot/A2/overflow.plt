# Gnuplot script file for plotting data
set title "Machine Overflow and Underflow"
set xlabel "number of terms N"
set ylabel "log Value"
set xr [.5:155]
set yr [-55:55]
set nologscale y
set nologscale x
set pointsize 1.5
set bar small
set grid
plot "overflow.dat" using 1:(log10($2)) title 'Overflow' with linespoints,\
     "overflow.dat" using 1:(log10($3)) title 'Underflow' with linespoints
