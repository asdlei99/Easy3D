/********************************************************************
 * Copyright (C) 2015 Liangliang Nan <liangliang.nan@gmail.com>
 * https://3d.bk.tudelft.nl/liangliang/
 *
 * This file is part of Easy3D. If it is useful in your research/work,
 * I would be grateful if you show your appreciation by citing it:
 * ------------------------------------------------------------------
 *      Liangliang Nan.
 *      Easy3D: a lightweight, easy-to-use, and efficient C++ library
 *      for processing and rendering 3D data.
 *      Journal of Open Source Software, 6(64), 3255, 2021.
 * ------------------------------------------------------------------
 *
 * Easy3D is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 3
 * as published by the Free Software Foundation.
 *
 * Easy3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 ********************************************************************/

#ifndef EASY3D_RENDERER_TEXT_RENDERER_H
#define EASY3D_RENDERER_TEXT_RENDERER_H

#include <vector>
#include <string>

#include <easy3d/core/types.h>


namespace easy3d {

    /**
     * \brief TextRenderer enables quick and easy string rendering in OpenGL applications.
     *
     * \class TextRenderer easy3d/renderer/text_renderer.h
     *
     * \details It supports truetype (TTF) fonts and Unicode strings. All glyphs are cached in OpenGL textures and
     *      font rasterization is done using 'stb_truetype.h.'
     *      TextRenderer allows you to:
     *          - switch between fonts;
     *          - change character spacing;
     *          - enable/disable kerning;
     * \todo For a large number of strings/characters, it is necessary to separate buffer creation and rendering.
     * \todo Performance evaluation.
     */
    class TextRenderer {
    public:
        /**
         * \brief Constructor.
         * \param dpi_scale The DPI scale factor.
         * \param texture_size The size of the font textures. Suggested values are 512, 1024, 2048 ...
         * \param mipmaps True to create mipmaps for the font textures.
         */
        explicit TextRenderer(float dpi_scale = 1.0f, int texture_size = 512, bool mipmaps = false);

        /**
         * Destructor.
         */
        ~TextRenderer();

        /**
         * \brief Add a font from a file. This function must be called at least once to add a font.
         * \param font_file The font file (.ttf, etc.).
         * \return True if the font was successfully added, false otherwise.
         */
        bool add_font(const std::string &font_file);

        /**
         * \brief The number of available fonts.
         * \return The number of available fonts.
         */
        std::size_t num_fonts() const { return font_ids_.size(); }

        /**
         * \brief The names of available fonts.
         * \return A const reference to the vector of font names.
         */
        const std::vector<std::string> &font_names() const { return font_names_; }

        /**
         * \brief Draw the text.
         * \param text The string to be drawn.
         * \param x The x-coordinate of the starting position, relative to the left edge of the content area.
         * \param y The y-coordinate of the starting position. If upper_left is true, this position is relative to the
         *        top edge of the content area. Otherwise, it is relative to the bottom edge of the content area.
         * \param font_size The font size.
         * \param font_id The id of the font used to draw the text, which is generated by calling to add_font(). 0 is
         *        the first font, 1 is the second, etc.
         * \param font_color The font color.
         * \param upper_left True to define the origin in the upper left corner of the content area. Otherwise, it is
         *        defined in the bottom left corner of the content area.
         * \return The end position of the x-coordinate. This allows you to draw another string after the previous one.
         *
         * \note This function will draw the text in one line and thus line breaks (i.e., "\n") will be ignored.
         */
        float draw(const std::string &text, float x, float y, float font_size,
                   int font_id = 0, const vec3 &font_color = vec3(0, 0, 0), bool upper_left = true
        ) const;


        // -------------------------------------------------------------------------------------------------------------
        // Multi-line text rendering

        /** \brief Horizontal alignment. **/
        enum Align {
            ALIGN_LEFT,     ///< Align text to the left.
            ALIGN_RIGHT,    ///< Align text to the right.
            ALIGN_CENTER    ///< Align text to the center.
        };

        /**
         * \brief Draw multi-line text with alignment support. This method produces line breaks for text with "\n".
         * \param text The string to be drawn.
         * \param x The x-coordinate of the starting position, relative to the left edge of the content area.
         * \param y The y-coordinate of the starting position. If upper_left is true, this position is relative to the
         *        top edge of the content area. Otherwise, it is relative to the bottom edge of the content area.
         * \param font_size The font size.
         * \param align Specifies how the lines are aligned.
         * \param font_id The id of the font used to draw the text, which is generated by calling to add_font(). 0 is
         *        the first font, 1 is the second, etc.
         * \param font_color The font color.
         * \param line_spacing The line spacing, which is a ratio relative to line height. A zero value means no extra
         *        space between lines.
         * \param upper_left True to define the origin in the upper left corner of the content area. Otherwise, it is
         *        defined in the bottom left corner of the content area.
         * \return The region occupied by the text.
         */
        Rect draw(const std::string &text, float x, float y, float font_size, Align align/* = ALIGN_LEFT*/,
                  int font_id = 0, const vec3 &font_color = vec3(0, 0, 0),
                  float line_spacing = 0.0f, bool upper_left = true
        ) const;

        // -------------------------------------------------------------------------------------------------------------

        /**
         * \brief Set the spacing between consecutive characters. The default character spacing is 0.
         * \param spacing The expected character spacing.
         */
        void set_character_spacing(float spacing);

        /**
         * \brief Query the spacing between consecutive characters.
         * \return The spacing between consecutive characters.
         */
        float character_spacing() const;

        /**
         * \brief Set kerning.
         * \param kerning The expected kerning behavior.
         */
        void set_kerning(bool kerning);

        /**
         * \brief Query the kerning behavior. Kerning is disabled by default.
         * \return The kerning behavior.
         */
        bool kerning() const;

        /**
         * \brief Query the height of the font.
         * \param font_size The font size.
         * \return The height of the font in pixels.
         */
        float font_height(float font_size) const;

        /**
         * \brief Query the width of a string (treated as if with no space between characters).
         * \details Useful to position a string. For example, with the string width, its X-center can be computed
         *      as: viewer_width * 0.5 - string_width * 0.5.
         * \param str The string to measure.
         * \param font_size The font size.
         * \return The width of the string in pixels.
         */
        float string_width(const std::string& str, float font_size) const;
        
        /**
         * \brief Query the height of a string.
         * \param str The string to measure.
         * \param font_size The font size.
         * \return The height of the string in pixels.
         */
        float string_height(const std::string& str, float font_size) const;
        
        /**
         * \brief Query the bounding rectangle of a string (treated as if with no space between characters).
         * \param str The string to measure.
         * \param x The x-coordinate of the starting position, relative to the left edge of the content area.
         * \param y The y-coordinate of the starting position, relative to the top edge of the content area.
         * \param font_size The font size.
         * \return The bounding rectangle of the string (in pixels).
         */
        Rect string_bounding_rect(const std::string& str, float x, float y, float font_size) const;

    private:

        void flush_draw(const vec3 &font_color) const;

        //if the text has newlines, it will be treated as if was called into drawing multiple lines
        Rect _get_bbox(const std::string &text, float size, float x, float y, Align align, float line_spacing) const;

    private:
        int texture_size_;
        void *stash_;
        std::vector<int> font_ids_;
        std::vector<std::string> font_names_;
    };

}

#endif  // EASY3D_RENDERER_TEXT_RENDERER_H
