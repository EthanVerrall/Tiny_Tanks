// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "widget/label.h"
#include "utils/defs.h"
#include "utils/logger.h"

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::widget {

// ===================================================================
// Using directives
// -------------------------------------------------------------------

using namespace tiny_tanks::utils;

// ===================================================================
// class Label
// -------------------------------------------------------------------

// -------------------------------------------------------------------
Label::Label(sf::RenderWindow* render_window)
    : Widget(render_window)
    , m_font(DEFAULT_TEXT_FONT)
    , m_text(m_font, "")
    , m_rect({})
    , m_is_content_scaled(true)
    , m_state(State::Visible)
    , m_delta_offset({})
    , m_margins({})
{}

// -------------------------------------------------------------------
Label::Label(sf::RenderWindow* render_window, std::string const& text)
    : Widget(render_window)
    , m_font(DEFAULT_TEXT_FONT)
    , m_text(m_font, text)
    , m_rect({})
    , m_is_content_scaled(true)
    , m_state(State::Visible)
    , m_delta_offset({})
    , m_margins({})
{}
// -------------------------------------------------------------------
void Label::set_pos(sf::Vector2f const& pos) {

    m_pos = pos;
}

// -------------------------------------------------------------------
void Label::set_origin(sf::Vector2f const& origin) {

    m_text.setOrigin(origin);
    m_rect.setOrigin(origin);
}

// -------------------------------------------------------------------
Widget_type Label::is() const {

    return Widget_type::Label;
}

// -------------------------------------------------------------------
void Label::draw() {

    if (m_state == State::Hidden) {

        return;
    }

    // Set text position first so global bounds are accurate
    m_text.setPosition(m_pos);
    m_text.move(m_delta_offset);

    // Check if rect should be scaled or not
    if (m_is_content_scaled) {

        // Get the global text bounds after all positional updates
        sf::FloatRect const text_bounds = m_text.getGlobalBounds();

        // Update the rect size based on margins and text size
        m_rect.setSize({
            text_bounds.size.x + static_cast<float>(m_margins.left) + static_cast<float>(m_margins.right),
            text_bounds.size.y + static_cast<float>(m_margins.top)  + static_cast<float>(m_margins.bottom)
        });

        // Reposition the rect to contain the text, account for margins also
        m_rect.setPosition({
            text_bounds.position.x - static_cast<float>(m_margins.left),
            text_bounds.position.y - static_cast<float>(m_margins.top)
        });

    } else {
        // Get the base size of the rect which was adjusted by the user not automatically scaled
        sf::Vector2f const base_size = m_rect.getSize();

        // Update the rect size based on margins only
        m_rect.setSize({
            base_size.x + static_cast<float>(m_margins.left) + static_cast<float>(m_margins.right),
            base_size.y + static_cast<float>(m_margins.top)  + static_cast<float>(m_margins.bottom)
        });

        // Reposition the rect based on the user settings and account for margins also
        m_rect.setPosition({
            m_pos.x + m_delta_offset.x - static_cast<float>(m_margins.left),
            m_pos.y + m_delta_offset.y - static_cast<float>(m_margins.top)
        });
    }

    // Draw the shapes
    m_render_window->draw(m_rect);
    m_render_window->draw(m_text);
}

// -------------------------------------------------------------------
void Label::set_text(std::string const& text) {

    m_text.setString(text);
}

// -------------------------------------------------------------------
std::string Label::get_text() const {

    return m_text.getString();
}

// -------------------------------------------------------------------
void Label::clear() {

    m_text.setString("");
}

// -------------------------------------------------------------------
void Label::scale_content(bool const is_content_scaled) {

    m_is_content_scaled = is_content_scaled;
}

// -------------------------------------------------------------------
bool Label::is_content_scaled() const {

    return m_is_content_scaled;
}

// -------------------------------------------------------------------
void Label::hide(bool const is_hidden) {

    if (is_hidden) { m_state = State::Hidden;  LOG(Log_lvl::TRACE) << "Label state change: Hidden";  }
    else           { m_state = State::Visible; LOG(Log_lvl::TRACE) << "Label state change: Visible"; }
}

// -------------------------------------------------------------------
bool Label::is_hidden() const {

    if (m_state == State::Hidden) { return true;  }
    else                          { return false; }
}

// -------------------------------------------------------------------
void Label::set_margins(
    float const top,
    float const bottom,
    float const left,
    float const right
    ) {

    bool ok = true;

    if (top    < 0.0f) { LOG(Log_lvl::WARNING) << "Unable to set a negative top margin: "    << top;    ok = false; }
    if (bottom < 0.0f) { LOG(Log_lvl::WARNING) << "Unable to set a negative bottom margin: " << bottom; ok = false; }
    if (left   < 0.0f) { LOG(Log_lvl::WARNING) << "Unable to set a negative left margin: "   << left;   ok = false; }
    if (right  < 0.0f) { LOG(Log_lvl::WARNING) << "Unable to set a negative right margin: "  << right;  ok = false; }

    if (ok) {

        m_margins.top    = top;
        m_margins.bottom = bottom;
        m_margins.left   = left;
        m_margins.right  = right;
    }
}

// -------------------------------------------------------------------
float Label::get_margin_top() const {

    return m_margins.top;
}

// -------------------------------------------------------------------
float Label::get_margin_bottom() const {

    return m_margins.bottom;
}

// -------------------------------------------------------------------
float Label::get_margin_left() const {

    return m_margins.left;
}

// -------------------------------------------------------------------
float Label::get_margin_right() const {

    return m_margins.right;
}

// -------------------------------------------------------------------
void Label::set_font(sf::Font const& font) {

    m_font = font;
    m_text.setFont(m_font);
}

// -------------------------------------------------------------------
sf::Font Label::get_font() const {

    return m_font;
}

// -------------------------------------------------------------------
void Label::set_border_thickness(float const thickness) {

    m_rect.setOutlineThickness(thickness);
}

// -------------------------------------------------------------------
float Label::get_border_thickness() const {

    return m_rect.getOutlineThickness();
}

// -------------------------------------------------------------------
void Label::set_character_size(unsigned int const size) {

    m_text.setCharacterSize(size);
}

// -------------------------------------------------------------------
unsigned int Label::get_character_size() const {

    return m_text.getCharacterSize();
}

// -------------------------------------------------------------------
void Label::set_text_style(sf::Text::Style const style) {

    m_text.setStyle(style);
}

// -------------------------------------------------------------------
sf::Text::Style Label::get_text_style() const {

    return static_cast<sf::Text::Style>(m_text.getStyle());
}

// -------------------------------------------------------------------
void Label::set_text_color(sf::Color const& color) {

    m_text.setFillColor(color);
}

// -------------------------------------------------------------------
sf::Color Label::get_text_color() const {

    return m_text.getFillColor();
}

// -------------------------------------------------------------------
void Label::set_text_outline_color(sf::Color const& color) {

    m_text.setOutlineColor(color);
}

// -------------------------------------------------------------------
sf::Color Label::get_text_outline_color() const {

    return m_text.getOutlineColor();
}

// -------------------------------------------------------------------
void Label::set_text_outline_thickness(float const thickness) {

    m_text.setOutlineThickness(thickness);
}

// -------------------------------------------------------------------
float Label::get_text_outline_thickness() const {

    return m_text.getOutlineThickness();
}

// -------------------------------------------------------------------
void Label::set_background_color(sf::Color const& color) {

    m_rect.setFillColor(color);
}

// -------------------------------------------------------------------
sf::Color Label::get_background_color() const {

    return m_rect.getFillColor();
}

// -------------------------------------------------------------------
void Label::set_border_color(sf::Color const& color) {

    m_rect.setOutlineColor(color);
}

// -------------------------------------------------------------------
sf::Color Label::get_border_color() const {

    return m_rect.getOutlineColor();
}

// -------------------------------------------------------------------
sf::FloatRect Label::get_local_bounds() const {

    return m_rect.getLocalBounds();
}

// -------------------------------------------------------------------
sf::FloatRect Label::get_global_bounds() const {

    return m_rect.getGlobalBounds();
}
// -------------------------------------------------------------------
void Label::move(sf::Vector2f const& delta_offset) {

    m_delta_offset += delta_offset;
}

// -------------------------------------------------------------------
void Label::set_rect_size(sf::Vector2f const& size) {

    m_rect.setSize(size);
}

// -------------------------------------------------------------------
sf::Vector2f Label::get_rect_size() const {

    return m_rect.getSize();
}

// -------------------------------------------------------------------
void Label::scale_text(sf::Vector2f const& factor) {

    m_text.scale(factor);
}

// -------------------------------------------------------------------
void Label::scale_rect(sf::Vector2f const& factor) {

    m_rect.scale(factor);
}

// -------------------------------------------------------------------
sf::Vector2f Label::get_text_scale() const {

    return m_text.getScale();
}

// -------------------------------------------------------------------
sf::Vector2f Label::get_rect_scale() const {

    return m_rect.getScale();
}

} // tiny_tanks::widget
