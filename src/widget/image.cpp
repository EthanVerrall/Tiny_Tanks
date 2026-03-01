// ===================================================================
// Includes
// -------------------------------------------------------------------

#include "widget/image.h"
#include "utils/defs.h"
#include "utils/logger.h"
#include "utils/maths.h"

#include <numbers>

// ===================================================================
// Namespaces
// -------------------------------------------------------------------

namespace tiny_tanks::widget {

// ===================================================================
// Using directives
// -------------------------------------------------------------------

using namespace tiny_tanks::utils;

// ===================================================================
// class Image_frame
// -------------------------------------------------------------------

// -------------------------------------------------------------------
Image_frame::Image_frame(const std::vector<sf::Vector2f>& points)
    : m_points(points)
    {

    update();
}

// -------------------------------------------------------------------
std::size_t Image_frame::getPointCount() const {

    return m_points.size();
}

// -------------------------------------------------------------------
sf::Vector2f Image_frame::getPoint(std::size_t index) const {

    return m_points[index];
}

// ===================================================================
// class Image
// -------------------------------------------------------------------

// -------------------------------------------------------------------
Image::Image(sf::RenderWindow* render_window)
    : Widget(render_window)
    , m_texture(DEFAULT_TEXTURE)
    , m_frame(m_calculate_shape(DEFAULT_SHAPE_NUM_VERTICES))
    , m_num_vertices(DEFAULT_SHAPE_NUM_VERTICES)
    , m_state(State::Visible)
    , m_delta_offset({})
    , m_size({1.0f, 1.0f})
    , m_scale_factor(1.0f)
    {

    m_frame.setTexture(&m_texture);
}

// -------------------------------------------------------------------
Image::Image(sf::RenderWindow* render_window, sf::Texture const& image_texture)
    : Widget(render_window)
    , m_texture(image_texture)
    , m_frame(m_calculate_shape(DEFAULT_SHAPE_NUM_VERTICES))
    , m_num_vertices(DEFAULT_SHAPE_NUM_VERTICES)
    , m_state(State::Visible)
    , m_delta_offset({})
    , m_size({1.0f, 1.0f})
    , m_scale_factor(1.0f)
    {

    m_frame.setTexture(&m_texture);
}

// -------------------------------------------------------------------
Image::Image(sf::RenderWindow* render_window, sf::Texture const& image_texture, unsigned int const num_vertices)    : Widget(render_window)
    , m_texture(image_texture)
    , m_frame(m_calculate_shape(num_vertices))
    , m_num_vertices(num_vertices < 3 ? 0u : num_vertices)
    , m_state(State::Visible)
    , m_delta_offset({})
    , m_size({1.0f, 1.0f})
    , m_scale_factor(1.0f)
    {

    m_frame.setTexture(&m_texture);
}

// -------------------------------------------------------------------
void Image::set_pos(sf::Vector2f const& pos) {

    m_pos = pos;
}

// -------------------------------------------------------------------
void Image::set_origin(sf::Vector2f const& origin) {

    m_frame.setOrigin(origin);
}

// -------------------------------------------------------------------
Widget_type Image::is() const {

    return Widget_type::Image;
}

// -------------------------------------------------------------------
void Image::draw() {

    if (m_state == State::Hidden) {

        return;
    }

    // Apply size and scaling
    m_apply_size_and_scale();

    // Position + any movement offset
    m_frame.setPosition(m_pos);
    m_frame.move(m_delta_offset);

    // Rotation
    m_frame.setRotation(m_rotation);

    // Finally draw the image
    m_render_window->draw(m_frame);
}

// -------------------------------------------------------------------
void Image::set_image(sf::Texture const& image_texture) {

    m_texture = image_texture;
}

// -------------------------------------------------------------------
sf::Texture Image::get_image() const {

    return m_texture;
}

// -------------------------------------------------------------------
void Image::set_size(sf::Vector2f const& size) {

    m_size = size;
}

// -------------------------------------------------------------------
sf::Vector2f Image::get_size() const {

    return m_size;
}

// -------------------------------------------------------------------
void Image::set_scale(float const factor) {

    m_scale_factor = factor;
}

// -------------------------------------------------------------------
float Image::get_scale() const {

    return m_scale_factor;
}

// -------------------------------------------------------------------
void Image::set_num_vertices(unsigned int const num_vertices) {

    if (num_vertices < 0u) {

        LOG(Log_lvl::WARNING) <<
            "Could not set shape number of vertices: " <<
            num_vertices <<
            " < 3";

        return;
    } else {

        m_num_vertices    = num_vertices;
        auto const points = m_calculate_shape(m_num_vertices);

        m_frame = Image_frame(points);
        m_frame.setTexture(&m_texture);
    }
}

// -------------------------------------------------------------------
unsigned int Image::get_num_vertices() const {

    return m_num_vertices;
}

// -------------------------------------------------------------------
void Image::hide(bool const is_hidden) {

    if (is_hidden) { m_state = State::Hidden;  LOG(Log_lvl::TRACE) << "Image state change: Hidden";  }
    else           { m_state = State::Visible; LOG(Log_lvl::TRACE) << "Image state change: Visible"; }
}

// -------------------------------------------------------------------
bool Image::is_hidden() const {

    if (m_state == State::Hidden) { return true;  }
    else                          { return false; }
}

// -------------------------------------------------------------------
void Image::set_border_thickness(float const thickness) {

    m_frame.setOutlineThickness(thickness);
}

// -------------------------------------------------------------------
float Image::get_border_thickness() const {

    return m_frame.getOutlineThickness();
}

// -------------------------------------------------------------------
void Image::set_border_color(sf::Color const& color) {

    m_frame.setOutlineColor(color);
}

// -------------------------------------------------------------------
sf::Color Image::get_border_color() const {

    return m_frame.getOutlineColor();
}

// -------------------------------------------------------------------
void Image::set_color_filter(sf::Color const& color) {

    m_frame.setFillColor(color);
}

// -------------------------------------------------------------------
sf::Color Image::get_color_filter() const {

    return m_frame.getFillColor();
}

// -------------------------------------------------------------------
sf::FloatRect Image::get_local_bounds () const {

    return m_frame.getLocalBounds();
}

// -------------------------------------------------------------------
sf::FloatRect Image::get_global_bounds() const {

    return m_frame.getGlobalBounds();
}

// -------------------------------------------------------------------
void Image::set_rotation(sf::Angle const& angle) {

    m_rotation = angle;
}

// -------------------------------------------------------------------
sf::Angle Image::get_rotation() const {

    return m_rotation;
}

// -------------------------------------------------------------------
void Image::rotate(sf::Angle const& angle) {

    m_rotation += angle;
}

// -------------------------------------------------------------------
void Image::move(sf::Vector2f const& delta_offset) {

    m_delta_offset += delta_offset;
}

// -------------------------------------------------------------------
void Image::m_apply_size_and_scale() {

    // Get current (unscaled) local bounds
    sf::FloatRect const local = m_frame.getLocalBounds();
    float         const cur_x = local.size.x;
    float         const cur_y = local.size.y;

    // Desired size is m_size. local.x/y are in same units
    float const scale_x = (m_size.x / cur_x) * m_scale_factor;
    float const scale_y = (m_size.y / cur_y) * m_scale_factor;

    // Apply scaling
    m_frame.setScale({scale_x, scale_y});
}

// -------------------------------------------------------------------
std::vector<sf::Vector2f> Image::m_calculate_shape(unsigned int num_vertices) {

    // The "perfect" shape is a circle but of course we cant get perfect
    // circle, so we will approximate a circle using num_vertices to
    // approximate. This result will be a num_vertices-polygon.
    // (unit circle so no radius).

    // Check if we can actually create a shape
    if (num_vertices < 3) {

        LOG(Log_lvl::WARNING) <<
            "Could not create shape with vertices: " <<
            num_vertices <<
            " < 3";

        // Use default number of vertices
        num_vertices = DEFAULT_SHAPE_NUM_VERTICES;
    }

    // Reserve space for our points
    std::vector<sf::Vector2f> points{};
    points.reserve(num_vertices);

    float const step  = static_cast<float>(2.0f * PI / static_cast<float>(num_vertices));  // angle_step = 2*pi / num_vertices
    float const start = static_cast<float>(PI / 4.0f                                   );  // start at right side

    for (unsigned i = 0; i < num_vertices; ++i) {

        // theta = start + i * step
        float const theta = start + static_cast<float>(i) * step;

        points.emplace_back(static_cast<float>(std::cos(theta)),  // x = cos(theta)
                            static_cast<float>(std::sin(theta))); // y = sin(theta)
    }

    return points;
}

} // tiny_tanks::widget
