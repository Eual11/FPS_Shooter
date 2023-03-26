#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>

#define SCREEN_WIDTH 640 //screen width
#define SCREEN_HIGHT 480 //scree height in px
#define MAP_WIDTH 24 // the width of map in terms of squares
#define MAP_HEIGHT  24// the height of the map in terms of squares
int init(void);
void close(void);
void logerr(void);
uint32_t pixel[SCREEN_HIGHT*SCREEN_WIDTH]; //texture to draw too
void drawpixel(int x, int y,uint32_t col);
int w = SCREEN_WIDTH;
int h = SCREEN_HIGHT;
int gWorldMap[MAP_WIDTH][MAP_HEIGHT] = {
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
}; //our map


SDL_Window *gWindow = NULL;

SDL_Surface *gScreenSurface = NULL;
SDL_Texture *gTexture= NULL;
SDL_Renderer *gRenderer = NULL;

static void verlines(int x,int y0,int y1,uint32_t col)
{
    x = x<SCREEN_WIDTH-1?x:SCREEN_WIDTH;
    for(int y=y0;y<y1;y++)
    {
        pixel[x+(SCREEN_WIDTH*y)] = col;
    }
}
static void horlines(int x0, int x1, int y, uint32_t col)
{
    y= y<SCREEN_HIGHT-1?y:SCREEN_HIGHT-1;
    for(int x=x0; x<x1;++x)
    {
        pixel[x+SCREEN_WIDTH*y] = col;
    }
}

