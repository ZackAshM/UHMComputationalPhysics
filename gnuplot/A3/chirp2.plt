# Gnuplot script file for chirp 
set title "Chirp: cos((wt)^3)exp(-(t/4)^8), w=2pi rad/sec"
set xlabel "time, s"
set ylabel "pressure amplitude, Pa"
set xr [-0.8:0.8]
set yr [-28:28]
set nologscale y  # set these in case they were set log from another time
set nologscale x
set grid
set samples 100000  # this gives finer sampling over xrange
set key off  # turn off the legend in the plot
A = 20.0;
omega = 2*pi;
# gnuplot uses "x" for all independent variables, so it represents time t here:
plot A*(cos((omega*x)**3))*(exp(-(x/4)**8)) with lines
