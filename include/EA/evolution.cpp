 
#include "evolution.hpp"


EvolutionaryAlgorithm::EvolutionaryAlgorithm()
{

}

vector<int> EvolutionaryAlgorithm::orderCrossover(const vector<int>& parent1, const vector<int>& parent2, int start, int end){
    // int nCity = parent1.size();
    // vector<int> child(nCity, -1); // Initialize child with -1 (or any placeholder)
    
    // // Copy the selected segment from parent1 to child
    // for (int ii = 0; ii <= start; ++ii) {
    //     child[ii] = parent1[ii];
    // }
    // for (int ii = end; ii < nCity; ++ii) {
    //     child[ii] = parent1[ii];
    // }

    // // Fill the remaining positions in child with elements from parent2
    // int currentIdx = (start + 1) % nCity; // Start filling after the end index
    // for (int ii = 0; ii < nCity; ++ii) {
    //     int parent2Value = parent2[ii];
    //     // Only add if the value is not already in the child
    //     if (find(child.begin(), child.end(), parent2Value) == child.end()) {
    //         child[currentIdx] = parent2Value;
    //         currentIdx = (currentIdx + 1) % nCity; // Move to the next index
    //     }
    // }
    // return child;
    int nCity = parent1.size();
    vector<int> child(nCity, -1); // Initialize child with -1 (or any placeholder)
    
    // Copy the selected segment from parent1 to child
    for (int ii = start; ii <= end; ++ii) {
        child[ii] = parent1[ii];
    }

    // Fill the remaining positions in child with elements from parent2
    int currentIdx = (end + 1) % nCity; // Start filling after the end index
    for (int ii = 0; ii < nCity; ++ii) {
        int parent2Value = parent2[ii];
        // Only add if the value is not already in the child
        if (find(child.begin(), child.end(), parent2Value) == child.end()) {
            child[currentIdx] = parent2Value;
            currentIdx = (currentIdx + 1) % nCity; // Move to the next index
        }
    }
    return child;    
}

void EvolutionaryAlgorithm::swapMutation(vector<int>& chromosome) {
    int idx1 = rand() % chromosome.size();
    int idx2 = rand() % chromosome.size();
    swap(chromosome[idx1], chromosome[idx2]);
}

void EvolutionaryAlgorithm::inversionMutation(vector<int>& chromosome, int start, int end){
    if (start > end) {
        swap(start, end);
    }
    reverse(chromosome.begin() + start, chromosome.begin() + end + 1);
}

