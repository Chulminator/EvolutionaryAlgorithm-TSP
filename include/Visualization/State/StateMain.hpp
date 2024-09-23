
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../State.hpp"
#include "../SoundPlayer.hpp"
#include "../MusicPlayer.hpp"

#include "../GUI/Container.hpp"
#include "../../EA/TSP.hpp"
#include "../PauseableClock.hpp"

	enum Step
	{
		Step1 = 0,
		Step2,
		Step3,
		Step4,
		Step5,
		StepCount
	};

class StateMain : public State
{
	public:
							StateMain(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

	private:
		void 						resetTSP();
		void 						proceedTSP();
		void 						setVisualizer();

	private:
    sf::RenderWindow&	 mWindow;
    sf::Vector2f 			 windowSize;
		Step							 step;

		std::vector<std::array<float, 2>>	customCoords;

		MusicPlayer* 			music;
		SoundPlayer&			mSounds;

		GUI::Container		mGUIContainer;
		PauseableClock 		stateTime;
		sf::Time          accumulatedTime;
 
		// tsp
		TSP 							tsp;
		TSPVisualizer 		visualizer;
		bool							evolutionFlag;

		// Step
		bool							  flagChangeStep;
		sf::RectangleShape  blurryBox;


		// step1
		sf::Text  				           mText1;
    std::vector<sf::CircleShape> selectedPoints;
		sf::Vector2f                 minXY;
		sf::Vector2f                 maxXY;
    
};

