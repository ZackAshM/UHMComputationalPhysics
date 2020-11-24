# Gnuplot script file for chirp integration
set samples 100000
set title "Sum vs Upper Time Limit from t_1 = -6.0 s"
set xlabel "Upper Limit t_2 (s)"
set ylabel "Running Sum of Integral"
unset xr
set yr [-0.1:3.6]
unset key
set nologscale y  # set these in case they were set log from another time
set nologscale x
set grid
plot 'fchirp.dat' using 2:3 with lines lc 7

