 
#include "TSPVisualizer.hpp"

TSPVisualizer::TSPVisualizer()
: transparency(255)
{
  font.loadFromFile(".\\Media\\times.ttf");
}

// void TSPVisualizer::setGeometry(const vector<int>& vecChromosome,
//                                 const vector<array<float, 2>>& coords){ 
//   int nCity = vecChromosome.size();

//   points.clear();
//   lines.clear(); 

//   lines.resize(nCity);
//   for (int ii = 0; ii < nCity; ++ii){ 
//     sf::CircleShape circle(5); // radius setting
//     // circle.setPosition(sf::Vector2f(coords[ii][0], coords[ii][1])); // 원의 위치 설정
//     circle.setPosition(sf::Vector2f(coords[ii][0], coords[ii][1])); // 원의 위치 설정
//     circle.setFillColor(sf::Color::Black); // 색상 설정
//     sf::Color color = circle.getFillColor();
//     // circle.setFillColor(sf::Color(50, 50, 50));
//     circle.setFillColor(sf::Color(color.r/255*transparency, 
//                                   color.g/255*transparency, 
//                                   color.b/255*transparency ));
//     points.push_back(circle); // 벡터에 추가
//   }

//   for (int ii = 0; ii < nCity; ++ii){   
//     if (ii < nCity - 1) {
//       lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
//                                   sf::Vector2f( coords[vecChromosome[ii+1]][0], coords[vecChromosome[ii+1]][1]),
//                                   3.  );
//     }
//     else{
//       lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
//                                   sf::Vector2f( coords[vecChromosome[0]][0], coords[vecChromosome[0]][1]),
//                                   3.  );
//     }
//   }
//   return;
// }


void TSPVisualizer::setCities( const vector<array<float, 2>>& coords_){
  coords = coords_;
  int nCity = coords.size();
  points.clear();
  for (int ii = 0; ii < nCity; ++ii){ 
    sf::CircleShape circle(5); // radius setting
    // circle.setPosition(sf::Vector2f(coords[ii][0], coords[ii][1])); // 원의 위치 설정
    circle.setPosition(sf::Vector2f(coords[ii][0], coords[ii][1])); // 원의 위치 설정
    circle.setFillColor(sf::Color::Black); // 색상 설정
    sf::Color color = circle.getFillColor();
    // circle.setFillColor(sf::Color(50, 50, 50));
    circle.setFillColor(sf::Color(color.r/255*transparency, 
                                  color.g/255*transparency, 
                                  color.b/255*transparency ));
    points.push_back(circle); // 벡터에 추가

  }
  return;  
}
                  
void TSPVisualizer::setChromosome(const vector<int>& vecChromosome){
  int nCity = vecChromosome.size();
  lines.clear(); 
  lines.resize(nCity);
    // // // // // // //   
  mTextsAtPoints.clear();
  mTextsAtPoints.resize(nCity);
    // // // // // // //   
  for (int ii = 0; ii < nCity; ++ii){   
    if (ii < nCity - 1) {
      lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
                                  sf::Vector2f( coords[vecChromosome[ii+1]][0], coords[vecChromosome[ii+1]][1]),
                                  3.  );
    // // // // // // // 
      mTextsAtPoints[ii].setFont(font);
	    mTextsAtPoints[ii].setString(to_string(ii+1));
      mTextsAtPoints[ii].setPosition( (coords[vecChromosome[ii]][0] + coords[vecChromosome[ii+1]][0])/2,
                                           (coords[vecChromosome[ii]][1] + coords[vecChromosome[ii+1]][1])/2  );
      mTextsAtPoints[ii].setCharacterSize(15);
      mTextsAtPoints[ii].setFillColor(sf::Color::Black);
    // // // // // // // 
    }
    else{
      lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
                                  sf::Vector2f( coords[vecChromosome[0]][0], coords[vecChromosome[0]][1]),
                                  3.  );
    // // // // // // // 
      mTextsAtPoints[ii].setFont( font );
	    mTextsAtPoints[ii].setString(to_string(ii+1));
      mTextsAtPoints[ii].setPosition( (coords[vecChromosome[ii]][0] + coords[vecChromosome[0]][0])/2,
                                           (coords[vecChromosome[ii]][1] + coords[vecChromosome[0]][1])/2  );
      mTextsAtPoints[ii].setCharacterSize(15);
      mTextsAtPoints[ii].setFillColor(sf::Color::Black);
    // // // // // // // 
    }
  }
  return;
}


                  
void TSPVisualizer::setChromosome(const vector<int>& vecChromosome, const sf::Color color){
  int nCity = vecChromosome.size();
  lines.clear(); 
  lines.resize(nCity);
    // // // // // // //   
  mTextsAtPoints.clear();
  mTextsAtPoints.resize(nCity);
    // // // // // // //   
  for (int ii = 0; ii < nCity; ++ii){   
    if (ii < nCity - 1) {
      lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
                                  sf::Vector2f( coords[vecChromosome[ii+1]][0], coords[vecChromosome[ii+1]][1]),
                                  3.  );
    // // // // // // // 
      mTextsAtPoints[ii].setFont(font);
	    mTextsAtPoints[ii].setString(to_string(ii+1));
      mTextsAtPoints[ii].setPosition( (coords[vecChromosome[ii]][0] + coords[vecChromosome[ii+1]][0])/2,
                                           (coords[vecChromosome[ii]][1] + coords[vecChromosome[ii+1]][1])/2  );
      mTextsAtPoints[ii].setCharacterSize(15);
      mTextsAtPoints[ii].setFillColor(sf::Color::Black);
    // // // // // // // 
    }
    else{
      lines[ii] = createLineShape(sf::Vector2f( coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]),
                                  sf::Vector2f( coords[vecChromosome[0]][0], coords[vecChromosome[0]][1]),
                                  3.  );
    // // // // // // // 
      mTextsAtPoints[ii].setFont( font );
	    mTextsAtPoints[ii].setString(to_string(ii+1));
      mTextsAtPoints[ii].setPosition( (coords[vecChromosome[ii]][0] + coords[vecChromosome[0]][0])/2,
                                           (coords[vecChromosome[ii]][1] + coords[vecChromosome[0]][1])/2  );
      mTextsAtPoints[ii].setCharacterSize(15);
      mTextsAtPoints[ii].setFillColor(sf::Color::Black);
    // // // // // // // 
    }
    lines[ii].setFillColor(color);
  }
  return;
}


void TSPVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  
  states.transform *= getTransform();

  int nCity = points.size();
  for (int ii = 0; ii < nCity; ++ii){    
	  target.draw(lines[ii], states);  
  }
  for (int ii = 0; ii < nCity; ++ii){        
	  target.draw(points[ii], states);    
  }  
    // // // // // // //   
  for (int ii = 0; ii < nCity; ++ii){        
	  target.draw(mTextsAtPoints[ii], states);    
  }  
    // // // // // // //   
  return;
}

sf::RectangleShape TSPVisualizer::createLineShape(const sf::Vector2f& start, 
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
    line.setFillColor(sf::Color::Red); // 색상 설정
    sf::Color color = line.getFillColor();
    line.setFillColor(sf::Color(color.r, color.g, color.b, transparency));

    line.move(thickness*1.5, thickness*1.5);

    return line; // 생성한 직사각형 반환
}

void TSPVisualizer::setTransparency(const int transparency_){
  if( transparency < 0 ){
    transparency = 0;
  }
  else if (transparency > 255 ){
    transparency = 255;
  }
  else{
    transparency = transparency_;
  }
}

