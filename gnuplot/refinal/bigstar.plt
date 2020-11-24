# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "_bs50.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.1
set output '_bs50wh.gif'
stats data_file nooutput
last_line = 5000
Rcl = 15.0
Nstar = 51
step = 100

unset key
unset contour
unset grid
set title "Massive Object vs Star Cluster"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
set yr [-2.2*Rcl:2.2*Rcl]
set xr [-2.2*Rcl:2.2*Rcl]

set key top right textcolor 'black'

#set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind

do for [line_number=1:last_line:step] {
table_file="/tmp/gnuplot_tabbs.dat"
set table table_file
plot for [i=7:5*Nstar:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1 notitle
unset table

table_file2="/tmp/gnuplot_tab2.dat"
set table table_file2
plot "<(sed -n '".line_number."p' ".data_file.")" u 2:3 notitle
unset table

t = (line_number - 1)
set label (t+1) "Time = ".t." x10^{4} yrs" front at graph 0.7,0.1 textcolor "black"

plot table_file2 with points pt 7 ps 1.5 lc 'red' title "Massive Star 150M",\
	table_file with points pt 7 ps 1 lc 'black' notitle
	
print "Frames done: ".line_number."
unset label (t+1)

}


	
