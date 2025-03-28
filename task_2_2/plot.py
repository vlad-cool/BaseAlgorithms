#!env python3
import matplotlib.pyplot as plt
import os

plots_x = {}
plots_y = {}

with open(os.path.join(os.path.dirname(__file__), "plots_data_count.csv"), "r") as f: 
    for line in f.readlines():
        name, x, y = list(line.split(","))
        name = name.strip()
        x = float(x)
        y = float(y)
        
        if name not in plots_x.keys():
            plots_x[name] = []
            plots_y[name] = []
        
        plots_x[name].append(x)
        plots_y[name].append(y)

plt.figure(figsize=(8, 6))

for plot in plots_x.keys():
    plt.plot(plots_x[plot], plots_y[plot], label=plot)

plt.xscale('log')
plt.yscale('log')
plt.xlabel("Number of elements")
plt.ylabel("Sorting time")
plt.legend(loc='upper left', bbox_to_anchor=(0.03, 0.97))
plt.title("Comparing sorting algorithms")

plt.savefig(os.path.join(os.path.dirname(__file__), "plot_count.png"))

plots_x = {}
plots_y = {}

with open(os.path.join(os.path.dirname(__file__), "plots_data_size.csv"), "r") as f: 
    for line in f.readlines():
        name, x, y = list(line.split(","))
        name = name.strip()
        x = float(x)
        y = float(y)
        
        if name not in plots_x.keys():
            plots_x[name] = []
            plots_y[name] = []
        
        plots_x[name].append(x)
        plots_y[name].append(y)

plt.figure(figsize=(8, 6))

for plot in plots_x.keys():
    plt.plot(plots_x[plot], plots_y[plot], label=plot)

plt.xscale('linear')
plt.yscale('log')
plt.xlabel("Length of integers")
plt.ylabel("Sorting time")
plt.legend(loc='upper left', bbox_to_anchor=(0.03, 0.97))
plt.title("Comparing sorting algorithms")

plt.savefig(os.path.join(os.path.dirname(__file__), "plot_size.png"))

plots_x = {}
plots_y = {}

with open(os.path.join(os.path.dirname(__file__), "plots_data_shuffle.csv"), "r") as f: 
    for line in f.readlines():
        name, x, y = list(line.split(","))
        name = name.strip()
        x = float(x)
        y = float(y)
        
        if name not in plots_x.keys():
            plots_x[name] = []
            plots_y[name] = []
        
        plots_x[name].append(x)
        plots_y[name].append(y)

plt.figure(figsize=(8, 6))

for plot in plots_x.keys():
    plt.plot(plots_x[plot], plots_y[plot], label=plot)

plt.xscale('linear')
plt.yscale('log')
plt.xlabel("Shuffle percent")
plt.ylabel("Sorting time")
plt.legend(loc='upper left', bbox_to_anchor=(0.03, 0.97))
plt.title("Comparing sorting algorithms")

plt.savefig(os.path.join(os.path.dirname(__file__), "plot_shuffle.png"))
