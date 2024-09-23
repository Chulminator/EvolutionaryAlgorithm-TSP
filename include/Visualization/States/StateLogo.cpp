#include "StateLogo.hpp"
// #include "Utility.hpp"
#include "../ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


StateLogo::StateLogo(StateStack& stack, Context context)
: State(stack, context)
, mLogoTime(sf::Time::Zero)
, mbrightnessTime(sf::Time::Zero)
, brightness()
, mTransparency(200)
, music(context.music)
{	
	music->setVolume(100.);
	mSpriteLogo.setTexture(context.textures->get(Textures::ProfilePhoto));
	
	sf::FloatRect spriteBounds = mSpriteLogo.getLocalBounds();
	sf::Vector2f  windowSize  = static_cast<sf::Vector2f>(context.window->getSize());
	mSpriteLogo.setOrigin(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f);
	mSpriteLogo.setPosition(windowSize.x/2., windowSize.y/2.-windowSize.y/16);

	brightness.setSize(windowSize);
	brightness.setFillColor(sf::Color(0,0,0,mTransparency)); 
	
	music->play(Music::LogoTheme);
	music->setLoop(false);
}

void StateLogo::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.clear(sf::Color::White);
	window.draw( mSpriteLogo );
	window.draw( brightness );
}

bool StateLogo::update(sf::Time dt)
{
	mLogoTime       += dt;
	mbrightnessTime += dt;

	if ( mLogoTime >= sf::seconds(4.0f) ){
		music->stop();
		requestStackPop();
		requestStackPush(States::Home);
	}

	if( mbrightnessTime >= sf::seconds(0.0f) ){
		if( mTransparency > 0 ){
			mTransparency -= 10;
		}
		else{
			mTransparency = 0;
		}
		brightness.setFillColor(sf::Color(0,0,0,mTransparency)); 
	}

	return true;
}

bool StateLogo::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		music->stop();
		requestStackPop();
		requestStackPush(States::Home);
	}

	return true;
}