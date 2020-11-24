set term wxt
set title 'Baseball Projectile Range, v_0 = 45.2m/s'
set xlabel '{/Symbol q} ({/Symbol \260})'
set ylabel 'range (m)'
set xr [20:70]
set auto y 
set xtics
set ytics
set origin 0,0
set size 1,1
set key vert top right
set pointsize 1

plot 'anglevrange.dat' u 1:2 with points lt 7 lc 'blue' title 'no drag',\
	'anglevrange.dat' u 1:3 with points lt 7 lc 'red' title 'with drag'
