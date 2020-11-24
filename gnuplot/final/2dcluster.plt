# Plot file for 2D cluster data

set terminal qt
set size 1,1
set origin 0,0

unset key
unset contour
set grid
set size square

set title "Randomly Generated 2D Star Cluster"
set palette defined ( 0 "blue", 150 "red" )
set cblabel "mass (Solar Masses)"
set ticslevel 0
set ylabel 'Distance (ly)'
set yr [-10:10]
set xlabel 'Distance (ly)'
set xr [-10:10]

plot '2dclust.dat' u 1:2:4 with points pt 7 ps 0.25 lc palette
	
