#!env python3
import subprocess
import os
import random

with open(os.path.join(os.path.dirname(__file__), "tests.txt"), "r") as f:    
    for line in f.readlines():
        size, min_val, max_val = list(map(int, line.split()))
        a = [size]
        for j in range(size):
            a.append(random.randrange(min_val, max_val, 5))
        
        result = subprocess.run([os.path.join(os.path.dirname(__file__), "./task_2_1")],
                                input=" ".join(list(map(str, a))),
                                capture_output=True,
                                text=True)

        print(result.stdout.strip())
        
        # print("\033[0;32mOK\033[0;0m" if result.stdout.strip() == outputs[i].strip() else f"\033[1;31mERROR on test {i}\033[0;0m")