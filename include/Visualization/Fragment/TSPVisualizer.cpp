 
#include "TSPVisualizer.hpp"

TSPVisualizer::TSPVisualizer()
// : gm()
{
  // gm = create_model();
  // std::make_shared<graphMaster>();
}

void TSPVisualizer::setGeometry(const vector<int>& vecChromosome,
                                const vector<array<double, 2>>& coords){ 
  int nCity = vecChromosome.size();

  points.clear();
  lines.clear(); 

  lines = sf::VertexArray(sf::PrimitiveType::Lines, nCity * 2); // 멤버 변수에 할당
  for (int ii = 0; ii < nCity; ++ii){ 
    sf::CircleShape circle(3); // 반지름 50의 원 생성
    circle.setPosition(coords[ii][0], coords[ii][1]); // 원의 위치 설정
    circle.setFillColor(sf::Color::Black); // 색상 설정
    points.push_back(circle); // 벡터에 추가

    // printf("%lf, %lf\n", coords[vecChromosome[ii]][0], coords[vecChromosome[ii]][1]);

    lines[2*ii] = sf::Vertex(sf::Vector2f(coords[vecChromosome[ii]][0], 
                                          coords[vecChromosome[ii]][1]), sf::Color::Red);
    if (ii < nCity - 1) {
      lines[ii*2+1] = sf::Vertex(sf::Vector2f(coords[vecChromosome[ii+1]][0], 
                                              coords[vecChromosome[ii+1]][1]), sf::Color::Red);
    } else {
      lines[ii*2+1] = sf::Vertex(sf::Vector2f(coords[vecChromosome[0]][0], 
                                              coords[vecChromosome[0]][1]), sf::Color::Red);
    }
  }
  return;
}

void TSPVisualizer::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  
  states.transform *= getTransform();

	target.draw(lines, states);  
  int nCity = points.size();
  for (int ii = 0; ii < nCity; ++ii){        
	  target.draw(points[ii], states);    
  }  
  return;
}
