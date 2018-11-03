#!/usr/bin/python
from matplotlib import pyplot as plt
from subprocess import check_output
import numpy as np

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

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
    'p43': 5620,
    'rbg323': 1326,
    'rbg358': 1163,
    'rbg403': 2465,
    'rbg443': 2720,
    'ry48p': 14422,
}

bar_width = 0.7

def getPlotStuff(alg):
    if alg == '1':
        return ("RS", 0)
    if alg == '7':
        return ("LS Greedy", 1)
    if alg == '8':
        return ("LS Steepest", 2)
    return ()

a = check_output('./evaluate.sh').decode('utf-8')
lines = a.split("\n")[:-1]

instances = {'RS': {'color':'red'},
             'LS Greedy': {'color':'green'},
             'LS Steepest': {'color':'blue'},
            }
for k, v in instances.items():
    v['pos'] = []
    v['mean_t'] = []
    v['std_t'] = []
    v['mean_s'] = []
    v['std_s'] = []
    v['min_s'] = []

labels = []
positions = []
for i in range(0, len(lines), 4):
    print(lines[i])
    line = lines[i].split()
    labels.append(line[0].replace(".atsp", ""))
    positions.append(int(lines[i+1])+bar_width)

    plot_stuff = getPlotStuff(lines[i].split()[-1])
    times = np.fromstring(lines[i+2], dtype=np.float32, sep=' ')
    scores = np.fromstring(lines[i+3], dtype=np.int32, sep=' ') / BEST[labels[-1]]

    instances[plot_stuff[0]]['pos'].append(positions[-1] + (plot_stuff[1]-1)*bar_width)
    instances[plot_stuff[0]]['mean_t'].append(np.mean(times))
    instances[plot_stuff[0]]['std_t'].append(np.std(times))
    instances[plot_stuff[0]]['mean_s'].append(np.mean(scores))
    instances[plot_stuff[0]]['std_s'].append(np.std(scores))
    instances[plot_stuff[0]]['min_s'].append(np.min(scores))

# wykres 1
for k, v in instances.items():
    plt.bar(v['pos'], v['mean_s'], width=bar_width,
            color=v['color'], yerr=v['std_s'], label=k)

plt.xticks(positions, labels)
plt.ylabel(r'$\frac{\eta}{\eta_{min}}$', fontsize=18)
plt.legend()
plt.show()

# wykres 2
for k, v in instances.items():
    plt.bar(v['pos'], v['min_s'], width=bar_width,
            color=v['color'], label=k)

plt.xticks(positions, labels)
plt.ylabel(r'$\frac{\eta}{\eta_{min}}$', fontsize=18)
plt.legend()
plt.show()

# wykres 3
for k, v in instances.items():
    plt.bar(v['pos'], v['mean_t'], width=bar_width,
            color=v['color'], yerr=v['std_t'], label=k)
plt.xticks(positions, labels)
plt.ylabel(r'Czas [s]}', fontsize=18)
plt.yscale('log')
plt.legend()
plt.show()





