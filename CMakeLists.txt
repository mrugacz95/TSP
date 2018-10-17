cmake_minimum_required(VERSION 3.12)
project(TSP)

set(CMAKE_CXX_STANDARD 17)

include_directories(Headers)
include_directories(Headers/Ants)
include_directories(Headers/GeneticAlgorithm)
include_directories(Sources)

add_executable(TSP
        Headers/Ants/Ant.h
        Headers/Ants/AntsAlgorithm.h
        Headers/Ants/EdgePheromone.h
        Headers/GeneticAlgorithm/GeneticAlgorithm.h
        Headers/GeneticAlgorithm/Path.h
        Headers/GeneticAlgorithm/Population.h
        Headers/BranchAndBound.h
        Headers/BruteForce.h
        Headers/ClosestNeighbour.h
        Headers/Edge.h
        Headers/Graph.h
        Headers/ListGraph.h
        Headers/MatrixGraph.h
        Headers/RandomSolver.h
        Headers/SimulatedAnnealing.h
        Headers/Solver.h
        Sources/Ants/Ant.cpp
        Sources/Ants/AntsAlgorithm.cpp
        Sources/Ants/EdgePheromone.cpp
        Sources/GeneticAlgorithm/GeneticAlgorithm.cpp
        Sources/GeneticAlgorithm/Path.cpp
        Sources/GeneticAlgorithm/Population.cpp
        Sources/BranchAndBound.cpp
        Sources/BruteForce.cpp
        Sources/ClosestNeighbour.cpp
        Sources/Edge.cpp
        Sources/ListGraph.cpp
        Sources/MatrixGraph.cpp
        Sources/RandomSolver.cpp
        Sources/SimulatedAnnealing.cpp
        Sources/Solver.cpp
        main.cpp
        Headers/GraphLoader.h
        Sources/RandomGraphLoader.cpp
        Headers/RandomGraphLoader.h)
