#include "PauseableClock.hpp"

PauseableClock::PauseableClock()
: mPausedTime(sf::Time::Zero)
, mIsPaused(true)
{

}

void PauseableClock::pause() {
    if (!mIsPaused) {
        mPausedTime = mClock.getElapsedTime();
        mIsPaused = true;
    }
}

void PauseableClock::resume() {
    if (mIsPaused) {
        mClock.restart();
        mIsPaused = false;
    }
}

void PauseableClock::reset() {
    mClock.restart();
    mPausedTime = sf::Time::Zero;
    mIsPaused = false;
}

sf::Time PauseableClock::getElapsedTime() const {
    if (mIsPaused) {
        return mPausedTime;
    } else {
        return mPausedTime + mClock.getElapsedTime();
    }
}
