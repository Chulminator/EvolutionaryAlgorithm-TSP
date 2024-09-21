
#include <iostream>
#include <vector>
#include <array>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <random>
#include "./include/TSP.hpp"
// #include "./include/evolution.hpp"


int main(){
// // // // // // input // // // // // //
    int nCity        = 10; // The number of city
    int nChromosome  = 10; // The number of Chromosome

    TSP tsp(nCity, nChromosome);
    tsp.solve();

    return 0;

}
