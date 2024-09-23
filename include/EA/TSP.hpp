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
#include "../Visualization/Fragment/TSPVisualizer.hpp"

using namespace std; // use a namespace


class TSP {
public: 
    TSP(int nCity_, int nChromosome_);

    void reset(int nCity_, int nChromosome_);

    void generateCity();

    void generateChromosome(); 
    
    const bool endCondition();

    void solveOneStep();  

    const bool isAnalysisOver() const;  

    const vector<int>& getBestChromosome() const;

    // const vector<array<float, 2>>& getCoords() const;
    vector<array<float, 2>> getCoords() const;
private:

    void CalculateFitness();
    
    int randomSelect(int num);
    
    void sortChromosome();
    
    const int getGeneration() const;

    void initSortIndex();

    void crossover();

    void mutation();

    void newChromosome();
    
    void previousChromosome();


private:
    int nCity;
    int nChromosome;

    // Chromosome
    int nPrevious;
    int nNewlyCreation;
    int nCrossover;
    int nMutation;

    // The number of parents pool to be selected
    int nParent;

    // what percent woule be mutated or crossovered in a chromosome
    float mutationRate; 
    float crossoverRate; 

    bool   isOver;

    // To update new chromosome;
    unsigned int idxChromosome; 

    vector<array<float, 2>> coord;
    vector<vector<int>> vecChromosome; // 2nd order vector whose size is (nChromosome, nCity)
    vector<vector<int>> vecNewChromosome; // 2nd order vector whose size is (nChromosome, nCity)
    vector<float> vecDistance;
    std::vector<int> idxSort;
    unsigned int nGeneration;
    std::random_device rd; // random device
    std::mt19937 gen; // Mersenne Twister engine

    EvolutionaryAlgorithm evol;
};

#endif
