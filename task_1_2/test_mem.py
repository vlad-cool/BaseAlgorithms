#!env python3
import subprocess
import os

with open(os.path.join(os.path.dirname(__file__), "tests.txt"), "r") as f:
    s = f.read()
    
    tests = s.split("####################")
        
    inputs = tests[0::2]
    outputs = tests[1::2]
    
    for i in range(len(inputs)):
        result = subprocess.run(["valgrind", os.path.join(os.path.dirname(__file__), "./task_1_2")],
                                input=inputs[i],
                                capture_output=True,
                                text=True)

        print(f"{inputs[i]} -> \n {result.stderr}")
