#!env python3
import subprocess
import os

with open(os.path.join(os.path.dirname(__file__), "tests.txt"), "r") as f:
    for line in f.readlines():
        result = subprocess.run(["valgrind", os.path.join(os.path.dirname(__file__), "./task_1_1")],
                                input=line,
                                capture_output=True,
                                text=True)

        print(f"{line} -> \n {result.stderr}")