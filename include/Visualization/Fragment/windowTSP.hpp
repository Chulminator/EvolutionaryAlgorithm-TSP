#ifndef TRAVELLINGPROB
#define TRAVELLINGPROB

#define PI 3.141592653589793

#include <numeric> // iota
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <ctime>  // std::time
#include <time.h>
#include <unordered_set>
#include "evolution.hpp"

using namespace std; // use a namespace


class TSP {
public: 
    TSP(int nCity_, int nChromosome_);

    void generateCity();

    void generateChromosome(); 

    void CalculateFitness();
    
    int randomSelect(int num);
    
    void sortChromosome();
    
    const int getGeneration();

    void initSortIndex();
    
    bool endCondition();

    void crossover();

    void mutation();

    void newChromosome();
    
    void previousChromosome();

    void solve();  

private:
    int nCity;
    int nChromosome;

    // Chromosome
    int nCrossover;
    int nMutation;
    int nNewlyCreation;
    int nPrevious;

    // The number of parents pool to be selected
    int nParent;

    // what percent woule be mutated or crossovered in a chromosome
    double mutationRate; 
    double crossoverRate; 


    // To update new chromosome;
    unsigned int idxChromosome; 

    vector<array<double, 2>> coord;
    vector<vector<int>> vecChromosome; // 2nd order vector whose size is (nChromosome, nCity)
    vector<vector<int>> vecNewChromosome; // 2nd order vector whose size is (nChromosome, nCity)
    vector<double> vecDistance;
    std::vector<int> idxSort;
    unsigned int nGeneration;
    std::random_device rd; // random device
    std::mt19937 gen; // Mersenne Twister engine

    EvolutionaryAlgorithm evol;

};

#endif
