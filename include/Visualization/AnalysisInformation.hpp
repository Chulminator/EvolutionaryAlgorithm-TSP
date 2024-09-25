#pragma once

#include <iostream>
#include <array>

// #include <.\EA\TSP.hpp>
#include "../EA/EAIdentifier.hpp"
// #include <EAIdentifier.hpp>
// #include "../../EA/EAIdentifier.hpp"


using namespace std;
class AnalysisInfo
{
	public:
		AnalysisInfo();
		void setNChromosome(const int nChromosome_);
		void setNCity(const int nCity_);
		void setNGeneration(const int nGeneration_);
		void setNTypeEvol(const array<int ,Evolution::TypeCount> nTypeEvol_);

		const int& getNChromosome() const;
		const int& getNCity() const;
		const int& getNGeneration() const;
		const array<int ,Evolution::TypeCount>& getNTypeEvol() const;

	private:
		int nCity;
		int nChromosome;
		int nGneration;
		array<int ,Evolution::TypeCount> nTypeEvol;
};