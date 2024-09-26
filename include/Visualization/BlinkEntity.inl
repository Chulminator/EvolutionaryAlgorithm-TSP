

template <typename Entity>
BlinkEntity<Entity>::BlinkEntity()
: blinkTime(sf::Time::Zero)
, flagBlink(false)
{
	// mTextStep1.setPosition(windowSize.x/2, windowSize.y/2);
}

template <typename Entity>
void BlinkEntity<Entity>::setEntity(Entity& entity_) {
	entity = entity_;  // Assign the entity
	if constexpr (std::is_same_v<Entity, sf::RectangleShape>) {
		sf::Color color = entity.getFillColor();
		entity.setFillColor(sf::Color(color.r, 
																	color.g, 
																	color.b, 
																	0));
	}
	else if constexpr (std::is_same_v<Entity, sf::Text>) {
		sf::Color color = entity.getFillColor();
		entity.setFillColor(sf::Color(color.r, 
																	color.g, 
																	color.b, 
																	0));
	} else if constexpr (std::is_same_v<Entity, sf::Sprite>) {
		printf("Check implementation here \n");
		printf("BlinkEntity.inl\n");
		exit(1);
		sf::Color color = entity.getFillColor();
		entity.setColor(sf::Color(color.r, 
															color.g, 
															color.b, 
															0));
	}
}

template <typename Entity>
void BlinkEntity<Entity>::startBlink() {
	flagBlink = true; 
}

template <typename Entity>
bool BlinkEntity<Entity>::update(sf::Time dt){
	if (flagBlink) {
		blinkTime += dt;
		float alpha = 0;
		if (blinkTime < sf::seconds(0.3f)) {
			alpha = 255. * (blinkTime.asSeconds() / 0.3f);
		} else if (blinkTime < sf::seconds(1.3f)) {
			alpha = 255.;
		} else if (blinkTime < sf::seconds(1.6f)) {
			alpha = 255 * (1 - (blinkTime.asSeconds() - 1.3f) / 0.3f);
		} else {
			flagBlink = false; 
			blinkTime = sf::Time::Zero;
		}

		// Set the color of the entity object (an instance of Entity)
		if constexpr (std::is_same_v<Entity, sf::RectangleShape>) {
			sf::Color color = entity.getFillColor();
			entity.setFillColor(sf::Color(color.r, 
																		color.g, 
																		color.b, 
																		static_cast<int>(alpha)));
		}
		else if constexpr (std::is_same_v<Entity, sf::Text>) {
			sf::Color color = entity.getFillColor();
			entity.setFillColor(sf::Color(color.r, 
																		color.g, 
																		color.b, 
																		static_cast<int>(alpha)));
		} 
		else if constexpr (std::is_same_v<Entity, sf::Sprite>) {
			sf::Color color = entity.getColor();
			entity.setColor(sf::Color(color.r, 
																color.g, 
																color.b, 
																static_cast<int>(alpha)));
		}
	}
	return false;
}
template <typename Entity>
bool BlinkEntity<Entity>::handleEvent(const sf::Event& event){
  return false;
}

template <typename Entity>
void BlinkEntity<Entity>::draw(sf::RenderTarget& target, sf::RenderStates states) const{  	
	if( flagBlink ){
		sf::Color color = entity.getFillColor();
  	target.draw(entity, states); 
	}
  return;
}

