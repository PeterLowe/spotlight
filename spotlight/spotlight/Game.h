/// <summary>
/// author Pete Lowe April 2022
/// Example of spotlight
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
const float RADIUS = 75.0f; // radius of spotlight
const sf::Color DARK{ 55,55,55,255 }; // colour used to dim background to lighlight spotlight
const int RADIUSi = static_cast<int>(RADIUS); // radius in integer used in intRect
const int SPOTLIGHT_WIDTH = static_cast<int>(RADIUS * 2); // width of spotlight for texture intRect
const int SPOTLIGHT_HEIGHT = static_cast<int>(RADIUS * 2); // same

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_caveTexture; // texture used for sfml logo
	sf::Sprite m_caveSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_lightsOn{ true }; // control background image display
	sf::CircleShape m_cirleSpotlight{ RADIUS }; // spotlight circle


	bool m_circleOn{ false }; // control is spotlight is on
	

};

#endif // !GAME_HPP

