#include "CommandQueue.hpp"


void CommandQueue::push(const TetrisGame::Action& action)
{
	mQueue.push(action);
}

TetrisGame::Action CommandQueue::pop()
{
	TetrisGame::Action action = mQueue.front();
	mQueue.pop();
	return action;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}
