#include "AnalysisInformation.hpp"

AnalysisInfo::AnalysisInfo()
: nCity(-1)
, nChromosome(-1)
, nGneration(-1)
{

}

void AnalysisInfo::setNChromosome(const int nChromosome_){
	nChromosome = nChromosome_;
}

void AnalysisInfo::setNCity(const int nCity_){
	nCity = nCity_;
}

void AnalysisInfo::setNTypeEvol(const array<int ,Evolution::TypeCount> nTypeEvol_){
	nTypeEvol = nTypeEvol_;
}

void AnalysisInfo::setNGeneration(const int nGeneration_){
	nGneration = nGeneration_;
}

const int& AnalysisInfo::getNChromosome() const{
	return nChromosome;
};

const int& AnalysisInfo::getNCity() const{
	return nCity;
}

const int& AnalysisInfo::getNGeneration() const{
	return nGneration;
}

const array<int ,Evolution::TypeCount>& AnalysisInfo::getNTypeEvol() const{
	return nTypeEvol;
}