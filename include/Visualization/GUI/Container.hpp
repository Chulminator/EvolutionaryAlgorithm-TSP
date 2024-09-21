#ifndef BOOK_CONTAINER_HPP
#define BOOK_CONTAINER_HPP

#include "Component.hpp"

#include <vector>
#include <memory>


namespace GUI
{

class Container : public Component
{
    public:
        typedef std::shared_ptr<Container> Ptr;
            

	public:
							Container();
							Container(bool flagUpDown_);

        void				pack(Component::Ptr component);
        
        void				giveSelection();
        void				giveSelection(std::size_t index);

        virtual bool		isSelectable() const;
        virtual void		handleEvent(const sf::Event& event);
        virtual bool		update(sf::Time dt);


        bool				hasActivation() const;
    private:
        virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

        bool				hasSelection() const;
        void				select(std::size_t index);
        void				selectNext();
        void				selectPrevious();


    private:
        std::vector<Component::Ptr>		mChildren;
        int								mSelectedChild;
        bool                            flagUpDown;
};

}

#endif // BOOK_CONTAINER_HPP
