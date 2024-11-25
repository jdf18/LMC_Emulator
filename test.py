import subprocess
import time
from json import loads
from concurrent.futures import ThreadPoolExecutor
from os import path

EXECUTABLE = path.abspath('cmake-build-debug\\LMCEmulator.exe')
BINARY = path.abspath('src\\collatz.lmc')
CORRECT_DATA = path.abspath('src\\collatz.json')

def filter_correct_under_1000(answer):
    correct_answer = []
    for e in answer:
        if e < 1000:
            correct_answer.append(e)
        else:
            correct_answer.append(0)
            break
    return correct_answer

def check_output(command, answer, i) -> bool:
    out = subprocess.check_output(command, shell=True)

    passed = all(map(lambda x:x[0]==x[1], zip(
        answer[1:],
        tuple(map(int, filter(lambda x:x, map(str.strip, out.decode().split('\n')))))
    )))

    if not passed:
        print(f"Failed n = {i}")
        print(out)
        print(answer)
    else:
        print("Passed", i)

    return passed


if __name__ == '__main__':
    with open(CORRECT_DATA, 'r') as file:
        collatz_data = loads(file.read())

    def return_params(i):
        return (
            f"{EXECUTABLE} {BINARY} {i}",
            filter_correct_under_1000(collatz_data[i-1]),
            i
        )

    parameters = tuple(map(return_params, range(1, 1000)))
    start = time.time()

    with ThreadPoolExecutor() as executor:
        results = tuple(executor.map(lambda p:check_output(*p), parameters))

    end = time.time()

    if all(results):
        print("All tests passed.")
    else:
        print("Not all tests passed.")

    print("Time taken:",end-start)