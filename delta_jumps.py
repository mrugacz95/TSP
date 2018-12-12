#!/usr/bin/python
import re
from collections import defaultdict

import matplotlib
import numpy as np
from matplotlib import pyplot as plt

# plt.rc('text', usetex=True)
# plt.rc('font', family='Arial')
from matplotlib.ticker import ScalarFormatter

matplotlib.rc('font', **{'sans-serif': 'Arial',
                         'family': 'sans-serif'})

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

bar_width = 0.4


def getPlotStuff(alg):
    return {
        '7': ("LS Greedy", 0),
        '8': ("LS Steepest", 1),
        '4': ("SA", 2),
        '9': ("TS", 3)
    }.get(alg)


with open('delta_jumps', 'r') as fh:
    a = fh.read()
lines = a.split("\n")[:-1]

instances = {
    'LS Greedy': defaultdict(list),
    'LS Steepest': defaultdict(list),
    'SA': defaultdict(list),
    'TS': defaultdict(list),
}

instances['LS Greedy']['linestyle'] = ':'
instances['LS Steepest']['linestyle'] = '--'
instances['SA']['linestyle'] = '-'
instances['TS']['linestyle'] = '-.'
for k, v in instances.items():
    v['pos_d'] = []
    v['pos_j'] = []
    v['mean_d'] = []
    v['std_d'] = []
    v['mean_j'] = []
    v['std_j'] = []

labels = []
positions = []
instances_sizes = []
for i in range(0, len(lines), 4):
    print(lines[i])
    line = lines[i].split()
    labels.append(line[0].replace(".atsp", ""))
    positions.append(POS[labels[-1]] * 3 + bar_width)

    instance_size = int(re.findall('\d+', line[0])[0])
    instances_sizes.append(instance_size)

    plot_stuff = getPlotStuff(lines[i].split()[-1])
    deltas = np.fromstring(lines[i + 2], dtype=np.float32, sep=' ')
    jumps = np.fromstring(lines[i + 3], dtype=np.int32, sep=' ')

    instances[plot_stuff[0]]['pos_d'].append(POS[labels[-1]] * 3 + 2 * plot_stuff[1] * bar_width)
    instances[plot_stuff[0]]['pos_j'].append(POS[labels[-1]] * 3 + (2 * plot_stuff[1] + 1) * bar_width)
    instances[plot_stuff[0]]['mean_d'].append(np.mean(deltas))
    instances[plot_stuff[0]]['std_d'].append(np.std(deltas))
    instances[plot_stuff[0]]['mean_j'].append(np.mean(jumps))
    instances[plot_stuff[0]]['std_j'].append(np.std(jumps))
    instances[plot_stuff[0]]['instance_size'].append(instance_size)

# wykres 1
legend = []
fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)
for k, v in reversed(list(instances.items())):
    lists = sorted(zip(*[v['instance_size'], v['mean_d']]))
    new_x, new_y = list(zip(*lists))
    ax1.errorbar(new_x, new_y, elinewidth=5, yerr=v['std_d'], label=k, alpha=0.75,
                 linestyle=v['linestyle'])
    ax1.set_yscale('log')
    ax1.set_ylabel('Liczba sprawdzonych rozwiązań')

for k, v in reversed(list(instances.items())):
    lists = sorted(zip(*[v['instance_size'], v['mean_j']]))
    new_x, new_y = list(zip(*lists))
    ax2.errorbar(new_x, new_y, elinewidth=5, yerr=v['std_j'], label=k, alpha=0.75,
                 linestyle=v['linestyle'])

    to_remove = [48, 35, 44, 47, 53, 358, 403, 64]
    plt.xscale('log')
    ax2.set_ylabel('Liczba kroków')

    ax2.get_xaxis().set_major_formatter(ScalarFormatter())
    ax2.get_xaxis().set_tick_params(which='minor', size=0)
    ax2.get_xaxis().set_tick_params(which='minor', width=0)

    used_instances = [inst for inst in instances_sizes[::3] if inst not in to_remove]
    ax2.set_xticks(used_instances)
    ax2.set_yscale('log')

# plt.xticks(positions, labels)
plt.legend()
plt.savefig('report/pics/steps.pdf')
