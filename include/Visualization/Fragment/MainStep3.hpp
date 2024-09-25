#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <deque>

#include "../../EA/TSP.hpp"
#include "../State.hpp"
#include "../ResourceHolder.hpp"
#include "../GUI/Container.hpp"
#include "../../EA/EvolalgorithmIdentifier.hpp"
#include "../PauseableClock.hpp"

using namespace std; // use a namespace

class MainStep3: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    MainStep3(State::Context context);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool update(sf::Time dt);
    bool handleEvent(const sf::Event& event);

    void setParameters(const string mStringNChromosome,
                       const array<string, Evolution::TypeCount>& mStringPercent,
                       const std::vector<std::array<float, 2>>& Coords,
                       const sf::Vector2f minXY_,
                       const sf::Vector2f maxXY_);

private:
    void proceedTSP();
    void setLocalCities();
    void setChromosomes();
                
private:
    sf::Vector2f 			     windowSize;
    sf::RectangleShape           BoundaryBox;
    array<sf::RectangleShape, Evolution::TypeCount> BoundaryBoxEvol;
    array<sf::Text, Evolution::TypeCount> mTextEvol;
		 
    // tsp
    TSP 				tsp;
    array<TSPVisualizer, Evolution::TypeCount> mTypeVisualizer;
    deque<float> distanceHistory;

    bool              isConverged;
    bool              isRunning;
    bool              flagPause;
    sf::Time          accumulatedTime;
    // PauseableClock 	  stepTime;

    // parameters
    int nCity;
    int nChromosome;
    array<int, Evolution::TypeCount> nTypeEvol;

    sf::Text  				     mText1;
    array<vector<array<float,2>>, Evolution::TypeCount> cityCoords;
    array< vector<sf::CircleShape>, Evolution::TypeCount> cityCircles;
    
    std::vector<std::array<float, 2>>	orgCoords;
    sf::Vector2f minXY;
    sf::Vector2f maxXY;    
    // GUI::Container mGUIContainerButton;
    // GUI::Container mGUIContainerLabel;

friend class StateMain;

};

