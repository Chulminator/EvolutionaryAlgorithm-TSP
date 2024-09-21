
#pragma once

#include "../State.hpp"
#include "../SoundPlayer.hpp"
#include "../MusicPlayer.hpp"

#include "../GUI/Container.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class StateHome : public State
{
	public:
							StateHome(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		MusicPlayer* 			music;
		SoundPlayer&			mSounds;

		GUI::Container		mGUIContainer;
};

