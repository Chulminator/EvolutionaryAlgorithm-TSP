
#ifndef BOOK_BUTTON_HPP
#define BOOK_BUTTON_HPP

#include "Component.hpp"
#include "../ResourceIdentifiers.hpp"
#include "../State.hpp"

// #include <SFML/Graphics/Sprite.hpp>
// #include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


class SoundPlayer;

namespace GUI
{

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;

		enum Type
		{
			Normal,
			Selected,
			Pressed,
			ButtonCount
		};


	public:
								Button(State::Context context);

        void					setCallback(Callback callback);
        void					setText(const std::string& text);
        void					setToggle(bool flag);
        void					ChangeSelectability();

        virtual bool			isSelectable() const;
        virtual void			select();
        virtual void			deselect();

        virtual void			activate();
        virtual void			deactivate();

        virtual void			handleEvent(const sf::Event& event);
        virtual bool			update(sf::Time dt);

        sf::FloatRect			getLocalBounds();
        void setTextPosition(const sf::Vector2f &position);
        void setTextPosition(float x, float y);

        void setTextOrigin(float x, float y);


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void					changeTexture(Type buttonType);


    private:
        Callback				mCallback;
        sf::Sprite				mSprite;
        sf::RectangleShape 		mBox;
        sf::Text				mText;
        bool					mIsToggle;
		SoundPlayer&			mSounds;
		bool        			mIsSelectable;
        sf::RenderWindow&	    mWindow;
};

}

#endif // BOOK_BUTTON_HPP
