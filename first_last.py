#!/usr/bin/python
import matplotlib
import numpy as np
from matplotlib import pyplot as plt

matplotlib.rc('font', **{'sans-serif': 'Arial',
                         'family': 'sans-serif'})


def getPlotStuff(alg):
    if alg == '7':
        return ("LS Greedy", 0)
    if alg == '8':
        return ("LS Steepest", 1)
    return ()


def main():
    filename = 'first_last_small'
    with open(filename, 'r') as fh:
        a = fh.read()
    lines = a.split("\n")[:-1]

    instances = {
    }

    for i in range(0, len(lines), 4):
        print(lines[i])
        plot_stuff = getPlotStuff(lines[i].split()[-1])
        first_s = np.fromstring(lines[i + 2], dtype=np.float32, sep=' ')
        last_s = np.fromstring(lines[i + 3], dtype=np.int32, sep=' ')

        instances[lines[i]] = {}
        instances[lines[i]]['first_s'] = first_s
        instances[lines[i]]['last_s'] = last_s
        instances[lines[i]]['color'] = np.random.rand(1, 3)
        instances[lines[i]]['name'] = lines[i].split()[0].replace(".atsp", "") + " " + plot_stuff[0]
        if plot_stuff[1]:
            print("XDD")
            instances[lines[i]]['type'] = 'x'
        else:
            instances[lines[i]]['type'] = 'o'

    # plot 3
    for k, v in instances.items():
        print(v)
        plt.scatter(v['first_s'], v['last_s'], c=v['color'], s=1.5, marker='^',  # v['type'],
                    label=v['name'])
    plt.legend()
    plt.xlabel("długość rozwiązania początkowego")
    plt.ylabel("długość rozwiązania końcowego")
    plt.savefig(f'report/pics/{filename}.pdf')


if __name__ == '__main__':
    main()
