import os
import shutil
from collections import defaultdict
from subprocess import Popen, PIPE, STDOUT
from matplotlib import pyplot as plt
import numpy as np
from random import randint

INSTANCES_DIR = 'data'
RUN_NUMBER = 1000


def pairwise(iterable):
    "s -> (s0, s1), (s1, s2), (s2, s3), ..."
    for i in range(len(iterable)):
        yield (iterable[i], iterable[(i + 1) % len(iterable)])


def compare(sol1, sol2):
    pairs = set()
    sim = 0
    for pair in pairwise(sol1):
        pairs.add(pair)
    for pair in pairwise(sol2):
        if pair in pairs:
            sim += 1
    return sim / len(sol1)


ALGORITHMS = [8]


def find_best():
    for file in ['ftv38.atsp', 'ry48p.atsp']:
        if 'atsp' not in file:
            continue
        path = os.path.join(INSTANCES_DIR, file)
        best_path = os.path.join(INSTANCES_DIR, 'best_' + file.replace('atsp', 'txt'))
        print(file)
        if os.path.isfile(best_path):
            with open(best_path) as best_file:
                text = best_file.read().split('\n')
                solution = list(map(int, text[4].strip().split(' ')))
                quality = int(text[3])
            best = (quality, solution)
            print(best)
        else:
            best = (np.inf, None)
        for alg in ALGORITHMS:
            print(alg)
            for i in range(1000):
                if i % 100 == 0:
                    print(i, end=', ')
                pipe = Popen(['cmake-build-release/TSP'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
                seed = randint(0, np.iinfo(np.int32).max)
                output, err = pipe.communicate(bytes(f'1 {path} similarity.txt {seed} {alg}', 'utf8'))
                if err is not None:
                    print(err)
                    return
                with open('similarity.txt') as output:
                    text = output.read().split('\n')
                    solution = list(map(int, text[4].strip().split(' ')))
                    quality = int(text[3])
                if quality < best[0]:
                    print('found best', best)
                    best = (quality, solution)
                    shutil.copy('similarity.txt', best_path)
        print(best)


def main():
    for file in ['ftv38.atsp', 'ry48p.atsp']:

        best_path = os.path.join(INSTANCES_DIR, 'best_' + file.replace('atsp', 'txt'))
        with open(best_path) as output:
            text = output.read().split('\n')
            solution = list(map(int, text[4].strip().split(' ')))
            quality = int(text[3])
            best = (quality, solution)
        path = os.path.join(INSTANCES_DIR, file)
        solutions = []
        for i in range(RUN_NUMBER):
            pipe = Popen(['cmake-build-release/TSP'], stdout=PIPE, stdin=PIPE, stderr=STDOUT)
            seed = randint(0, np.iinfo(np.int32).max)
            output, err = pipe.communicate(bytes(f'1 {path} similarity.txt {seed} 8', 'utf8'))
            if err is not None:
                print(err)
                return
            with open('similarity.txt') as output:
                text = output.read().split('\n')
                solution = list(map(int, text[4].strip().split(' ')))
                quality = int(text[3])
                solutions.append((quality, solution))
        x = []
        y = []
        q = defaultdict(list)
        for quality, solution in solutions:
            comp = compare(solution, best[1])
            x.append(comp)
            y.append(quality)
            q[comp].append(quality / best[0] - 1)
        indicates = list(q.keys())
        data = list(q.values())
        plt.violinplot(data, indicates, widths=0.02)
        plt.xlabel('Podobieństwo rozwiązania')
        plt.ylabel(r'$\frac{\eta}{\eta_{min}}-1$')
        plt.savefig(f'report/pics/quality_similarity_{file}.pdf')
        plt.show()
        plt.clf()


if __name__ == '__main__':
    # assert compare([1, 2, 3, 4, 5], [1, 2, 3, 4, 5]) == 1.0
    # assert compare([5, 4, 3, 2, 1], [1, 2, 3, 4, 5]) == 0.0
    # assert compare([1, 2, 4, 3], [1, 2, 3, 4]) == 0.25
    # find_best()
    main()
