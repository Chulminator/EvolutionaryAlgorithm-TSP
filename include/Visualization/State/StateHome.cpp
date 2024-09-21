#include "StateHome.hpp"
#include "../ResourceHolder.hpp"
#include "../GUI/Button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


StateHome::StateHome(StateStack& stack, Context context)
: State(stack, context)
, music(context.music)
, mSounds(*context.sounds)
{		
	sf::FloatRect spriteBounds;
	sf::Vector2f  windowSize  = static_cast<sf::Vector2f>(context.window->getSize());
	double windowSizeX = windowSize.x;
	double windowSizeY = windowSize.y;
	
	
	auto startButton = std::make_shared<GUI::Button>(context);	
	startButton->setText("Start");
	spriteBounds = startButton->getLocalBounds();
	startButton->setOrigin(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);
	startButton->setPosition(windowSizeX*0.5, windowSizeY*0.5-spriteBounds.height);
	startButton->setCallback([this] ()
	{
		requestStateClear();
	});
	
	auto tutorialButton = std::make_shared<GUI::Button>(context);	
	tutorialButton->setText("Tutorial");
	spriteBounds = tutorialButton->getLocalBounds();
	tutorialButton->setOrigin(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);
	tutorialButton->setPosition(windowSizeX*0.5, windowSizeY*0.5);
	tutorialButton->setCallback([this] ()
	{
		requestStateClear();
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setText("Quit");
	spriteBounds = exitButton->getLocalBounds();
	exitButton->setOrigin(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);
	exitButton->setPosition(windowSizeX*0.5, windowSizeY*0.5+spriteBounds.height);
	exitButton->setCallback([this] ()
	{
		requestStateClear();
	});

	mGUIContainer.pack(startButton);
	mGUIContainer.pack(tutorialButton);
	mGUIContainer.pack(exitButton);	
	
	// music->setVolume(100.);
	// music->play(Music::LogoTheme);
	// music->setLoop(true);
}

void StateHome::draw()
{
	sf::RenderWindow& window = *getContext().window;	
	window.clear(sf::Color::White);
	window.draw(mGUIContainer);
}

bool StateHome::update(sf::Time dt)
{
	mGUIContainer.update(dt);
	return true;
}

bool StateHome::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}