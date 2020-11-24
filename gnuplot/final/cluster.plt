unset key
unset contour
set grid
set title "Randomly Generated Star Cluster"
set palette defined ( 0 "blue", 10 "red" )
set cblabel "mass (Solar Masses)"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
set yr [0:20]
set xr [0:20]
set view equal xyz
plot 'c.dat' i 0 u 2:3:8 with points pt 7 ps 0.35 lc palette,\
	'c.dat' i 1 u 2:3:8 with points pt 7 ps 0.35 lc palette
	
