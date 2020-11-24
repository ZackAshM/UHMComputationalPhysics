# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "bigstar.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.2
set output 'bigstar.gif'
stats data_file nooutput
last_line = 143
Rcl = 15.0
Nstar = 197
step = 1

unset key
unset contour
unset grid
set title "Massive Object vs Star Cluster"
#set palette defined ( 0 "red", 10 "blue" )
#set cblabel "mass (Solar Masses)"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
set yr [-2.2*Rcl:2.2*Rcl]
set xr [-2.2*Rcl:2.2*Rcl]

#set yr [-70:70]
#set xr [-70:70]

set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind
do for [line_number=1:last_line:step] {
table_file="/tmp/gnuplot_tab.dat"
set table table_file

#line_number = 1
t = line_number - 1

set label (t+1) "Time = ".t."yrs" front at graph 0.7,0.1 textcolor "white"
plot for [i=2:5*Nstar:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1 notitle
unset table
plot table_file with points pt 7 ps 0.35 lc 'white' notitle
print "Frames done: ".line_number."
unset label (t+1)
}

#plot for [i=2:1000:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1
#unset table
#plot table_file with points pt 7 ps 0.35 lc 'white'

	
