# plots row wise for 2D points with mass through time
# output is one png per plotted time step

reset
data_file = "heavy.dat"
#set terminal qt enhanced
set terminal gif animate delay 0.2
set output 'heavy.gif'
stats data_file nooutput
last_line = 2800
Rcl = 1.5813e-5
Nstar = 30
step = 10

unset key
unset contour
unset grid
#set title "Merging Open Star Clusters"
#set xlabel "distance (ly)"
#set ylabel "distance (ly)"
set ticslevel 0
set yr [-400:400]
set xr [-400:400]

set object 1 rectangle from graph 0,0 to graph 1,1 fc rgb "black" behind
do for [line_number=1:last_line:step] {
table_file="/tmp/gnuplotem_tab.dat"
set table table_file

#line_number = 1
t = line_number - 1

set label (t+1) "Time = ".t."yrs" front at graph 0.7,0.1 textcolor "white"
plot for [i=2:2*Nstar:2] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1 notitle
unset table
plot table_file with points pt 7 ps 1 lc 'white' notitle
print "Frames done: ".line_number."
unset label (t+1)
}

#plot for [i=2:1000:5] "<(sed -n '".line_number."p' ".data_file.")" u i:i+1
#unset table
#plot table_file with points pt 7 ps 1 lc 'white'

