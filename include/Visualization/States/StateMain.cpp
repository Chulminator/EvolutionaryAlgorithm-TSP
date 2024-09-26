#include "StateMain.hpp"
#include "../ResourceHolder.hpp"
#include "../GUI/Button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

StateMain::StateMain(StateStack& stack, Context context)
: State(stack, context)
, mWindow(*context.window)
, windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, step(Step1)
, music(context.music)
, mSounds(*context.sounds)
, stateTime()
, accumulatedTime(sf::Time::Zero)
, blinkTime(sf::Time::Zero)
, flagBlinkBlurBox(false)
, flagChangeStep(true)
, blurryBox(windowSize)
, classStep1(context)
, classStep2(context)
, classStep3(context)
{		
	music->play( Music::MainStep1 );
	music->setLoop(false);

	stateTime.reset();	

  blurryBox.setFillColor(sf::Color(255, 255, 255, 0)); // 초기 투명도 0

	auto startButton = std::make_shared<GUI::Button>(context);	
	startButton->setCallback([this] ()
	{
		music->stop();
		requestStackPop();
		requestStackPush(States::Result);
	});	
	mGUIContainer.pack( startButton );

}

void StateMain::blinkForNextStep(sf::Time dt){
	if (flagBlinkBlurBox) {
		blinkTime += dt;
    float alpha = 0;
		if (blinkTime < sf::seconds(0.3f) ) {
			alpha = 255. * (blinkTime.asSeconds() / 0.3f);
		}
		else if (blinkTime < sf::seconds(0.4f)) {
			alpha = 255.;
			if( flagChangeStep ){
        step = static_cast<Step>(static_cast<int>(step) + 1);
				if ( step == StepCount){
					step = static_cast<Step>(static_cast<int>(step) - 1);
				};
				flagChangeStep = false;
			}
		}
		else if (blinkTime < sf::seconds(0.7f)) {
			alpha = 255 * (1 - (blinkTime.asSeconds() - 0.4f) / 0.3f);
		} else {
			flagBlinkBlurBox = false; 
			blinkTime = sf::Time::Zero;
		}
		blurryBox.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		
	}
}

void StateMain::draw()
{
	sf::RenderWindow& window = *getContext().window;	
	window.clear(sf::Color::White);
	switch (step)
	{
	case Step1:
		window.draw(classStep1);
		break;	
	case Step2:
		window.draw(classStep2);
		break;	
	case Step3:
		window.draw(classStep3);
		break;	
	default:
		window.draw(classStep1);
		break;
	}

	if (flagBlinkBlurBox){
		window.draw( blurryBox );;
	}
	
}

bool StateMain::update(sf::Time dt)
{	
	sf::Time elapsedTime = stateTime.getElapsedTime();
	accumulatedTime += dt;

	switch (step)
	{
	case Step1:	
		classStep1.update(dt);
		break;	
	case Step2:		
		classStep2.update(dt);
		break;
	case Step3:		
		classStep3.update(dt);
		break;	
	default:
		classStep1.update(dt);
		break;
	}

	blinkForNextStep(dt);
	return true;
}

bool StateMain::handleEvent(const sf::Event& event)
{	
	switch (step)
	{
	case Step1:
		classStep1.handleEvent(event);		
		if (event.type == sf::Event::KeyReleased){
			if( classStep1.customCoords.size() > 4 ){
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
				{
					flagBlinkBlurBox      = true;
					flagChangeStep 				= true;
					classStep2.setNCity ( classStep1.customCoords.size() );
				}
			}
		}
		break;
	case Step2:
		classStep2.handleEvent(event);
		if( classStep2.flagGoNext == true ){
			flagBlinkBlurBox      = true;
			flagChangeStep 				= true;
			classStep3.setParameters( classStep2.mStringNChromosome,
															  classStep2.mStringPercent,
																classStep1.customCoords,
																classStep1.minXY,
																classStep1.maxXY);
																
			music->stop();
		}
		break;
	case Step3:
		classStep3.handleEvent(event);
		if( classStep3.flagGoNext == true ){
			mGUIContainer.handleEvent(event);
		}
		break;
	default:
		classStep1.handleEvent(event);	
		break;
	}
	return false;
}
