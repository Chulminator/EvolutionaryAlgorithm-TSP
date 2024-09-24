 
#include "MainStep3.hpp"

MainStep3::MainStep3(State::Context context)
: windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
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

void MainStep3::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(mText1, states);  
  target.draw(BoundaryBox, states);    
  for (int ii = 0; ii < points.size(); ++ii){        
	  target.draw(points[ii], states);    
  }  
  return;
}

bool MainStep3::update(sf::Time dt){
  return false;
}

bool MainStep3::handleEvent(const sf::Event& event){
  
  return false;
}

// void MainStep3::setCities(const std::vector<std::array<float, 2>>& Coords,
//                           const sf::Vector2f minXY,
//                           const sf::Vector2f maxXY){
  
//   float padding = BoundaryBox.getSize().x / 20; // boxSize/20
//   sf::Vector2f adjustedMinXY = {minXY.x - padding, minXY.y - padding};
//   sf::Vector2f adjustedMaxXY = {maxXY.x + padding, maxXY.y + padding};

//   for (const auto& coord : Coords) {
//     std::array<float, 2> newCoord;
//     newCoord[0] = (coord[0] - adjustedMinXY.x) * (BoundaryBox.getSize().x / (adjustedMaxXY.x - adjustedMinXY.x));
//     newCoord[1] = (coord[1] - adjustedMinXY.y) * (BoundaryBox.getSize().y / (adjustedMaxXY.y - adjustedMinXY.y));
    
//     // BoundaryBox의 원점에 맞춰 위치 조정
//     newCoord[0] += BoundaryBox.getPosition().x;
//     newCoord[1] += BoundaryBox.getPosition().y;

//     customCoords.push_back(newCoord);
    
//     sf::CircleShape circle(5); 
//     circle.setPosition(sf::Vector2f(newCoord[0], newCoord[1])); // 원의 위치 설정
//     circle.setFillColor(sf::Color::Black); // 색상 설정
//     // printf("%lf %lf \n", newCoord[0], newCoord[1]);
//     points.push_back(circle);
//   }
// }