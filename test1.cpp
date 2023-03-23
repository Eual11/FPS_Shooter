#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gTestSurface = NULL;

int init(void);
void close_prog(void);
SDL_Surface *load_image(char *filepath);

int main(int argc, char **argv)
{
    SDL_Surface *RedSurface = NULL;
    SDL_Surface *GreenSurface = NULL;
    SDL_Surface *BlueSurface = NULL;
   
    if(init()<0)
    {
        printf("cannot initialize\n");

        return 1;
    }
    
    char s[] = "./assets/img/src_img_aki.png";
    gTestSurface = load_image(s);
     RedSurface = load_image("assets/img/red.bmp");
    BlueSurface = load_image("assets/img/blue.bmp");
    GreenSurface = load_image("assets/img/green.bmp");

    if(!gTestSurface)
    {
        printf("cannot load bitmap\n %s",SDL_GetError());

        return 1;
    }

    // SDL_BlitSurface(gTestSurface,NULL,gScreenSurface,NULL);
    SDL_Rect dstrect;
    dstrect.x =0;
    dstrect.y=0;
    dstrect.w = SCREEN_WIDTH;
    dstrect.h = SCREEN_HEIGHT;
    SDL_BlitScaled(gTestSurface,NULL,gScreenSurface,&dstrect);
    SDL_UpdateWindowSurface(gWindow);
    SDL_Event e;
    bool running = true;
    while(running)
    {
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
                        case SDLK_r:
                        {
                            // SDL_BlitSurface(RedSurface,NULL,gScreenSurface,NULL);
                            SDL_BlitScaled(RedSurface,NULL,gScreenSurface,&dstrect);
                            
                            break;
                        }
                        case SDLK_b:
                        {
                            SDL_BlitScaled(BlueSurface,NULL,gScreenSurface,&dstrect);

                            break;

                        }
                        case SDLK_g:
                        {
                            SDL_BlitScaled(GreenSurface,NULL,gScreenSurface,&dstrect);


                            break;
                        }
                        case SDLK_a:
                        {
    SDL_BlitScaled(gTestSurface,NULL,gScreenSurface,&dstrect);
                          
                            break;

                        }
                    }

                    break;
                }
            }
        }
        SDL_UpdateWindowSurface(gWindow);
    }

    SDL_FreeSurface(gTestSurface);
    close_prog();

    return 0;

}

int init(void)
{
    //initilizes the window
    //returns a less than zero value if error occurs
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        return -1;
    }

    gWindow = SDL_CreateWindow("?",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

    if(gWindow == NULL)
    {
        printf("%s\n",SDL_GetError());
        return -2;

    }

    int imgflags = IMG_INIT_PNG;

    // if(!(IMG_Init(imgflags) & imgflags))
    // {
    //     printf("couldn't initialize img\n");
    //     return -3;
    // }
    gScreenSurface = SDL_GetWindowSurface(gWindow);



    return 0;
}
void close_prog(void)
{
    //close the program and frees the window

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    SDL_Quit();

}
SDL_Surface *load_image(char *filepath)
{
    //The final optimized image
    SDL_Surface *tmp_surface = NULL;
    tmp_surface = IMG_Load(filepath);

    SDL_Surface *optimized_surface = NULL;

    optimized_surface = SDL_ConvertSurface(tmp_surface,gScreenSurface->format,0);

    SDL_FreeSurface(tmp_surface);
    return optimized_surface;
    }
