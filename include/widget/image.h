#ifndef WIDGET_IMAGE_H
#define WIDGET_IMAGE_H

// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "SFML/Graphics.hpp"
#include "utils/logger.h"
#include "widget/widget.h"
#include "utils/defs.h"

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::widget {

// ===================================================================
// class Image_frame
// -------------------------------------------------------------------

class Image_frame final : public sf::Shape {
public:
    explicit Image_frame(const std::vector<sf::Vector2f>& points);

    virtual std::size_t getPointCount() const override;

    virtual sf::Vector2f getPoint(std::size_t index) const override;

private:
    std::vector<sf::Vector2f> m_points;
};

// ===================================================================
// class Image
// -------------------------------------------------------------------

class Image final : public Widget {

public:
    explicit Image(sf::RenderWindow* render_window);

    Image(sf::RenderWindow* render_window, sf::Texture const& image_texture);

    Image(sf::RenderWindow* render_window, sf::Texture const& image_texture, unsigned int const num_vertices);

    void set_pos(sf::Vector2f const& pos) override;

    void set_origin(sf::Vector2f const& origin) override;

    Widget_type is() const override;

    void draw() override;

    void        set_image(sf::Texture const& image_texture);
    sf::Texture get_image(/*----------------------------*/) const;

    void         set_size(sf::Vector2f const& size);
    sf::Vector2f get_size(/*--------------------*/) const;

    void  set_scale(float const factor);
    float get_scale(/*--------------*/) const;

    void         set_num_vertices(unsigned int const num_vertices);
    unsigned int get_num_vertices(/*---------------------------*/) const;

    void hide     (bool const is_hidden);
    bool is_hidden(/*----------------*/) const;

    void  set_border_thickness(float const thickness);
    float get_border_thickness(/*-----------------*/) const;

    void      set_border_color(sf::Color const& color);
    sf::Color get_border_color(/*------------------*/) const;

    void      set_color_filter(sf::Color const& color);
    sf::Color get_color_filter(/*------------------*/) const;

    sf::FloatRect get_local_bounds () const;
    sf::FloatRect get_global_bounds() const;

    void      set_rotation(sf::Angle const& angle);
    sf::Angle get_rotation(/*------------------*/) const;
    void      rotate      (sf::Angle const& angle);

    void move(sf::Vector2f const& delta_offset);

private:

    enum class State {

        Visible,
        Hidden
    };

    sf::Texture m_texture;
    Image_frame m_frame;

    unsigned int m_num_vertices;

    State m_state;

    sf::Vector2f m_delta_offset;
    sf::Vector2f m_size;
    float        m_scale_factor;
    sf::Angle    m_rotation;

    void m_apply_size_and_scale();

    std::vector<sf::Vector2f> m_calculate_shape(unsigned int num_vertices);
};

} // tiny_tanks::widget

#endif // WIDGET_IMAGE_H
