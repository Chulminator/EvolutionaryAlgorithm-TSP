#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <cmath>
#include <random>

#include "../State.hpp"
#include "../ResourceHolder.hpp"

#include "../BlinkEntity.hpp"

using namespace std; // use a namespace

class MainStep1: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    MainStep1(State::Context context);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool		update(sf::Time dt);
    bool		handleEvent(const sf::Event& event);
                
private:
    sf::Vector2f 			 windowSize;

    std::vector<std::array<float, 2>>	customCoords;
    sf::Text  				     mText1;
    std::vector<sf::CircleShape> selectedPoints;
    sf::Vector2f                 minXY;
    sf::Vector2f                 maxXY;
    
    BlinkEntity<sf::Text>	     blinkTextStep1;
    sf::Text 					 mTextStep1;
friend class StateMain;

};

