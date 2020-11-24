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
#set auto xy
set title "Earth and Moon Orbit About Center of Mass"
set ylabel "Distance (10^6 m)"
set xlabel "Distance (10^6 m)"
set key ins vert right top font ",8" box opaque
set xtics
set ytics

set out "em.png"
set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red

set multiplot
#set object 3 rect from graph 0.65,0.8 to graph 1,1  front fc rgb 'white' fs solid 0.0 noborder
set arrow 1 from graph 0.3,0.81 to graph 0.49,0.96 lw 1.5
set arrow 2 from graph 0.3,0.5 to graph 0.47,0.5 lw 1.5
plot 'em1.dat' u ($2/scale):($3/scale) with lines lc 'dark-green' title 'Earth Orbit',\
	 'em1.dat' u ($6/scale):($7/scale) with lines lc 'black' title 'Moon Orbit',\
	 fe1(x) lc 'dark-blue' title "Earth",\
	 fe2(x) lc 'dark-blue' notitle,\
	 fm1(x) lc 'gray' title "Moon",\
	 fm2(x) lc 'gray' notitle
unset arrow 1
unset arrow 2
#unset object 3
set object rect from graph 0,0 to graph 1,1 fc rgb 'white' fs solid 0.0 noborder
set size 0.3, 0.3
set origin 0.25, 0.6
unset title
unset ylabel
unset xlabel 
unset key
unset xtics
unset ytics
set yr [moondown:moonup]
set xr [-1.5*Rm:1.5*Rm]
plot 'em1.dat' u ($6/scale):($7/scale) with lines lc 'black',\
	 fm1(x) lc 'gray',\
	 fm2(x) lc 'gray'
set origin 0.25, 0.36
set xr [-1.5*Re:1.5*Re]
set yr [earthdown:earthup]
plot 'em1.dat' u ($2/scale):($3/scale) with lines lc 'dark-green',\
	 fe1(x) lc 'dark-blue',\
	 fe2(x) lc 'dark-blue'
replot
unset multiplot

set terminal wxt
set size 1,1