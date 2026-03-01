#ifndef BASIC_BUTTON_H
#define BASIC_BUTTON_H

#include "SFML/Graphics.hpp"
#include "widget/button.h"
#include "utils/defs.h"
#include <variant>
#include <string>

//TO DO
//cpp file
//comments
//use logger

namespace tiny_tanks::widget {

	class Basic_button : public Button {
	
	public:
		
		//---------------------------------------------------------
		//Button Constructors and Destructors
		//---------------------------------------------------------

		//Square button with no text
		Basic_button(sf::RenderWindow* render_window, const sf::Vector2f& vector,
			const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Square button with text
		Basic_button(sf::RenderWindow* render_window, const sf::Vector2f& vector,
			const std::string& button_text, const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Circle shape button with no text
		Basic_button(sf::RenderWindow* render_window, const float radius, const size_t point_count,
			const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);

		//Circle shape button with text
		Basic_button(sf::RenderWindow* render_window, const float radius, const size_t point_count,
			const std::string& button_text, const sf::Color& bg_color = tiny_tanks::utils::DEFAULT_WIDGET_BACKGROUND);
		
		~Basic_button() = default;



		//---------------------------------------------------------
		//Button Functionality
		//---------------------------------------------------------

		bool is_hovered() const override;
		void draw() override;
		void move(const sf::Vector2f& delta_offset) override;
		void rotate_button(const sf::Angle& angle);
		void clear();
		Widget_type is() const override;



		//---------------------------------------------------------
		//Button shape and position and states
		//---------------------------------------------------------

		//Set

		void set_pos(sf::Vector2f const& pos) override;
		void set_origin(sf::Vector2f const& origin) override;
		void set_rotation(const sf::Angle& angle) const;
		void set_visiable(const bool visiable) override;
		void set_hoverable(const bool hoverable) override;
		void set_clickable(const bool clickable) override;

		//Get

		sf::Angle get_rotation() const;



		//---------------------------------------------------------
		//Button-styling
		//---------------------------------------------------------
		
		//Set
		
		void set_background_color(const sf::Color& bg_color);
		void set_border_color(const sf::Color& border_color);
		void set_border_thickness(const float border_thickness);

		//Get

		sf::Color get_background_color() const;
		sf::Color get_border_color() const;
		float get_border_thickness() const;



		//---------------------------------------------------------
		//Button-text-styling
		//---------------------------------------------------------

		//Set

		void set_font(const sf::Font& font);

		void set_text(const std::string& button_text);

		void set_text_color(const sf::Color& color);

		void set_text_style(const sf::Text::Style text_style);

		void set_text_outline_color(const sf::Color& outline_color);

		void set_text_outline_thickness(const float outline_thickness);


		//Get

		sf::Font get_font()  const;

		sf::Text get_text() const;

		sf::Color get_text_color() const;

		sf::Text::Style get_text_style() const;

		sf::Color get_text_outline_color() const;

		float get_text_outline_thickness() const;		
		
		std::string get_text_as_string() const;
		


		//---------------------------------------------------------
		//Margin AND alignment
		//---------------------------------------------------------

		void set_text_mode(tiny_tanks::widget::Basic_button::Text_mode text_mode);
		tiny_tanks::widget::Basic_button::Text_mode get_text_mode() const;

		void set_text_alignment(const tiny_tanks::utils::Alignment alignment);
		tiny_tanks::utils::Alignment get_text_alignment() const;

		void set_margins(

			float const top,
			float const bottom,
			float const left,
			float const right
		);

		float get_margin_top() const;
		float get_margin_bottom() const;
		float get_margin_left() const;
		float get_margin_right() const;



		//---------------------------------------------------------
		//Class members
		//---------------------------------------------------------

	private:
		std::variant<sf::RectangleShape, sf::CircleShape> m_shape;
		sf::Text m_text;
		tiny_tanks::utils::Alignment m_text_aligment;
		sf::Font m_font;

		enum class Text_mode {

			Mode_margin,
			Mode_alignment

		} m_text_mode;

		struct {

			float top;
			float bottom;
			float left;
			float right;

		} m_margins;
	};
}

#endif //BASIC_BUTTON_H