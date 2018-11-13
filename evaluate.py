#!/usr/bin/python
from collections import defaultdict

import numpy as np
from matplotlib import pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

POS = {
    'br17': 1,
    'ftv33': 2,
    'ftv35': 3,
    'ftv38': 4,
    'p43': 5,
    'ftv44': 6,
    'ftv47': 7,
    'ry48p': 8,
    'ft53': 9,
    'ftv55': 10,
    'ftv64': 11,
    'ft70': 12,
    'ftv70': 13,
    'kro124p': 14,
    'ftv170': 15,
    'rbg323': 16,
    'rbg358': 17,
    'rbg403': 18,
    'rbg443': 19,
}

BEST = {
    'br17': 39,
    'ft53': 6905,
    'ft70': 38673,
    'ftv33': 1286,
    'ftv35': 1473,
    'ftv38': 1530,
    'ftv44': 1613,
    'ftv47': 1776,
    'ftv55': 1608,
    'ftv64': 1839,
    'ftv70': 1950,
    'ftv90': 1579,
    'ftv100': 1788,
    'ftv110': 1958,
    'ftv120': 2166,
    'ftv130': 2307,
    'ftv140': 2420,
    'ftv150': 2611,
    'ftv160': 2683,
    'ftv170': 2755,
    'kro124': 36230,
    'kro124p': 36230,  # simple copy of 124
    'p43': 5620,
    'rbg323': 1326,
    'rbg358': 1163,
    'rbg403': 2465,
    'rbg443': 2720,
    'ry48p': 14422,
}

BAR_WIDTH = 0.4


def getPlotStuff(alg):
    return {
        '1': ('RS', 0),
        '3': ('H Nearest', 1),
        '7': ('LS Greedy', 2),
        '8': ('LS Steepest', 3)
    }.get(alg, ())


def main():
    with open('evaluation', 'r') as fh:
        a = fh.read()
    lines = a.split("\n")[:-1]

    instances = {'RS': defaultdict(list, {'color': 'red'}),
                 'H Nearest': defaultdict(list, {'color': 'purple'}),
                 'LS Greedy': defaultdict(list, {'color': 'green'}),
                 'LS Steepest': defaultdict(list, {'color': 'blue'}),
                 }


    labels = []
    positions = []
    for i in range(0, len(lines), 4):
        print(lines[i])
        line = lines[i].split()
        labels.append(line[0].replace(".atsp", ""))
        positions.append(POS[labels[-1]] * 3 + BAR_WIDTH)

        plot_stuff = getPlotStuff(lines[i].split()[-1])
        times = np.fromstring(lines[i + 2], dtype=np.float32, sep=' ')
        scores = np.fromstring(lines[i + 3], dtype=np.int32, sep=' ') / BEST[labels[-1]] - 1

        instances[plot_stuff[0]]['pos'].append(POS[labels[-1]] * 3 + (plot_stuff[1] - 1) * BAR_WIDTH)
        instances[plot_stuff[0]]['mean_t'].append(np.mean(times))
        instances[plot_stuff[0]]['std_t'].append(np.std(times))
        instances[plot_stuff[0]]['mean_s'].append(np.mean(scores))
        instances[plot_stuff[0]]['quality'].append((1 / np.mean(scores) - 1))
        instances[plot_stuff[0]]['std_s'].append(np.std(scores))
        instances[plot_stuff[0]]['min_s'].append(np.min(scores))
        instances[plot_stuff[0]]['instance'].append(POS[labels[-1]])

    plt.xticks(positions, labels)
    plt.ylabel(r'$\frac{\eta}{\eta_{min}}-1$', fontsize=18)
    plt.legend()
    plt.savefig('report/pics/plot_mean.pdf')
    plt.clf()

    # plot 2
    for k, v in instances.items():
        plt.bar(v['pos'], v['min_s'], width=BAR_WIDTH,
                color=v['color'], label=k)

    plt.xticks(positions, labels)
    plt.ylabel(r'$\frac{\eta}{\eta_{min}}-1$', fontsize=18)
    plt.legend()
    plt.savefig('report/pics/plot_min.pdf')
    plt.clf()

    # plot 3
    plt.figure(num=None, figsize=(10, 6))
    for k, v in instances.items():
        plt.plot(v['instance'], v['mean_t'], color=v['color'], label=k, marker='o', linewidth=0)
    plt.xticks(list(POS.values()), list(POS.keys()))
    plt.yscale('log')
    plt.ylabel(r'Czas [s]')
    plt.legend()
    # plt.show()
    plt.savefig('report/pics/plot_mean_time.pdf')
    plt.gcf().clear()
    plt.clf()

    # plot 4
    for k, v in instances.items():
        plt.plot(v['quality'], v['mean_t'], color=v['color'], marker='o',
                 linestyle='', label=k)

    plt.ylabel(r'Czas [s]', fontsize=18)
    plt.xlabel(r'$\frac{\eta}{\eta_{min}}-1$', fontsize=18)
    plt.yscale('log')
    plt.xscale('log')
    plt.legend()
    plt.savefig('report/pics/quality.pdf')
    plt.clf()


if __name__ == '__main__':
    main()
