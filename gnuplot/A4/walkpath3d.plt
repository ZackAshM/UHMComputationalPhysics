# Gnuplot script file for walk3d.dat 

set out 'walkpath3d.png'
set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set nologscale y  # set these in case they were set log from another time
set nologscale x
set nologscale z
unset grid
set bar small
set pointsize 0.5
set origin 0,0
set size 1
set grid 
set key off  # turn off the legend in the plot
	set title "3-dimensional random walk, single path"
	set xlabel "x distance"
	set ylabel "y distance"
	set zlabel "z distance" rotate by 90
	splot 'walkpath3d.dat' u 2:3:4 with lines lc 6 lw 1.5
	replot
unset output

set terminal wxt
set size 1,1