#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>

void Init(char MINES[10][10], char JEU[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            JEU[i][j] = '-';
            MINES[i][j] = '0';
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void AfficheJeu(char JEU[10][10])
//{
//    printf("\n\n");
//    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
//    printf("___|______________________________\n");
//    for (int i = 0; i < 10; i++)
//    {
//        if (i < 9)
//            printf(" %d | ", i + 1);
//        else
//            printf("%d | ", i + 1);
//        for (int j = 0; j < 10; j++)
//        {
//            printf("%c  ", JEU[i][j]);
//        }
//        printf("\n");
//    }
//}
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void AfficheMines(char MINES[10][10])
//{
//    printf("\n\n");
//    printf("   | 1  2  3  4  5  6  7  8  9  10\n");
//    printf("___|______________________________\n");
//    for (int i = 0; i < 10; i++)
//    {
//        if (i < 9)
//            printf(" %d | ", i + 1);
//        else
//            printf("%d | ", i + 1);
//        for (int j = 0; j < 10; j++)
//        {
//            printf("%c  ", MINES[i][j]);
//        }
//        printf("\n");
//    }
//}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void PlaceMines(char MINES[10][10], int NbMines)
{
    int Pmines;
    srand(time(NULL));
    for (Pmines = 0; Pmines < NbMines; Pmines++)
    {
        int i = rand() % 10;
        int j = rand() % 10;
        if (MINES[i][j] == '0')
        {
            MINES[i][j] = 'X';
        }
        else
        {
            NbMines++;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CompteMines(char MINES[10][10])
{
    int i, j, nbMines;

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            nbMines = 0;
            if (MINES[i][j] == '0' && MINES[i][j] != 'X')
            {
                // Compter les mines autour de la case vide
                int k, l;
                for (k = i - 1; k <= i + 1; k++)
                {
                    for (l = j - 1; l <= j + 1; l++)
                    {
                        if (k >= 0 && k < 10 && l >= 0 && l < 10 && MINES[k][l] == 'X')
                        {
                            nbMines++;
                        }
                    }
                }
                if (nbMines > 0)
                {
                    MINES[i][j] = '0' + nbMines;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void DecouvrirCase(char MINES[10][10], char JEU[10][10], int i, int j)
{
    if (MINES[i][j] != ' ')
    {
        JEU[i][j] = MINES[i][j];
    }

    if (MINES[i][j] == '0')
    {
        for (int k = i - 1; k <= i + 1; k++)
        {
            for (int l = j - 1; l <= j + 1; l++)
            {
                if (k >= 0 && k < 10 && l >= 0 && l < 10) //est-ce que la case est dans la grille
                {

                    if (MINES[k][l] == '0' && JEU[k][l] == '-') //On vérifie que la case contient un zéro
                    {
                        JEU[k][l] = '0';
                        DecouvrirCase(MINES, JEU, k, l);
                    }
                    else if (MINES[k][l] != '0' && JEU[k][l] == '-') //On découvre toutes les case non vide autour
                    {
                        JEU[k][l] = MINES[k][l];
                    }
                }
            }
        }
    }

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void PlacerDrapeau(char JEU[10][10], int i, int j) {
    JEU[i][j] = '@';
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//void Choisir(char MINES[10][10], char JEU[10][10])
//{
//    int i, j;
//    do
//    {
//        printf("\n");
//        printf("Veuillez entrer la case choisie (numero de ligne [espace] numero de colonne) : ");
//        while (scanf_s("%d %d", &i, &j) == 0)
//        {
//            printf("Vous devez saisir deux nombres avec un [espace] entre !\n");
//            while (getchar() != '\n')
//                continue;
//        }
//    } while (i < 1 || i > 10 || j < 1 || j > 10);
//
//    int choix;
//    printf("Vous avez choisi la case (%d,%d). Que voulez-vous faire ?\n", i, j);
//    i = i - 1;
//    j = j - 1;
//    do
//    {
//        printf("\t1. Decouvrir une case\n");
//        printf("\t2. Placer un drapeau\n");
//        printf("\t\tVotre choix : ");
//        while (scanf_s("%d", &choix) == 0)
//        {
//            printf("\tVous devez saisir 1 ou 2 !\n");
//            while (getchar() != '\n')
//                continue;
//        }
//    } while (choix < 0 || choix>2);
//
//    if (choix == 1)
//    {
//        DecouvrirCase(MINES, JEU, i, j);
//        if (MINES[i][j] == 'X')
//        {
//            AfficheMines(MINES);
//            printf("\tBOOM! perdu......\n");
//            exit(0);
//        }
//
//        AfficheJeu(JEU);
//    }
//    else if (choix == 2)
//    {
//        PlacerDrapeau(JEU, i, j);
//        AfficheJeu(JEU);
//    }
//}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int EstTermine(char JEU[10][10], char MINES[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (JEU[i][j] == '-' && MINES[i][j] != 'X')
            {
                return 0;
            }
        }
    }
    printf("\n");
    printf("GG mec!");
    printf("\n");
    return 1;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const int ROWS = 10;
const int COLS = 10;
int NbMines;
char JEU[10][10];
char MINES[10][10];

int main(int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;
    int statut = EXIT_FAILURE;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    if (0 != SDL_CreateWindowAndRenderer(500, 500, SDL_WINDOW_SHOWN, &window, &renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        goto Quit;
    }
    surface = SDL_LoadBMP("src/case_0.bmp");
    if (NULL == surface)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        goto Quit;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        goto Quit;
    }
    SDL_FreeSurface(surface);
    surface = NULL;

    PlaceMines(MINES, NbMines);
    statut = EXIT_SUCCESS;

    while (1)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto Quit;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    int i = event.button.y / 50;
                    int j = event.button.x / 50;
                    printf("Clic gauche a la position : (%d, %d)\n", event.button.x / 50, event.button.y / 50);
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    int i = event.button.y / 50;
                    int j = event.button.x / 50;
                    printf("Clic droit a la position : (%d, %d)\n", event.button.x / 50, event.button.y / 50);
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect dst = { 10, 10, 50, 50 };
        SDL_Rect src = { 10, 10, 50, 50 };

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                dst.x = j * 50;
                dst.y = i * 50;


                SDL_RenderCopy(renderer, texture, &src, &dst);
            }
        }

        SDL_RenderPresent(renderer);
    }

Quit:
    if (NULL != surface)
        SDL_FreeSurface(surface);
    if (NULL != texture)
        SDL_DestroyTexture(texture);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
