#include "StateResult.hpp"
#include "../ResourceHolder.hpp"

#include <SFML/Graphics/RenderWindow.hpp>


StateResult::StateResult(StateStack& stack, Context context)
: State(stack, context)
, windowSize( static_cast<sf::Vector2f>(context.window->getSize()) )
, music(context.music)
{	
	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Result - Press 'r' to restart");
	mText1.setCharacterSize(windowSize.x/30); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/20, windowSize.y/20);
	mText1.setFillColor(sf::Color::Black);
		
	mTextXLabel.setFont(context.fonts->get(Fonts::Main2));
	mTextXLabel.setString("Generation");
	mTextXLabel.setCharacterSize(windowSize.x/25); // 글자 크기 설정 (50 포인트)
	mTextXLabel.setPosition(windowSize.x*9/20, windowSize.y*17/20);
	mTextXLabel.setFillColor(sf::Color::Black);

	mTextYLabel.setFont(context.fonts->get(Fonts::Main2));
	mTextYLabel.setString("Fitness");
	mTextYLabel.setCharacterSize(windowSize.x/30); // 글자 크기 설정 (50 포인트)
	mTextYLabel.setPosition(windowSize.x*5/80, windowSize.y*12/20);
	mTextYLabel.setFillColor(sf::Color::Black);
  mTextYLabel.setRotation(-90);


  auto typeEvol = context.analysisInfo->getNTypeEvol();

	vecMinMax.clear();
	FILE *fileHistory;
  fileHistory = fopen("./Media/History.txt", "r");

	float minDistance = std::numeric_limits<float>::max();
	float maxDistance = std::numeric_limits<float>::lowest();

	int nGen = context.analysisInfo->getNGeneration();
	for ( int ii = 0; ii < nGen; ++ii ){
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
    tmp[Evolution::NewChromosome] = std::make_pair(*minNewCromosome, *maxNewCromosome);
		vecMinMax.push_back(tmp);

    minDistance = std::min(minDistance, vecMinMax[ii][Evolution::Elitism].first);
    minDistance = std::min(minDistance, vecMinMax[ii][Evolution::Crossover].first);
    minDistance = std::min(minDistance, vecMinMax[ii][Evolution::Mutation].first);
    minDistance = std::min(minDistance, vecMinMax[ii][Evolution::NewChromosome].first);
    
    // Check the maximum values across all types of evolution
    maxDistance = std::max(maxDistance, vecMinMax[ii][Evolution::Elitism].second);
    maxDistance = std::max(maxDistance, vecMinMax[ii][Evolution::Crossover].second);
    maxDistance = std::max(maxDistance, vecMinMax[ii][Evolution::Mutation].second);
    maxDistance = std::max(maxDistance, vecMinMax[ii][Evolution::NewChromosome].second);
	}

	sf::Vector2f 	origin    = {windowSize.x*2/20,  windowSize.y*17/20  };
	sf::Vector2f 	xAxisMax  = {windowSize.x*18/20, windowSize.y*17/20  }; 
	sf::Vector2f 	yAxisMax  = {windowSize.x*2/20,  windowSize.y*1/5  };
	sf::Vector2f 	xAxisMin  = {windowSize.x*1/20, windowSize.y*17/20  }; 
	sf::Vector2f 	yAxisMin  = {windowSize.x*2/20,  windowSize.y*18/20  };

	minDistance *= 0.5f;
	// maxDistance *= 1.1f;
	// maxDistance *= 1.1f;


	lines.push_back( createLineShape(xAxisMin,
														 xAxisMax,
														 3.) );
															
	lines.push_back( createLineShape(yAxisMin,
														 yAxisMax,
														 3.) );

	circles.clear();

	for (int ii = 1; ii < nGen; ++ii) {

		float xOffset = origin.x + ii * ((windowSize.x*15./20.)/static_cast<float>( nGen ));
		
		// // Normalizing ii to a logarithmic scale between 1 and nGen
		// float logMin = log(1)+ 1;            // log(1) is 0, so this is our starting point
		// float logMax = log(nGen);          // log of the maximum generation

		// // Compute the logarithmic value for the current ii
		// float logValue = log(static_cast<float>(ii));

		// // Normalize the logValue to be between 0 and 1
		// float normalizedLog = (logValue - logMin) / (logMax - logMin);

		// // Map normalizedLog to the desired range on the X-axis
		// float xOffset = origin.x + normalizedLog * (3.0 / 4.0 * windowSize.x);

		// 각 진화 유형의 최소 및 최대 원 그리기
		// New Chromosome
		float minYNewChromosome = origin.y - (vecMinMax[ii][Evolution::NewChromosome].first - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		float maxYNewChromosome = origin.y - (vecMinMax[ii][Evolution::NewChromosome].second - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		sf::CircleShape circleMinNewChromosome(2);
		circleMinNewChromosome.setPosition(xOffset, minYNewChromosome);
		circleMinNewChromosome.setFillColor(sf::Color::Green);
		circles.push_back(circleMinNewChromosome);

		sf::CircleShape circleMaxNewChromosome(2);
		circleMaxNewChromosome.setPosition(xOffset, maxYNewChromosome);
    circleMaxNewChromosome.setOutlineColor(sf::Color::Green);
    circleMaxNewChromosome.setOutlineThickness(1); 
    circleMaxNewChromosome.setFillColor(sf::Color::Transparent);
		circles.push_back(circleMaxNewChromosome);

		// Mutation
		float minYMutation = origin.y - (vecMinMax[ii][Evolution::Mutation].first - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		float maxYMutation = origin.y - (vecMinMax[ii][Evolution::Mutation].second - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		sf::CircleShape circleMinMutation(2);
		circleMinMutation.setPosition(xOffset, minYMutation);
		circleMinMutation.setFillColor(sf::Color::Blue);
		circles.push_back(circleMinMutation);

		sf::CircleShape circleMaxMutation(2);
		circleMaxMutation.setPosition(xOffset, maxYMutation);
    circleMaxMutation.setOutlineColor(sf::Color::Blue);
    circleMaxMutation.setOutlineThickness(1); 
    circleMaxMutation.setFillColor(sf::Color::Transparent);
		circles.push_back(circleMaxMutation);

		// Crossover
		float minYCrossover = origin.y - (vecMinMax[ii][Evolution::Crossover].first - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		float maxYCrossover = origin.y - (vecMinMax[ii][Evolution::Crossover].second - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		sf::CircleShape circleMinCrossover(2);
		circleMinCrossover.setPosition(xOffset, minYCrossover);
		circleMinCrossover.setFillColor(sf::Color::Red);
		circles.push_back(circleMinCrossover);

		sf::CircleShape circleMaxCrossover(2);
		circleMaxCrossover.setPosition(xOffset, maxYCrossover);
    circleMaxCrossover.setOutlineColor(sf::Color::Red);
    circleMaxCrossover.setOutlineThickness(1); 
    circleMaxCrossover.setFillColor(sf::Color::Transparent);
		circles.push_back(circleMaxCrossover);
		
		// Elitism
		float minYElitism = origin.y - (vecMinMax[ii][Evolution::Elitism].first - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		float maxYElitism = origin.y - (vecMinMax[ii][Evolution::Elitism].second - maxDistance)/(minDistance-maxDistance)*(3./4.*windowSize.y);
		sf::CircleShape circleMinElitism(2);
		circleMinElitism.setPosition(xOffset, minYElitism);
		circleMinElitism.setFillColor(sf::Color::Magenta);
		circles.push_back(circleMinElitism);
		
		sf::CircleShape circleMaxElitism(2);
		circleMaxElitism.setPosition(xOffset, maxYElitism);
    circleMaxElitism.setOutlineColor(sf::Color::Magenta);
    circleMaxElitism.setOutlineThickness(1); 
    circleMaxElitism.setFillColor(sf::Color::Transparent);
		circles.push_back(circleMaxElitism);
	}

	// vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMax;
	// vector<array< sf::CircleShape, Evolution::TypeCount>> chromosomesMin;
	// for ( int ii = 0; ii < context.analysisInfo->getNGeneration(); ++ii ){
	// 	array< sf::CircleShape, Evolution::TypeCount> cirleMax;
	// 	array< sf::CircleShape, Evolution::TypeCount> cirleMin; 설정 
  //   circle.setPosition(sf::Vector2f(coords[ii][0], coords[ii][1])); // 원의 위치 설정
	// 	cirleMax[Evolution::Crossover]		 = circle.setFillColor(sf::Color::Red); // 색상 설정
	// 	cirleMax[Evolution::Elitism]			 = circle.setFillColor(sf::Color::Magenta); // 색상 설정
	// 	cirleMax[Evolution::Mutation]			 = circle.setFillColor(sf::Color::Blue); // 색상 설정
	// 	cirleMax[Evolution::NewChromosome] = circle.setFillColor(sf::Color::Green); // 색상
    
  //   chromosomesMax.push_back(cirleMax); // 벡터에 추가
	// }
}

void StateResult::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.clear(sf::Color::White);
	window.draw( mText1 );

  for (int ii = 0; ii < lines.size(); ++ii){    
	  window.draw(lines[ii]); 
  }

  for (int ii = 0; ii < circles.size(); ++ii){        
	  window.draw(circles[ii]);
  }  

	window.draw( mTextXLabel );
	window.draw( mTextYLabel );
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
		if ( event.key.code == sf::Keyboard::R )
		{
			// music->stop();
			requestStackPop();
			requestStackPush(States::Home);
		}
	}

	return true;
}




sf::RectangleShape StateResult::createLineShape(const sf::Vector2f& start, 
                                                const sf::Vector2f& end, 
                                                float thickness) 
{
    // 라인의 길이와 각도 계산
    float length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
    float angle = std::atan2(end.y - start.y, end.x - start.x) * 180 / 3.14159; // 라인의 각도 (도 단위)

    // 직사각형 생성
    sf::RectangleShape line(sf::Vector2f(length, thickness));
    line.setPosition(start);
    line.setOrigin(0, thickness / 2); // 중심을 직사각형의 중간으로 설정
    line.setRotation(angle); // 각도에 따라 회전
    line.setFillColor(sf::Color::Black); // 색상 설정

    line.move(thickness*1.5, thickness*1.5);

    return line; // 생성한 직사각형 반환
}

sf::RectangleShape StateResult::createLineShape(const sf::Vector2f& start, 
                                                const sf::Vector2f& end, 
                                                float thickness,
																								sf::Color color) 
{
    // 라인의 길이와 각도 계산
    float length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));
    float angle = std::atan2(end.y - start.y, end.x - start.x) * 180 / 3.14159; // 라인의 각도 (도 단위)

    // 직사각형 생성
    sf::RectangleShape line(sf::Vector2f(length, thickness));
    line.setPosition(start);
    line.setOrigin(0, thickness / 2); // 중심을 직사각형의 중간으로 설정
    line.setRotation(angle); // 각도에 따라 회전
    line.setFillColor(color); // 색상 설정

    line.move(thickness*1.5, thickness*1.5);

    return line; // 생성한 직사각형 반환
}