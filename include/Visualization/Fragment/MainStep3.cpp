 
#include "MainStep3.hpp"

MainStep3::MainStep3(State::Context context)
: windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, BoundaryBox(sf::Vector2f(windowSize.x*9/10, windowSize.y*3/4))
, nChromosome(0)
, tsp()
, minXY(windowSize)
, maxXY(sf::Vector2f(0,0))
, flagGoNext(false)
, isConverged(false)
, isRunning(false)
, flagPause(false)
, accumulatedTime(sf::Time::Zero)
, analysisInfo( *context.analysisInfo )
, music(context.music)
// , stepTime()
{  
  fileHistory = fopen("./Media/History.txt", "wt");

  distanceHistory.resize(1000, std::numeric_limits<float>::max());

	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Step 3\n Evolution - Press 'Enter' to start");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/20, windowSize.y/20);
	mText1.setFillColor(sf::Color::Black);

  
  mTextRemark.setFont(context.fonts->get(Fonts::Main2));
	mTextRemark.setString("* # indicates the number of chromosomes\t\t** Press 'p' to pause");
	mTextRemark.setCharacterSize(context.window->getSize().x/60); 
	mTextRemark.setPosition(windowSize.x*1/20, windowSize.y*19/20);
	mTextRemark.setFillColor(sf::Color::White);

  BoundaryBox.setPosition(windowSize.x*1/20, windowSize.y*1/5 );
  BoundaryBox.setFillColor(sf::Color(200, 200, 200, 50 )); // 색상 설정
  
  // Boundary Box 
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    BoundaryBoxEvol[ii].setSize( sf::Vector2f(windowSize.x*2/5, windowSize.y*3/10) );
    BoundaryBoxEvol[ii].setFillColor(sf::Color(200, 200, 200, 50 )); // 색상 설정
  }
  BoundaryBoxEvol[Evolution::Crossover].setPosition(windowSize.x*3/40, windowSize.y*1/4);
  BoundaryBoxEvol[Evolution::Mutation].setPosition(windowSize.x*21/40, windowSize.y*1/4);
  BoundaryBoxEvol[Evolution::Elitism].setPosition(windowSize.x*3/40, windowSize.y*5/8);
  BoundaryBoxEvol[Evolution::NewChromosome].setPosition(windowSize.x*21/40, windowSize.y*5/8);

  // Text
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    mTextEvol[ii].setFont(context.fonts->get(Fonts::Main2));
    mTextEvol[ii].setCharacterSize(context.window->getSize().x/35); // 글자 크기 설정 (50 포인트)
    mTextEvol[ii].setFillColor(sf::Color::Black);
  }
  mTextEvol[Evolution::Crossover].setString("Crossover");
  mTextEvol[Evolution::Mutation].setString("Mutation");
  mTextEvol[Evolution::Elitism].setString("Elitism");
  mTextEvol[Evolution::NewChromosome].setString("New Chromosome");

  mTextEvol[Evolution::Crossover].setPosition(windowSize.x*3/40, windowSize.y*1/5);
  mTextEvol[Evolution::Mutation].setPosition(windowSize.x*21/40, windowSize.y*1/5);
  mTextEvol[Evolution::Elitism].setPosition(windowSize.x*3/40, windowSize.y*23/40);
  mTextEvol[Evolution::NewChromosome].setPosition(windowSize.x*21/40, windowSize.y*23/40);

}

void MainStep3::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(mText1, states);  
  target.draw(BoundaryBox, states);    
  
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    target.draw(BoundaryBoxEvol[ii], states);    
  }

	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    target.draw(mTextEvol[ii], states);    
  }

	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    target.draw(mTypeVisualizer[ii], states);    
  }
    target.draw(mTextRemark, states);
  return;
}

bool MainStep3::update(sf::Time dt){
	// sf::Time elapsedTime = stepTime.getElapsedTime();
  if ( flagPause == false){    
    accumulatedTime += dt;
    if( isRunning == true && !isConverged){
      proceedTSP();
    }
  }
  
  return false;
}

bool MainStep3::handleEvent(const sf::Event& event){
  
  if( isRunning && !isConverged ){
    if (event.type == sf::Event::KeyReleased){
      if (event.key.code == sf::Keyboard::P )
      {
        if( flagPause ){
          flagPause = false;
          music->setPaused(false);
        }
        else{
          flagPause = true;
          music->setPaused(true);
        }
      }
    }
  }

  if( !isRunning && !isConverged ){	
		if (event.type == sf::Event::KeyReleased){
      if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
      {
  			music->play( Music::MainStep3 );
        music->setLoop(false);
        isRunning = true;
	      mTextRemark.setFillColor(sf::Color::Black);
      }
		}
  }

  // if (isConverged){
	// 	if (event.type == sf::Event::KeyReleased){
  //     if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
  //     {
  //       analysisInfo.setNChromosome( nChromosome );
  //       analysisInfo.setNCity( nCity );
  //       analysisInfo.setNTypeEvol( nTypeEvol );  
  //       analysisInfo.setNGeneration( tsp.getGeneration() );  
  //       flagGoNext = true;
  //     }
	// 	}
  // }
  return false;
}


