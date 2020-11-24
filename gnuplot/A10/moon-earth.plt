

set term wxt size 700,700 enhanced font "SVBasic Manual, 12"

set xlabel 'distance, Mm' enhanced font "SVBasic Manual, 12"
set ylabel 'distance, Mm' enhanced font "SVBasic Manual, 12"

#set xr [-450:100]
#set yr [-100:450]

set title 'Moon-Earth orbit'

plot 'em1.dat' every 100 u ($6/1e6):($7/1e6) w p pt 6 ps 0.9 title 'Moon', \
     'em1.dat' u ($2/1e6):($3/1e6) w p pt 6 ps 1.8 title 'Earth';
