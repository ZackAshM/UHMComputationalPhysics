# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "_sing50.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.1
set output '_sing50co.gif'
stats data_file nooutput
last_line = 5000
Rcl = 15
Nstar = 50
step = 20

unset key
unset contour
unset grid
set title "Open Star Clusters Through Time"
set palette defined ( 0 "red", 10 "blue" )
set cblabel "mass (Solar Masses)"
set xlabel "distance (ly)"
set ylabel "distance (ly)"
set ticslevel 0
set yr [-1.1*Rcl:1.1*Rcl]
set xr [-1.1*Rcl:1.1*Rcl]

#set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind

do for [line_number=1:last_line:step] {

table_file="/tmp/gnuplot_tab1.dat"
set table table_file

t = line_number - 1
set label (t+1) "Time = ".t." x10^{4} yrs" front at graph 0.6,0.1 textcolor "black"

#plot 'c.dat' i 0 u 2:3:8 with points pt 7 ps 0.35 lc palette
splot for [i=2:5*Nstar:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1:i+4		#use splot for mass
unset table

plot table_file with points pt 7 ps 1 lc palette notitle

print "Frames done: ".line_number."
unset label (t+1)

}

	
