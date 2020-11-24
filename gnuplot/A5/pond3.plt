
# Gnuplot script file for plotting data
# This file is called pond3_i.plt, i = number of trials
trials = "10 30 100 300 1000 3000 10000 30000 100000"
set xlabel 'X distance'
set ylabel 'Y distance'
set zlabel 'Z distance'
set xr [-1.05:1.05]
set yr [-1.05:1.05]
set zr [-1.05:1.05]
set ticslevel  0
set origin 0,0
set size 1
set view equal xyz
set pointsize 0.95
set nokey 
do for [i in trials]{
	  if (i = 100000){set yr [-1.05:0]} else {}
	  set title 'Monte Carlo Integration of a Sphere for '.i.' Trials'
	  splot "pond3_".i.".dat" index 0 using 1:2:3 with points lc 7,\
      "pond3_".i.".dat" index 1 using 1:2:3 with points lc 6
	  set out "pond3_".i.".png"
	  load "savepng"
	  }