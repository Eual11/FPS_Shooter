#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
//initializaer for window and screen surface
int init(void);
//frees surfaces and closes he window

//loads an image into a surface
SDL_Surface *Load_Image(char *filepath);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
void close()
{
	//Free loaded image

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
int main(int argc, char **argv)
{
    printf("%s running with %d args\n",*argv,argc);

int c;
    if((c=init())<0)
    {
        printf("couldn't initialize\n\n, %d",c);
        return -1;
    }
    SDL_Surface *sImgSurface = NULL;
    sImgSurface = Load_Image("./assets/img/src_img_aki.png");

    if(!sImgSurface) 
    {
        printf("couldn't load img\n");
        return -1;

    }

    bool running = true;
    SDL_Event e;
    /* u sure u do love me*/
    SDL_Rect dsrect;
    dsrect.x =0;
    dsrect.y =0;
    dsrect.w =SCREEN_WIDTH;
    dsrect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(sImgSurface,NULL,gScreenSurface,&dsrect);
    SDL_UpdateWindowSurface(gWindow);
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                {
                    running =false;
                    break;
                }
            }  
        }
    }
    SDL_FreeSurface(gScreenSurface);
    close();
    return 0;
}


int init(void)
{
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        return -1;
    }

    gWindow=SDL_CreateWindow("Test_3",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(!gWindow)
    {
        printf("%s\n",SDL_GetError());
        return -2;
    }

    int imgflags = IMG_INIT_PNG;

    if(!(IMG_Init(imgflags) &imgflags))
    {
        return -1;
    }

    gScreenSurface= SDL_GetWindowSurface(gWindow);

    return 0;


}



SDL_Surface *Load_Image(char *filepath)
{
    SDL_Surface *tmp_surface =NULL;

    tmp_surface = IMG_Load(filepath);

    SDL_Surface *optimaized_surface = SDL_ConvertSurface(tmp_surface,gScreenSurface->format,0);

    SDL_FreeSurface(tmp_surface);

    tmp_surface = NULL;

    return optimaized_surface;

}
void clsoe_prog(void)
{
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}