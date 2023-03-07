//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//
//void Init(char MINES[10][10], char JEU[10][10])
//{
//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < 10; j++)
//        {
//            JEU[i][j] = '-';
//            MINES[i][j] = '0';
//        }
//    }
//}
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
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void PlaceMines(char MINES[10][10], int NbMines)
//{
//    int Pmines;
//    srand(time(NULL));
//    for (Pmines = 0; Pmines < NbMines; Pmines++)
//    {
//        int i = rand() % 10;
//        int j = rand() % 10;
//        if (MINES[i][j] == '0')
//        {
//            MINES[i][j] = 'X';
//        }
//        else
//        {
//            NbMines++;
//        }
//    }
//}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void CompteMines(char MINES[10][10])
//{
//    int i, j, nbMines;
//
//    for (i = 0; i < 10; i++)
//    {
//        for (j = 0; j < 10; j++)
//        {
//            nbMines = 0;
//            if (MINES[i][j] == '0' && MINES[i][j] != 'X')
//            {
//                // Compter les mines autour de la case vide
//                int k, l;
//                for (k = i - 1; k <= i + 1; k++)
//                {
//                    for (l = j - 1; l <= j + 1; l++)
//                    {
//                        if (k >= 0 && k < 10 && l >= 0 && l < 10 && MINES[k][l] == 'X')
//                        {
//                            nbMines++;
//                        }
//                    }
//                }
//                if (nbMines > 0)
//                {
//                    MINES[i][j] = '0' + nbMines;
//                }
//            }
//        }
//    }
//}
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void DecouvrirCase(char MINES[10][10], char JEU[10][10], int i, int j)
//{
//    if (MINES[i][j] != ' ')
//    {
//        JEU[i][j] = MINES[i][j];
//    }
//
//    if (MINES[i][j] == '0')
//    {
//        for (int k = i - 1; k <= i + 1; k++)
//        {
//            for (int l = j - 1; l <= j + 1; l++)
//            {
//                if (k >= 0 && k < 10 && l >= 0 && l < 10) //est-ce que la case est dans la grille
//                {
//
//                    if (MINES[k][l] == '0' && JEU[k][l] == '-') //On v�rifie que la case contient un z�ro
//                    {
//                        JEU[k][l] = '0';
//                        DecouvrirCase(MINES, JEU, k, l);
//                    }
//                    else if (MINES[k][l] != '0' && JEU[k][l] == '-') //On d�couvre toutes les case non vide autour
//                    {
//                        JEU[k][l] = MINES[k][l];
//                    }
//                }
//            }
//        }
//    }
//
//}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//void PlacerDrapeau(char JEU[10][10], int i, int j) {
//    JEU[i][j] = 'F';
//}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
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
//    printf("Vous avez choisi la case (%d,%d).\ Que voulez-vous faire ?\n", i, j);
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
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//
//int EstTermine(char JEU[10][10], char MINES[10][10])
//{
//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < 10; j++)
//        {
//            if (JEU[i][j] == '-' && MINES[i][j] != 'X')
//            {
//                return 0;
//            }
//        }
//    }
//    printf("\n");
//    printf("GG mec!");
//    printf("\n");
//    return 1;
//}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//int main()
//{
//
//    int choix; {};//choix d'une case
//    char JEU[10][10];//grille de jeu
//    char MINES[10][10];//grille avec les Mines 
//    int NbMines;//Nombre de Mines
//
//    do
//    {
//        printf("Combien de mines voulez-vous ? (maximum 99)\n");
//        while (scanf_s("%d", &NbMines) == 0)
//        {
//            printf("Vous devez saisir un nombre !\n");
//            while (getchar() != '\n')
//                continue;
//        }
//    } while (NbMines < 1 || NbMines > 99);
//
//    Init(MINES, JEU);
//    AfficheJeu(JEU);
//    PlaceMines(MINES, NbMines);
//    CompteMines(MINES);
//    while (!EstTermine(JEU, MINES))
//    {
//        Choisir(MINES, JEU);
//    }
//
//    return 0;
//}