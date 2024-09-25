#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class PauseableClock {
public:
    PauseableClock();

    void pause();
    void resume();
    void reset();
    sf::Time getElapsedTime() const;

private:
    sf::Clock mClock;
    sf::Time mPausedTime;
    bool mIsPaused;
};