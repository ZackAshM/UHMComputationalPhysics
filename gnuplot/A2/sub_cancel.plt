# Gnuplot script file for plotting sub_cancel.dat
set title "Sub Cancel"
set xlabel "log N"
set ylabel "log fractional error"
set nologscale y
set nologscale x
set pointsize 1.5
set bar small
set grid
plot "sub_cancel.dat" using (log10($1)):(log10($8)) title 'Fractional Error' with linespoints
set out "sub_cancel.png"
load 'savepng'