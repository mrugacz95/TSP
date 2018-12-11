#ifndef TSP_TABUSEARCH_H
#define TSP_TABUSEARCH_H


#include <random>
#include "Solver.h"

class TabuSearch : public Solver {

public:
    /**
     * Implements Tabu search
     * @param k how many moves to generate for future
     */
    TabuSearch(unsigned k, unsigned cadence);

    std::string getName() override;

    void printParameters() override;

    ~TabuSearch() override = default;

    unsigned int countSolutionLength(std::vector<int> &vec) override;

private:
    void solve() override;

    std::vector<std::vector<unsigned >> tabu;

    std::default_random_engine engine;
    unsigned k;
    unsigned cadence;

    class Move {
    public:
        Move(unsigned from, unsigned to, int delta) : from(from), to(to), delta(delta) {}

        unsigned from, to;
        int delta;

        int operator<(const Move &rhs) const {
            return delta < rhs.delta;
        }
    };

    void setTabu(unsigned a, unsigned b, unsigned val);

    unsigned getTabu(unsigned a, unsigned b);
};


#endif //TSP_TABUSEARCH_H