void MainStep3::setParameters(const string mStringNChromosome,
                              const array<string, Evolution::TypeCount>& mStringPercent,
                              const std::vector<std::array<float, 2>>& Coords,
                              const sf::Vector2f minXY_,
                              const sf::Vector2f maxXY_){

  nCity = Coords.size();
  minXY = minXY_;
  maxXY = maxXY_;
  orgCoords = Coords;


  nChromosome = stoi(mStringNChromosome);
  int finalSum = 0;
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    double tmp = static_cast<double>( std::stoi(mStringPercent[ii]) * nChromosome);
    tmp /= 100.;
    nTypeEvol[ii] = static_cast<int>(tmp);
    nTypeEvol[ii] = nTypeEvol[ii] == 0 ?  1 : nTypeEvol[ii];
    finalSum += nTypeEvol[ii];
  }
  nTypeEvol[0] += nChromosome - finalSum;  
  // string str = "Crossover - "+  to_string(nTypeEvol[Evolution::Crossover]);
  mTextEvol[Evolution::Crossover].setString("Crossover - #:"+  to_string(nTypeEvol[Evolution::Crossover]));
  mTextEvol[Evolution::Mutation].setString("Mutation - #:"+ to_string(nTypeEvol[Evolution::Mutation]));
  mTextEvol[Evolution::Elitism].setString("Elitism - #:"+ to_string(nTypeEvol[Evolution::Elitism]));
  mTextEvol[Evolution::NewChromosome].setString("New Chromosome - #:"+ to_string(nTypeEvol[Evolution::NewChromosome]));

  tsp.reset( nCity, nChromosome, orgCoords, nTypeEvol);
  setLocalCities();
  setChromosomes();
  // stepTime.reset();

  return;                               
}

void MainStep3::setLocalCities(  ){ 
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    float padding = BoundaryBox.getSize().x / 40; // boxSize/20
    sf::Vector2f adjustedMinXY = {minXY.x - padding, minXY.y - padding};
    sf::Vector2f adjustedMaxXY = {maxXY.x + padding, maxXY.y + padding};

    std::vector<std::array<float, 2>>	localCoords;
    for (const auto& coord : orgCoords) {
      std::array<float, 2> newCoord;
      newCoord[0] = (coord[0] - adjustedMinXY.x) * (BoundaryBoxEvol[ii].getSize().x / (adjustedMaxXY.x - adjustedMinXY.x));
      newCoord[1] = (coord[1] - adjustedMinXY.y) * (BoundaryBoxEvol[ii].getSize().y / (adjustedMaxXY.y - adjustedMinXY.y));
      
      // BoundaryBox의 원점에 맞춰 위치 조정
      newCoord[0] += BoundaryBoxEvol[ii].getPosition().x;
      newCoord[1] += BoundaryBoxEvol[ii].getPosition().y;
      localCoords.push_back(newCoord);
    }
    mTypeVisualizer[ii].setCities( localCoords );
  }
  return;
}

void MainStep3::setChromosomes(Evolution::Type type){
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    
    if( type == ii ){
      mTypeVisualizer[ii].setChromosome( tsp.getBestTypeChromosome()[ii], sf::Color::Blue );
    }
    else{
      mTypeVisualizer[ii].setChromosome( tsp.getBestTypeChromosome()[ii], sf::Color::Red );
    }
  }  
}


void MainStep3::setChromosomes(){
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
    mTypeVisualizer[ii].setChromosome( tsp.getBestTypeChromosome()[ii] );
  }  
}


void MainStep3::proceedTSP(){
	tsp.solveOneStep();
  float distancePrev = distanceHistory.front();
  distanceHistory.pop_front();
  auto bestDist =  tsp.getBestDistance();
  distanceHistory.push_back( bestDist.first );

  vector<float> distance = tsp.getDistance();
  for ( int ii = 0; ii < distance.size(); ++ii ){
    fprintf(fileHistory, "%f ", distance[ii]);
  }
  fprintf(fileHistory, "\n");
  fflush(fileHistory); 
  if( distanceHistory.back() == distancePrev ){
    fclose(fileHistory);
    mText1.setString("Step 3: Converged! Press 'Enter' for the next\nCurrent Generation: " + to_string(tsp.getGeneration()));
    isConverged = true;
    isRunning   = false;
    
    analysisInfo.setNChromosome( nChromosome );
    analysisInfo.setNCity( nCity );
    analysisInfo.setNTypeEvol( nTypeEvol );  
    analysisInfo.setNGeneration( tsp.getGeneration() );  
    flagGoNext = true;
  }

// 	// printf("\tAnalysis ing\n");		
	if( accumulatedTime >= sf::seconds(0.1f) && !isConverged){
		accumulatedTime = sf::Time::Zero;    
    // setChromosomes(bestDist.second);    
    setChromosomes();    
    mText1.setString("Step 3: Optimal Routes from Genetic Pools\nCurrent Generation: " + to_string(tsp.getGeneration()));
	}

}

