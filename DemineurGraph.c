#include <SDL.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>


#define NUM_ROWS 15
#define NUM_COLS 15
#define CASE_SIZE 20
#define GRID_OFFSET_X 150
#define GRID_OFFSET_Y 100

typedef struct Case {
    bool mine;
    bool decouvert;
    int chiffre;
} Case;

Case cases[NUM_ROWS][NUM_COLS];

void Init(SDL_Renderer* renderer);
void AfficheJeu(SDL_Renderer* renderer);
void AfficheMine(SDL_Renderer* renderer);
void DecouvreCase(SDL_Renderer* renderer, int row, int col);
void DecouvreVoisines(SDL_Renderer* renderer, int row, int col);
void AfficheChiffre(SDL_Renderer* renderer, int row, int col, int chiffre);

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Demineur", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    bool quit = false;

    srand(time(NULL));

    Init(renderer);
    AfficheJeu(renderer);
    AfficheMine(renderer);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);

                int row = (y - GRID_OFFSET_Y) / CASE_SIZE;
                int col = (x - GRID_OFFSET_X) / CASE_SIZE;

                if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
                {
                    DecouvreCase(renderer, row, col);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void Init(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 158, 158, 158, 255);
    SDL_RenderClear(renderer);
}

void AfficheJeu(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 158, 158, 158, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int row = 0; row < NUM_ROWS; row++)
    {
        for (int col = 0; col < NUM_COLS; col++)
        {
            SDL_Rect case_rect = { GRID_OFFSET_X + col * CASE_SIZE, GRID_OFFSET_Y + row * CASE_SIZE, CASE_SIZE, CASE_SIZE };
            SDL_RenderDrawRect(renderer, &case_rect);
        }
    }

    SDL_RenderPresent(renderer);
}

void AfficheMine(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    for (int i = 0; i < 10; i++)
    {
        int row = rand() % NUM_ROWS;
        int col = rand() % NUM_COLS;

        SDL_Rect mine_rect = { GRID_OFFSET_X + col * CASE_SIZE, GRID_OFFSET_Y + row * CASE_SIZE, CASE_SIZE, CASE_SIZE };
        SDL_RenderFillRect(renderer, &mine_rect);
    }
}

void DecouvreCase(SDL_Renderer* renderer, int row, int col)
{
    
    if (cases[row][col].decouvert) {
        return;
    }

    
    cases[row][col].decouvert = true;

    // case miné
    if (cases[row][col].mine) {
        printf("BOOM! Vous avez perdu.\n");
        exit(0);
    }

    // cases voisines
    if (cases[row][col].chiffre == 0) {
        DecouvreVoisines(renderer, row, col);
    }

    if (cases[row][col].chiffre > 0) {
        AfficheChiffre(renderer, row, col, cases[row][col].chiffre);
    }
}

void DecouvreVoisines(SDL_Renderer* renderer, int row, int col)
{
    // Parcourir les cases voisines
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i;
            int c = col + j;
            // Vérifier si la case est dans la grille
            if (r >= 0 && r < NUM_ROWS && c >= 0 && c < NUM_COLS) {
                // Découvrir la case
                DecouvreCase(renderer, r, c);
            }
        }
    }
}

void AfficheChiffre(SDL_Renderer* renderer, int row, int col, int chiffre)
{
    SDL_Rect dest_rect = { GRID_OFFSET_X + col * CASE_SIZE, GRID_OFFSET_Y + row * CASE_SIZE, CASE_SIZE, CASE_SIZE };

    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    switch (chiffre) {
    case 1:
        surface = SDL_LoadBMP("src/case_1.bmp");
        break;
    case 2:
        surface = SDL_LoadBMP("src/case_2.bmp");
        break;
    case 3:
        surface = SDL_LoadBMP("src/case_3.bmp");
        break;
    case 4:
        surface = SDL_LoadBMP("src/case_4.bmp");
        break;
    case 5:
        surface = SDL_LoadBMP("src/case_5.bmp");
        break;
    case 6:
        surface = SDL_LoadBMP("src/case_6.bmp");
        break;
    case 7:
        surface = SDL_LoadBMP("src/case_7.bmp");
        break;
    case 8:
        surface = SDL_LoadBMP("src/case_8.bmp");
        break;
    }

    if (surface == NULL) {
        printf("Erreur : impossible de charger l'image %d.bmp.\n", chiffre);
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

    SDL_DestroyTexture(texture);
}



