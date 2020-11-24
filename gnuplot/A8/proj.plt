set term wxt
set title 'Baseball Projectile, v_0 = 45.2m/s, {/Symbol q}_0 = 40{/Symbol \260}'
set xlabel 'x (m)'
set ylabel 'y (m)'
set auto x
set xr [0:]
set yr [0:]
set xtics
set ytics
set origin 0,0
set size 1,1
set key vert top right
set pointsize 0.5
set grid

plot 'proj40.dat' u 8:4 with lines lc 'black' title 'no drag',\
    'proj40d.dat' u 8:4 with lines dashtype 2 lc 'black' title 'drag, no wind',\
	'projwind.dat' u 8:4 with lines lc 'blue' title 'parallel wind',\
	'projwindopp.dat' u 8:4 with lines lc 'red' title 'anti-parallel wind'
