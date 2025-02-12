#!env python3
import subprocess
import os

with open(os.path.join(os.path.dirname(__file__), "tests.txt"), "r") as f:
    s = f.read()
    
    tests = s.split("####################")
        
    inputs = tests[0::2]
    outputs = tests[1::2]
    
    for i in range(len(inputs)):
        result = subprocess.run([os.path.join(os.path.dirname(__file__), "./task_1_2")],
                                input=inputs[i],
                                capture_output=True,
                                text=True)

        print(f"{inputs[i].strip()} -> {result.stdout.strip()}")
        
        print("\033[0;32mOK\033[0;0m" if result.stdout.strip() == outputs[i].strip() else f"\033[1;31mERROR on test {i}\033[0;0m")