
reset
q(x) = (26.2215*x)**(0.5)
k(x) = (26.2215*(1-x))**(0.5)
b = 1
a = 2

set samples 100000

f(x) = cos(q(x)*b)*cosh(k(x)*(a-b)) - (((q(x))**2-(k(x))**2)/(2*q(x)*k(x)))*sin(q(x)*b)*sinh(k(x)*(a-b))

set xr [0.1:1.0]
set yr [-2:2]
set ylabel 'LHS Equation 15.61 in eV and nm'
set xlabel 'Energy (eV)'
set title 'Kronig-Penney Solution: Energy Bands'


set out "481p2.png"
set terminal pngcairo size 700,525 enhanced font 'Verdana,14'

# Line styles
set border linewidth 1.5
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  
# blue
set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  
# red


set multiplot
set key top right font ",10"

set arrow 1 from graph 0.158,0.56 to graph 0.105,0.5

plot f(x),\
     1 lt 'dashed' lc 'black',\
     -1 lt 'dashed' lc 'black',\
     0 lt 1 lc 'black' notitle

set key bottom right font ",10"
set parametric
set trange [-10:10]
plot 0.1898,t lc 'blue',\
	0.1932,t lc 'blue',\
	0.6835,t lc 'blue',\
	0.7278,t lc 'blue',\
	0.1909,t lc 'orange',\
	0.7039,t lc 'orange'

unset arrow 1

set size 0.38, 0.33
set origin 0.184, 0.55
unset key
set xr [0.179:0.201]
set xtics 0.18,0.01,0.20
set yr [-1:1]
unset xlabel
unset ylabel
unset title
unset parametric
set object 1 rect from graph 0,0 to graph 1,1 behind fc rgb 'white' fs solid 0.0 noborder
plot f(x),\
     1 lt 'dashed' lc 'black',\
     -1 lt 'dashed' lc 'black',\
     0 lt 1 lc 'black'
unset object 1
set parametric
plot 0.1898,t lc 'blue',\
	0.1932,t lc 'blue',\
	0.1909,t lc 'orange'

replot

unset multiplot
unset parametric

set terminal qt
set size 1,1

