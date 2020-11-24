# makefile for c++ programs
#
# to create binary executable "area" below, type "make area"
#
# If you don't have a "bin" folder for binaries, create it first
#
# the "#" is the comment character for makefile scripts
#
# this section sets some variables/alaises
# The syntax "$(HOME)" gives substitution of the variable HOME
# change "your_username" below to appropriate name
# ** for Mac users, this will probably be /Users/[yourname] instead of /home **
#
HOME = /home/zackashm
#HOME =/Users/gorham   # uncomment this for the mac
BIN  =  $(HOME)/bin
LOCALDIR = $(HOME)/work
#
# this section for compiler flags and link libraries
# -O3 gives a high degree of code optimization, -W gives all warnings
# and -g turns on the debug options
#
GFLAGS  = -O3 -W -g 
LIBS    = -lm
CC      = g++
#
# Now for the actual compiling instructions:
# make sure that the space before $(CC)
# is a tab whenever you add a new compiler line.
# The syntax below is such that each left-justified name is
# the "target" (or final product executable program) of the make,
# and the tabbed-in lines that follow provide all of the steps needed
# to make that executable binary file and put it into ~/bin

# Note: -o means output name ___, -c means compile only (for example something with no main)
# Structure:
# (target): (dependencies)
# (1 TAB) (instructions)
# Example:
# target: dependencies target.cpp
# 	g++ target.cpp dependency.cpp dependency.h -o /home/zackashm/bin/target
# dependencies: dependency.cpp dependency.h
# 	g++ -c dependency.cpp dependency.h
#
# In terminal:
# >make target
# >(computer stuff)
# >target
# >(target runs)

# Lab 1 -------------------------------------------------------------
area:
	$(CC) $(GFLAGS) area.cpp -o $(BIN)/area $(LIBS)
overflow:
	$(CC) $(GFLAGS) overflow.cpp -o $(BIN)/overflow $(LIBS)
pi_approx_LW:
	$(CC) $(GFLAGS) pi_approx_LW.cpp -o $(BIN)/pi_approx_LW $(LIBS)
sub_cancel:
	$(CC) $(GFLAGS) sub_cancel.cpp -o $(BIN)/sub_cancel $(LIBS)
# Lab 2 -------------------------------------------------------------
bounce:
	$(CC) $(GFLAGS) bounce.cpp -o $(BIN)/bounce $(LIBS)
dbounce:
	$(CC) $(GFLAGS) dbounce.cpp -o $(BIN)/dbounce $(LIBS)
clineargs:
	$(CC) $(GFLAGS) clineargs.cpp -o $(BIN)/clineargs $(LIBS)
# Lab 3 -------------------------------------------------------------
integ1:
	$(CC) $(GFLAGS) integ1.cpp -o $(BIN)/integ1 $(LIBS)
finalchirp:
	$(CC) $(GFLAGS) finalchirp.cpp -o $(BIN)/finalchirp $(LIBS)
# Lab 4 -------------------------------------------------------------
randompair:
	$(CC) $(GFLAGS) randompair.cpp -o $(BIN)/randompair $(LIBS)
walkrandom:
	$(CC) $(GFLAGS) walkrandom.cpp -o $(BIN)/walkrandom $(LIBS)
walk3d:
	$(CC) $(GFLAGS) walk3d.cpp -o $(BIN)/walk3d $(LIBS)
# Lab 5 -------------------------------------------------------------
pond2:
	$(CC) $(GFLAGS) pond2.cpp -o $(BIN)/pond2 $(LIBS)
pond3:
	$(CC) $(GFLAGS) pond3.cpp -o $(BIN)/pond3 $(LIBS)
pond3t:
	$(CC) $(GFLAGS) pond3_trials.cpp -o $(BIN)/pond3t $(LIBS)
hypersphereMC:
	$(CC) $(GFLAGS) hypersphereMC.cpp -o $(BIN)/hypersphereMC $(LIBS)
integsphere:
	$(CC) $(GFLAGS) integsphere.cpp -o $(BIN)/integsphere $(LIBS)
hypersphereMC_manip:
	$(CC) $(GFLAGS) hypersphereMC_manip.cpp -o $(BIN)/hypersphereMC_manip $(LIBS)
