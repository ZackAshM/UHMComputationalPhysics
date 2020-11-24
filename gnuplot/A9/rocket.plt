set term wxt
set title 'Rocket Launch'
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

plot for [i = 20:80:5] 'r'.i.'.dat' u 2:4 with lines lc i title 'angle = '.i.''
