#include <SDL3/SDL.h>

#include <iostream>
#include <memory>

int main() {
    std::cout << "Hello, World!" << std::endl;

    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_InitSubSystem Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::shared_ptr<SDL_Window> win(SDL_CreateWindow("Hello SDL", 1920, 1080, 0), SDL_DestroyWindow);
    if (!win) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::shared_ptr<SDL_Renderer> ren(SDL_CreateRenderer(win.get(), "vulkan"), SDL_DestroyRenderer);
    if (!ren) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::shared_ptr<SDL_Surface> bmp(SDL_LoadBMP("example.bmp"), SDL_DestroySurface);
    if (!bmp) {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::shared_ptr<SDL_Texture> tex(SDL_CreateTextureFromSurface(ren.get(), bmp.get()), SDL_DestroyTexture);
    if (!tex) {
        std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }


    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // get mouse position
        float x, y;
        SDL_GetMouseState(&x, &y);
        // std::cout << "Mouse position: " << x << ", " << y << std::endl;

        SDL_RenderClear(ren.get());
        SDL_FRect dst = {(int)x, (int)y, 128, 128};
        SDL_RenderTexture(ren.get(), tex.get(), nullptr, &dst);
        SDL_RenderPresent(ren.get());
    }

 

    SDL_Quit();


    return 0;
}
