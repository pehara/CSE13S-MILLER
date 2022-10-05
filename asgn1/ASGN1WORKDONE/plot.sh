#!/bin/bash

make clean && make

#Length main program
rm -f /tmp/length.dat
for n in {2..10000}; do
	echo -n $n "" >> /tmp/length.dat 
	./collatz -n $n | wc -l >> /tmp/length.dat
	
	./collatz -n $n | wc -l >> /tmp/length1.dat
done

#make clean && make
#./value  > /tmp/value.dat

#Max Value main program
##rm -f /tmp/value.dat
for n in {2..10000}; do
	echo -n $n "" >> /tmp/value.dat
	./collatz -n $n | sort -nr | head -n 1 >> /tmp/value.dat
done

#histogram main program
#sort /tmp/length.dat -o /tmp/sorted.dat
#sort /tmp/sorted.dat -u > /tmp/histogram.dat
cat /tmp/length1.dat | sort -n | uniq -c | awk '{print $2 " " $1}' > /tmp/histogram.dat
#gnuplot settings for each of the graphs
gnuplot <<END
	set terminal pdf
	set output "length.pdf"
	set xlabel "x"
	set ylabel "y"
	set pointsize 0.1
	set zeroaxis
	set title "Collatz Sequence Length"
	plot "/tmp/length.dat" with points title ""
END

gnuplot <<END
    	set terminal pdf
    	set output "value.pdf"
    	set xlabel "x"
    	set ylabel "y"
	set yrange [0:100000]
	set pointsize 0.1
    	set zeroaxis
    	set title "Maxium Collatz Sequence Value"
    	plot "/tmp/value.dat" with points title ""
END

gnuplot <<END
    	set terminal pdf
    	set output "histogram.pdf"
    	set xlabel "x"
    	set ylabel "y"
	set pointsize 0.1
	set style data histogram
	set xrange [0:225]
	set yrange [0:200]
	set boxwidth 0.5
    	set zeroaxis
    	set title "Collatz Sequence Length Histogram"
	plot "/tmp/histogram.dat" using 2:1 with lp
END

