set terminal pngcairo enhanced font "Arial,14" size 800,600
set output "cpu_utilization.png"

# 設定黑色背景
set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "black" behind

# 調整標題和軸標籤顏色
set title "CPU Utilization Comparison" textcolor rgb "white"
set xlabel "Method" textcolor rgb "white"
set ylabel "Utilization" textcolor rgb "white"

# 設定 y 軸範圍
set yrange [0:1.1]

# 設定直方圖風格
set style data histograms
set style fill solid 0.5 border -1
set boxwidth 0.3
set key outside textcolor rgb "white"

# 設定 x 軸標籤旋轉角度
set xtic rotate by -45 textcolor rgb "white"

# 設定 y 軸刻度顏色
set ytics textcolor rgb "white"

# 設定網格顏色
set grid linecolor rgb "gray"

# 繪圖，使用不同顏色以適應黑色背景
plot "cpu_utilization.dat" using 2:xtic(1) title "Core 1" linecolor rgb "cyan", \
     "" using 3 title "Core 2" linecolor rgb "yellow", \
     "" using 4 title "Core 3" linecolor rgb "magenta"
