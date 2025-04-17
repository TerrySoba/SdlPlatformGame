#include "platform/sdl/sound_controller_sdl.h"
#include "platform/sdl/music_controller_sdl.h"
#include "framebuffer_gfx.h"
#include "shared_ptr.h"
#include "i18n.h"
#include "game.h"
#include "credits_scroller.h"
#include "exception.h"
#include "sdl_gfx.h"

#include <SDL3/SDL.h>

#include <iostream>
#include <memory>
#include <cmath>

class GameWrapper {
public:
    GameWrapper(std::shared_ptr<SDL_Texture> renderTexture) :
        m_renderTexture(renderTexture)
    {
        tnd::shared_ptr<SoundController> sound(new SoundControllerSdl());

        I18N::loadTranslations("strings.en");
        
        m_gfx.reset(new FramebufferGfx());
        // Keyboard keyboard;
    
        GameExitCode exitCode = GAME_EXIT_QUIT;
        {
            tnd::shared_ptr<Animation> enemy(new Animation("enemy.ani", "enemy.tga"));
            tnd::shared_ptr<Animation> seekerEnemy(new Animation("enemy2.ani", "enemy2.tga"));
            tnd::shared_ptr<Animation> guffin(new Animation("guffin.ani", "guffin.tga"));
            tnd::shared_ptr<Animation> guy(new Animation("guy.ani", "guy.tga"));
            tnd::shared_ptr<Animation> fireBall(new Animation("fire.ani", "fire.tga"));
            tnd::shared_ptr<Animation> jetPack(new Animation("jet.ani", "jet.tga"));
            tnd::shared_ptr<Animation> tentacle(new Animation("tentacle.ani", "tentacle.tga"));
            tnd::shared_ptr<Animation> projectile(new Animation("bullet.ani", "bullet.tga"));
            tnd::shared_ptr<Animation> tentacleArm(new Animation("ten_arm.ani", "ten_arm.tga"));
            tnd::shared_ptr<Animation> eye(new Animation("eye.ani", "eye.tga"));

            tnd::shared_ptr<MusicController> music(new MusicControllerSdl());

            GameAnimations animations = {guy, enemy, seekerEnemy, guffin, fireBall, jetPack, tentacle, projectile, tentacleArm, eye};

            m_game.reset(new Game(m_gfx, sound, music, animations, "%02x%02x", LevelNumber(1,1)));
        }
    }

    void drawFrame() {
        // Call the game render function here
        m_game->drawFrame();

        // lock the texture
        void* pixels;
        int pitch;
        SDL_Rect rect = {0,0,320,200};
        SDL_LockTexture(m_renderTexture.get(), NULL, &pixels, &pitch);

        m_gfx->renderToMemory(pixels, pitch, PixelFormat::PIXEL_FORMAT_RGB888);

        // unlock the texture
        SDL_UnlockTexture(m_renderTexture.get());

    }

    uint32_t getFrameCount() const {
        return m_game->getFrameCount();
    }

private:
    tnd::shared_ptr<SDL_Texture> m_renderTexture;
    tnd::shared_ptr<Game> m_game;
    tnd::shared_ptr<GfxOutput> m_gfx;
};

