import re

# 讀取輸入數據
data = """First_Fit
Core 1
utilization of core 1: 0.999974
Core 2
utilization of core 2: 0.992253
Core 3
utilization of core 3: 0.955730

Best_Fit
Core 1
utilization of core 1: 0.999974
Core 2
utilization of core 2: 0.992253
Core 3
utilization of core 3: 0.955730
"ERROR Task : 18" Add into cpu fault

Worst_Fit
Core 1
utilization of core 1: 0.889138
Core 2
utilization of core 2: 0.966727
Core 3
utilization of core 3: 0.903609
"""

# 解析數據
methods = ["First_Fit", "Best_Fit", "Worst_Fit"]
core_utilizations = {method: [] for method in methods}

current_method = None
for line in data.split("\n"):
    line = line.strip()
    if line in methods:
        current_method = line
    match = re.search(r"utilization of core \d+: (\d+\.\d+)", line)
    if match and current_method:
        core_utilizations[current_method].append(float(match.group(1)))

# 輸出成 GNUPLOT 可讀格式
with open("cpu_utilization.dat", "w") as f:
    f.write("# Method Core1 Core2 Core3\n")
    for method in methods:
        f.write(f"{method} {core_utilizations[method][0]} {core_utilizations[method][1]} {core_utilizations[method][2]}\n")

# 生成 GNUPLOT 指令
with open("plot.gp", "w") as f:
    f.write("""\
set terminal pngcairo enhanced font "Arial,14" size 800,600
set output "cpu_utilization.png"
set title "CPU Utilization Comparison"
set xlabel "Method"
set ylabel "Utilization"
set yrange [0:1.1]
set style data histograms
set style fill solid 0.5 border -1
set boxwidth 0.3
set key outside
set xtic rotate by -45
plot "cpu_utilization.dat" using 2:xtic(1) title "Core 1" linecolor rgb "blue", \
     "" using 3 title "Core 2" linecolor rgb "orange", \
     "" using 4 title "Core 3" linecolor rgb "green"
""")

print("Data written to cpu_utilization.dat")
print("GNUPLOT script saved as plot.gp")
print('Run "gnuplot plot.gp" to generate the plot.')


