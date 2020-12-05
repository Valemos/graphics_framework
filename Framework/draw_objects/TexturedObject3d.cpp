#include "TexturedObject3d.h"
#include "stb_image.h"


TexturedObject3d::TexturedObject3d(const Texture& texture,
                                   const glm::vec3 &edgeColor,
                                   const glm::vec3 &figureScale) :
        Object3D({0, 0, 0}, edgeColor, figureScale), texture_(nullptr) {
    texture_ = texture;
}

void TexturedObject3d::LoadGlObjectProperties(Renderer &renderer) const {
    static const auto is_textured_loc = glGetUniformLocation(renderer.get_shader_program(), "isTextured");
    glUniform1i(is_textured_loc, true);
    glBindTexture(GL_TEXTURE_2D, texture_.get_id());
}

void TexturedObject3d::InitGlBuffers() {
    glGenVertexArrays(1, &VAO_id);
    glBindVertexArray(VAO_id);

    //bind all additional buffers
    glGenBuffers(1, &object_buffer_id_);
    glBindBuffer(GL_ARRAY_BUFFER, object_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, object_buffer_.size() * sizeof(float), 0, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void TexturedObject3d::LoadGlBuffers() {
    glBindVertexArray(VAO_id);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER, object_buffer_id_);
    glBufferData(GL_ARRAY_BUFFER, object_buffer_.size() * sizeof(float), object_buffer_.data(), GL_STATIC_DRAW);
}
