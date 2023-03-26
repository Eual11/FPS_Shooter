#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

#define sw 640
#define sh 480
#define  mw 24
#define mh 24

const int SCREEN_WIDTH = sw;
const int SCREEN_HEIGHT = sh;
SDL_Window *gWindow = NULL;
SDL_Texture *gTexture = NULL;
SDL_Renderer *gRenderer = NULL;

int gMap[mw*mh]={
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
            


};
int init(void);
void close(void);

int main(int argc, char **argv)
{


    init();

    int nWallW = 20;
    int nWallH = 20;
    int nPlW = 10;
    int nPlH = 10;
    float fPosX = 16;
    float fPosY = 27;
    int xOffset = 10;
    double fFov = 2*M_PI;
    double fAngle=0;
    SDL_FRect Player;
    Player.x = nPlW*fPosX;
    Player.y = nPlH*fPosY;
    Player.w  = nPlW;
    Player.h = nPlH;
    
    
    bool running = true;



    SDL_Event e;

    while(running)
    {

        double fMinFov = -fFov/2;
        double fMaxFov = fFov/2;
        double fSpacing = 0.009;
        double l = 0;
        double theta=0;
        SDL_SetRenderDrawColor(gRenderer,0xff,0xFF,0xff,0xff);
        for(double theta = fMinFov; theta<fMaxFov;theta+=fSpacing)
        {
        double l = 0;

            double fLineStartX = Player.x+(Player.w/2);
            double fLineStartY = Player.y+(Player.h/2);
            double fLineEndX = cos(theta)*l*nWallW;
            double fLineEndY =sin(theta)*l*nWallH;

//////////////////////////////////////////////////////////////
            while(true)
            {
            fLineEndX = cos(theta)*l*nWallW;
            fLineEndY =sin(theta)*l*nWallH;
            double tLineEndX = fLineEndX;
            fLineEndX = fLineStartX+(fLineEndX*cos(fAngle)- fLineEndY*sin(fAngle));
            fLineEndY = fLineStartY+(tLineEndX*sin(fAngle)+fLineEndY*cos(fAngle));

            int nMapX = (int)fLineEndX/nWallW;
            int nMapY = (int)fLineEndY/nWallH;
             nMapX= nMapX<0?0:nMapX;
             nMapY= nMapY<0?0:nMapY;
             nMapX = nMapX>sw-1?sw-1:nMapX;
             nMapY = nMapY>sw-1?sw-1:nMapY;

             
                if(gMap[nMapX+(mw*nMapY)])
                {
                    break;
                }
                l+=0.1;
            }
            SDL_RenderDrawLineF(gRenderer,fLineStartX,fLineStartY,fLineEndX,fLineEndY);
            
        }
        
       while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                {
                    running = false;

                    break;
                }
                case SDL_KEYDOWN:
                {
                    switch (e.key.keysym.sym)
                    {
                        case SDLK_w:
                        {
                            Player.y-=1.9;
                             

                            break;
                        }
                        case SDLK_s:
                        {
                            Player.y+=1.9;
                             

                            break;
                        }
                         case SDLK_a:
                        {
                            Player.x-=1.9;
                           
                            break;
                        }
                         case SDLK_d:
                        {
                            Player.x+=1.9;
                            
                            break;
                        }
                        case SDLK_LEFT:
                        {
                            fAngle+=0.1;
                            break;
                        }
                        case SDLK_RIGHT:
                        {
                            fAngle+=0.1;
                            break;
                        }
                    }
                    break;
                }

            }
        }
        SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0xff,0xff);
        for(int i=0; i <(mw*mh); i++)
        {
            int x = i%mw;
            int y = i/mw; //origin is top left

            if(gMap[i])
            {
            SDL_FRect Wall; 
            Wall.w = nWallW;
            Wall.h = nWallH;
            Wall.x = nWallH*x;
            Wall.y = nWallH*y;

            SDL_RenderFillRectF(gRenderer,&Wall);
            }

        }
        SDL_SetRenderDrawColor(gRenderer,0xFF,0,0,0XFF);
    SDL_RenderFillRectF(gRenderer,&Player);




       
        SDL_RenderPresent(gRenderer);
         SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
        SDL_RenderClear(gRenderer);

    }

    close();
    return 0;
}


int init(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Test 6",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    // gScreenSurface = SDL_GetWindowSurface(gWindow);

    gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    gTexture = SDL_CreateTexture(gRenderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH,SCREEN_HEIGHT);
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