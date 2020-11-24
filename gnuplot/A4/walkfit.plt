# Gnoplot script file for fitting 
# and plotting walkrandom path dist vs number of steps
unset title
unset xlabel
set ylabel 'Average Distance per 4 Trials'
set nologscale x
set nologscale y
f(x) = x**p;
p = 0.5
fit f(x) 'walk41000.dat' via p 
set pointsize 1.5
set bar small
set key bottom right
set grid
plot 'walk41000.dat' title 'Walk Distance Data' with errorbars lc 'red', \
  f(x) lc 'black' lw 2 title 'fit f(x) = x^{0.5048}', \
  x**0.5 lc 'blue' lw 1 title 'theoretical x^{0.5}'