# Lab 6 -------------------------------------------------------------
timeseriesdecay:
	$(CC) $(GFLAGS) timeseriesdecay.cpp -o $(BIN)/tsd $(LIBS)
poissonnorm:
	$(CC) $(GFLAGS) poissonnorm.cpp -o $(BIN)/poisn $(LIBS)
tsd_min_bin:
	$(CC) $(GFLAGS) tsd_min_bin.cpp -o $(BIN)/tsdmb $(LIBS)
isotope1:
	$(CC) $(GFLAGS) Isotope1.cpp -o $(BIN)/iso1 $(LIBS)
isotopeC:
	$(CC) $(GFLAGS) IsotopeC.cpp -o $(BIN)/isoC $(LIBS)
# Lab 7 -------------------------------------------------------------
harmosc1a:
	$(CC) $(GFLAGS) harmosc1a.cpp -o $(BIN)/harmo $(LIBS)
FRK2xv:
	$(CC) -c FRK2xv.cpp
harmoscRK2:  FRK2xv
	$(CC) $(GFLAGS) harmoscRK2.cpp  FRK2xv.o -o $(BIN)/harmork2 $(LIBS)
FRK4xv:
	$(CC) -c FRK4xv.cpp
harmoscRK4:  FRK4xv
	$(CC) $(GFLAGS) harmoscRK4.cpp  FRK4xv.o -o $(BIN)/harmork4 $(LIBS)
FRK4thetaw: FRKthetaw.cpp
	$(CC) -c FRK4thetaw.cpp
pendRK4:  FRK4thetaw
	$(CC) $(GFLAGS) pendRK4.cpp  FRK4thetaw.o -o $(BIN)/pendrk4 $(LIBS)
# Lab 8 -------------------------------------------------------------
3VectorOps: 3Vector.cpp 
	$(CC) -c 3Vector.cpp  
3Vector: 3VectorOps 3Vectortest.cpp 
	$(CC) $(GFLAGS) 3Vectortest.cpp  3Vector.cpp -o $(BIN)/3vectest $(LIBS)
vecFRK4xv: vecFRK4xv.cpp 
	$(CC) -c vecFRK4xv.cpp
projectile: 3VectorOps vecFRK4xv projectile.cpp 
	$(CC) $(GFLAGS) projectile.cpp  vecFRK4xv.o 3Vector.o -o $(BIN)/projectile $(LIBS)
# Lab 9 -------------------------------------------------------------
VecFRK4: VecFRK4.cpp
	$(CC) -c VecFRK4.cpp
rocket: VecFRK4  rocket.cpp
	$(CC) $(GFLAGS) rocket.cpp  VecFRK4.cpp -o $(BIN)/rocket $(LIBS)
#solmod: VecFRK4.cpp initialize_atmosphere.cpp
#	$(CC) -c VecFRK4.cpp initialize_atmosphere.cpp
rocsol:  initialize_atmosphere.cpp rocketsol.cpp
	$(CC) $(GFLAGS) VecFRK4.cpp initialize_atmosphere.cpp rocketsol.cpp  -o $(BIN)/rocsol $(LIBS)
# Lab 10 -------------------------------------------------------------
e_m: VecFRK4
	$(CC) $(GFLAGS) VecFRK4.cpp earth_moon.cpp -o $(BIN)/e_m $(LIBS)
e_m2: vecFRK4xv 3VectorOps
	$(CC) $(GFLAGS) vecFRK4xv.o 3Vector.o earth_moonV2.cpp -o $(BIN)/e_m2 $(LIBS)
vec3Dtest:
	$(CC) $(GFLAGS) Vector3Dtest.cpp -o $(BIN)/vec3Dtest $(LIBS)
# Final --------------------------------------------------------------
merger:
	$(CC) $(GFLAGS) merger.cpp -o $(BIN)/merger $(LIBS)


	
# For Phys490:
weizsaecker:	
	$(CC) $(GFLAGS) weizsaecker.cpp -o $(BIN)/weizsaecker $(LIBS)
clean:
	rm *.o;
# Whenever you add a new program to your collection of work,
# you add new lines in the file to govern the compiling of your new program.
# end of makefile

