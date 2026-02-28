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
	1) A button should have the total number of sides needed to draw it or a collection of points
	
	2) The Button should have the total number of sides or collection of points, these will determine how it
	   is drawn. 
	   (Keeping track of the buttons TSA might be useful? Maybe not?)

	3) Origin point and Position -- base widget class

	4) Scale && Rotation

	5)A background, image/animation/filled colour. Foreground Text colour.

	6) Be able to contain text in the button (This wont be needed for image and sprite buttons, obv...)

	7) Border, thickness and colour

	8)State, is clickable? is hidden? is hovered? - bool?

	9) The button should handle a click event

	10) A button could also just be text with no box around it but really it will be a box that is invisable
		and tiny and closly wrapped around the text 
		(Research how modern gaming approaches this problem)
	
	11) A Font type is also important

*/

#include "widget/widget.h"

namespace tiny_tanks::widget {

	class Button : public Widget {

	};
};


#endif //WIDGET_BASE_BUTTON