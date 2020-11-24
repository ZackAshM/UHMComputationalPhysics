# Gnuplot loop script file for plotting dbounce0i.dat for 1 <= i <= 9

filename = "dbounce0".i.".dat"
plotfile = "dbounce0".i.".png"
set output plotfile

set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set nologscale y
set nologscale x
unset title
unset xlabel
unset ylabel
set key right center
set pointsize 1.5
set bar small
set grid
set multiplot
	set size 1, 0.5
	set xtics format ""
	set title "Bounce with Energy Loss; C = 0.".i.""
	set ylabel "Time (s)"
	set origin 0.0, 0.45; plot filename using 1:3 title 'Total Time' with linespoints lc 7,\
		filename using 1:2 title 'Bounce Time' with linespoints lc 6
	unset title
	set xtics format "%1.f"
	set ylabel "Height (m)"
	set xlabel "Bounce Count"
	set origin 0.0, 0.0; plot filename using 1:6 title 'Total Distance' with linespoints lc 7,\
		filename using 1:5 title 'Bounce Height' with linespoints lc 6
	replot
	unset multiplot
unset output

set terminal wxt
set size 1,1
	


i = i + 1
if (i <= n) reread