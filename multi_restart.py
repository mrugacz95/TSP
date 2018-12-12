import os
from subprocess import Popen, PIPE, STDOUT
from matplotlib import pyplot as plt
import numpy as np
from random import randint

INSTANCES_DIR = 'data'
RUN_NUMBER = 300


def main():
    for file in ['ry48p.atsp', 'ftv35.atsp']:
        if 'atsp' not in file:
            continue
        path = os.path.join(INSTANCES_DIR, file)
        results = np.empty(RUN_NUMBER)
        print(file)
        for i in range(RUN_NUMBER):
            pipe = Popen(['cmake-build-release/TSP'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
            seed = randint(0, np.iinfo(np.int32).max)
            output, err = pipe.communicate(bytes(f'1 {path} ./multi_run.txt {seed} 8  ', 'utf8'))
            if err is not None:
                print(err)
                return
            # print(output)
            with open('multi_run.txt') as output:
                results[i] = int(output.read().split('\n')[3])
                # print(results[i])
        min_result = np.empty(RUN_NUMBER)
        avg_result = np.empty(RUN_NUMBER)
        for i in range(RUN_NUMBER):
            min_result[i] = np.min(results[:i + 1])
            avg_result[i] = np.average(results[:i + 1])
        plt.plot(results, label='Jakość', linestyle='-')
        plt.plot(min_result, '-', label='Max', linestyle="-.")
        plt.plot(avg_result, label='Avg', linestyle="--")
        plt.legend()
        plt.xlabel('Numer uruchomienia')
        plt.ylabel('Jakość rozwiązania')
        # plt.show()
        plt.savefig(f'report/pics/multi_run_{file.replace(".", "_")}.pdf')
        plt.clf()


if __name__ == '__main__':
    main()
