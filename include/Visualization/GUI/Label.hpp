#ifndef BOOK_LABEL_HPP
#define BOOK_LABEL_HPP

#include "Component.hpp"
#include "../ResourceIdentifiers.hpp"
#include "../ResourceHolder.hpp"

#include <SFML/Graphics/Text.hpp>


namespace GUI
{

class Label : public Component
{
    public:
        typedef std::shared_ptr<Label> Ptr;
            
	public:
							Label(const std::string& text, const FontHolder& fonts);

        virtual bool		isSelectable() const;
        virtual void		handleEvent(const sf::Event& event);
        virtual bool		update(sf::Time dt);

		void				setText(const std::string& text);
        void                blink();
        void                stopBlink();
        
        void                setCharacterSize( int fontSize );

    private:
        void				draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::Text  mText;
        sf::Uint8 colorAlpha;
        sf::Uint8 dAlpha;
};

}

#endif // BOOK_LABEL_HPP
