 
#include "TSP.hpp"



TSP::TSP(int nCity_, int nChromosome_)
: nCity(nCity_)
, nChromosome(nChromosome_) 
, coord(nCity_) 
, vecChromosome(nChromosome_, vector<int>(nCity))
, vecNewChromosome(nChromosome_, vector<int>(nCity))
, vecDistance(nChromosome_, 0.0)
, idxSort(nChromosome_)
, nGeneration(1)
, evol()
, gen(rd())
, idxChromosome(0)
, mutationRate(0.3)
, crossoverRate(0.4)
, isOver(true)
{
  generateCity();
  generateChromosome();
  vecNewChromosome = vecChromosome;

  nPrevious      = static_cast<int>(nChromosome * 0.2); 
  nNewlyCreation = static_cast<int>(nChromosome * 0.2);
  nCrossover     = static_cast<int>(nChromosome * 0.3);
  nMutation      = nChromosome - nPrevious - nNewlyCreation - nCrossover;

  nParent        = static_cast<int>(nChromosome * 0.5);
  
  printf("==================================\n");
  printf("Chromosome from the previous:\t%d\n", nPrevious);
  printf("Chromosome newly created:\t%d\n", nNewlyCreation);
  printf("Chromosome from the Crossover:\t%d\n", nCrossover);
  printf("Chromosome from the Mutation:\t%d\n", nMutation);
  printf("==================================\n");
}

void TSP::reset(int nCity_, int nChromosome_) {
  nCity       = nCity_;
  nChromosome = nChromosome_; 
  nGeneration = 1;

  coord.clear();
  vecChromosome.clear();
  vecNewChromosome.clear();
  vecDistance.clear();
  idxSort.clear();
 
  coord.resize(nCity_);
  vecChromosome.resize(nChromosome_, std::vector<int>(nCity_));
  vecNewChromosome.resize(nChromosome_, std::vector<int>(nCity_));
  vecDistance.resize(nChromosome_, 0.0);
  idxSort.resize(nChromosome_); 

  generateCity();
  generateChromosome();
  vecNewChromosome = vecChromosome;

  nPrevious      = static_cast<int>(nChromosome * 0.2); 
  nNewlyCreation = static_cast<int>(nChromosome * 0.2);
  nCrossover     = static_cast<int>(nChromosome * 0.3);
  nMutation      = nChromosome - nPrevious - nNewlyCreation - nCrossover;

  nParent        = static_cast<int>(nChromosome * 0.5);
  
  printf("==================================\n");
  printf("Chromosome from the previous:\t%d\n", nPrevious);
  printf("Chromosome newly created:\t%d\n", nNewlyCreation);
  printf("Chromosome from the Crossover:\t%d\n", nCrossover);
  printf("Chromosome from the Mutation:\t%d\n", nMutation);
  printf("==================================\n");
}
void TSP::generateCity() {
  for (int ii = 0; ii < nCity; ii++) {
    double theta = ii / static_cast<double>(nCity) * PI * 2.0;
    // coord[ii][0] = cos(theta)*100.;
    // coord[ii][1] = sin(theta)*100.;
    coord[ii][0] = cos(theta);
    coord[ii][1] = sin(theta);
  }
  return;
}

void TSP::generateChromosome() {
    std::default_random_engine engine(static_cast<unsigned int>(std::time(0)));    
    for (int ii = 0; ii < nChromosome; ii++) {
        for (int jj = 0; jj < nCity; jj++) {
            vecChromosome[ii][jj] = jj; 
        }
        std::shuffle(vecChromosome[ii].begin(), vecChromosome[ii].end(), engine);
    }
    return;
}

void TSP::CalculateFitness() {
    for (int jj = 0; jj < nChromosome; jj++) {
        double distance = 0.0;
        for (int ii = 0; ii < nCity - 1; ii++) {
            distance += sqrt(pow(coord[vecNewChromosome[jj][ii]][0] - coord[vecNewChromosome[jj][ii + 1]][0], 2) +
                             pow(coord[vecNewChromosome[jj][ii]][1] - coord[vecNewChromosome[jj][ii + 1]][1], 2));
        }
        distance += sqrt(pow(coord[vecNewChromosome[jj][0]][0] - coord[vecNewChromosome[jj][nCity - 1]][0], 2) +
                         pow(coord[vecNewChromosome[jj][0]][1] - coord[vecNewChromosome[jj][nCity - 1]][1], 2));

        vecDistance[jj] = distance;
    }
    return;
}

