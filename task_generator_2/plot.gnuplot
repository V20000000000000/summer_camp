
set terminal pngcairo size 800,600
set output 'cpu_utilization.png'
set title "CPU Core Utilization"
set xlabel "Mode"
set ylabel "Utilization"
set key outside
set style data histograms
set style fill solid
set boxwidth 0.8
set yrange [0:1.2]
set grid ytics
plot "cpu_data.dat" using 3:4:xtic(2) title columnheader(1) linecolor variable
