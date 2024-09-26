#include "MusicPlayer.hpp"


MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{	
	mFilenames[Music::LogoTheme]  = "Media/Music/LogoSound.wav";
	mFilenames[Music::Home]       = "Media/Music/Happy-Boy-Theme-Kevin-MacLeod.wav";
	mFilenames[Music::MainStep1]  = "Media/Music/Hot-Swing-Kevin-MacLeod.wav";
	// mFilenames[Music::MainStep2]  = "Media/Music/SoundBar.wav";
	mFilenames[Music::MainStep3]  = "Media/Music/Danse-Macabre-Busy-Strings-Kevin-MacLeod.wav";
	mFilenames[Music::Result]     = "Media/Music/Light-Sting-Kevin-MacLeod.wav";
}

void MusicPlayer::play(Music::ID theme)
{
	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop()
{
	mMusic.stop();
}

void MusicPlayer::changeMusic(Music::ID theme) {
		mMusic.stop(); // 현재 음악 정지		
		std::string filename = mFilenames[theme];
		if (!mMusic.openFromFile(filename)){
			throw std::runtime_error("Music " + filename + " could not be loaded.");
		}
		mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}

void MusicPlayer::setLoop(bool playLoop)
{
	mMusic.setLoop(playLoop);
}

bool MusicPlayer::getStatus()
{
	bool flag = mMusic.getStatus() == sf::Music::Playing;
	return flag;
}
