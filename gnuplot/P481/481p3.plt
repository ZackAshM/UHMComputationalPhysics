
reset

Eg = 0.1909
Ee = 0.7039

kg = (26.2215*Eg)**(0.5)
qg = (26.2215*(1-Eg))**(0.5)
ke = (26.2215*Ee)**(0.5)
qe = (26.2215*(1-Ee))**(0.5)

A = 5.16
D = 1.18
B = 3.64
C = 1.08

f1(x) = A*exp(qg*x)
f2(x) = D*cos(kg*x)
f3(x) = A*exp(-qg*x)

g1(x) = B*exp(qe*x)
g2(x) = -C*sin(ke*x)
g3(x) = -B*exp(-qe*x)

f(x) = x<-0.5 ? f1(x) : x>0.5 ? f3(x) : f2(x)
g(x) = x<-0.5 ? g1(x) : x>0.5 ? g3(x) : g2(x)

set samples 500000

set xr [-3:3]
#set yr [-2:2]
set xlabel 'x (nm)'
set ylabel 'State Function'
set title 'Band Wavefunctions'

set key top right

plot f(x) lc 'blue' title 'Ground State',\
	g(x) lc 'red' title 'Excited State'



