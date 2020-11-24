# Gnuplot script file for walk.dat 

set out 'ogwalkdist.png'
set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set nologscale y  # set these in case they were set log from another time
set nologscale x
set grid
set bar small
set pointsize 0.5
set key off  # turn off the legend in the plot
#	set title "2-dimensional random walk, single path"
#	set xlabel "x distance"
#	set ylabel "y distance"
#	plot 'walkpath.dat' u 2:3 with lines lc 6
	set title 'Path distance'
	set ylabel "average distance per trial"
	set xlabel "step number"
	plot 'walk.dat' with errorbars lc 7
	replot
unset output

set terminal wxt
set size 1,1