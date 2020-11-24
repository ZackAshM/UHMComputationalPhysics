set size 1,1
set origin 0,0
set size square
set samples 15000
scale = 1e6
Re = 6.3710e6/scale
Me = 5.8736e24
Rm = 1.73710e6/scale
Mm = 7.3477e22
Dem = 3.84403e8/scale
Recm = Dem*Mm / (Me + Mm)
Rmcm = Dem*Me / (Me + Mm)
fe1(x) = (Re**2 - x**2)**0.5 - Recm
fe2(x) = -(Re**2 - x**2)**0.5 - Recm
fm1(x) = (Rm**2 - x**2)**0.5 + Rmcm
fm2(x) = -(Rm**2 - x**2)**0.5 + Rmcm

moonup = Rmcm+1.5*Rm
moondown = Rmcm-1.5*Rm
earthup = -Recm+1.5*Re
earthdown = -Recm-1.5*Re

set yr [-400:400]
set xr [-400:400]
set title "Apollo Orbit around Earth"
set ylabel "Distance (10^6 m)"
set xlabel "Distance (10^6 m)"
set key ins vert right top font ",8" box opaque
set xtics
set ytics
#set auto xy

plot 'ap1.dat' u ($2/scale):($3/scale) with lines lc 'dark-green' title 'Earth Orbit',\
	 'ap1.dat' u ($6/scale):($7/scale) with lines lc 'red' title 'Apollo Orbit',\
	 'ap1.dat' u ($4/scale):($5/scale) with lines lc 'black' title 'Moon Orbit'