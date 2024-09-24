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
#include "../GUI/Container.hpp"

using namespace std; // use a namespace

class MainStep3: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    MainStep3(State::Context context);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool		update(sf::Time dt);
    bool		handleEvent(const sf::Event& event);

    void setCities(const std::vector<std::array<float, 2>>& Coords,
                   const sf::Vector2f minXY,
                   const sf::Vector2f maxXY);
                
private:
    sf::Vector2f 			     windowSize;

    sf::Text  				     mText1;
    std::vector<std::array<float, 2>>	customCoords;
    std::vector<sf::CircleShape> points;
    sf::RectangleShape           BoundaryBox;

    
    GUI::Container mGUIContainerButton;
    GUI::Container mGUIContainerLabel;

friend class StateMain;

};

