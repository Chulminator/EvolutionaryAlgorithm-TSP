#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

// #include "CommandQueue.hpp"

#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"
#include "ResourceIdentifiers.hpp"

#include "StateStack.hpp"

#include "./State/StateIdentifiers.hpp"
#include "./State/StateLogo.hpp"
#include "./State/StateHome.hpp"
#include "./State/StateMain.hpp"

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
};
