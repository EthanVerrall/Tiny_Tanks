#ifndef WIDGET_BASE_BUTTON
#define WIDGET_BASE_BUTTON

/*	
 	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////
	Button will be a base class
	Basic Button && Vertex_button && image button && image vertex button && sprite button
	--- These will derive from button
	///////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////

	ATRIBUTES:
	1) A button should have the total number of sides needed to draw it or a collection of points -- in derived class
	
	2) How to draw it -- in derived class

	3) Origin point and Position -- base widget class

	4) Scale && Rotation -- in derived class

	5) A background, image/animation/filled colour. Foreground Text colour. -- in derived class

	6) Be able to contain text in the button (This wont be needed for image and sprite buttons, obv...) -- in derived class

	7) Border, thickness and colour -- in derived class

	8) State, is clickable? is hidden? is hovered? - bool? - Base button class

	9) The button should handle a click event - contains virtual function

	10) A button could also just be text with no box around it but really it will be a box that is invisable
		and tiny and closly wrapped around the text 
		(Research how modern gaming approaches this problem) -- derived class
	
	11) A Font type is also important -- derived class

*/

#include "widget/widget.h"

namespace tiny_tanks::widget {

	class Button : public Widget {

	protected:

		bool m_visiable{};
		bool m_hoverable{};
		bool m_clickable{};
	
	public:

		/*
		--------------------------------
		Virtual functions
		--------------------------------
		*/

		virtual ~Button() = default;

		virtual void set_pos(sf::Vector2f const& pos) = 0; 

		virtual void set_origin(sf::Vector2f const& origin) = 0;

		virtual void draw() = 0;

		void virtual set_visiable(const bool visiable) = 0;

		void virtual set_hoverable(const bool hoverable) = 0;

		void virtual set_clickable(const bool clickable) = 0;

		bool get_visiable() const { return m_visiable; }

		bool get_hoverable() const { return m_hoverable; }

		bool get_clickable() const { return m_clickable; }

		Widget_type is() const override { return Widget_type::Button; }
	};
};


#endif //WIDGET_BASE_BUTTON