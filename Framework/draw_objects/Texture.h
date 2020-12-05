#ifndef GRAPHICALFRAMEWORK_TEXTURE_H
#define GRAPHICALFRAMEWORK_TEXTURE_H


#include <string>

class Texture {
    unsigned int texture_id_ = -1;

    int width_ = 0, height_ = 0, channels_count_ = 0;
    std::string image_file_;

public:
    explicit Texture(std::string  image_file);

    void Create();

    unsigned int get_id() const;
};


#endif //GRAPHICALFRAMEWORK_TEXTURE_H
