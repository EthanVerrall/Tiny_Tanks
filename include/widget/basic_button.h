#ifndef BASIC_BUTTON_H
#define BASIC_BUTTON_H

#include "SFML/Graphics.hpp"
#include "widget/button.h"
#include "utils/defs.h"
#include <variant>

//TO DO
//ADD text border and color, for the actual text
//cpp file
//comments
//use logger

namespace tiny_tanks::widget {

	class Basic_button : public Button {
	
	public:
		
		//Square
		Basic_button(sf::RenderWindow* render_window, const sf::Vector2f& vector,
			const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Square
		Basic_button(sf::RenderWindow* render_window, const sf::Vector2f& vector,
			const sf::Text& button_text, const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Circle shape
		Basic_button(sf::RenderWindow* render_window, const float radius, const size_t point_count,
			const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Circle shape
		Basic_button(sf::RenderWindow* render_window, const float radius, const size_t point_count,
			const sf::Text& button_text, const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);
		
		//
		~Basic_button() = default;

		//Basic Setters
		void set_background_color(const sf::Color& bg_color);

		void set_border_color(const sf::Color& border_color);

		void set_border_thickness(const float border_thickness);

		void set_font(const sf::Font& font);

		void set_text(const sf::Text& button_text);

		void set_text_color(const sf::Color& color);

		void set_text_alignment(const tiny_tanks::utils::Alignment alignment);

		void rotate_button(const sf::Angle& angle);

		void set_visiable(const bool visiable) override;

		void set_hoverable(const bool hoverable) override;

		void set_clickable(const bool clickable) override;

		void set_pos(sf::Vector2f const& pos) override;

		void set_origin(sf::Vector2f const& origin) override;

		Widget_type is() const override;

		//Basic Getters
		sf::Color get_background_color() const;
			 
		sf::Color get_border_color() const;

		float get_border_thickness() const;
			 
		sf::Font get_font()  const;
			 
		sf::Text get_text() const;
			 
		sf::Color get_text_color() const;
			 
		tiny_tanks::utils::Alignment get_text_alignment() const;
			 
		void get_rotation(const sf::Angle& angle) const;

		//Functionality
		bool is_hovered() const override;

		void draw() override;

	private:
		std::variant<sf::RectangleShape, sf::CircleShape> m_shape;
		sf::Text m_text;
		tiny_tanks::utils::Alignment m_text_aligment;
		sf::Font m_font;
	};
}

#endif //BASIC_BUTTON_H