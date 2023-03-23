#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HIGHT 480

int init(void);
void close(void);
void logerr(void);
uint32_t pixel[SCREEN_HIGHT*SCREEN_WIDTH];
void drawpixel(int x, int y,uint32_t col);
SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;
SDL_Texture *gTexture= NULL;
SDL_Renderer *gRenderer = NULL;

static void verline(int x, uint32_t col)
{
    x = x<SCREEN_WIDTH-1?x:SCREEN_WIDTH-1;
    for(int y=0;y <SCREEN_HIGHT;y++)
    {
        pixel[x+(SCREEN_HIGHT*y)]=col;
    }

}


int main(int argc, char **argv)
{
    

    // randpts(SCREEN_WIDTH,SCREEN_HIGHT);
    init();
    verline(5,0xff0000ff);
    SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
    bool running = true;
    SDL_Event e;
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_QUIT:
                {
                    running = false;
                    break;
                }
            }
        }
        SDL_UpdateTexture(gTexture,NULL,pixel,SCREEN_WIDTH*4);
        SDL_RenderClear(gRenderer);

        // SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);
        
        SDL_RenderCopyEx(gRenderer,gTexture,NULL,NULL,0.0,NULL,SDL_FLIP_VERTICAL);
        SDL_RenderPresent(gRenderer);
        
    }
    close();
}


int init(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Test 5",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HIGHT,SDL_WINDOW_SHOWN);

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    gTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH,SCREEN_HIGHT);
    // gTexture = SDL_CreateTextureFromSurface(gRenderer,gScreenSurface);


    return 0;

}

void close(void)
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyTexture(gTexture);
    SDL_Quit();
}
void logerr(void)
{
    printf("%s at line %d",SDL_GetError(),__LINE__);
}
void randpts(int w, int h){
    for(int i =0; i <w; i++)
    {
       
            srand(i);
            int p = w*h*rand();
            pixel[p] = 0xff000000;
    }
}
void drawpixel(int x, int y,uint32_t col)
{
    int pt = y*SCREEN_HIGHT+(x);
    if(pt<(SCREEN_HIGHT*SCREEN_WIDTH))
    {
        pixel[pt] = col;
    }
}