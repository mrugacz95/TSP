cmake_minimum_required(VERSION 3.10)
project(TSP)

set(CMAKE_CXX_STANDARD 17)

include_directories(Headers)

set(HEADER_FILES Headers/Ants/Ant.h
        Headers/Ants/AntsAlgorithm.h
        Headers/Ants/EdgePheromone.h
        Headers/GeneticAlgorithm/GeneticAlgorithm.h
        Headers/GeneticAlgorithm/Path.h
        Headers/GeneticAlgorithm/Population.h
        Headers/AsymmetricMatrixGraph.h
        Headers/BranchAndBound.h
        Headers/BruteForce.h
        Headers/ClosestNeighbour.h
        Headers/Edge.h
        Headers/Graph.h
        Headers/ListGraph.h
        Headers/RandomSolver.h
        Headers/SimulatedAnnealing.h
        Headers/Solver.h
        Headers/SymmetricMatrixGraph.h
        Headers/LocalSearch.h)
set(SOURCE_FILES main.cpp
        Sources/Ants/Ant.cpp
        Sources/Ants/AntsAlgorithm.cpp
        Sources/Ants/EdgePheromone.cpp
        Sources/GeneticAlgorithm/GeneticAlgorithm.cpp
        Sources/GeneticAlgorithm/Path.cpp
        Sources/GeneticAlgorithm/Population.cpp
        Sources/AsymmetricMatrixGraph.cpp
        Sources/BranchAndBound.cpp
        Sources/BruteForce.cpp
        Sources/ClosestNeighbour.cpp
        Sources/Edge.cpp
        Sources/ListGraph.cpp
        Sources/RandomSolver.cpp
        Sources/SimulatedAnnealing.cpp
        Sources/Solver.cpp
        Sources/SymmetricMatrixGraph.cpp
        Sources/LocalSearch.cpp
        Sources/LocalSearch.cpp)
add_executable(TSP ${SOURCE_FILES} ${HEADER_FILES})

