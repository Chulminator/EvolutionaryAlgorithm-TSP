#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"
#include "ResourceIdentifiers.hpp"
#include "AnalysisInformation.hpp"

#include "StateStack.hpp"

#include "./States/StateIdentifiers.hpp"
#include "./States/StateLogo.hpp"
#include "./States/StateHome.hpp"
#include "./States/StateMain.hpp"
#include "./States/StateResult.hpp"

class Visualization : private sf::NonCopyable
{
	public:
		Visualization();
		void					run();

	private:
		void					processInput();
		void					update(sf::Time elapsedTime);
		void					render();

		sf::ContextSettings createContextSettings();

		void					registerStates();

	private:
		static const sf::Time	TimePerFrame;

		sf::RenderWindow		mWindow;
		TextureHolder				mTextures;
		FontHolder					mFonts;

		MusicPlayer				mMusic;
		SoundPlayer				mSounds;
		StateStack				mStateStack;
		AnalysisInfo      analysisInfo;
};
