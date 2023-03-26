#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define PI M_PI
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT  24
int w = SCREEN_WIDTH;
int h = SCREEN_HEIGHT;
int gWorldMap[MAP_WIDTH][MAP_HEIGHT] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};
SDL_Window *gWindow=NULL;
SDL_Texture *gTexture=NULL;
SDL_Renderer *gRenderer =NULL;
int nRectH =20;
int nPlayerWidth =10;
int nPlayerHeight =10;
double fPosX = 13;
double fPosY = 12;
double fDirX =1;
double fDirY =0;
double fPlaneX = 0;
double fPlaneY = 1;
double fAngle =0;
clock_t OldTime =0;
clock_t Time =0;
int nRectW=20;
int xOffset = 60;
int init(void);
void close(void);
void logerr(void);
double fFov = PI/2;
int main(int argc, char **argv)
{
    init();
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2" );
    bool running = true;
    SDL_Event e;
    SDL_FRect Player;
    Player.x = xOffset+fPosX*nRectW;
    Player.y = fPosY* nRectH;
    Player.w = nPlayerWidth;
    Player.h = nPlayerHeight;
    while(running)
    {
        //RenderPlayer  
    
    //Render Player
    SDL_SetRenderDrawColor(gRenderer,0,0XFF,0,0XFF);

    // for(int x=0; x <w;++x)
    // {
    //     //casting time
    //     double fCamera = 2*x/(double)(w)-1;
    //     double fRayDirX = fPosX+fPlaneX*fCamera;
    //     double fRayDirY = fPosY+fPlaneY*fCamera;

    //     int nMapX = (int)(fPosX);
    //     int nMapY = (int)(fPosY);
    //     int side;
    //     int hit=0;
    //     double fDeltaX;
    //     double fDeltaY;

    //     fDeltaX = fRayDirX==0? 1e30: fabs(1/fRayDirX);
    //     fDeltaY = fRayDirY==0? 1e30: fabs(1/fRayDirY);


    //     int nStepX;
    //     int nStepY;
    //     double fSideDeltaX;
    //     double fSideDeltaY;

    //     if(fRayDirX>0)
    //     {
    //         nStepX =1;
    //         fSideDeltaX = (nMapX+1-fPosX)*fDeltaX;

    //     }
    //     else
    //     {
    //         nStepX =-1;
    //         fSideDeltaX = (fPosX-nMapX)*fDeltaX;
    //     }
        
    //     if(fRayDirY>0)
    //     {
    //         nStepY =1;
    //         fSideDeltaY = (nMapY+1-fPosY)*fDeltaY;
    //     }
    //     else
    //     {
    //         nStepY =-1;
    //         fSideDeltaY = (fPosY-nMapY)*fDeltaY;
    //     }

        

    //     while (!hit)
    //     {
    //         if(fSideDeltaX<fSideDeltaY)
    //         {
    //             nMapX+=nStepX;
    //             fSideDeltaX+=fDeltaX;
    //             side =0;
    //         }
    //         else
    //         {
    //             nMapY+=nStepY;
    //             fSideDeltaY+=fDeltaY;
    //             side =1;
    //         }


    //         nMapX=nMapX<0?0:nMapX;
    //         nMapY=nMapY<0?0:nMapY;
    //         nMapX=nMapX>=MAP_WIDTH-1? MAP_WIDTH-1: nMapX;
    //         nMapY=nMapY >= MAP_HEIGHT-1? MAP_HEIGHT-1: nMapY;
    //         if(gWorldMap[nMapX][nMapY]) 
    //         {
    //         hit = 1;    
    //         }

    //     }
    //     double fLineEndX;
    //     double fLineEndY;
        
    //     fLineEndX = Player.x+(fSideDeltaX-fDeltaX)*SCREEN_WIDTH;
    //     fLineEndY = Player.y+(fSideDeltaY-fDeltaY)*SCREEN_HEIGHT;

    //     SDL_RenderDrawLineF(gRenderer,Player.x,Player.y,fLineEndX,fLineEndY);
    // }

    fPosX = Player.x+(Player.w/2);
    fPosY = Player.y+(Player.h/2);
    double fMinFov = -fFov/2;
    double fMaxFov = fFov/2;
    double theta_spacing = 0.30719;
    double l =10;//(fPosY/nRectH) -MAP_HEIGHT;
    double fLineEndX;
    double fLineEndY;
    for(double theta = fMinFov;theta<=fMaxFov;theta+=theta_spacing)
    {
        // while(true)
        {
            fLineEndX = cos(theta)*l;
        fLineEndY = sin(theta)*l;

        double tLineEndX = fLineEndX;
        double tLineEndY = fLineEndY;

        fLineEndX = fLineEndX*cos(fAngle)- fLineEndY*sin(fAngle);
        fLineEndY = tLineEndX*sin(fAngle)+fLineEndY*cos(fAngle);
        int nMapX = ((fPosX)/nRectW+fLineEndX);
        int nMapY = ((fPosY)/nRectH+fLineEndY);

        // if(gWorldMap[nMapX][nMapY]) 
        // {
        //    break;
        // }
        // l+=0.41;      

        }
        // printf("theta: %f, fLIneEndX: %f, fLineEndY: %f, L :%f\n",theta,fLineEndX,fLineEndY,l);
        SDL_RenderDrawLineF(gRenderer,fPosX,fPosY,fPosX+(fLineEndX)*nRectW,fPosY+fLineEndY*nRectH);
    }
    SDL_SetRenderDrawColor(gRenderer,0xFF,0,0,0XFF);
    SDL_RenderFillRectF(gRenderer,&Player);


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

                    switch(e.key.keysym.sym)
                    {
                        case SDLK_w:
                        {
                           Player.y-=0.5;
                           break;
                        }
                        case SDLK_s:
                        {
                           Player.y+=0.5;
                           break;
                            
                        }
                        case SDLK_a:
                        {
                            fAngle-=0.0174533*2;
                            break;
                        }
                           case SDLK_d:
                        {
                            fAngle+=0.0174533*2;
                            break;
                        }
                        
                    }
                    break;
                }
            }
        }

        


        SDL_SetRenderDrawColor(gRenderer,0XFF,0XFF,0XFF,0XFF);
        for(int x=0; x <MAP_WIDTH;x++)
        {
            for(int y=0; y<MAP_HEIGHT;y++)
            {
                if(gWorldMap[x][y])
                {
                    SDL_Rect Wall;
                    Wall.x = xOffset+x*nRectW;
                    Wall.y= y*nRectH;
                    Wall.w = nRectW;
                    Wall.h = nRectH;
                    SDL_RenderFillRect(gRenderer,&Wall);


                }
                    
            }
        }
        
        SDL_RenderPresent(gRenderer);
        
        SDL_SetRenderDrawColor(gRenderer,0,0,0,0);
        
        SDL_RenderClear(gRenderer);

    }
    close();
    return 0;
}

int init(void)
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Test 5",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

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