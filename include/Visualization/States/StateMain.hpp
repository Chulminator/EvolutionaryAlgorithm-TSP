
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../State.hpp"
#include "../SoundPlayer.hpp"
#include "../MusicPlayer.hpp"

#include "../GUI/Container.hpp"
#include "../../EA/TSP.hpp"
#include "../PauseableClock.hpp"
#include "../Utility.hpp"

#include "../Fragment/MainStep1.hpp"
#include "../Fragment/MainStep2.hpp"
#include "../Fragment/MainStep3.hpp"

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
		void						blinkForNextStep(sf::Time dt);
		void 						resetTSP();
		void 						proceedTSP();
		void 						setVisualizer();

	private:
    sf::RenderWindow&	 mWindow;
    sf::Vector2f 			 windowSize;
		Step							 step;

		MusicPlayer* 			music;
		SoundPlayer&			mSounds;
		
		PauseableClock 		stateTime;
		sf::Time          accumulatedTime;
		 
		// // tsp
		// TSP 							tsp;
		// TSPVisualizer 		visualizer;

		// Step
		MainStep1           classStep1;
		MainStep2           classStep2;
		MainStep3           classStep3;

		bool							  flagChangeStep;
		bool							  flagBlinkBlurBox;
		sf::Time            blinkTime;
		sf::RectangleShape  blurryBox;
		
		// Step1		
};