int main(int argc, char **argv)
{
   
    init();
    SDL_SetRenderDrawColor(gRenderer,0x00,0x00,0x00,0x00);
    bool running = true;
    SDL_Event e;

    double fPosX = 12; //Xpos of the player in the map
    double fPosY = 5; //Yposition of the player in the map
    double fPlaneX = 0;
    double fPlaneY = 0.66;
    double fDirX = -1;
    double fDirY =0;
    clock_t time=0;
    clock_t oldtime=0;
    // verlines(100,0,SCREEN_HIGHT/2,0XFF0000FF);
    // verlines(0,SCREEN_HIGHT,100,0XFF0000FF);



    while(running)
    {
        for(int x=0; x<w;++x)
        {
            double fCamera = 2*x/(double(w))-1;
            double fRayDirX = fPosX+fPlaneX*fCamera;
            double fRayDirY = fPosY+fPlaneY*fCamera;

            int nMapX = int(fPosX);
            int nMapY = int(fPosY);

            int side;
            int hit =0;
            double fSideDeltaX;
            double fSideDeltaY;
            double fDeltaX = fRayDirX==0? 1e30: fabs(1/fRayDirX);

            double fDeltaY = fRayDirY==0? 1e30: fabs(1/fRayDirY);

            double fWallDist;

            int nStepX;
            int nStepY;

            if(fRayDirX >0)
            {
                nStepX =1;

                fSideDeltaX = (nMapX+1.0-fPosX)*fDeltaX;

            }
            else 
            {
                nStepX = -1;
                fSideDeltaX = (fPosX-nMapX)*fDeltaX;
            }

            if(fRayDirY >0)
            {
                nStepY=1;
                fSideDeltaY = (nMapY+1-fPosY)*fDeltaY;
            }
            else 
            {
                nStepY =-1;
                fSideDeltaY = (fPosY-nMapY)*fDeltaY;
            }

            //perform DDA
            while(!hit)
            {
                if(fSideDeltaX < fSideDeltaY)
                {
                    nMapX+=nStepX;
                    fSideDeltaX+=fDeltaX;
                    side =0;
                }
                else 
                {
                    nMapY+=nStepY;
                    fSideDeltaY+=fDeltaY;
                    side =1;
                }

                if(gWorldMap[nMapX][nMapY]) {
                    hit =1;
                }
            }

            if(side ==0)
            {
                fWallDist = fSideDeltaX-fDeltaX;
            }
            else 
            {
                fWallDist = fSideDeltaY-fDeltaY;
            }


            int nLineHeight = h/fWallDist;
            int nLineStart = -nLineHeight/2+h/2;
            if(nLineStart<0) {nLineStart =0;}

            int nLineEnd = nLineHeight/2+h/2;
            if(nLineEnd>=h)
            {
                nLineEnd = h-1;
            }
            // printf("line start: %d, line end: %d\n",nLineStart,nLineEnd);
            // printf("dist:%f \n",fWallDist);

            uint32_t color;

            switch(gWorldMap[nMapX][nMapY])
            {
                case 0:
                {
                    color = 0x00;
                    break;
                }
                case 1:
                {
                    color = 0xFF0000FF;
                    break;
                }
                case 2:
                {
                    color = 0x00FF00FF;
                    break;
                }
                case 4:
                {
                    color = 0x00FFFF;
                    break;
                }
             
            }
            verlines(x,nLineStart,nLineEnd,color);

        }

        oldtime = time;

        time = clock();

        double fFrameTime = (double)(time-oldtime)/CLOCKS_PER_SEC;
        // printf("%f time\n",fFrameTime);

        double fMoveSpeed = fFrameTime;
        double fRotSpeed = fFrameTime;



        while(SDL_PollEvent(&e))
        {
            switch (e.type)
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
                            printf("%f is sh\n",fMoveSpeed);
                            int nPosX =(int)fPosX;
                            int nPosY = (int)(fPosY+fDirY*fMoveSpeed);
                            nPosX= nPosX<0?0:nPosX;
                            nPosX= nPosX>=MAP_WIDTH?MAP_WIDTH-1:nPosX;

                            nPosY= nPosY<0?0:nPosY;
                            nPosY= nPosY>=MAP_WIDTH?MAP_HEIGHT-1:nPosY;
                           printf("%d\n",gWorldMap[nPosX][nPosY]);

                            if(gWorldMap[nPosX][nPosY]==0)
                            {
                                fPosY+=fPosY+fDirY*fMoveSpeed;
                            }
                            nPosX = (int)(fPosX+fDirX*fMoveSpeed);
                            nPosX= nPosX<0?0:nPosX;
                            nPosX= nPosX>=MAP_WIDTH?MAP_WIDTH-1:nPosX;

                            nPosY= nPosY<0?0:nPosY;
                            nPosY= nPosY>=MAP_WIDTH?MAP_HEIGHT-1:nPosY;
                           printf("%d\n",gWorldMap[nPosX][nPosY]);

                            if(gWorldMap[nPosX][nPosY]==0)
                            {
                                fPosX+=fPosX+fDirX*fMoveSpeed;

                            }
                            // printf("Dirx: %f, Diry: %f\n",fDirX,fDirY);


                            break;
                        }
                        case SDLK_s:
                        {
                            printf("%f is sh\n",fMoveSpeed);
                            int nPosX =(int)fPosX;
                            int nPosY = (int)(fPosY-fDirY*fMoveSpeed);
                            nPosX= nPosX<0?0:nPosX;
                            nPosX= nPosX>=MAP_WIDTH?MAP_WIDTH-1:nPosX;

                            nPosY= nPosY<0?0:nPosY;
                            nPosY= nPosY>=MAP_WIDTH?MAP_HEIGHT-1:nPosY;
                           printf("%d\n",gWorldMap[nPosX][nPosY]);

                            if(gWorldMap[nPosX][nPosY]==0)
                            {
                                fPosY-=fPosY+fDirY*fMoveSpeed;
                            }
                            nPosX = (int)(fPosX-fDirX*fMoveSpeed);
                            nPosX= nPosX<0?0:nPosX;
                            nPosX= nPosX>=MAP_WIDTH?MAP_WIDTH-1:nPosX;

                            nPosY= nPosY<0?0:nPosY;
                            nPosY= nPosY>=MAP_WIDTH?MAP_HEIGHT-1:nPosY;
                           printf("%d x: %d y: %d\n",gWorldMap[nPosX][nPosY],nPosX,nPosY);

                            if(gWorldMap[nPosX][nPosY])
                            {
                                fPosX-=fPosX+fDirX*fMoveSpeed;

                            }
                            // printf("Dirx: %f, Diry: %f\n",fDirX,fDirY);


                            break;
                        }
                        case SDLK_d:{
                            double fOldDirX=fDirX;
                            fDirX = fDirX*cos(-fRotSpeed)-fDirY*sin(-fRotSpeed);
                            fDirY =fOldDirX*sin(-fRotSpeed)+fDirY*cos(-fRotSpeed);
                            double fOldPlaneX = fPlaneX;

                             fPlaneX = fPlaneX*cos(-fRotSpeed)-fPlaneY*sin(-fRotSpeed);
                            fPlaneX =fOldPlaneX*sin(-fRotSpeed)+fPlaneY*cos(-fRotSpeed);
                            // printf("Dirx: %f, Diry: %f\n",fDirX,fDirY);

                            
                            
                            break;
                        }
                           case SDLK_a:{
                            double fOldDirX=fDirX;
                            fDirX = fDirX*cos(fRotSpeed)-fDirY*sin(fRotSpeed);
                            fDirY =fOldDirX*sin(fRotSpeed)+fDirY*cos(fRotSpeed);
                            double fOldPlaneX = fPlaneX;

                             fPlaneX = fPlaneX*cos(fRotSpeed)-fPlaneY*sin(fRotSpeed);
                            fPlaneX =fOldPlaneX*sin(fRotSpeed)+fPlaneY*cos(fRotSpeed);
                            // printf("Dirx: %f, Diry: %f\n",fDirX,fDirY);
                            
                            
                            break;
                        }
 

                        
                    }
                    break;
                }
            }
        }
        SDL_UpdateTexture(gTexture,NULL,pixel,SCREEN_WIDTH*4);
        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer,gTexture,NULL,NULL);
        
        // SDL_RenderCopyEx(gRenderer,gTexture,NULL,NULL,0.0,NULL,SDL_FLIP_VERTICAL);
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