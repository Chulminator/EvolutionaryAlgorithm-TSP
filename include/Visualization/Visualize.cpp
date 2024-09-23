#include "Visualize.hpp"

const sf::Time Visualization::TimePerFrame = sf::seconds(1.f/60.f);

Visualization::Visualization()
// : mWindow(sf::VideoMode(800, 600), "Evolutionary algorithm", sf::Style::Close | sf::Style::Resize, createContextSettings())
// : mWindow(sf::VideoMode(1200, 900), "Evolutionary algorithm", sf::Style::Close, createContextSettings())
: mWindow(sf::VideoMode(1200, 900), "Evolutionary algorithm", sf::Style::Close | sf::Style::Resize, createContextSettings())
, mTextures()
, mFonts()
, mMusic()
, mSounds()
, mStateStack(State::Context(mWindow, 
														mTextures,
														mFonts, 
														mMusic, 
														mSounds))
{
	mWindow.setKeyRepeatEnabled(false);
	mWindow.setVerticalSyncEnabled(true);
 	// Font load
	mFonts.load(Fonts::Main, 	"Media/Sansation.ttf");
	mFonts.load(Fonts::Main2, 	"Media/times.ttf");
	// Textures load
	mTextures.load(Textures::ProfilePhoto, "Media/Textures/ProfilePhoto.png");	
	registerStates();	
	// mStateStack.pushState(States::Home);
	mStateStack.pushState(States::Logo);
	mMusic.setVolume(25.f);
}

void Visualization::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();
			update(TimePerFrame);
			// Check inside this loop, because stack might be empty before update() call
			if (mStateStack.isEmpty())
				mWindow.close();
		}
		render();
	}
}

void Visualization::processInput()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Visualization::update(sf::Time elapsedTime)
{
	mStateStack.update(elapsedTime);
}

void Visualization::render()
{
	// window.clear(sf::Color::White);
	mWindow.clear();	
	mStateStack.draw();
	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void Visualization::registerStates()
{
	mStateStack.registerState<StateLogo>(States::Logo);
	mStateStack.registerState<StateHome>(States::Home);
	mStateStack.registerState<StateMain>(States::Main);
}

sf::ContextSettings Visualization::createContextSettings() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Set the level of anti-aliasing
    return settings;
}
