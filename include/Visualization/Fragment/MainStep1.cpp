 
#include "MainStep1.hpp"

MainStep1::MainStep1(State::Context context)
: windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, minXY(windowSize)
, maxXY(sf::Vector2f(0,0))
, blinkTextStep1()
{

	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Step 1\n Click to select cities, then press 'Enter' when done");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/20, windowSize.y/20);
	mText1.setFillColor(sf::Color::Black);
  
	// step1
	// sf::Text mTextStep1;
	mTextStep1.setFont(context.fonts->get(Fonts::Main2));
	mTextStep1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mTextStep1.setString("Click more than five cities");
  mTextStep1.setOrigin(mTextStep1.getLocalBounds().width / 2, 
											 mTextStep1.getLocalBounds().height / 2);
	mTextStep1.setPosition(windowSize.x/2, windowSize.y/2);
	mTextStep1.setFillColor(sf::Color::Black); // 초기 투명도 0
	blinkTextStep1.setEntity(mTextStep1);
}

bool MainStep1::update(sf::Time dt){
  blinkTextStep1.update(dt);
  return false;
}

bool MainStep1::handleEvent(const sf::Event& event){
  
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

  
  if( customCoords.size() <= 2 ){
    if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
    {
      blinkTextStep1.startBlink();
    }
  }
  return false;
}


void MainStep1::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(mText1, states);  
  for (int ii = 0; ii < selectedPoints.size(); ++ii){            
    target.draw(selectedPoints[ii], states);  
  }    
  
  target.draw(blinkTextStep1);	
  return;
}
