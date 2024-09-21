#ifndef BOOK_COMMANDQUEUE_HPP
#define BOOK_COMMANDQUEUE_HPP

#include "TetrisIdentifiers.hpp"
#include <queue>
// #include "Tetris.hpp"

enum Action
{
	MoveLeft,
	MoveRight,
	MoveDown,
	Rotate,
	Drop,
	ActionCount
};

class CommandQueue
{
	public:
		void									push(const TetrisGame::Action& action);
		TetrisGame::Action								pop();
		bool									isEmpty() const;
		
	private:
		std::queue<TetrisGame::Action>	 mQueue;
};


#endif // BOOK_COMMANDQUEUE_HPP
