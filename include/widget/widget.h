#ifndef WIDGET_BASE_WIDGET_H
#define WIDGET_BASE_WIDGET_H

// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "SFML/Graphics.hpp"
#include "utils/logger.h"

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::widget {

// ===================================================================
// Enums
// -------------------------------------------------------------------

enum class Widget_type {

    // Add as we make widgets
    Button,
    Label,
    Text_edit,
    Image,
    Sprite
};

// ===================================================================
// class Widget
// -------------------------------------------------------------------

class Widget {

protected:
    explicit Widget(sf::RenderWindow* render_window)
        : m_render_window(render_window)
        , m_origin       ({})
        , m_pos          ({})
    {}

    sf::RenderWindow* m_render_window;
    sf::Vector2f            m_origin;
    sf::Vector2f            m_pos;

public:
    virtual ~Widget() = default;

    virtual void set_pos(sf::Vector2f const& pos) = 0;
    sf::Vector2f get_pos() const { return m_pos; }

    virtual void set_origin(sf::Vector2f const& origin) = 0;
    sf::Vector2f get_origin() const { return m_origin; }

    virtual Widget_type is() const = 0;

    virtual void draw() = 0;

    void set_render_target(sf::RenderWindow* render_window) {

        if (render_window == nullptr) {

            LOG(Log_lvl::ERROR) << "Render window pointer is null";
        } else {

            m_render_window = render_window;
        }
    }
};

} // tiny_tanks::widget

#endif // WIDGET_BASE_WIDGET_H
