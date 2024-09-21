#include "Button.hpp"
#include "../Utility.hpp"
#include "../SoundPlayer.hpp"
#include "../ResourceHolder.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(State::Context context)
: mCallback()
// , mSprite(context.textures->get(Textures::Buttons))
, mBox(sf::Vector2f(100, 50))
, mText("", context.fonts->get(Fonts::Main), 35)
, mIsToggle(false)
, mSounds(*context.sounds)
, mIsSelectable(true)
{
	changeTexture(Normal);
	sf::FloatRect bounds = mBox.getLocalBounds();
	mBox.setFillColor(sf::Color(0,0,0,0));
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mBox.setSize(sf::Vector2f(text.length()*20., 50.));
	mText.setString(text);
	centerOrigin(mText);
	mText.setPosition(text.length()*10., 25.);
	mText.setFillColor(sf::Color::Black);

	// mText.setPosition(mBox.getPosition());
	// printf("%e\t%e\n",mBox.getPosition().x, mBox.getPosition().y);
	// printf("%e\t%e\n",mText.getOrigin().x, mText.getOrigin().y);
	// printf("%e\t%e\n",mBox.getOrigin().x, mBox.getOrigin().y);
	// printf("=================\n");
	// sf::FloatRect bounds = mBox.getLocalBounds();
	// mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setTextPosition(const sf::Vector2f &position)
{
	mText.setPosition(position);
}

void Button::setTextPosition(float x, float y){
	mText.setPosition(x, y);
}

void Button::setToggle(bool flag)
{
	mIsToggle = flag;
}

void Button::ChangeSelectability(){
	if (mIsSelectable){
		mIsSelectable = false;
		deselect();
	}
	else{
		mIsSelectable = true;
	}
}

bool Button::isSelectable() const
{
    return mIsSelectable;
}

void Button::select()
{
	Component::select();

	changeTexture(Selected);
}

void Button::deselect()
{
	Component::deselect();
	changeTexture(Normal);
}

void Button::activate()
{
	Component::activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
	if (mIsToggle){
		mSounds.play(SoundEffect::Click);
		changeTexture(Pressed);
	}

	if (mCallback){
		// mSounds.play(SoundEffect::Combo2);
		mSounds.play(SoundEffect::Button);
		mCallback();
	}

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
	if (!mIsToggle){
		deactivate();
	}
	// mSounds.play(SoundEffect::Button);
}

void Button::deactivate()
{
	Component::deactivate();

	if (mIsToggle)
	{
    // Reset texture to right one depending on if we are selected or not.
		if (isSelected()){
			changeTexture(Selected);
		}
		else{
			changeTexture(Normal);
		}
	}
}

void Button::handleEvent(const sf::Event&)
{
}

bool Button::update(sf::Time dt)
{
	return false;
}

sf::FloatRect	Button::getLocalBounds(){
	return mBox.getLocalBounds();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	// target.draw(mSprite, states);
	target.draw(mBox, states);
	target.draw(mText, states);
}

void Button::changeTexture(Type buttonType){
	if ( buttonType == Type::Normal ) {
		// mBox.setFillColor(sf::Color::Blue);
		// mBox.setFillColor(sf::Color(255,255,255));
		mBox.setFillColor(sf::Color(0,0,0,0));
		mText.setStyle(sf::Text::Regular); 
	}
	else if ( buttonType == Type::Selected ) {
		mBox.setFillColor(sf::Color(0,0,0,0));
		// mBox.setFillColor(sf::Color(255,255,255));		
		mText.setStyle(sf::Text::Bold); 
		
	}
	else if ( buttonType == Type::Pressed ) {
		// mBox.setFillColor(sf::Color::Red);
		mBox.setFillColor(sf::Color(0,0,0,0));
		// mBox.setFillColor(sf::Color(255,255,255));
		mText.setStyle(sf::Text::Bold); 
	}
}
}
