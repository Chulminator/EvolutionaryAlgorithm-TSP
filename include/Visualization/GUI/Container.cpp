#include "Container.hpp"
#include "../Foreach.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
, flagUpDown(true)
{
}

Container::Container(bool flagUpDown_)
: mChildren()
, mSelectedChild(-1)
, flagUpDown(flagUpDown_)
{
}

void Container::pack(Component::Ptr component)
{
	mChildren.push_back(component);

	if (!hasSelection() && component->isSelectable())
		select(mChildren.size() - 1);
}

void Container::giveSelection(){
	mSelectedChild = -1;
	int ii = 0;
	FOREACH(const Component::Ptr& child, mChildren){
		if (child->isSelectable()){
			select(ii);
			break;
		}
		++ii;
	}
}

void Container::giveSelection(std::size_t index){
	if (mChildren.at(index)->isSelectable()){
		select(index);
	}
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
{
    // If we have selected a child then give it events
	if (hasSelection() && mChildren[mSelectedChild]->isActive())
	{
		mChildren[mSelectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		if ( flagUpDown ){
			if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
			{
				selectPrevious();
			}
			else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
			{
				selectNext();
			}
			else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (hasSelection())			
					mChildren[mSelectedChild]->activate();
			}
		}
		else{if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
			{
				selectPrevious();
			}
			else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
			{
				selectNext();
			}
			else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
			{
				if (hasSelection())			
					mChildren[mSelectedChild]->activate();
			}
		}
	}
}

bool Container::update(sf::Time dt){
	FOREACH(const Component::Ptr& child, mChildren)
		child->update(dt);
	return false;
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

	FOREACH(const Component::Ptr& child, mChildren)
		target.draw(*child, states);
}

bool Container::hasSelection() const
{
	return mSelectedChild >= 0;
}

bool Container::hasActivation() const
{	
	FOREACH(const Component::Ptr& child, mChildren){
		if( child->isActive() ){
			return true;
		}
	}
	return false;
}

void Container::select(std::size_t index)
{
	if (mChildren[index]->isSelectable())
	{
		if (hasSelection())
			mChildren[mSelectedChild]->deselect();

		mChildren[index]->select();
		mSelectedChild = index;
	}
}

void Container::selectNext()
{
	if (!hasSelection())
		return;

	// Search next component that is selectable, wrap around if necessary
	int next = mSelectedChild;
	do
		next = (next + 1) % mChildren.size();
	while (!mChildren[next]->isSelectable());

	// Select that component
	select(next);
}

void Container::selectPrevious()
{
	if (!hasSelection())
		return;

	// Search previous component that is selectable, wrap around if necessary
	int prev = mSelectedChild;
	do
		prev = (prev + mChildren.size() - 1) % mChildren.size();
	while (!mChildren[prev]->isSelectable());

	// Select that component
	select(prev);
}

}
