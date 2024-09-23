
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../State.hpp"
#include "../SoundPlayer.hpp"
#include "../MusicPlayer.hpp"

#include "../GUI/Container.hpp"
#include "../../EA/TSP.hpp"
#include "../PauseableClock.hpp"


class StateHome : public State
{
	public:
							StateHome(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		void 						resetTSP();
		void 						proceedTSP();

	private:
    sf::RenderWindow&	 mWindow;
    sf::Vector2f 			 windowSize;

		MusicPlayer* 			music;
		SoundPlayer&			mSounds;

		GUI::Container		mGUIContainer;
		PauseableClock 		stateTime;
		sf::Time          accumulatedTime;
 
		// tsp
		TSP 							tsp;
		TSPVisualizer 		visualizer;
		bool							evolutionFlag;

		// tsp
};

