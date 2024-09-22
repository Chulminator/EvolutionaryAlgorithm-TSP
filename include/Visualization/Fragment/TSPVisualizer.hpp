#pragma once

// #include <GraphMaster.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>

using namespace std; // use a namespace

class TSPVisualizer: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    TSPVisualizer();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setGeometry(const vector<int>& vecNewChromosome,
                     const vector<array<double, 2>>& coords);

                         
private:
    std::vector<sf::CircleShape> points;
    sf::VertexArray lines;
};

