
#pragma once

#include "../State.hpp"
#include "../MusicPlayer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class StateLogo : public State
{
	public:
							StateLogo(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::RectangleShape      brightness;
		int                     mTransparency;
		sf::Time 		  					mbrightnessTime;

		sf::Sprite		mSpriteLogo;
		sf::Time 		  mLogoTime;

		MusicPlayer* music;
};

