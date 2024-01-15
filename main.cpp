#include<bits/stdc++.h>
#include<math.h>
#include "include/SDL.h"
#include "include/SDL_ttf.h"

using namespace std;
int foodX;
int foodY;
int direction=1;
int score=0;
int rectenglex=100;
int rectengley=100;
vector<pair<int,int>>snakebody;
vector<pair<int,int>>snakebody1;
SDL_Event event;
SDL_Window* window=SDL_CreateWindow("Snake Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_SHOWN);
SDL_Renderer* renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
bool quit=false;
bool pause=false;

void foodpos()
{
    cout<<"score:"<<score++<<endl;
    foodX = rand() % (780 /10 ) * 10;
    foodY = rand() % (580 / 10) * 10;
    if(direction==1)
    {
         snakebody.push_back( make_pair(rectenglex+10,rectengley) );
    }
    else if(direction==2)
    {
         snakebody.push_back( make_pair(rectenglex-10,rectengley) );
    }
    else if(direction==3)
    {
         snakebody.push_back( make_pair(rectenglex,rectengley+10) );
    }
    else if(direction==4)
    {
         snakebody.push_back( make_pair(rectenglex,rectengley-10) );
    }
}
void DrawRect(int x, int y) {
    SDL_Rect rect = { x, y, 10, 10};
    SDL_RenderFillRect(renderer, &rect);
}
void nextdirection()
{ 
        switch (event.key.keysym.sym) 
                    {
                        case SDLK_LEFT:
                     { if(direction!=1)
                       direction=2;
                     break;}
                    case SDLK_RIGHT:
                    { if(direction!=2)
                      direction=1;
                        break;}
                        case SDLK_UP:
                          { if(direction!=3)
                          direction=4;
                          break;}
                    case SDLK_DOWN:
                        { if(direction!=4)
                        direction=3;
                        break;
                        
                    case SDLK_SPACE:
                        pause = !pause;
                        break;
                    }

    } }
    void Drawfood()
    {  
        int radius=10;
         while(radius--)
    for(int angle=0;angle<360;angle++)
    {
        int x=foodX+radius*cos(angle*M_PI/180);
         int y=foodY+radius*sin(angle*M_PI/180);
         SDL_RenderDrawPoint(renderer,x,y);}
    }
    void foodcollision()
    {
         if(((foodX-rectenglex)<=20&&(foodX-rectenglex)>=0)&&((rectengley-foodY)>=0&&(rectengley-foodY)<=10))
         foodpos();
  else if(((foodX-rectenglex)<=20&&(foodX-rectenglex)>=0)&&((foodY-rectengley)>=0&&(foodY-rectengley)<=20))
         foodpos();
  else if(((rectenglex-foodX)<=10&&(rectenglex-foodX)>=0)&&((foodY-rectengley)>=0&&(foodY-rectengley)<=20))
        foodpos();
   else if(((foodX-rectenglex)<=10&&(foodX-rectenglex)>=0)&&((foodY-rectengley)>=0&&(foodY-rectengley)<=20))
        foodpos();
    }
 void snakehead()
    {
       if(direction==1)
            { rectenglex+=10;
                if(rectenglex==800)
                rectenglex=10;}
   else if(direction==2)
   { rectenglex-=10;
   if(rectenglex==0)
   rectenglex=790;}
   else if(direction==3)
   { rectengley+=10;
   if(rectengley==600)
   rectengley=10;}
   else if(direction==4)
   { rectengley-=10;
   if(rectengley==0)
   rectengley=590;}
    }
  void movebody()
  {   snakehead();
    snakebody1=snakebody;
    snakebody[snakebody.size()-1].first=rectenglex;
    snakebody[snakebody.size()-1].second=rectengley;
    SDL_SetRenderDrawColor(renderer,0,200,50,255);
    DrawRect(snakebody[snakebody.size()-1].first, snakebody1[snakebody.size()-1].second);
    for(int i=snakebody.size()-1;i>0;i--)
    { snakebody[i-1]=snakebody1[i];
        DrawRect(snakebody[i].first,snakebody[i].second);
    }

  }
  void snakecollision()
     {
        for(int i=0;i<snakebody.size()-2;i++)
          {
               if(snakebody[i].first==rectenglex&&snakebody[i].second==rectengley)
               {  //SDL_SetRenderDrawColor(renderer,50,100,50,255);
                    //    SDL_RenderClear(renderer);
                 //SDL_RenderPresent(renderer);
                     SDL_Delay(2000);
                quit=true;
                  break;
               }
          }

     }

// Function to initialize SDL and SDL TTF, show score, and clean up
void showScore() {
    
    
    // Load font
    TTF_Font* font = TTF_OpenFont("Lato-Bold.ttf", 16);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Render score
    SDL_Color B = {0, 0, 255};

    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, B);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int x = 800/2-surface->w/2;
    int y = 600/2-surface->h/2;


    SDL_Rect destRect = {x, y, surface->w, surface->h};

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    return;
}

void gameOver() {
    
    SDL_SetRenderDrawColor(renderer,50,50,50,255);
    SDL_RenderClear(renderer);
    // Load font
    TTF_Font* font = TTF_OpenFont("Lato-Bold.ttf", 50);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Render score
    SDL_Color C = {0, 0, 0};

    char scoreText[20];
    sprintf(scoreText, "GAME OVER!");

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, C);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int x = 800/2-surface->w/2;
    int y = 600/2-surface->h/2;


    SDL_Rect destRect = {x, y, surface->w, surface->h};

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
    SDL_RenderPresent(renderer);
    cout<<"GAME OVER"<<endl;


    return;
}


int main(int argc,char* argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO)!=0)
    {
        cout<<"SDL_Init Error"<<endl;
        return 1;
    }

    TTF_Init();
 snakebody.push_back( make_pair(rectenglex,rectengley) );
 snakebody.push_back( make_pair(rectenglex+10,rectengley) );
 rectenglex+=10;
 foodpos();
while(quit!=true)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT)
        {
            quit=true;
        }
     else if(event.type == SDL_KEYDOWN) 
     nextdirection();
    }
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    showScore();
    SDL_SetRenderDrawColor(renderer,255,0,0,255);
    Drawfood();
    if (!pause) {
        foodcollision();
        movebody();
        snakecollision();
        if (quit) break;
        SDL_RenderPresent(renderer);
    }
          if(score<=10)
          SDL_Delay(70);
           else if(score>10&&score<=20)
          SDL_Delay(60);
          else if(score>20&&score<=30)
          SDL_Delay(50);
          else if(score>30&&score<=40)
          SDL_Delay(40);
          else
          SDL_Delay(30); 
}
 gameOver();
 SDL_Delay(3000);
 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 TTF_Quit();
 SDL_Quit();
 return 0;
 }