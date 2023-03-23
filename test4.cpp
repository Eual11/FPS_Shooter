#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Renderer *gRenderer = NULL;
int init(void);
SDL_Texture *Load_Texture(char *filepath);
void close_program(void);

int main(int argc, char **argv)
{
    int x;
    init();
    SDL_Texture *TestTexture = NULL;
    SDL_Texture *tRedTexture, *tGreenTexture, *tBlueTexture;
    tRedTexture = Load_Texture("./assets/img/red.bmp");
    tGreenTexture = Load_Texture("./assets/img/green.bmp");
    tBlueTexture = Load_Texture("./assets/img/foo.png");

    TestTexture = Load_Texture("./assets/img/src_img_aki.png");
    SDL_SetTextureColorMod(TestTexture,0xff,0,0);

    SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0xFF);

    bool running = true;
    SDL_Event e;
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                {
                    running =false;
                }
            }
        }
        SDL_RenderClear(gRenderer);
        SDL_Rect dstRect;
        dstRect.x = 0;
        dstRect.y=0;
        dstRect.w=SCREEN_WIDTH/2;
        dstRect.h = SCREEN_HEIGHT/2;
        SDL_RenderSetViewport(gRenderer,&dstRect);
        SDL_RenderCopy(gRenderer,TestTexture,&dstRect,NULL);

        //red
        dstRect.x =SCREEN_WIDTH/2;
        dstRect.y=0;
        dstRect.w=SCREEN_WIDTH/2;
        dstRect.h = SCREEN_HEIGHT/2;
        SDL_RenderSetViewport(gRenderer,&dstRect);
        SDL_RenderCopy(gRenderer,tRedTexture,NULL,NULL);
        //green
        dstRect.x =0;
        dstRect.y=SCREEN_HEIGHT/2;
        dstRect.w=SCREEN_WIDTH/2;
        dstRect.h = SCREEN_HEIGHT/2;
        SDL_RenderSetViewport(gRenderer,&dstRect);
        SDL_RenderCopy(gRenderer,tGreenTexture,NULL,NULL);
        //blue
        dstRect.x =0;
        dstRect.y=SCREEN_HEIGHT/2;
        dstRect.w=SCREEN_WIDTH/2;
        dstRect.h = SCREEN_HEIGHT/2;
        SDL_RenderSetViewport(gRenderer,&dstRect);
        SDL_RenderCopy(gRenderer,tBlueTexture,NULL,NULL);
        // SDL_RenderCopy()
        SDL_RenderPresent(gRenderer);
    }
    close_program();
    return 0;   
}

int init(void)
{
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        return -1;
    }

    gWindow = SDL_CreateWindow("Test3", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(!gWindow)
    {
        return -2;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);

    if(!gRenderer)
    {
        return -3;
    }

    IMG_Init(IMG_INIT_PNG);


    return 0;
}
void close_program(void)
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    IMG_Quit();
    SDL_Quit();
}
SDL_Texture *Load_Texture(char *filepath)
{
    SDL_Surface *tmp_surface = NULL;
    tmp_surface = IMG_Load(filepath);
    SDL_SetColorKey(tmp_surface,SDL_TRUE,SDL_MapRGB(tmp_surface->format,0x00,0xff,0xf0));
    SDL_Texture *tmp_texture = SDL_CreateTextureFromSurface(gRenderer,tmp_surface);
    SDL_FreeSurface(tmp_surface);
    return tmp_texture;
}