#pragma once

// #include <GraphMaster.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <cmath>
#include <random>

using namespace std; // use a namespace

class TSPVisualizer: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    TSPVisualizer();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // void setGeometry(const vector<int>& vecNewChromosome,
    //                  const vector<array<float, 2>>& coords);
                     
    void setCities( const vector<array<float, 2>>& coords_);
                     
    void setChromosome(const vector<int>& vecChromosome);
                     
    void setTransparency(const int transparency_);

    sf::RectangleShape createLineShape(const sf::Vector2f& start, 
                                       const sf::Vector2f& end, 
                                       float thickness);

private:
    int transparency;
    vector<array<float, 2>> coords;
    std::vector<sf::CircleShape> points;
    std::vector<sf::RectangleShape> lines;
    // // // // // // //     
    std::vector<sf::Text>        mTextsAtPoints;
    sf::Font font;
    // // // // // // //     
};

