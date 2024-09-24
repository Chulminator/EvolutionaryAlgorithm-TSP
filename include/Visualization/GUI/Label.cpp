#include "Label.hpp"
#include "../Utility.hpp"
#include <iostream>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <cmath>


namespace GUI
{

Label::Label(const std::string& text, const FontHolder& fonts)
: mText(text, fonts.get(Fonts::Main2), 35)
, colorAlpha(255)
, dAlpha(20)
{
	mText.setFillColor(sf::Color::Black);
}

bool Label::isSelectable() const
{
    return false;
}

void Label::handleEvent(const sf::Event&)
{
}

bool Label::update(sf::Time dt)
{
	return false;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Label::blink()
{	
	const sf::Color textColor = mText.getFillColor();	
	if( colorAlpha > 0 || colorAlpha < 256 ){
		colorAlpha -= dAlpha;
	}
	if ( colorAlpha <= 0 ){
		colorAlpha = 0;
		dAlpha *= -1;
	}
	if ( colorAlpha >= 256 ){
		colorAlpha = 255;
		dAlpha *= -1;
	}
	
	mText.setFillColor (sf::Color(textColor.r, textColor.g, textColor.b, colorAlpha));	
}

void Label::stopBlink()
{		
	const sf::Color textColor = mText.getFillColor();	
	mText.setFillColor (sf::Color(textColor.r, textColor.g, textColor.b));	
	// mText.setFillColor (sf::Color(textColor.r, textColor.g, textColor.b, 0));	
}

sf::FloatRect Label::getLocalBounds() const
{		
	return mText.getLocalBounds();
}

void Label::setCharacterSize(int fontSize)
{		
	// if (fontSize <= 0){
	// 	assert();
	// }
	// else{
	mText.setCharacterSize(fontSize);	
	centerOrigin(mText);
	// }
// }

// void Label::setAlignment( const Align align_ ) {
// 	align = align_;
// }

}
}