#!env python3
import subprocess
import os
import random

subprocess.run(["rm", os.path.join(os.path.dirname(__file__), "plots_data_count.csv")])
subprocess.run(["rm", os.path.join(os.path.dirname(__file__), "plots_data_shuffle.csv")])

with open(os.path.join(os.path.dirname(__file__), "tests_count.txt"), "r") as f:    
    for line in f.readlines():
        size, min_val, max_val = list(map(int, line.split()))
        a = [size]
        for j in range(size):
            a.append(random.randint(min_val, max_val))
        
        result = subprocess.run([os.path.join(os.path.dirname(__file__), "./task_2_1"), os.path.join(os.path.dirname(__file__), "plots_data_count.csv")],
                                input=" ".join(list(map(str, a))),
                                capture_output=True,
                                text=True)

        print(result.stdout.strip())
    
with open(os.path.join(os.path.dirname(__file__), "tests_shuffle.txt"), "r") as f:    
    for line in f.readlines():
        size, min_val, max_val, shuffle_val = list(map(int, line.split()))
        a = []
        for j in range(size):
            a.append(random.randint(min_val, max_val))
        
        a.sort()
        
        for i in range(0, size * shuffle_val // 100):
            a[random.randint(1, size - 1)] = random.randint(min_val, max_val)
        
        a = [size, *a]
        
        result = subprocess.run([os.path.join(os.path.dirname(__file__), "./task_2_1"), os.path.join(os.path.dirname(__file__), "plots_data_shuffle.csv"), str(shuffle_val)],
                                input=" ".join(list(map(str, a))),
                                capture_output=True,
                                text=True)

        print(result.stdout.strip())
    