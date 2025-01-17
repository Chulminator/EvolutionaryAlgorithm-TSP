#include "State.hpp"
#include "StateStack.hpp"


// State:: GameOption::GameOption()
// : volMusic(100)
// , volSound(100)
// , speedTetris(1)
// , keyboardSensitivity(3)
// , flagPause(false)
// {
// }

State::Context::Context(sf::RenderWindow& window,
												TextureHolder& textures,
 											  FontHolder& fonts,
												MusicPlayer& music,
												SoundPlayer& sounds,
												AnalysisInfo& analysisInfo)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, music(&music)
, sounds(&sounds)
, analysisInfo(&analysisInfo)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
