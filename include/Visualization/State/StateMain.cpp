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
, evolutionFlag( true )
, tsp(10, 100)
, accumulatedTime(sf::Time::Zero)
, flagChangeStep(false);
, minXY(windowSize)
, maxXY(sf::Vector2f(0,0))
{		
	visualizer.setTransparency(255);
	stateTime.reset();	
	sf::FloatRect spriteBounds;

	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Step 1\n Click to select cities, then press Enter when done");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/10, windowSize.y/10);
	mText1.setFillColor(sf::Color::Black);
}

void StateMain::draw()
{
	sf::RenderWindow& window = *getContext().window;	
	window.clear(sf::Color::White);
	switch (step)
	{
	case Step1:
		window.draw(mText1);		
		for (int ii = 0; ii < selectedPoints.size(); ++ii){        
			window.draw(selectedPoints[ii]);		
		}  
		break;	
	default:
		break;
	}
	// window.draw(visualizer);
	// window.draw(mGUIContainer);
}

bool StateMain::update(sf::Time dt)
{	
	sf::Time elapsedTime = stateTime.getElapsedTime();
	accumulatedTime += dt;

	switch (step)
	{
	case Step1:		
		break;	
	default:
		break;
	}
	// if ( elapsedTime >= sf::seconds(2.f) && evolutionFlag == true){
	// 	// printf("proceedTSP\n");
	// 	proceedTSP();
	// }

	// if( accumulatedTime >= sf::seconds(2.f) && evolutionFlag == false ){
	// 	// printf("resetTSP\n");
	// 	resetTSP();
	// }

	// mGUIContainer.update(dt);
	return true;
}

bool StateMain::handleEvent(const sf::Event& event)
{	
	switch (step)
	{
	case Step1:
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				std::array<float, 2> coord;
				coord[0] = static_cast<float>( event.mouseButton.x );
				coord[1] = static_cast<float>( event.mouseButton.y );
				customCoords.push_back( coord );
				sf::CircleShape circle(5);     	
    		circle.setPosition(sf::Vector2f(coord[0], coord[1])); // 원의 위치 설정
    		circle.setFillColor(sf::Color::Black); // 색상 설정
				selectedPoints.push_back( circle );
				if( minXY.x > coord[0]){
					minXY.x = coord[0];
				}
				if( minXY.y > coord[1]){
					minXY.y = coord[1];
				}
				if( maxXY.x < coord[0]){
					maxXY.x = coord[0];
				}
				if( maxXY.y < coord[1]){
					maxXY.y = coord[1];
				}
			}
		}
		if (event.type == sf::Event::KeyReleased){
			step = Step2;
			flagChangeStep = true;
		}
		break;	
	default:
		break;
	}
	mGUIContainer.handleEvent(event);
	return false;
}

void StateMain::resetTSP(){
	// printf("Reset========================\n");
	accumulatedTime = sf::Time::Zero;
	evolutionFlag = true;
	stateTime.reset();			
	tsp.reset(10, 10*10);
	setVisualizer();
}

void StateMain::proceedTSP(){
	tsp.solveOneStep();
	if( accumulatedTime >= sf::seconds(0.1f) || tsp.isAnalysisOver()){
		accumulatedTime = sf::Time::Zero;
		setVisualizer();
	}

	if( tsp.isAnalysisOver() ){
		evolutionFlag = false;
		accumulatedTime = sf::Time::Zero;
	}	
}

void StateMain::setVisualizer(){
	vector<array<float, 2>> coords = tsp.getCoords();
	for (auto& element : coords) {
			element[0] *= windowSize.x/4;
			element[1] *= windowSize.x/4;
	}
	visualizer.setGeometry(tsp.getBestChromosome(), coords);
	visualizer.setPosition(windowSize.x/2, windowSize.y/2);
}
