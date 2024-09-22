#include "StateHome.hpp"
#include "../ResourceHolder.hpp"
#include "../GUI/Button.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


StateHome::StateHome(StateStack& stack, Context context)
: State(stack, context)
, mWindow(*context.window)
, windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, music(context.music)
, mSounds(*context.sounds)
, stateTime()
, tsp( 20, 100 )
, visualizer( )
, evolutionFlag( false )
, accumulatedTime(sf::Time::Zero)
{		
	stateTime.reset();	

	sf::FloatRect spriteBounds;
	
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
		
	vector<array<double, 2>> coords = tsp.getCoords();
	for (auto& element : coords) {
			element[0] *= 200;
			element[1] *= 200;
	}
	visualizer.setGeometry(tsp.getBestChromosome(), coords);
	visualizer.setPosition(windowSizeX/2, windowSizeY/2);

}

void StateHome::draw()
{
	sf::RenderWindow& window = *getContext().window;	
	window.clear(sf::Color::White);
	window.draw(visualizer);
	window.draw(mGUIContainer);
}

bool StateHome::update(sf::Time dt)
{	
	sf::Time elapsedTime = stateTime.getElapsedTime();
	accumulatedTime += dt;

	if ( elapsedTime > sf::seconds(3.f) && evolutionFlag == false){
		evolutionFlag = true;
		tsp.solve(); // analysis starts after 1 seconds from Prob gen
		printf("\tAnalysis starts\n");
	}

	if( accumulatedTime >= sf::seconds(1.f) && tsp.isAnalysisOver() ){
		accumulatedTime = sf::Time::Zero;
		vector<array<double, 2>> coords = tsp.getCoords();
		for (auto& element : coords) {
				element[0] *= 200;
				element[1] *= 200;
		}
		visualizer.setGeometry(tsp.getBestChromosome(), coords);
		visualizer.setPosition(windowSize.x/2, windowSize.y/2);
		printf("\tScreen update\n");
	}

	if( tsp.isAnalysisOver() && accumulatedTime >= sf::seconds(3.f)){
		accumulatedTime = sf::Time::Zero;
		printf("\tScreen update\n");
		// evolutionFlag = false;

	}
		

		// stateTime.reset();

	mGUIContainer.update(dt);
	return true;
}

bool StateHome::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}