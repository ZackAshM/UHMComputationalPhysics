# Gnuplot loop script file for plotting a single dbounce.dat file
# Set i = 10*C

# filename = "dbounce00".i.".dat"
# plotfile = "dbounce00".i.".png"
# set output plotfile

# set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
# set border linewidth 1.5
# set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
# set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set nologscale y
set nologscale x
unset title
unset xlabel
unset ylabel
set key right center
set pointsize 1
set bar small
set grid
# set multiplot
	# set size 1, 0.5
	# set xtics format ""
	set title "Bounce Height vs Time"
	set xlabel "Time (s)"
	set ylabel "Bounce Height (m)"
	plot 'bounce001.dat' using 3:5 title 'C = 0.01' with linespoints lc 0,\
	     'bounce01.dat' using 3:5 title 'C = 0.1' with linespoints lc 1,\
	     'bounce02.dat' using 3:5 title 'C = 0.2' with linespoints lc 2,\
	     'bounce03.dat' using 3:5 title 'C = 0.3' with linespoints lc 3,\
	     'bounce04.dat' using 3:5 title 'C = 0.4' with linespoints lc 4,\
	     'bounce05.dat' using 3:5 title 'C = 0.5' with linespoints lc 5,\
	     'bounce06.dat' using 3:5 title 'C = 0.6' with linespoints lc 6,\
	     'bounce07.dat' using 3:5 title 'C = 0.7' with linespoints lc 7,\
	     'bounce08.dat' using 3:5 title 'C = 0.8' with linespoints lc 8,\
	     'bounce09.dat' using 3:5 title 'C = 0.9' with linespoints lc 9
	     
#	set origin 0.0, 0.45; plot filename using 1:3 title 'Total Time' with linespoints lc 7,\
#		filename using 1:2 title 'Bounce Time' with linespoints lc 6
#	unset title
#	set xtics format "%1.f"
#	set ylabel "Height (m)"
#	set xlabel "Bounce Count"
#	set origin 0.0, 0.0; plot filename using 1:6 title 'Total Distance' with linespoints lc 7,\
#		filename using 1:5 title 'Bounce Height' with linespoints lc 6
#	replot
# 	unset multiplot
set out 'bounceHvT.png'
load 'savepng'

# set terminal wxt
# set size 1,1
	