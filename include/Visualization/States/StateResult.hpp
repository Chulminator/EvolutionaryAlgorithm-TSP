
#pragma once


// #include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <array>
#include <vector>
#include <algorithm>

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


	private:
    sf::Vector2f 			     windowSize;

		// line 2개 
		vector< array< pair<float, float>, Evolution::TypeCount >> vecMinMax;

		vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMax;
		vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMin;
    std::vector<sf::RectangleShape> lines;

		sf::Text    mText1;

		MusicPlayer* music;
};

