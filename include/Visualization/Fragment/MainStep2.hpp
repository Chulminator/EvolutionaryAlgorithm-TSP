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

using namespace std; // use a namespace

class MainStep2: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    MainStep2(State::Context context);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool		update(sf::Time dt);
    bool		handleEvent(const sf::Event& event);

    void setCities(std::vector<std::array<float, 2>> Coords);
                
private:
    sf::Vector2f 			     windowSize;

    sf::Text  				     mText1;
    std::vector<std::array<float, 2>>	customCoords;
    std::vector<sf::CircleShape> selectedPoints;
    sf::RectangleShape           BoundaryBox;
friend class StateMain;

};

