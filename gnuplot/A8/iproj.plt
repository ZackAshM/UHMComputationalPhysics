set term wxt
set title 'Baseball Projectile, v_0 = 45.2m/s, {/Symbol q}_0 = '.i.'{/Symbol \260}'
set xlabel 'x (m)'
set ylabel 'y (m)'
set xr [0:]
set yr [0:]
set xtics
set ytics
set origin 0,0
set size 1,1
set key vert top right
set pointsize 0.5

plot 'proj'.i.'.dat' u 8:4 with lines lt 2 lc 'blue' title 'no drag',\
	'proj'.i.'d.dat' u 8:4 with lines lt 2 lc 'red' title 'with drag'
	#tan(i*pi/180)*x - 0.5*9.8*x**2/(45.2*cos(i*pi/180))**2 lc 'black' lw 1.5 title 'no drag true'
	
set out 'proj'.i.'.png'
load 'savepng'
	
i = i + 5
if (i<=60) reread