#include<bits/stdc++.h>
#include<math.h>
#include "include/SDL.h"
#include "include/SDL_ttf.h"
#include "include/SDL_mixer.h"

#define W 900
#define H 600
#define GRID 15

using namespace std;

bool isRunning = true;
bool pause;
int score;
//int bcount=0;
int ls = -1;
int bonusTime;
bool fl=true;

typedef struct Snake {
    vector<pair<int, int>> snakebody;
    char direction;
     Uint32 bonusFoodStartTime;
} Snake;
Snake snake;

pair<int, int> food;
pair<int, int> bonusfood;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event e;
Mix_Chunk* wavFile;
Mix_Chunk* bonusSound;
//Mix_Chunk* bonusVanish;
Mix_Chunk* tata;

void foodpos()
{
    food.first = rand() % (W / GRID) * GRID;
    food.second = rand() % (H / GRID) * GRID;
}

void bonusfoodpos()
{
    bonusfood.first = rand() % (W / GRID) * GRID;
    bonusfood.second = rand() % (H / GRID) * GRID;

    snake.bonusFoodStartTime = SDL_GetTicks();

    //bonusTime=SDL_GetTicks();
   //bcount=0;

}

void initialize()
{

   /* bonusfood.first = -100;
    bonusfood.second = -100;
    */

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    pause=false;
    snake.snakebody.push_back(make_pair(0, 0));
    snake.snakebody.push_back(make_pair(10, 0));
    snake.direction = 'R';
    //rectenglex += 10;
    foodpos();
    score = 0;
    //bcount=0;

     //ls = -1;

    SDL_CreateWindowAndRenderer(W, H, 0, &window, &renderer);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    wavFile = Mix_LoadWAV("eatSound.wav");
    Mix_Music* BM = Mix_LoadMUS("GOT.mp3");
    Mix_PlayMusic(BM, -1);
    //Mix_Music* bonusM = Mix_LoadMUS("wow.mp3")

    bonusSound=Mix_LoadWAV("wow.mp3");
    tata = Mix_LoadWAV("khatam.mp3");
    //bonusVanish=Mix_LoadWAV("aayein.mp3");
}

void processInput()
{
   while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            isRunning = false;
        else if (e.type = SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                exit(0);
                //isRunning = false;
                break;

            case SDLK_UP:
               if(snake.direction !='D')
               {
                snake.direction='U';
                //if(pause)pause=!pause;
               }
                break;

                case SDLK_DOWN:
               if(snake.direction !='U')
               {
                snake.direction='D';
                //if(pause)pause=!pause;
               }
                break;

                 case SDLK_RIGHT:
               if(snake.direction !='L')
               {
                snake.direction='R';
                //if(pause)pause=!pause;
               }
                break;

                 case SDLK_LEFT:
               if(snake.direction !='R')
               {
                snake.direction='L';
                //if(pause)pause=!pause;
               }
                break;

                 case SDLK_SPACE:
                        pause = !pause;
                        break;
            
            default:
                break;
            }
        }
    }
}

