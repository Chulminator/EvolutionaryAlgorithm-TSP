#pragma once

using namespace std; // use a namespace

class TSPVisualizer {
public: 
    TSPVisualizer(int nCity_, int nChromosome_);

private:
    // std::vector< std:: >
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

