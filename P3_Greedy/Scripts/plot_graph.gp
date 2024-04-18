#!/bin/gnuplot  
# This script is made to received a path with a set of points with the format "(x,y)" and will print them
# on a graph connecting the adjacent points with a line

# Parameters: <data> <title> <output>
# <data> path of the file with the points
# <title> title of the graph
# <output> path of the output image

# Execution: gnuplot -c plot_graph.gp <data> <title> <output>

DATA=ARG1
TITLE=ARG2
IMAGE_NAME=ARG3

set terminal png
set output IMAGE_NAME

set xlabel "X"
set ylabel "Y"

set datafile separator "(,)"

plot DATA using 2:3 with linespoints pointtype 7 title TITLE
#short version:
#using -> u
#with -> w
#linespoints -> lp
#pointtype -> pt
