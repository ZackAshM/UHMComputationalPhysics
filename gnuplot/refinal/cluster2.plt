# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "_real50.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.1
set output '_realwh50.gif'
stats data_file nooutput
last_line = 2000
Rcl = 15
Nstar = 100
N1 = 50
step = 100

unset key
unset contour
unset grid
set title "Merging Open Star Clusters"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
set yr [-2.2*Rcl:2.2*Rcl]
set xr [-2.2*Rcl:2.2*Rcl]

#set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind

do for [line_number=1:last_line:step] {

table_file="/tmp/gnuplot_tabw.dat"
set table table_file
plot for [i=2:5*(N1-1)+2:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1 notitle
unset table

table_file2="/tmp/gnuplot_tabw2nd.dat"
set table table_file2
plot for [i=5*N1+2:5*(Nstar-1)+2:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1 notitle
unset table

t = (line_number - 1)
set label (t+1) "Time = ".t." x10^{4} yrs" front at graph 0.7,0.1 textcolor "black"

plot table_file with points pt 7 ps 1 lc 'black' notitle,\
	 table_file2 with points pt 7 ps 1 lc 'red' notitle

print "Frames done: ".line_number."
unset label (t+1)

}
