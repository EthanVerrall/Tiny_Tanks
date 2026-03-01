#include "SFML/Graphics.hpp"
#include "widget/widget.h"
#include "utils/logger.h"

// Set global logger settings (MUST be done before main)
int              const ENABLED_LOG_LVLS	      = Log_lvl::ALL_LOG_LVLS;
std::string_view const LOG_SPECIFIC_FILE_ONLY = "ALL";

// Example logging:
// 	LOG(Log_lvl::ERROR) << "No memory to create object in vector: " << 5;
// Output for this is then:
// 	[ERROR]
// 	[Time: 20:17:54]
// 	[File: main.cpp]
// 	[Line: 18]
// 	[Function: int __cdecl main(void)]
// 	[Logger: No memory to create object in vector: 5]

int main() {

	using namespace tiny_tanks::widget;

	//Create default render window, not full screen, 8 levels of gpu anti aliasing
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8u;

	//Here is the window
	sf::RenderWindow window(sf::VideoMode({ 1200u,800u }), "Window", sf::Style::Default, sf::State::Windowed, settings);

	//Create main window loop
	while (window.isOpen()) {

		//Poll for events
		while (std::optional<sf::Event> current_event = window.pollEvent()) {

			//Top right exit button event, mouse click it
			if (current_event->is<sf::Event::Closed> () ){

				window.close();
			}
		}

		//Clear every frame before drawing
		window.clear(sf::Color::White);

		/*
		--------------------------
		Draw below here with window.draw(my_object)
		--------------------------
		*/

		//Displays everything drawn
		window.display();
	}

	return 0;
}