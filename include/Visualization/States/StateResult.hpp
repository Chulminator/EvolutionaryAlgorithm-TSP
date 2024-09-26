
#pragma once


// #include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <vector>
#include <algorithm>
#include <cmath>

#include "../State.hpp"
#include "../MusicPlayer.hpp"
#include "../../EA/EAIdentifier.hpp"

using namespace std;

class StateResult : public State
{
	public:
							StateResult(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

		sf::RectangleShape  createLineShape(const sf::Vector2f& start, 
                                        const sf::Vector2f& end, 
                                        float thickness);

		sf::RectangleShape  createLineShape(const sf::Vector2f& start, 
																				const sf::Vector2f& end, 
																				float thickness,
																				sf::Color color);
	private:
    sf::Vector2f 			     windowSize;

		// line 2개 
		vector< array< pair<float, float>, Evolution::TypeCount >> vecMinMax;

		// vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMax;
		// vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMin;
    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> lines;

		sf::Text    mText1;
		sf::Text    mTextYLabel;
		sf::Text    mTextXLabel;
		
		array<sf::Text, Evolution::TypeCount>        mTextLegend;
		array<sf::CircleShape, Evolution::TypeCount> mCircleLegend;
		    
		

		MusicPlayer* music;
};

