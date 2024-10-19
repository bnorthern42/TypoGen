#include "render.hpp"
#include <cairo/cairo-ft.h>
#include <cairo/cairo.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

void renderTypography(const std::string& text, const std::string& fontPath, int fontSize, int width, int height, const std::string& filename)
{
    // Initialize Cairo
    cairo_surface_t* surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t* cr = cairo_create(surface);

    // Set background color (white)
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Load custom font if available
    if (!fontPath.empty()) {
        FT_Library ft;
        FT_Face face;
        if (FT_Init_FreeType(&ft)) {
            std::cerr << "Could not initialize FreeType library\n";
            return;
        }
        if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
            std::cerr << "Could not load font\n";
            return;
        }
        cairo_font_face_t* cairo_ft_face = cairo_ft_font_face_create_for_ft_face(face, 0);
        cairo_set_font_face(cr, cairo_ft_face);
    } else {
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL); // Default font
    }

    // Set font size and color
    cairo_set_font_size(cr, fontSize);
    cairo_set_source_rgb(cr, 0, 0, 0); // Black font color

    // Render the text
    cairo_move_to(cr, width / 4, height / 2);
    cairo_show_text(cr, text.c_str());

    // Save the image to file
    cairo_surface_write_to_png(surface, filename.c_str());

    // Cleanup
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}
