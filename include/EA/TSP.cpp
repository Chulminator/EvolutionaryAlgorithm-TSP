 
#include "TSP.hpp"



TSP::TSP(const int nCity_, const int nChromosome_)
: nCity(nCity_)
, nChromosome(nChromosome_) 
, coord(nCity_) 
, vecChromosome(nChromosome_, vector<int>(nCity))
, vecNewChromosome(nChromosome_, vector<int>(nCity))
, vecDistance(nChromosome_, 0.0)
, idxSort(nChromosome_)
, nGeneration(0)
, evol()
, gen(rd())
, idxChromosome(0)
, mutationRate(0.3)
, crossoverRate(0.4)
, isOver(true)
, goal( PI * 2 )
{
  generateCity();
  generateChromosome();
  vecNewChromosome = vecChromosome;
  CalculateFitness();    
  sortChromosome();

  nPrevious      = static_cast<int>(nChromosome * 0.2); 
  nNewlyCreation = static_cast<int>(nChromosome * 0.2);
  nCrossover     = static_cast<int>(nChromosome * 0.3);
  nMutation      = nChromosome - nPrevious - nNewlyCreation - nCrossover;

  nParent        = static_cast<int>(nChromosome * 0.7);
  
  printf("==================================\n");
  printf("Chromosome from the previous:\t%d\n", nPrevious);
  printf("Chromosome newly created:\t%d\n", nNewlyCreation);
  printf("Chromosome from the Crossover:\t%d\n", nCrossover);
  printf("Chromosome from the Mutation:\t%d\n", nMutation);
  printf("==================================\n");
}

TSP::TSP()
: nCity(0)
, nChromosome(0) 
, coord(0) 
, vecChromosome(0, vector<int>(0))
, vecNewChromosome(0, vector<int>(0))
, vecDistance(0, 0.0)
, idxSort(0)
, nGeneration(0)
, evol()
, gen(rd())
, idxChromosome(0)
, mutationRate(0.3)
, crossoverRate(0.4)
, isOver(true)
, goal( PI * 2 )
{

}

void TSP::reset(const int& nCity_, const int& nChromosome_) {
  nCity       = nCity_;
  nChromosome = nChromosome_; 
  nGeneration = 0;

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
  CalculateFitness();    
  sortChromosome();

  nPrevious      = static_cast<int>(nChromosome * 0.2); 
  nNewlyCreation = static_cast<int>(nChromosome * 0.2);
  nCrossover     = static_cast<int>(nChromosome * 0.3);
  nMutation      = nChromosome - nPrevious - nNewlyCreation - nCrossover;

  nParent        = static_cast<int>(nChromosome * 0.7);
  
  printf("==================================\n");
  printf("Chromosome from the previous:\t%d\n", nPrevious);
  printf("Chromosome newly created:\t%d\n", nNewlyCreation);
  printf("Chromosome from the Crossover:\t%d\n", nCrossover);
  printf("Chromosome from the Mutation:\t%d\n", nMutation);
  printf("==================================\n");
}


void TSP::reset(const int nCity_, const int nChromosome_, 
                const vector<array<float, 2>>& coord_,
                const array<int, Evolution::TypeCount>& nTypeEvol){

  nCity       = nCity_;
  nChromosome = nChromosome_; 
  nGeneration = 0;
  goal        = 0.;

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
  
  generateCity(coord_);
  generateChromosome();
  vecNewChromosome = vecChromosome;
  CalculateFitness();    
  sortChromosome();

  nPrevious      = nTypeEvol[Evolution::Elitism];
  nNewlyCreation = nTypeEvol[Evolution::NewChromosome];
  nCrossover     = nTypeEvol[Evolution::Crossover];
  nMutation      = nTypeEvol[Evolution::Mutation];

  nParent        = static_cast<int>(nChromosome * 0.7);
  
  printf("==================================\n");
  printf("Chromosome from the previous:\t%d\n", nPrevious);
  printf("Chromosome newly created:\t%d\n", nNewlyCreation);
  printf("Chromosome from the Crossover:\t%d\n", nCrossover);
  printf("Chromosome from the Mutation:\t%d\n", nMutation);
  printf("==================================\n");
}





