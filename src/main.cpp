#include "SFML/Graphics.hpp"
#include "widget/widget.h"

int main() {

	//Create default render window, not full screen, 8 levels of gpu anti aliasing
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8u;

	//Here is the window
	sf::RenderWindow window (sf::VideoMode({ 1200u,800u }), "Window", sf::Style::Default, sf::State::Windowed, settings);

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