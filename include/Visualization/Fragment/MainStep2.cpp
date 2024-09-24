 
#include "MainStep2.hpp"

MainStep2::MainStep2(State::Context context)
: windowSize(static_cast<sf::Vector2f>(context.window->getSize()))
, mblinkTime(sf::Time::Zero)
, isSumCent(false)
, flagGoNext(false)
, blinkTextStep2()
{
	mText1.setFont(context.fonts->get(Fonts::Main2));
	mText1.setString("Step 2\n Set the parameters for the evolution");
	mText1.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mText1.setPosition(windowSize.x/10, windowSize.y/10);
	mText1.setFillColor(sf::Color::Black);

  // mGUIContainerButton
	addButtonLabel(Evolution::Type::Crossover,	    windowSize.y*5./12.f, "Crossover: ", context);
	addButtonLabel(Evolution::Type::Mutation,	      windowSize.y*6./12.f, "Mutation: ", context);
	addButtonLabel(Evolution::Type::Elitism,	      windowSize.y*7./12.f, "Elitism: ", context);
	addButtonLabel(Evolution::Type::NewChromosome, 	windowSize.y*8./12.f, "New Chromosome: ", context);

	auto nextButton = std::make_shared<GUI::Button>(context);
	nextButton->setText("Next");
	nextButton->setToggle(true); 
	nextButton->setCallback(
			[this, nextButton] ()
		{
			if ( checkParameters() ){
				updateLabels();
				nextButton->deactivate();
				flagGoNext = true;
			}
			else{
      	blinkTextStep2.startBlink();
				nextButton->deactivate();
			}
			
		}
	);
	sf::FloatRect spriteBounds;
	spriteBounds = nextButton->getLocalBounds();
	nextButton->setTextOrigin(spriteBounds.left, spriteBounds.top + spriteBounds.height * 0.5f);
	nextButton->setTextPosition(windowSize.x*0.2, windowSize.y*9./12.f);
	mGUIContainerButton.pack(nextButton);		

	
	// ;
	mTextStep2.setFont(context.fonts->get(Fonts::Main2));
	mTextStep2.setCharacterSize(context.window->getSize().x/25); // 글자 크기 설정 (50 포인트)
	mTextStep2.setString("One of the parameters is empty or zero");
  mTextStep2.setOrigin(mTextStep2.getLocalBounds().width / 2, 
											 mTextStep2.getLocalBounds().height / 2);
	// mTextStep2.setPosition(windowSize.x*3/4, windowSize.y*7/8);
	mTextStep2.setPosition(windowSize.x/2, windowSize.y/2);
	mTextStep2.setFillColor(sf::Color::Black); // 초기 투명도 0
	blinkTextStep2.setEntity(mTextStep2);
}

void MainStep2::draw(sf::RenderTarget& target, sf::RenderStates states) const{

  target.draw(mText1, states);  
	target.draw( mGUIContainerButton );
	target.draw( mGUIContainerLabel );
  target.draw( blinkTextStep2 );
  return;
}

bool MainStep2::update(sf::Time dt){	
  blinkTextStep2.update(dt);
	blinkActivated(dt);  
  return false;
}

bool MainStep2::handleEvent(const sf::Event& event){
	// 시작하자마자 released 눌려서 안됨
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t type = 0; type < Evolution::Type::TypeCount; ++type)
	{
		if (mBindingButtons[type]->isActive()){
			isKeyBinding = true;

			if (event.type == sf::Event::TextEntered) {
				std::string input = mStringPercent[type]; // 사용자 입력을 저장할 문자열
				if (event.text.unicode < 128) { // ASCII 범위 내의 문자만 처리
					char enteredChar = static_cast<char>(event.text.unicode);
					if (isdigit(enteredChar)) { // 숫자인 경우
						input += enteredChar; // 입력 문자열에 추가
					} else if (enteredChar == '\b') { // 백스페이스 처리
						input.clear();
					}
				}
				if (input.length() >=2){
					input = input.substr(input.size() - 2);
				}

				mStringPercent[type] = input;
				std::cout << "input " << mStringPercent[type] << std::endl;
    return 0;
			}			
			if (event.type == sf::Event::KeyReleased){
				if (event.key.code == sf::Keyboard::Enter){			
					mBindingButtons[type]->deactivate();
					mBindingLabels[type]->stopBlink();
				}
			}
			break;
		}
	}

	if (isKeyBinding){
		updateLabels();
	}
	else{
		mGUIContainerButton.handleEvent(event);		
	}
  
  return false;
}


