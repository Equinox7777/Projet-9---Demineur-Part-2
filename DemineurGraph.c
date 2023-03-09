#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define ROWS 10
#define COLS 10
#define MINE_COUNT 10

const int CASE_CACHEE = 0;

typedef enum {
    CASE_VIDE = 0,
    CASE_MINE = 1,
    CASE_DECOUVERTE = 2,
    CASE_DRAPEAU = 3
} Case;



SDL_Texture* charger_texture(SDL_Renderer* renderer, const char* filename);
void afficher_case(SDL_Renderer* renderer, SDL_Texture* textures[4], int row, int col, Case cases[ROWS][COLS], bool afficher_mines);
void afficher_grille(SDL_Renderer* renderer, SDL_Texture* textures[4], Case cases[ROWS][COLS], bool afficher_mines);
void initialiser_jeu(Case cases[ROWS][COLS], bool mines[ROWS][COLS]);
void decouvrir_case(Case cases[ROWS][COLS], bool mines[ROWS][COLS], int row, int col);
void placer_drapeau(Case cases[ROWS][COLS], int row, int col);
int compter_mines(bool mines[ROWS][COLS], int row, int col);
bool verifier_victoire(Case cases[ROWS][COLS], bool mines[ROWS][COLS]);
void afficher_victoire(SDL_Renderer* renderer);
void afficher_defaite(SDL_Renderer* renderer);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

