#!/usr/bin/python
import itertools
import re
from collections import defaultdict

import numpy as np
from matplotlib import pyplot as plt
from matplotlib.ticker import ScalarFormatter

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
        '4': ('SA', 2),
        '7': ('LS Greedy', 3),
        '8': ('LS Steepest', 4),
        '9': ('TS', 5)
    }.get(alg, ())


def main():
    with open('evaluation', 'r') as fh:
        a = fh.read()
    lines = a.split("\n")[:-1]

    instances = {'RS': {'marker': '.', 'ls': ':'},
                 'H Nearest': {'marker': '*', 'ls': '-.'},
                 'SA': {'marker': '^', 'ls': '--'},
                 'LS Greedy': {'marker': 'v', 'ls': ':'},
                 'LS Steepest': {'marker': '1', 'ls': '--'},
                 'TS': {'marker': '+', 'ls': '-'}
                 }

    for k, v in instances.items():
        instances[k]['pos'] = []
        instances[k]['mean_t'] = []
        instances[k]['std_t'] = []
        instances[k]['mean_s'] = []
        instances[k]['std_s'] = []
        instances[k]['min_s'] = []
        instances[k]['quality'] = []
        instances[k]['instance'] = []
        instances[k]['instance_size'] = []

    labels = []
    instances_sizes = []
    positions = []
    for i in range(0, len(lines), 4):
        print(lines[i])
        line = lines[i].split()
        labels.append(line[0].replace(".atsp", ""))
        instances_sizes.append(int(re.findall('\d+', line[0])[0]))
        positions.append(POS[labels[-1]] * 3 + BAR_WIDTH)

        plot_stuff = getPlotStuff(lines[i].split()[-1])
        times = np.fromstring(lines[i + 2], dtype=np.float32, sep=' ')
        scores = np.fromstring(lines[i + 3], dtype=np.int32, sep=' ') / BEST[labels[-1]] - 1

        instances[plot_stuff[0]]['pos'].append(POS[labels[-1]] * 3 + (plot_stuff[1] - 1) * BAR_WIDTH)
        instances[plot_stuff[0]]['mean_t'].append(np.mean(times))
        instances[plot_stuff[0]]['std_t'].append(np.std(times))
        instances[plot_stuff[0]]['mean_s'].append(np.mean(scores))
        instances[plot_stuff[0]]['quality'].append(1 / (np.mean(scores)))
        instances[plot_stuff[0]]['std_s'].append(np.std(scores))
        instances[plot_stuff[0]]['min_s'].append(np.min(scores))
        instances[plot_stuff[0]]['instance'].append(POS[labels[-1]])
        instances[plot_stuff[0]]['instance_size'].append(int(re.findall('\d+', line[0])[0]))

    # plot 1 avg score
    fig, ax = plt.subplots()
    for k, v in instances.items():
        lists = sorted(zip(*[v['instance_size'], v['mean_s']]))
        new_x, new_y = list(zip(*lists))
        ax.errorbar(new_x, new_y,
                    yerr=v['std_s'], label=k, alpha=0.75, elinewidth=5,
                    linestyle=v['ls'])

    ax.set_ylabel(r'$\frac{\eta}{\eta_{min}}-1$')
    ax.set_xscale('log')
    to_remove = [48, 35, 44, 47, 53, 358, 403, 64]
    used_instances = [inst for inst in instances_sizes[::3] if inst not in to_remove]
    ax.set_xticks(used_instances)
    ax.get_xaxis().set_major_formatter(ScalarFormatter())
    ax.get_xaxis().set_tick_params(which='minor', size=0)
    ax.get_xaxis().set_tick_params(which='minor', width=0)
    ax.legend()
    plt.savefig('report/pics/plot_mean.pdf')
    plt.clf()

    # plot 2 best score
    for k, v in instances.items():
        lists = sorted(zip(*[v['pos'], v['min_s']]))
        new_x, new_y = list(zip(*lists))
        plt.plot(new_x, new_y,
                 label=k, marker=v['marker'], alpha=0.75)

    plt.xticks(positions, instances_sizes)
    plt.ylabel(r'$\frac{\eta}{\eta_{min}}-1$')
    plt.xlabel('Rozmiar instancji')
    plt.legend()
    plt.savefig('report/pics/plot_min.pdf')
    plt.clf()

    # plot 3 run time
    plt.figure(num=None, figsize=(10, 6))
    for k, v in instances.items():
        lists = sorted(zip(*[v['instance_size'], v['mean_t']]))
        new_x, new_y = list(zip(*lists))
        plt.plot(new_x, new_y, label=k, marker=v['marker'])
    # plt.xticks(list(POS.values()), list(POS.keys()))
    plt.yscale('log')
    plt.ylabel(r'Czas [s]')
    plt.xlabel(r'Rozmiar instancji')
    plt.legend()
    plt.savefig('report/pics/plot_mean_time.pdf')
    plt.gcf().clear()
    plt.clf()

    # plot 4 efficiency
    for k, v in instances.items():
        plt.plot(v['quality'], v['mean_t'], marker=v['marker'],
                 linestyle='', label=k)

    plt.ylabel(r'Czas [s]')
    plt.xlabel(r'$\frac{1}{\frac{\eta}{\eta_{min}}-1}$')
    plt.yscale('log')
    plt.legend()
    # plt.plot([0, 2.5], [0.00007, 200], 'k-', lw=1)
    # plt.plot([0, 20], [0.00007, 40], 'k-', lw=1)
    # plt.plot([0, 0.001], [20, 0.1], 'k-', lw=1)
    plt.xlim(-2, 20)
    plt.savefig('report/pics/quality.pdf')
    plt.clf()


if __name__ == '__main__':
    main()
