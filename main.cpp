#include <iostream>
#include <fstream>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#if __EMSCRIPTEN__
#include <emscripten/bind.h>
#include <emscripten/val.h>
#endif

unsigned char *image_vector;
int width;
int height;
int channels;
unsigned char *img;
stbi__context s;
void isitup(){
    std::cout << "si" << std::endl;
}

int get_raw_ptr()
{
    return (int)image_vector;
}

int get_width()
{
    return width;
}

int get_height()
{
    return height;
}

int get_num_channels()
{
    return channels;
}

int get_size(){
    return width * height * 4;
}

void read_file(std::string input_image_path)
{
    // load image

    unsigned char *img = stbi_load(input_image_path.c_str(), &width, &height, &channels, 0);

    unsigned bytePerPixel = channels;
    int i=0;
    int j=0;
    int x=0;
    unsigned char *pixelOffset = img + (i + x * j) * bytePerPixel;
    //std::vector<unsigned char> buf(*s.img_buffer, *s.img_buffer_end);
    image_vector = pixelOffset;
}

#if __EMSCRIPTEN__
int main(int argc, char* argv[]){
    std::cout << "shared memory cpp has loaded" << std::endl;
    return 0;
}
#else
int main(int argc, char *argv[])
{
    if(argc < 3){
        std::cout << "usage: ./a.out path/to/image.png path/to/output.file" << std::endl;
        exit(1);
    }

    std::string input_path = std::string(argv[1]);
    std::cout << "input_path: " << input_path << std::endl;

    std::string output_path = std::string(argv[2]);
    std::cout << "output_path: " << output_path << std::endl;

    read_file(input_path);
    //std::cout << "size: " << get_size() << std::endl;

}

#endif

#if __EMSCRIPTEN__
EMSCRIPTEN_BINDINGS(shared_memory){
    emscripten::function("isitup", &isitup);
    emscripten::function("read_file", &read_file);
    emscripten::function("get_raw_ptr", &get_raw_ptr);
    emscripten::function("get_width", &get_width);
    emscripten::function("get_height", &get_height);
    emscripten::function("get_size", &get_size);
    emscripten::function("get_num_channels", &get_num_channels);
    emscripten::register_vector<unsigned char>("vector<unsigned char>");
}
#endif
