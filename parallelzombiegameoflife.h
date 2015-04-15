#ifndef PARALLELZOMBIEGAMEOFLIFE_H
#define PARALLELZOMBIEGAMEOFLIFE_H

#include <iostream>
#include <vector>
#include "gameconfig.h"

class ParallelZombieGameOfLife
{
private:
    std::vector< std::vector<int> > m;
    int iterations;
    int grid;

    void printMatrix();
    void applyRule(int& cel, std::vector<int>& neibors);

public:
    ParallelZombieGameOfLife(int grid, int iterations, std::vector< std::vector<int> >& gridConfig);
    ParallelZombieGameOfLife(GameConfig gf);
    void run();
    void runParallel(int initIndex, int finalIndex);
    ~ParallelZombieGameOfLife();

    // For each iteration, each thread will pick a boundage to  cycle throuth
    // The sync occours on applying the rules. Only one thread may apply
    // the rules once a time because.
};

#endif // PARALLELZOMBIEGAMEOFLIFE_H