bool isCollision()
{
    pair<int,int> head = snake.snakebody.front();
    for (auto it = next(snake.snakebody.begin()); it != snake.snakebody.end(); ++it)
    {
            const auto part = *it;
            if (head.first == part.first && head.second == part.second)
            {
                return true;
            } 
    }

    if ((snake.snakebody.front().first >= 60 && snake.snakebody.front().first < 60+3*GRID &&
        snake.snakebody.front().second >= 60 && snake. snakebody.front().second < 60+8*GRID) ||

        (snake.snakebody.front().first >= 60 && snake.snakebody.front().first < 60+8*GRID &&
        snake.snakebody.front().second >= 60 && snake.snakebody.front().second < 60+3*GRID) ||

        (snake.snakebody.front().first >= (W-60-(3*GRID)) && snake.snakebody.front().first < (W-60-(3*GRID))+3*GRID &&
        snake.snakebody.front().second >= (H-60-(8*GRID)) && snake.snakebody.front().second < (H-60-(8*GRID))+8*GRID) ||

        (snake.snakebody.front().first >= (W-60-(8*GRID)) && snake.snakebody.front().first < (W-60) &&
        snake.snakebody.front().second >= (H-60-3*GRID) && snake.snakebody.front().second < (H-60)) ||

        (snake.snakebody.front().first >= ((W/GRID)/2*GRID) && snake.snakebody.front().first < (((W/GRID)/2*GRID)+3*GRID) &&
        snake.snakebody.front().second >= ((H/GRID)/2*GRID-6*GRID) && snake.snakebody.front().second < ((H/GRID)/2*GRID+6*GRID)) ||

        (snake.snakebody.front().first >= (((W/GRID)/2*GRID)-4*GRID) && snake.snakebody.front().first < ((W/GRID)/2*GRID)-4*GRID+11*GRID) && 
        snake.snakebody.front().second >= ((H/GRID)/2*GRID-2*GRID) && snake.snakebody.front().second < (((H/GRID)/2*GRID-2*GRID)+3*GRID) ||

        (snake.snakebody.front().first >= 60 && snake.snakebody.front().first < 60+3*GRID &&
        snake.snakebody.front().second >= H-60-(8*GRID) && snake. snakebody.front().second < H-60) ||

        (snake.snakebody.front().first >= 60 && snake.snakebody.front().first < 60+8*GRID &&
        snake.snakebody.front().second >= H-60-(3*GRID) && snake.snakebody.front().second < H-60) ||

        (snake.snakebody.front().first >= (W-60-(3*GRID)) && snake.snakebody.front().first < (W-60-(3*GRID))+3*GRID &&
        snake.snakebody.front().second >= 60 && snake. snakebody.front().second < 60+8*GRID ||

        (snake.snakebody.front().first >= (W-60-(8*GRID)) && snake.snakebody.front().first < (W-60) &&
        snake.snakebody.front().second >= (60) && snake.snakebody.front().second < (60+3*GRID))))

        {
            Mix_PlayChannel(-1, tata, 0);
            return true;
        }
    return false;
}

