#ifndef EVOLUTION
#define EVOLUTION

#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_set>

using namespace std; // use a namespace


class EvolutionaryAlgorithm{
  public:

    EvolutionaryAlgorithm();

    vector<int> orderCrossover(const vector<int>& parent1, const vector<int>& parent2, int start, int end);

    void swapMutation(vector<int>& chromosome);

    void inversionMutation(vector<int>& chromosome, int start, int end);

  private:

};





// vector<int> orderCrossover(const vector<int>& parent1, const vector<int>& parent2, int start, int end); 

// void swapMutation(vector<int>& chromosome);

// void inversionMutation(vector<int>& chromosome);

// vector< vector<int> > generateChromosome(int NCity, int NChromosome); 

// vector<double> CalculateFitness( vector< vector<int> > vecChromosome, vector< array<double, 2> > coord);


#endif

// gpt says
// vector<int> orderCrossover(const vector<int> parent1, const vector<int> parent2, int start, int end);
// 이 경우, parent1과 parent2는 값에 의한 전달입니다. 즉, 함수가 호출될 때, parent1과 parent2의 복사본이 생성되어 함수 내부로 전달됩니다.
// 이 방식은 메모리 사용량이 더 많고, 성능이 저하될 수 있습니다. 특히 큰 벡터를 전달할 때는 복사 비용이 발생하기 때문입니다.

// vector<int> orderCrossover(const vector<int>& parent1, const vector<int>& parent2, int start, int end);
// 이 경우, parent1과 parent2는 참조에 의한 전달입니다. 즉, 함수가 호출될 때, 원본 벡터에 대한 참조가 전달됩니다. 따라서 복사본이 생성되지 않으며, 메모리 사용량이 줄어들고 성능이 향상됩니다.
// 참조를 사용하면 원본 데이터가 변경되지 않도록 보장할 수 있습니다. (단, const 키워드 덕분에 함수 내부에서 원본 데이터를 수정할 수 없습니다.)
