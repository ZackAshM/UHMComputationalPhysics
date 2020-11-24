      # Gnuplot script file for plotting data in file "force.dat"
      # This file is called   force.plt
      set   autoscale                        # scale axes automatically
      unset log                              # remove any log-scaling
      unset label                            # remove any previous labels
      set xtic auto                          # set xtics automatically
      set ytic auto                          # set ytics automatically
      # set title "Force Deflection Data for a Beam and a Column"
      # set xlabel "Deflection (meters)"
      # set ylabel "Force (kN)"
      # set key at 0.01, 100
      set label "Yield Point" at 0.003, 260
      set arrow from 0.0028, 250 to 0.003, 280
      set xr [0.0:0.022]
      set yr [0:325]
      f1(x) = a1*tanh(x/b1)            # define the function to be fit
      a1 = 300; b1 = 0.005;            # initial guess for a1 and b1
      fit f1(x) '305GnuTut_force.dat' using 1:2 via a1, b1
      f2(x) = a2 * tanh(x/b2)            # define the function to be fit
      a2 = 300; b2 = 0.005;            # initial guess for a and b
      fit f2(x) '305GnuTut_force.dat' using 1:3 via a2, b2
	set key at 0.018,150 title "F(x) = A tanh (x/B)"             # title to key!
	set title "Force Deflection Data \n and curve fit"      # note newline!
	set pointsize 1.5                              # larger point!
	set xlabel 'Deflection, {/Symbol D}_x (m)'            # Greek symbols!
	set ylabel 'Force, {/Times-Italic F}_A, (kN)'            # italics!
	plot "305GnuTut_force.dat" using 1:2 title 'Column data' pt 4, \
"305GnuTut_force.dat" using 1:3 title 'Beam data' pt 2, \
a1 * tanh( x / b1 ) title 'Column-fit: A=309, B=0.00227', \
a2 * tanh( x / b2 ) title 'Beam-fit: A=260, B=0.00415'