void update()
{

    
    Uint32 currentTime = SDL_GetTicks(); //used to retrieve the current number of milliseconds that have passed since the SDL library was initialized.
    Uint32 bonusFoodElapsedTime = currentTime - snake.bonusFoodStartTime;

    if (bonusFoodElapsedTime >= 10000) {
        // Bonus food has been on the screen for more than 10 seconds
        
        //Mix_PlayChannel(-1, bonusVanish, 0);

        bonusfood.first = 2000;
        bonusfood.second = 3200;
    }

    /* int ctime = SDL_GetTicks();
    if ((ctime-bonusTime >= 6000))
    {
        fl=false;
        food.first = -100;
        food.second = -100;
    }*/

    pair<int,int> newH = snake.snakebody.front();
    if (snake.direction == 'R'){
        if (newH.first < W)
            newH.first += GRID;
        else
            newH.first %= W;
    }
    else if (snake.direction == 'D') {
        if (newH.second > H)
            newH.second = 0;
        else
            newH.second += GRID;
    }
    else if (snake.direction == 'L') {
        if (newH.first <= 0)
            newH.first = W-GRID;
        else
            newH.first -= GRID;
    }
    else if (snake.direction == 'U') {
        if (newH.second  > 0)
            newH.second -= GRID;
        else
            newH.second = H-GRID;
    }

    snake.snakebody.insert(snake.snakebody.begin(), newH);

    if (score%7==0 && score!=ls)
    {
        ls = score;
        bonusfoodpos();

        while ((bonusfood.first >= 60 && bonusfood.first < 60+3*GRID &&
        bonusfood.second >= 60 && bonusfood.second < 60+8*GRID) ||

        (bonusfood.first >= 60 && bonusfood.first < 60+8*GRID &&
        bonusfood.second >= 60 && bonusfood.second < 60+3*GRID) ||

        (bonusfood.first >= (W-60-(3*GRID)) && bonusfood.first < (W-60-(3*GRID))+3*GRID &&
        bonusfood.second >= (H-60-(8*GRID)) && bonusfood.second < (H-60-(8*GRID))+8*GRID) ||

        (bonusfood.first >= (W-60-(8*GRID)) && bonusfood.first < (W-60) &&
        bonusfood.second >= (H-60-3*GRID) && bonusfood.second < (H-60)) ||

        (bonusfood.first >= ((W/GRID)/2*GRID) && bonusfood.first < (((W/GRID)/2*GRID)+3*GRID) &&
        bonusfood.second >= ((H/GRID)/2*GRID-6*GRID) && bonusfood.second < ((H/GRID)/2*GRID+6*GRID)) ||

        (bonusfood.first >= (((W/GRID)/2*GRID)-4*GRID) && bonusfood.first < ((W/GRID)/2*GRID)-4*GRID+11*GRID &&
        bonusfood.second >= ((H/GRID)/2*GRID-2*GRID) && bonusfood.second < (((H/GRID)/2*GRID-2*GRID)+3*GRID)) ||

        (bonusfood.first >= 60 && bonusfood.first < 60+3*GRID &&
        bonusfood.second >= H-60-(8*GRID) && bonusfood.second < H-60) ||

        (bonusfood.first >= 60 && bonusfood.first < 60+8*GRID &&
        bonusfood.second >= H-60-(3*GRID) && bonusfood.second < H-60) ||

        (bonusfood.first >= (W-60-(3*GRID)) && bonusfood.first < (W-60-(3*GRID))+3*GRID &&
        bonusfood.second >= 60 && bonusfood.second < 60+8*GRID) ||

        (bonusfood.first >= (W-60-(8*GRID)) && bonusfood.first < (W-60) &&
        bonusfood.second >= (60) && bonusfood.second < (60+3*GRID)))

        {
            bonusfoodpos();
        }

    }

    /*if(bcount==7)
    {
        bonusfoodpos();
    }*/

    if (isCollision()) isRunning = false;
    
    //when snake collide with food
    else if (newH.first == food.first && newH.second == food.second){

        Mix_PlayChannel(-1, wavFile, 0);
        foodpos();

        while ((food.first >= 60 && food.first < 60+3*GRID &&
        food.second >= 60 && food.second < 60+8*GRID) ||

        (food.first >= 60 && food.first < 60+8*GRID &&
        food.second >= 60 && food.second < 60+3*GRID) ||

        (food.first >= (W-60-(3*GRID)) && food.first < (W-60-(3*GRID))+3*GRID &&
        food.second >= (H-60-(8*GRID)) && food.second < (H-60-(8*GRID))+8*GRID) ||

        (food.first >= (W-60-(8*GRID)) && food.first < (W-60) &&
        food.second >= (H-60-3*GRID) && food.second < (H-60)) ||

        (food.first >= ((W/GRID)/2*GRID) && food.first < (((W/GRID)/2*GRID)+3*GRID) &&
        food.second >= ((H/GRID)/2*GRID-6*GRID) && food.second < ((H/GRID)/2*GRID+6*GRID)) ||

        (food.first >= (((W/GRID)/2*GRID)-4*GRID) && food.first < ((W/GRID)/2*GRID)-4*GRID+11*GRID &&
        food.second >= ((H/GRID)/2*GRID-2*GRID) && food.second < (((H/GRID)/2*GRID-2*GRID)+3*GRID)) ||

        (food.first >= 60 && food.first < 60+3*GRID &&
        food.second >= H-60-(8*GRID) && food.second < H-60) ||

        (food.first >= 60 && food.first < 60+8*GRID &&
        food.second >= H-60-(3*GRID) && food.second < H-60) ||

        (food.first >= (W-60-(3*GRID)) && food.first < (W-60-(3*GRID))+3*GRID &&
        food.second >= 60 && food.second < 60+8*GRID) ||

        (food.first >= (W-60-(8*GRID)) && food.first < (W-60) &&
        food.second >= (60) && food.second < (60+3*GRID)))

        {
            foodpos();
        }

        score++;

        //increse snake size
        if (snake.direction == 'R') newH.first += GRID;
        else if (snake.direction == 'D') newH.second += GRID;
        if (snake.direction == 'L') newH.first -= GRID;
        else if (snake.direction == 'U') newH.second -= GRID;

        snake.snakebody.insert(snake.snakebody.begin(), newH);
        snake.snakebody.pop_back();
    }

    //snake collide with bonusfood
    else if (newH.first == bonusfood.first && newH.second == bonusfood.second){
        Mix_PlayChannel(-1, bonusSound, 0);
        score+=10;
        bonusfood.first = 2000;
        bonusfood.second = 3200;
    }
    else
        snake.snakebody.pop_back();
}

