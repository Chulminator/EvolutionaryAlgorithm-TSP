#ifndef BOOK_RESOURCEIDENTIFIERS_HPP
#define BOOK_RESOURCEIDENTIFIERS_HPP


// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
	class SoundBuffer;
}


namespace Textures
{
	enum ID
	{
		ProfilePhoto,
		// Jungle,
	};
}


namespace Fonts
{
	enum ID
	{
		Main,
		Main2,
	};
}

namespace SoundEffect
{
	enum ID
	{
		LineClear,
		Button,
		Click,
		Cymbal1,
		Cymbal2,
	};
}

namespace Music
{
	enum ID
	{
		LogoTheme,
		Home,
		MainStep1,
		MainStep3,
		Result,
	};
}


// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures::ID>					TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>								FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID>	SoundBufferHolder;

#endif // BOOK_RESOURCEIDENTIFIERS_HPP
