set size 1,1
set origin 0,0
set size square
scale = 1e6

set title "Distance Between Apollo and Moon"
set ylabel "Distance (10^6 m)"
set xlabel "Time (10^3 s)"
set nokey
set xtics
set ytics
set auto xy
set xr [0:]
set yr [0:]


plot 'apl.dat' u ($1/1e3):($9/scale) with lines lc 'red'