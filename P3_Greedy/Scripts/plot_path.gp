#!/bin/gnuplot  
# This script is made to received a path with a set of points with the format "(x,y)" and will print them
# on a graph connecting the adjacent points with a line

# Parameters: <data> <title> <output>
# <data> path of the file with the points
# <title> title of the graph
# <output> path of the output image
# <color> color of the linespoints

# Execution: gnuplot -c plot_graph.gp <data1> <data2> <title1> <title2> <mode1> <mode2> <output>

DATA1=ARG1
DATA2=ARG2
TITLE1=ARG3
TITLE2=ARG4
MODE1=ARG5
MODE2=ARG6
IMAGE_NAME=ARG7

set terminal png
set output IMAGE_NAME

set xlabel "X"
set ylabel "Y"

set datafile separator "(,)"

set xrange[0:1]
set yrange[0:1]
plot DATA1 using 2:3 with @MODE1 pointtype 7 title TITLE1, \
     DATA2 using 2:3 with @MODE2 pointtype 7 title TITLE2
#short version:
#using -> u
#with -> w
#linespoints -> lp
#pointtype -> pt