void showScore() {
    // Load font
    TTF_Font* font = TTF_OpenFont("Lato-Bold.ttf", 26);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    // Render score
    SDL_Color B = { 0, 0, 255 };

    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);

    SDL_Surface* surface = TTF_RenderText_Solid(font, scoreText, B);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int x = W / 2 - surface->w / 2;
    int y = 0;

    SDL_Rect destRect = { x, y, surface->w, surface->h };

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    // Clean up
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void gameOver() {
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // Load font
    TTF_Font* font = TTF_OpenFont("Lato-Bold.ttf", 50);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color C = { 0, 0, 0 };

    char Text[20];
    sprintf(Text, "GAME OVER!!!");

    SDL_Surface* surface = TTF_RenderText_Solid(font, Text, C);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int x = W / 2 - surface->w / 2;
    int y = H / 2 - surface->h / 2;

    SDL_Rect destRect = { x, y, surface->w, surface->h };

    // Copy texture to renderer
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    char scoreText[20];
    sprintf(scoreText, "Your Score: %d", score);

    SDL_Surface* surf = TTF_RenderText_Solid(font, scoreText, C);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    int xx = W / 2 - surf->w / 2;
    int yy = H / 2 - 1.5*surf->h;

    SDL_Rect destR = { xx, yy, surf->w, surf->h };

    // Copy texture to renderer
    SDL_RenderCopy(renderer, tex, NULL, &destR);
    SDL_RenderPresent(renderer);
    cout << "GAME OVER" << endl;

   /* Mix_Music* gameOverMusic = Mix_LoadMUS("khatam.mp3");
    Mix_PlayMusic(gameOverMusic, 0);*/


    // Clean up
    //Mix_FreeMusic(gameOverMusic);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}


void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    showScore();
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_Rect obs = {60, 60, 3*GRID, 8*GRID};
    SDL_RenderFillRect(renderer, &obs);
    SDL_Rect obs1 = {60, 60, 8*GRID, 3*GRID};
    SDL_RenderFillRect(renderer, &obs1);
    SDL_Rect obs2 = {W-60-(3*GRID), H-60-(8*GRID), 3*GRID, 8*GRID};
    SDL_RenderFillRect(renderer, &obs2);
    SDL_Rect obs3 = {W-60, H-60-3*GRID, -8*GRID, 3*GRID};
    SDL_RenderFillRect(renderer, &obs3);

    SDL_Rect obs4 = {W-60-3*GRID, 60, 3*GRID, 8*GRID};
    SDL_RenderFillRect(renderer, &obs4);
    SDL_Rect obs5 = {W-60, 60, -8*GRID, 3*GRID};
    SDL_RenderFillRect(renderer, &obs5);
    SDL_Rect obs6 = {60, H-60-(8*GRID), 3*GRID, 8*GRID};
    SDL_RenderFillRect(renderer, &obs6);
    SDL_Rect obs7 = {60, H-60-3*GRID, 8*GRID, 3*GRID};
    SDL_RenderFillRect(renderer, &obs7);

    SDL_Rect obs8 = {(W/GRID)/2*GRID, ((H/GRID)/2*GRID-6*GRID), 3*GRID, 12*GRID};
    SDL_RenderFillRect(renderer, &obs8);
    SDL_Rect obs9 = {((W/GRID)/2*GRID)-4*GRID, ((H/GRID)/2*GRID-2*GRID), 11*GRID, 3*GRID};
    SDL_RenderFillRect(renderer, &obs9);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    for (const auto sq : snake.snakebody)
    {
            SDL_Rect part = {sq.first, sq.second, GRID, GRID};
            SDL_RenderFillRect(renderer, &part);

    }
    SDL_SetRenderDrawColor(renderer, 240, 20, 24, 255);
    SDL_Rect f = {food.first, food.second, GRID, GRID};
    SDL_RenderFillRect(renderer, &f);

    SDL_SetRenderDrawColor(renderer, 24, 255, 24, 255);
    SDL_Rect bf = {bonusfood.first, bonusfood.second, GRID, GRID};
    SDL_RenderFillRect(renderer, &bf);

    SDL_RenderPresent(renderer);
}

void close()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main (int argc, char* argv[])
{
    initialize();
    while (isRunning)
    {
        processInput();
        if (!pause){
            Mix_ResumeMusic();
            update();
        } else
            Mix_PauseMusic();
        render();
        SDL_Delay((100-(0.5*score)));
    }

    gameOver();
    SDL_Delay(1500);
    close();
}

// Altaf Hossain
// dept: software engineering,sust
// reg no: 2021831002
// course name: making a 2D game using sdl 
// course code: swe150