SDL_Texture** charger_textures(SDL_Renderer* renderer) {
    SDL_Texture** textures = (SDL_Texture**)malloc(4 * sizeof(SDL_Texture*));
    textures[CASE_CACHEE] = charger_texture(renderer, "src/case_cachee.png");
    textures[CASE_DECOUVERTE] = charger_texture(renderer, "src/case_decouverte.png");
    textures[CASE_DRAPEAU] = charger_texture(renderer, "src/case_drapeau.png");
    textures[CASE_MINE] = charger_texture(renderer, "src/case_mine.png");
    return textures;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void afficher_case(SDL_Renderer* renderer, SDL_Texture* textures[4], int row, int col, Case cases[ROWS][COLS], bool afficher_mines) {
    SDL_Rect dst_rect = { col * 50, row * 50, 50, 50 };
    switch (cases[row][col]) {
    case CASE_VIDE:
        SDL_RenderCopy(renderer, textures[0], NULL, &dst_rect);
        break;
    case CASE_MINE:
        if (afficher_mines) {
            SDL_RenderCopy(renderer, textures[1], NULL, &dst_rect);
        }
        else {
            SDL_RenderCopy(renderer, textures[0], NULL, &dst_rect);
        }
        break;
    case CASE_DECOUVERTE:
        SDL_RenderCopy(renderer, textures[compter_mines((bool(*)[COLS])mines, row, col) + 1], NULL, &dst_rect);
        break;
    case CASE_DRAPEAU:
        SDL_RenderCopy(renderer, textures[2], NULL, &dst_rect);
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void afficher_grille(SDL_Renderer* renderer, SDL_Texture* textures[4], Case cases[ROWS][COLS], bool afficher_mines)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            afficher_case(renderer, textures, i, j, cases, afficher_mines);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

bool mines[ROWS][COLS];

void initialiser_jeu(Case cases[ROWS][COLS], bool mines[ROWS][COLS])
{
    // Initialiser toutes les cases à vide
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            cases[row][col] = CASE_VIDE;
        }
    }

    // Placer les mines aléatoirement
    int mine_count = 0;
    while (mine_count < MINE_COUNT) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        if (!mines[row][col]) {
            mines[row][col] = true;
            ++mine_count;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void decouvrir_case(Case cases[ROWS][COLS], bool mines[ROWS][COLS], int row, int col)
{
    if (cases[row][col] != CASE_CACHEE) {
        return;
    }

    if (mines[row][col]) {
        cases[row][col] = CASE_MINE;
        return;
    }

    int mine_count = compter_mines(mines, row, col);
    cases[row][col] = (Case)mine_count;

    if (mine_count == 0) {
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < ROWS && j >= 0 && j < COLS) {
                    decouvrir_case(cases, mines, i, j);
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void placer_drapeau(Case cases[ROWS][COLS], int row, int col)
{
    if (cases[row][col] != CASE_DECOUVERTE) {
        cases[row][col] = (cases[row][col] == CASE_DRAPEAU) ? CASE_VIDE : CASE_DRAPEAU;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int compter_mines(bool mines[ROWS][COLS], int row, int col)
{
    int mine_count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS && mines[r][c]) {
                mine_count++;
            }
        }
    }
    return mine_count;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

bool verifier_victoire(Case cases[ROWS][COLS], bool mines[ROWS][COLS])
{
    bool victoire = true;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (cases[row][col] == CASE_VIDE && !mines[row][col]) {
                victoire = false;
                goto Exit;
            }
            if (cases[row][col] == CASE_MINE && !mines[row][col]) {
                victoire = false;
                goto Exit;
            }
        }
    }

Exit:
    return victoire;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void afficher_victoire(SDL_Renderer* renderer)
{
    SDL_Rect rect = { 0, 0, 640, 600 };
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);

    SDL_Surface* surface = SDL_CreateRGBSurface(0, 640, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dst_rect = { 0, 250, 640, 100 };
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);

    SDL_DestroyTexture(texture);

    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* text_surface = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
    SDL_Rect text_rect;

    TTF_Font* font = TTF_OpenFont("src/arial.ttf", 50);
    if (font == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de la police de caractères : %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* text_texture;

    text_surface = TTF_RenderText_Solid(font, "Vous avez gagne !", color);
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_QueryTexture(text_texture, NULL, NULL, &text_rect.w, &text_rect.h);
    text_rect.x = (640 - text_rect.w) / 2;
    text_rect.y = 270;
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    TTF_CloseFont(font);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

void afficher_defaite(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_Rect rect = { 0, 0, 640, 600 }; 
    SDL_RenderFillRect(renderer, &rect); 
    SDL_RenderPresent(renderer);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    srand(time(NULL));

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* textures[4] = { NULL };
    Case cases[ROWS][COLS];
    bool mines[ROWS][COLS] = { false };
    bool afficher_mines = false;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (SDL_CreateWindowAndRenderer(640, 600, SDL_WINDOW_SHOWN, &window, &renderer) != 0) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    textures[0] = charger_texture(renderer, "case_0.bmp");
    textures[1] = charger_texture(renderer, "case_1.bmp");
    textures[2] = charger_texture(renderer, "case_2.bmp");
    textures[3] = charger_texture(renderer, "case_3.bmp");

    if (textures[0] == NULL || textures[1] == NULL || textures[2] == NULL || textures[3] == NULL) {
        fprintf(stderr, "Erreur lors du chargement des textures : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    initialiser_jeu(cases, mines);

    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                goto Quit;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int row = event.button.y / 50;
                    int col = event.button.x / 50;
                    if (!afficher_mines && cases[row][col] != CASE_DRAPEAU) {
                        if (mines[row][col]) {
                            afficher_mines = true;
                            afficher_grille(renderer, textures, cases, afficher_mines);
                            afficher_defaite(renderer);
                        }
                        else {
                            decouvrir_case(cases, mines, row, col);
                        }
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) {
                    int row = event.button.y / 50;
                    int col = event.button.x / 50;
                    placer_drapeau(cases, row, col);
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_r) {
                    initialiser_jeu(cases, mines);
                    afficher_mines = false;
                }
                else if (event.key.keysym.sym == SDLK_SPACE) {
                    afficher_mines = true;
                    afficher_grille(renderer, textures, cases, true);
                }
                break;
            default:
                break;
            }
        }
        afficher_grille(renderer, textures, cases, afficher_mines);
        if (verifier_victoire(cases, mines)) {
            afficher_victoire(renderer);
            afficher_grille(renderer, textures, cases, true);
            afficher_mines = true;
        }
    }

Quit:
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(textures[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
