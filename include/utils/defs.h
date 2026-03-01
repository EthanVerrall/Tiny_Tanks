#ifndef UTILS_DEFS_H
#define UTILS_DEFS_H

// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "SFML/Graphics.hpp"

#include "SFML/Graphics.hpp"

#include "SFML/Graphics.hpp"
#include <string_view>

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::utils {

// ===================================================================
// Enums
// -------------------------------------------------------------------

enum class Alignment {

    Left,
    Right,
    Top,
    Bottom,
    Center
};

// ===================================================================
// Widget constants
// -------------------------------------------------------------------

// Colors
inline sf::Color constexpr DEFAULT_TEXT_COLOR        = sf::Color::Black;
inline sf::Color constexpr DEFAULT_WIDGET_BACKGROUND = sf::Color::Blue;

// Fonts
inline std::string_view const DEFAULT_TEXT_FONT = "assets/fonts/Pennsylvania.otf";

// Constants
inline unsigned int constexpr DEFAULT_SHAPE_NUM_VERTICES = 3u;

// Textures
inline std::string_view const DEFAULT_TEXTURE = "assets/textures/Default_texture.png";

} // tiny_tanks::utils

#endif // UTILS_DEFS_H
