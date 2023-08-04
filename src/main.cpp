#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>

int main() {
    // Initialize SDL2 with the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Set the hint to enable headless rendering (no window)
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

    // Create a virtual window (1x1 pixel)
    SDL_Window* window = SDL_CreateWindow(
        "Headless Rendering",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        100,
        100,
        SDL_WINDOW_HIDDEN
    );

    if (window == nullptr) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a virtual renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture to render to
    int width = 100;
    int height = 100;
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return -1;
    }

    // Set the texture as the target for rendering
    SDL_SetRenderTarget(renderer, texture);

    // Set the rendering draw color (red: 255, green: 0, blue: 0)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Clear the renderer with the specified color
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // Draw a filled triangle using SDL_RenderDrawLine (3 lines to form the triangle)
    SDL_RenderDrawLine(renderer, 10, 10, 50, 100);
    SDL_RenderDrawLine(renderer, 50, 100, 100, 10);
    SDL_RenderDrawLine(renderer, 100, 10, 10, 10);

    // Save the rendering output to an image file (PNG format)
    SDL_RenderPresent(renderer);
    
    Uint32* pixels = (Uint32*)malloc(width * height * sizeof(Uint32));
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888, pixels, width * sizeof(Uint32));

    // Save the pixel data to an image using STB Image (PNG format in this example)
    int result = stbi_write_png("output.png", width, height, 4, pixels, width * sizeof(Uint32));

    // Check if the image was saved successfully
    if (result == 0) {
        //SDL_Log("Failed to save image: %s", stbi_failure_reason());
    }
    else {
        SDL_Log("Image saved successfully.");
    }

    // Cleanup and exit
    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
