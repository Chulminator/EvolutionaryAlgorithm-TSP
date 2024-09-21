#ifndef BOOK_MUSICPLAYER_HPP
#define BOOK_MUSICPLAYER_HPP

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include <map>
#include <string>


class MusicPlayer : private sf::NonCopyable
{
	public:
									MusicPlayer();

		void						play(Music::ID theme);
		void						stop();
		void 						changeMusic(Music::ID theme);

		void						setPaused(bool paused);
		void						setVolume(float volume);
		void            setLoop(bool playLoop);
		bool            getStatus();

	private:
		sf::Music							mMusic;
		std::map<Music::ID, std::string>	mFilenames;
		float								mVolume;
};

#endif // BOOK_MUSICPLAYER_HPP
