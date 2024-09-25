#include "StateResult.hpp"
#include "../ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


StateResult::StateResult(StateStack& stack, Context context)
: State(stack, context)
, windowSize( static_cast<sf::Vector2f>(context.window->getSize()) )
, music(context.music)
{	
	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Result - Click the 'X' in the upper-right corner to finish");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/20, windowSize.y/20);
	mText1.setFillColor(sf::Color::Black);
	
  auto typeEvol = context.analysisInfo->getNTypeEvol();

	vecMinMax.clear();
	FILE *fileHistory;
  fileHistory = fopen("./Media/History.txt", "r");
	for ( int ii = 0; ii < context.analysisInfo->getNGeneration(); ++ii ){
		vector<float> vecDistance(context.analysisInfo->getNChromosome());
		for ( int jj = 0; jj < context.analysisInfo->getNChromosome(); ++jj ){
			fscanf(fileHistory, "%f ", &vecDistance[jj]);
		}
		fscanf(fileHistory, "\n ");

    auto minElitism      = std::min_element(vecDistance.begin(), vecDistance.begin() + typeEvol[ Evolution::Elitism ] - 1);
    auto minCrossOver    = std::min_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ], vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] - 1);
    auto minMutation     = std::min_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ], vecDistance.begin()+ typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] + typeEvol[ Evolution::Mutation ]  - 1);
    auto minNewCromosome = std::min_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] + typeEvol[ Evolution::Mutation ] , vecDistance.end() - 1);

    auto maxElitism      = std::max_element(vecDistance.begin(), vecDistance.begin() + typeEvol[ Evolution::Elitism ] - 1);
    auto maxCrossOver    = std::max_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ], vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] - 1);
    auto maxMutation     = std::max_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ], vecDistance.begin()+ typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] + typeEvol[ Evolution::Mutation ]  - 1);
    auto maxNewCromosome = std::max_element(vecDistance.begin() + typeEvol[ Evolution::Elitism ] + typeEvol[ Evolution::Crossover ] + typeEvol[ Evolution::Mutation ] , vecDistance.end() - 1);

		// printf("%f %f %f %f\n", *minElitism, *minCrossOver, *minMutation, *minNewCromosome);
		// printf("%f %f %f %f--\n", *maxElitism, *maxCrossOver, *maxMutation, *maxMutation);
		array< pair<float, float>, Evolution::TypeCount > tmp;
		
    tmp[Evolution::Elitism]   = std::make_pair(*minElitism, *maxElitism);
    tmp[Evolution::Crossover] = std::make_pair(*minCrossOver, *maxCrossOver);
    tmp[Evolution::Mutation]  = std::make_pair(*minMutation, *maxMutation);
    tmp[Evolution::TypeCount] = std::make_pair(*minNewCromosome, *maxNewCromosome);
		vecMinMax.push_back(tmp);
	}





}

void StateResult::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.clear(sf::Color::White);
	window.draw( mText1 );
}

bool StateResult::update(sf::Time dt)
{
	return true;
}

bool StateResult::handleEvent(const sf::Event& event)
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
