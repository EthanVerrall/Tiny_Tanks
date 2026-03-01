#ifndef WIDGET_LABEL_H
#define WIDGET_LABEL_H

// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "SFML/Graphics.hpp"
#include "utils/logger.h"
#include "widget/widget.h"
#include "utils/defs.h"

#include <string_view>

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::widget {

// ===================================================================
// class Label
// -------------------------------------------------------------------

class Label final : public Widget {

public:
    explicit Label(sf::RenderWindow* render_window);

    Label(sf::RenderWindow* render_window, std::string const& text);

    void set_pos(sf::Vector2f const& pos) override;

    void set_origin(sf::Vector2f const& origin) override;

    Widget_type is() const override;

    void draw() override;

    void        set_text(std::string const& text);
    std::string get_text(/*-------------------*/) const;

    void clear();

    void scale_content    (bool const is_content_scaled);
    bool is_content_scaled(/*------------------------*/) const;

    void hide     (bool const is_hidden);
    bool is_hidden(/*----------------*/) const;

    void set_margins(
        float const top,
        float const bottom,
        float const left,
        float const right
    );

    float get_margin_top   () const;
    float get_margin_bottom() const;
    float get_margin_left  () const;
    float get_margin_right () const;

    void     set_font(sf::Font const& font);
    sf::Font get_font(/*----------------*/) const;

    void  set_border_thickness(float const thickness);
    float get_border_thickness(/*-----------------*/) const;

    void         set_character_size(unsigned int const size);
    unsigned int get_character_size(/*-------------------*/) const;

    void            set_text_style(sf::Text::Style const style);
    sf::Text::Style get_text_style(/*-----------------------*/) const;

    void      set_text_color(sf::Color const& color);
    sf::Color get_text_color(/*------------------*/) const;

    void      set_text_outline_color(sf::Color const& color);
    sf::Color get_text_outline_color(/*------------------*/) const;

    void  set_text_outline_thickness(float const thickness);
    float get_text_outline_thickness(/*-----------------*/) const;

    void      set_background_color(sf::Color const& color);
    sf::Color get_background_color(/*------------------*/) const;

    void      set_border_color(sf::Color const& color);
    sf::Color get_border_color(/*------------------*/) const;

    sf::FloatRect get_local_bounds () const;
    sf::FloatRect get_global_bounds() const;

    void move(sf::Vector2f const& delta_offset);

    void         set_rect_size(sf::Vector2f const& size);
    sf::Vector2f get_rect_size(/*--------------------*/) const;

    void scale_text(sf::Vector2f const& factor);
    void scale_rect(sf::Vector2f const& factor);

    sf::Vector2f get_text_scale() const;
    sf::Vector2f get_rect_scale() const;

private:

    enum class State {

        Visible,
        Hidden
    };

    sf::Font m_font;
    sf::Text m_text;

    sf::RectangleShape m_rect;

    bool  m_is_content_scaled;
    State m_state;

    sf::Vector2f m_delta_offset;

    struct {

        float top;
        float bottom;
        float left;
        float right;
    } m_margins;
};

} // tiny_tanks::widget

#endif // WIDGET_LABEL_H
