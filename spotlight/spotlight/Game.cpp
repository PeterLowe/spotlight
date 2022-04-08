/// <summary>
/// @author Peter Lowe
/// @date April 2022
/// 
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 900U, 500U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupVertexArray(); // initialise vertext array and other data
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseDown(newEvent);
		}
		if (sf::Event::MouseMoved == newEvent.type)
		{
			processMouseMove(newEvent);
		}

	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::L == t_event.key.code)
	{
		m_lightsOn = !m_lightsOn;
	}
}

/// <summary>
/// deal with mouse down
/// check if left button
/// then adjust texture rect and location for
/// spotlight circle
/// turn on spotlight
/// </summary>
/// <param name="t_event">mouse press event</param>
void Game::processMouseDown(sf::Event t_event)
{
	sf::IntRect area{ 0,0,SPOTLIGHT_WIDTH,SPOTLIGHT_HEIGHT };
	
	if (sf::Mouse::Button::Left == t_event.mouseButton.button)
	{
		m_circleOn = true;
	
		area.left = t_event.mouseButton.x - RADIUSi;
		area.top = t_event.mouseButton.y - RADIUSi;
		m_cirleSpotlight.setTextureRect(area);
		m_cirleSpotlight.setPosition(static_cast<float>(t_event.mouseButton.x) + RADIUS, static_cast<float>(t_event.mouseButton.y) + RADIUS);
	}
}

/// <summary>
/// check if left button down
/// update texture rect and position of
/// spotlight circle shape
/// </summary>
/// <param name="t_event">mouse move event</param>
void Game::processMouseMove(sf::Event t_event)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::IntRect area{ 0,0,SPOTLIGHT_WIDTH,SPOTLIGHT_HEIGHT };
		if (m_circleOn)
		{
			area.left = t_event.mouseMove.x - RADIUSi;
			area.top = t_event.mouseMove.y - RADIUSi;
			m_cirleSpotlight.setTextureRect(area);
			m_cirleSpotlight.setPosition(static_cast<float>(t_event.mouseMove.x) + RADIUS, static_cast<float>(t_event.mouseMove.y) + RADIUS);
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_circleOn = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	
	if (m_lightsOn)
	{
		m_caveSprite.setColor(sf::Color::White);
	}
	else
	{
		m_caveSprite.setColor(DARK); // makes background darker
	}
	m_window.draw(m_caveSprite);
	if (m_circleOn)
	{
		m_window.draw(m_cirleSpotlight);
	}
	m_window.draw(m_welcomeMessage);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("<L> to toggle light \nmouse drag to move spotlight");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(20U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::White);
	m_welcomeMessage.setOutlineThickness(1.0f);

}

/// <summary>
/// load the texture and setup the sprite for the background
/// setup the circle spotlight
/// </summary>
void Game::setupSprite()
{
	if (!m_caveTexture.loadFromFile("ASSETS\\IMAGES\\cave.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_caveSprite.setTexture(m_caveTexture);
	m_caveSprite.setPosition(0.0f, 0.0f);
	m_cirleSpotlight.setPosition(0.0f, 0.0f);
	m_cirleSpotlight.setOrigin(2*RADIUS, 2*RADIUS);
	m_cirleSpotlight.setTexture(&m_caveTexture);

}

void Game::setupVertexArray()
{
	float angle = M_2_PI / static_cast<float>(NO_POINTS);
	
	for (int i = 0; i < NO_POINTS; i++)
	{
		
		m_offsets[i].x = std::cos(angle * static_cast<float>(i)) * RADIUS;
		m_offsets[i].y = std::sin(angle * static_cast<float>(i)) * RADIUS;
	}
}
