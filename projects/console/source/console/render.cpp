/*
    This file gives definitions to global files(specifically those defined in text.h)
*/
#include "headers/text.h"

namespace console
{
}

namespace console
{
    namespace render
    {
        font* current_font = nullptr;

        abstractgl::program font_program;

        abstractgl::vertex_array font_vao;

        abstractgl::vertex_buffer font_vbo;

        glm::mat4 projection;
    }
} 