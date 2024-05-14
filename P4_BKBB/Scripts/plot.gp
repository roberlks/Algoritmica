#!/bin/gnuplot  
# This script is made to received a path with a set of points with the format "(x,y)" and will print them
# on a graph connecting the adjacent points with a line

# Parameters: <data> <title> <output>
# <data> path of the file with the points
# <title> title of the graph
# <output> path of the output image
# <mode> points, linespoints,...

# Execution: gnuplot -c plot.gp <data> <title> <output> <mode>

DATA=ARG1
TITLE=ARG2
IMAGE_NAME=ARG3
MODE=ARG4

set terminal png
set output IMAGE_NAME

set xlabel "Num ciudades (n)"
set ylabel "Tiempo (seg)"

plot DATA with @MODE title TITLE
#short version:
#using -> u
#with -> w
#linespoints -> lp
#pointtype -> pt