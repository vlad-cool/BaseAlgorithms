#!env python3
import subprocess
import os
import random

subprocess.run(["rm", os.path.join(os.path.dirname(__file__), "plots_data.csv")])

with open(os.path.join(os.path.dirname(__file__), "tests.txt"), "r") as f:    
    for line in f.readlines():
        size, min_val, max_val = list(map(int, line.split()))
        a = [size]
        for j in range(size):
            a.append(random.randrange(min_val, max_val, 5))
            
        result = subprocess.run([os.path.join(os.path.dirname(__file__), "./task_2_2"), os.path.join(os.path.dirname(__file__), "plots_data.csv")],
                                input=" ".join(list(map(str, a))),
                                capture_output=True,
                                text=True)

        print(result.stdout.strip())
    