
# Gnuplot script file for plotting data
# This file is called pond_trial.plt
set title 'Monte Carlo Fractional Error, Dim = 3'
set xlabel 'Number of Trials'
set ylabel 'Fractional Error'
set logscale x
set xr [10:100000]
set ticslevel  0
set origin 0,0
set pointsize 0.95
set nokey 
plot "pond3_trial_v_frac.dat" using 1:2 with linespoints lt 7,\
     "pond3_trial_v_frac1.dat" using 1:2 with linespoints lt 1 lc 1,\
	 "pond3_trial_v_frac2.dat" using 1:2 with linespoints lt 2,\
	 "pond3_trial_v_frac3.dat" using 1:2 with linespoints lt 6
      
