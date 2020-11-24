# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "resing2.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.2
set output 'resing2.gif'
stats data_file nooutput
last_line = 1000
Rcl = 15
Nstar = 30
step = 5

unset key
unset contour
unset grid
set title "Merging Open Star Clusters"
set palette defined ( 0 "red", 10 "blue" )
set cblabel "mass (Solar Masses)"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
#set yr [-10000:10000]
#set xr [-50000:50000]

set yr [-1.1*Rcl:1.1*Rcl]
set xr [-1.1*Rcl:1.1*Rcl]

#set yr [0:40]
#set xr [-10:30]

set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind
do for [line_number=1:last_line:step] {
table_file="/tmp/gnuplot_tab1.dat"
set table table_file

#line_number = 1
t = line_number - 1

set label (t+1) "Time = ".t."yrs" front at graph 0.7,0.1 textcolor "white"
#plot 'c.dat' i 0 u 2:3:8 with points pt 7 ps 0.35 lc palette
plot for [i=2:5*Nstar:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1#:i+4
unset table
plot table_file with points pt 7 ps 0.35 lc 'white' #lc palette notitle
print "Frames done: ".line_number."
unset label (t+1)
}

#plot for [i=2:1000:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1
#unset table
#plot table_file with points pt 7 ps 0.35 lc 'white'

	