int TSP::randomSelect(int num){
  // randomly select two nums from 0 to num-1
    std::uniform_int_distribution<> dis(0, num - 1);
  return dis(gen);
}

const int TSP::getGeneration() const{
  return nGeneration;
}


void TSP::sortChromosome(){
  initSortIndex();
  std::sort (idxSort.begin (), idxSort.end (), [this] 
      (int i1, int i2) {
          return vecDistance[i1] < vecDistance[i2];
      }
  );
}

void TSP::initSortIndex(){
  std::iota(idxSort.begin(), idxSort.end(), 0);  
}

const bool TSP::endCondition(){
  vecChromosome = vecNewChromosome;
  ++nGeneration;
  return vecDistance[idxSort[0]] > PI * 2 * 1.05;
}

void TSP::crossover(){
  // crossover
  idxChromosome = 0;
  int nCityCrossover = static_cast<int>(nCity * crossoverRate);
  for ( ; idxChromosome < nCrossover; ++idxChromosome ){      
    int idxParent1 = randomSelect(nParent);      
    int idxParent2;
    do {
        idxParent2 = randomSelect(nParent);
    } while (idxParent1 == idxParent2); 
    int start = randomSelect(nCity - nCityCrossover - 1);
    int end   = start + nCityCrossover; 
    vecNewChromosome[idxChromosome] =  
    evol.orderCrossover( vecChromosome[idxSort[idxParent1]],
                          vecChromosome[idxSort[idxParent2]],
                          start,
                          end);
  }
}

void TSP::mutation(){
  
  int nCityMutation = static_cast<int>(nCity * mutationRate);
  for ( int ii = 0; ii < nMutation; ++ii ){
    int start = randomSelect(nCity - nCityMutation - 1);
    int end   = start + nCityMutation; 
    vecNewChromosome[idxChromosome] =  vecChromosome[idxSort[ii]];
    evol.inversionMutation( vecNewChromosome[idxChromosome], start, end );
    idxChromosome++;
  }

  return;
}

void TSP::newChromosome(){
  std::default_random_engine engine(static_cast<unsigned int>(std::time(0)));
  for (int ii = 0; ii < nNewlyCreation; ++ii) {
    for (int jj = 0; jj < nCity; jj++) {
        vecNewChromosome[idxChromosome][jj] = jj;
    }    
    std::shuffle(vecNewChromosome[idxChromosome].begin(), vecNewChromosome[idxChromosome].end(), engine);
    idxChromosome++; 
  }
  return;
}
    
void TSP::previousChromosome(){
  for (int ii = 0; ii < nPrevious; ii++) {
    vecNewChromosome[idxChromosome++] = vecChromosome[idxSort[ii]];
  }
  
}

void TSP::solve(){
  isOver = false;
  do {    
    // Evolutionary algorithm
    crossover();
    mutation();
    newChromosome();
    previousChromosome();

    CalculateFitness();    
    sortChromosome();

    printf("Generation: %d | Shortest distance: %e \n", nGeneration, vecDistance[idxSort[0]]);

  }while( endCondition() );
  isOver = true;
  for ( int jj = 0; jj < nCity; ++jj ){        
    printf( "%d ", vecNewChromosome[idxSort[0]][jj]);
  }
}

const bool TSP::isAnalysisOver() const{
  return isOver;
}
    
const vector<int>& TSP::getBestChromosome() const{  
  return vecNewChromosome[0];
}

vector<array<double, 2>> TSP::getCoords() const{
  return coord;
}


    // if( idxSort[0] < nCrossover){
    //   printf("Crossover\n");
    // }
    // else if( idxSort[0] - nCrossover < nMutation ){
    //   printf("Mutation\n");
    // }
    // else if( idxSort[0] - nCrossover - nMutation < nNewlyCreation ){
    //   printf("NewlyGenerated\n");
    // }
    // else{
    //   printf("Previous\n");
    // }