void MainStep2::updateLabels()
{
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) 
	{
		Evolution::Type action = static_cast<Evolution::Type>(ii);    
    std::string str; // 사용자 입력을 저장할 문자열
    str = "<\t" + mStringPercent[ii] + " %\t>"; // Assign the formatted string to str
		mBindingLabels[ii]->setText(str);
	}
}

bool MainStep2::checkParameters(){
	int sum = 0;
	std::vector<int> percentages(Evolution::Type::TypeCount, 0);

	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
			if ( mStringPercent[ii] != "" || 
			     mStringPercent[ii] != "0" ||
			     mStringPercent[ii] != "00" ) {
					percentages[ii] = std::stoi(mStringPercent[ii]);
					sum += percentages[ii];
			}
			else{
				return false;
			}
	}

	// 합계가 100이 되도록 조정
	if (sum != 0) {
			int targetSum = 100;
			int difference = targetSum - sum;

			// 비율에 따라 차이를 분배
			for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
					if (mStringPercent[ii] != "") {
							// 비율에 따라 차이를 나누어 추가
							percentages[ii] += static_cast<int>(std::round((static_cast<double>(percentages[ii]) / sum) * difference));
					}
			}

			// 최종 합계가 100이 되도록 보정
			int finalSum = std::accumulate(percentages.begin(), percentages.end(), 0);
			int finalDifference = targetSum - finalSum;

			// 최종 차이를 첫 번째 요소에 추가하여 보정
			if (finalDifference != 0) {
					percentages[0] += finalDifference;
			}
	}

	// mStringPercent 업데이트
	for (std::size_t ii = 0; ii < Evolution::Type::TypeCount; ++ii) {
		mStringPercent[ii] = std::to_string(percentages[ii]);
	}

	return true;
}

void MainStep2::blinkActivated(sf::Time dt){
	mblinkTime += dt;	
	if( mblinkTime >= sf::seconds(0.05f) ){
		mblinkTime -= sf::seconds(0.05f);
		for (std::size_t type = 0; type < Evolution::Type::TypeCount; ++type)
		{
			if (mBindingButtons[type]->isActive())
			{			
				mBindingLabels[type]->blink();
				break;
			}
		}
	}
}


void MainStep2::addButtonLabel(Evolution::Type type, 
                               float y, 
                               const std::string& text, 
                               State::Context context)
{	
	sf::FloatRect spriteBounds;
	mBindingButtons[type] = std::make_shared<GUI::Button>(context);	
	mBindingButtons[type]->setText(text);	
	spriteBounds = mBindingButtons[type]->getLocalBounds();
  mBindingButtons[type]->setTextOrigin(spriteBounds.left, spriteBounds.top + spriteBounds.height * 0.5f);
	mBindingButtons[type]->setTextPosition(windowSize.x*0.2, y);
	mBindingButtons[type]->setToggle(true); 
	mGUIContainerButton.pack( mBindingButtons[type] );

	mBindingButtons[type]->setCallback([this, type] ()
	{
		mStringPercent[type] = "";		
		updateLabels();
	});
	

	mBindingLabels[type] = std::make_shared<GUI::Label>("", *context.fonts);
	mGUIContainerLabel.pack( mBindingLabels[type] ); 
  std::string str; 
  str = "<\t %\t>"; 
  mBindingLabels[type]->setText(str);
	mBindingLabels[type]->setCharacterSize(context.window->getSize().x/25);
	mBindingLabels[type]->setPosition(windowSize.x*0.7, y);
}

