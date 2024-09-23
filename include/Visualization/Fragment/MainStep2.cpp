 
#include "MainStep2.hpp"

MainStep2::MainStep2(State::Context context)
: windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, minXY(windowSize)
, maxXY(sf::Vector2f(0,0))
, BoundaryBox(sf::Vector2f(windowSize.x*2/3, windowSize.y*2/3))
{
	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Step 2\n Set the parameters for the evolution");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/10, windowSize.y/10);
	mText1.setFillColor(sf::Color::Black);

  BoundaryBox.setPosition(windowSize.x*1/20, windowSize.y*1/4 );
  BoundaryBox.setFillColor(sf::Color(200, 200, 200, 50 )); // 색상 설정
}

void MainStep2::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(mText1, states);  
  target.draw(BoundaryBox, states);  
  return;
}

bool MainStep2::update(sf::Time dt){
  return false;
}

bool MainStep2::handleEvent(const sf::Event& event){
  
  return false;
}

void MainStep2::setCities(const std::vector<std::array<float, 2>>& Coords,
                          sf::Vector2f minXY,
                          sf::Vector2f maxXY){
  
	for (auto coord : coords) {
			coord[0] *= windowSize.x/4;
			coord[1] *= windowSize.x/4;
	}
  
  sf::Vector2f boxOrigin = BoundaryBox.getOrigin();
  sf::Vector2f boxSize   = BoundaryBox.getOrigin();
  std::vector<std::array<float, 2>>	customCoords;

}