void TSP::generateCity() {
  for (int ii = 0; ii < nCity; ii++) {
    float theta = ii / static_cast<float>(nCity) * PI * 2.0;
    coord[ii][0] = cos(theta);
    coord[ii][1] = sin(theta);
  }
  return;
}


void TSP::generateCity(vector<array<float, 2>> coord_){
  coord = coord_;
  return;
}


void TSP::generateChromosome() {
    std::default_random_engine engine(static_cast<unsigned int>(std::time(0)));    
    for (int ii = 0; ii < nChromosome; ii++) {
        for (int jj = 0; jj < nCity; jj++) {
            vecChromosome[ii][jj] = jj; 
        }
        std::shuffle(vecChromosome[ii].begin()+1, vecChromosome[ii].end(), engine);
        vecNewChromosome[ii] = vecChromosome[ii];
    }
    return;
}

void TSP::CalculateFitness() {
    for (int jj = 0; jj < nChromosome; jj++) {
        float distance = 0.0;
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
    std::uniform_int_distribution<> dis(0, num-1);
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
  if( vecDistance[idxSort[0]] > goal){
    isOver = false;
  }
  else{
    isOver = true;
  }
  return isOver;
}

const bool TSP::isAlreadyInPool( ){
  for ( int ii = 0; ii < idxChromosome; ++ii ){
    if( std::equal(vecNewChromosome[ii].begin(), vecNewChromosome[ii].end(), vecNewChromosome[idxChromosome].begin()) ){
      return true;
    }
  }
  return false;
}

void TSP::crossover(){
  // crossover
  std::uniform_real_distribution<> dis(0, crossoverRate);
  double rate  = dis(gen);
  int nCityCrossover = static_cast<int>(nCity * rate);
  for ( ; idxChromosome < nCrossover+nPrevious; ++idxChromosome ){      
    int idxParent1 = randomSelect(nParent);      
    int idxParent2;
    do {
        idxParent2 = randomSelect(nParent);
    } while (idxParent1 == idxParent2); 
    int start = randomSelect(nCity - nCityCrossover - 1);
    int end   = start + nCityCrossover+1; 
    vecNewChromosome[idxChromosome] =  
    evol.orderCrossover( vecChromosome[idxSort[idxParent1]],
                          vecChromosome[idxSort[idxParent2]],
                          start,
                          end);     
    if (isAlreadyInPool()) {      
      --idxChromosome;
    }                          
  }
}

void TSP::mutation(){  
  std::uniform_real_distribution<> dis(0, mutationRate);
  double rate  = dis(gen);
  int nCityMutation = static_cast<int>(nCity * rate);

  for ( int ii = 0; ii < nMutation; ++ii ){
    int start = randomSelect(nCity - nCityMutation - 1);
    int end   = start + nCityMutation+1; 
    vecNewChromosome[idxChromosome] =  vecChromosome[idxSort[ii]];
    evol.inversionMutation( vecNewChromosome[idxChromosome], start, end );
    ++idxChromosome;
  }

  return;
}

void TSP::newChromosome(){
  std::default_random_engine engine(static_cast<unsigned int>(std::time(0)));
  for (int ii = 0; ii < nNewlyCreation; ++ii) {
    for (int jj = 0; jj < nCity; jj++) {
        vecNewChromosome[idxChromosome][jj] = jj;
    }    
    std::shuffle(vecNewChromosome[idxChromosome].begin()+1, vecNewChromosome[idxChromosome].end(), engine);
    idxChromosome++; 
  }
  return;
}
    
void TSP::previousChromosome(){
  idxChromosome = 0;  
  int ii = 0;
  for (; idxChromosome < nPrevious; ++idxChromosome) {
    vecNewChromosome[idxChromosome] = vecChromosome[idxSort[ii++]];
    if (isAlreadyInPool()) {
      if ( ii == nChromosome ){
        printf("I am here\n");
        getchar();
      }
      
      --idxChromosome;
    }
  }
  
}

void TSP::solveOneStep(){
  // Evolutionary algorithm 
  // exit(1);
  if( !endCondition() ){
    previousChromosome();
    crossover();
    mutation();
    newChromosome();

    CalculateFitness();    
    sortChromosome();

    printf("Generation: %d | Shortest distance: %e \n", nGeneration, vecDistance[idxSort[0]]);
  }
  
  // for ( int ii = 0; ii < nChromosome; ++ii ){        
  //   for ( int jj = 0; jj < nCity; ++jj ){        
  //     printf( "%d ", vecNewChromosome[ii][jj]);
  //   }
  //   printf( "\n" );
  // }
  // printf( "-----------------------------\n" );
  // exit(1);
}

// void TSP::solve(){
//   isOver = false;
//   do {    
//     // Evolutionary algorithm
//     crossover();
//     mutation();
//     newChromosome();
//     previousChromosome();

//     CalculateFitness();    
//     sortChromosome();

//     printf("Generation: %d | Shortest distance: %e \n", nGeneration, vecDistance[idxSort[0]]);

//   }while( endCondition() );
//   isOver = true;
// }

const bool TSP::isAnalysisOver() const{
  return isOver;
}
    
const vector<int>& TSP::getBestChromosome() const{  
  return vecNewChromosome[idxSort[0]];
}

const array<vector<int>, Evolution::TypeCount> TSP::getBestTypeChromosome() const{
  array<vector<int>, Evolution::TypeCount>  result;

  auto findFirstInRange = [](const std::vector<int>& vec, int lowerBound, int upperBound) {
      for (int i = 0; i < vec.size(); ++i) {
          if (vec[i] >= lowerBound && vec[i] <= upperBound) {
              return i; // 첫 번째로 발견된 인덱스를 반환
          }
      }
      return -1; // 범위 내의 값이 없는 경우 -1 반환
  };

  int firstPreviousIdx = findFirstInRange(idxSort, 0, 
                                                   nPrevious - 1);
  int firstCrossoverIdx = findFirstInRange(idxSort, nPrevious, 
                                                    nCrossover + nPrevious- 1);
  int firstMutationIdx = findFirstInRange(idxSort, nCrossover + nPrevious, 
                                                   nCrossover + nPrevious + nMutation - 1);
  int firstNewlyCreationIdx = findFirstInRange(idxSort, nCrossover + nPrevious + nMutation, 
                                                        nChromosome - 1);

  result[Evolution::Crossover]      = vecNewChromosome[idxSort[firstCrossoverIdx]];
  result[Evolution::Mutation]       = vecNewChromosome[idxSort[firstMutationIdx]];
  result[Evolution::Elitism]        = vecNewChromosome[idxSort[firstPreviousIdx]];
  result[Evolution::NewChromosome]  = vecNewChromosome[idxSort[firstNewlyCreationIdx]];
  return result;
}

const std::pair<float, Evolution::Type> TSP::getBestDistance() const{  
  if( idxSort[0] < nPrevious){
    return make_pair(vecDistance[idxSort[0]], Evolution::Elitism);
  }
  else if( idxSort[0] < nPrevious + nCrossover){
    return make_pair(vecDistance[idxSort[0]], Evolution::Crossover);
  }
  else if( idxSort[0] < nPrevious + nCrossover + nMutation){
    return make_pair(vecDistance[idxSort[0]], Evolution::Mutation);
  }
  else {
    return make_pair(vecDistance[idxSort[0]], Evolution::NewChromosome);
  }
}

const vector<float>& TSP::getDistance() const{
  return vecDistance;
}

vector<array<float, 2>> TSP::getCoords() const{
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