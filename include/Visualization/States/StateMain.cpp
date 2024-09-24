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
, visualizer( )
, tsp(10, 100)
, accumulatedTime(sf::Time::Zero)
, blinkTime(sf::Time::Zero)
, flagBlinkBlurBox(false)
, flagChangeStep(true)
, blurryBox(windowSize)
, classStep1(context)
, classStep2(context)
, classStep3(context)
{		
	visualizer.setTransparency(255);
	stateTime.reset();	

  blurryBox.setFillColor(sf::Color(255, 255, 255, 0)); // 초기 투명도 0


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
			if( classStep1.customCoords.size() > 2 ){
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
				{
					flagBlinkBlurBox      = true;
					flagChangeStep 				= true;
					// classStep2.setCities( classStep1.customCoords,
					// 											classStep1.minXY,
					// 											classStep1.maxXY );
				}
			}
		}
		break;
	case Step2:
		classStep2.handleEvent(event);
		if( classStep2.flagGoNext == true ){
			flagBlinkBlurBox      = true;
			flagChangeStep 				= true;
		}
		break;
	case Step3:
		classStep3.handleEvent(event);
		break;
	default:
		classStep1.handleEvent(event);	
		break;
	}
	return false;
}

// void StateMain::resetTSP(){
// 	// printf("Reset========================\n");
// 	accumulatedTime = sf::Time::Zero;
// 	stateTime.reset();			
// 	tsp.reset(10, 10*10);
// 	setVisualizer();
// }

// void StateMain::proceedTSP(){
// 	tsp.solveOneStep();
// 	if( accumulatedTime >= sf::seconds(0.1f) || tsp.isAnalysisOver()){
// 		accumulatedTime = sf::Time::Zero;
// 		setVisualizer();
// 	}

// 	if( tsp.isAnalysisOver() ){
// 		accumulatedTime = sf::Time::Zero;
// 	}	
// }

// void StateMain::setVisualizer(){
// 	vector<array<float, 2>> coords = tsp.getCoords();
// 	for (auto& element : coords) {
// 			element[0] *= windowSize.x/4;
// 			element[1] *= windowSize.x/4;
// 	}
// 	visualizer.setGeometry(tsp.getBestChromosome(), coords);
// 	visualizer.setPosition(windowSize.x/2, windowSize.y/2);
// }