int runGame() {
    uint32_t frameCounter = 0;

    try
    {
        tnd::shared_ptr<SoundController> sound(new SoundControllerSdl());

     
        I18N::loadTranslations("strings.en");
        

        tnd::shared_ptr<GfxOutput> gfx(new FramebufferGfx());
        // Keyboard keyboard;
    
        GameExitCode exitCode = GAME_EXIT_QUIT;
        {
            tnd::shared_ptr<Animation> enemy(new Animation("enemy.ani", "enemy.tga"));
            tnd::shared_ptr<Animation> seekerEnemy(new Animation("enemy2.ani", "enemy2.tga"));
            tnd::shared_ptr<Animation> guffin(new Animation("guffin.ani", "guffin.tga"));
            tnd::shared_ptr<Animation> guy(new Animation("guy.ani", "guy.tga"));
            tnd::shared_ptr<Animation> fireBall(new Animation("fire.ani", "fire.tga"));
            tnd::shared_ptr<Animation> jetPack(new Animation("jet.ani", "jet.tga"));
            tnd::shared_ptr<Animation> tentacle(new Animation("tentacle.ani", "tentacle.tga"));
            tnd::shared_ptr<Animation> projectile(new Animation("bullet.ani", "bullet.tga"));
            tnd::shared_ptr<Animation> tentacleArm(new Animation("ten_arm.ani", "ten_arm.tga"));
            tnd::shared_ptr<Animation> eye(new Animation("eye.ani", "eye.tga"));

            tnd::shared_ptr<MusicController> music(new MusicControllerSdl());

            GameAnimations animations = {guy, enemy, seekerEnemy, guffin, fireBall, jetPack, tentacle, projectile, tentacleArm, eye};

            Game game(gfx, sound, music, animations, "%02x%02x", LevelNumber(1,1));

            // game.drawFrame();
            // gfx->saveAsTgaImage("test.tga");
           
            // exitCode = game.runGameLoop();
            // frameCounter = game.getFrameCount();
        }

        // if (exitCode == GAME_EXIT_CREDITS)
        // {
        //     runCredits(*gfx, "credits.txt");
        // }
        
    }
    catch(const Exception& e)
    {
        printStr("Exception: ");
        printStr(e.what());
        printStr("\r\nerrno: ");

        char buf[10];
        intToString(errno, 10, buf, 10);
        printStr(buf);
        printStr("\r\n");
        return 1;
    }
    catch(...)
    {
        printStr("Unknown exception.\r\n");
        return 1;
    }

    printStr(BUILD_DATE + TinyString("\r\n") + I18N::getString(3).c_str());
    printf("Frame count: %d\n", frameCounter);
    fflush(stdout);

    return 0;
}


int main() {
    try {
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

        SDL_SetRenderVSync(ren.get(), 1);

        std::shared_ptr<SDL_Surface> bmp(SDL_LoadBMP("example.bmp"), SDL_DestroySurface);
        if (!bmp) {
            std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }

        // std::shared_ptr<SDL_Texture> tex(SDL_CreateTextureFromSurface(ren.get(), bmp.get()), SDL_DestroyTexture);
        
        std::shared_ptr<SDL_Texture> tex(SDL_CreateTexture(ren.get(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 320, 200), SDL_DestroyTexture);
        if (!tex) {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return 1;
        }


        bool quit = false;
        SDL_Event e;


        GameWrapper gameWrapper(tex);

        while (!quit) {
            while (SDL_PollEvent(&e)) {
                switch (e.type) {
                    case SDL_EVENT_QUIT:
                        quit = true;
                        break;
                    case SDL_EVENT_KEY_DOWN:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }

            // get mouse position
            float x, y;
            SDL_GetMouseState(&x, &y);
            // std::cout << "Mouse position: " << x << ", " << y << std::endl;

            // draw the frame
            gameWrapper.drawFrame();


            SDL_RenderClear(ren.get());
            SDL_FRect dst = {roundf(x), roundf(y), 640, 480};
            SDL_RenderTexture(ren.get(), tex.get(), nullptr, &dst);
            SDL_RenderPresent(ren.get());
        }

    

        SDL_Quit();

        std::cout << "Goodbye, frames:" << gameWrapper.getFrameCount() << std::endl;


    }
    catch(const Exception& e)
    {
        printStr("Exception: ");
        printStr(e.what());
        printStr("\r\nerrno: ");

        char buf[10];
        intToString(errno, 10, buf, 10);
        printStr(buf);
        printStr("\r\n");
        return 1;
    }
    catch(...)
    {
        printStr("Unknown exception.\r\n");
        return 1;
    }


    return 0;
}
