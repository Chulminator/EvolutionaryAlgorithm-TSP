#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <stack>
#include <numeric> // std::accumulate
#include <cmath>   // std::round


#include "../SoundPlayer.hpp"
#include "../State.hpp"
#include "../ResourceHolder.hpp"
#include "../GUI/Container.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Label.hpp"
#include "../../EA/EAIdentifier.hpp"
#include "../BlinkEntity.hpp"

using namespace std; // use a namespace

class MainStep2: public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public: 
    MainStep2(State::Context context);

    void    draw(sf::RenderTarget& target, sf::RenderStates states) const;
    bool	update(sf::Time dt);
    bool	handleEvent(const sf::Event& event);

    void 	setNCity(const int nCity_);

private:
    void 	blinkActivated(sf::Time dt);
    void	addButtonLabel(Evolution::Type type, float y, const std::string& text, State::Context context);
    void    updateLabels();

    bool 	checkParameters();
                
private:
    SoundPlayer&			mSounds;

    int                     nCity;
    sf::Text                mTextStep2;
    BlinkEntity<sf::Text>	blinkTextStep2;

    sf::Vector2f 			windowSize;

    sf::Text  				mText1;
    sf::Time                mblinkTime;
    
    bool                    isSumCent;
    bool                    hasZero;
    bool                    hasEnoghChromosome;
    bool                    flagGoNext;
    
    GUI::Button::Ptr        NChromosomeButton;
    GUI::Label::Ptr         NChromosomeLabel;
    std::string             mStringNChromosome;

    GUI::Container mGUIContainerButton;
    GUI::Container mGUIContainerLabel;
    std::array<GUI::Button::Ptr, Evolution::Type::TypeCount>	mBindingButtons;
    std::array<GUI::Label::Ptr, Evolution::Type::TypeCount> 	mBindingLabels;
    std::array<std::string, Evolution::Type::TypeCount>         mStringPercent;

friend class StateMain;
};

