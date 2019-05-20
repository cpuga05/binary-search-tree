//
//  main.cpp
//  BT
//
//  Created by Christian Puga on 7/3/18.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

typedef struct _node {
    struct _node *left;
    struct _node *right;
    struct _node *root;
    int value;
    int FE;
    int heightLeft;
    int heightRight;
} node;

typedef node *Node;

COORD coord = {0,0};
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColorAndBackground(int ForgC, int BackC) {
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
    return;
}

bool showAnimation = false, animationPause = false;
int timeSleepList[5] = {250, 500, 1000, 1500, 2000}, timeSleep = 2;

void printSquare(int x, int y, bool change = false) {
    char c1 = 201, c2 = 187, c3 = 188, c4 = 200, s1 = 205, s2 = 186;

    if (change) {
        SetColorAndBackground(2, 0);
    } else {
        SetColorAndBackground(3, 0);
    }

    gotoxy(x, y);
    printf("%c%c%c%c%c%c", c1, s1, s1, s1, s1, c2);
    gotoxy(x, y+1);
    printf("%c", s2);
    gotoxy(x+5, y+1);
    printf("%c", s2);
    gotoxy(x, y+2);
    printf("%c%c%c%c%c%c", c4, s1, s1, s1, s1, c3);
    SetColorAndBackground(15, 0);
}

void printLine(int x, int y, int width, int height, int direction) {
    char s1 = 182, s2 = 199, t1 = 202;

    gotoxy(x, y);
    printf("%c", t1);
}

void printNodesV(Node tree, int width, int height, int base, int level, Node node = NULL) {
    if (level == 1) {
        system("cls");
    }

    if (tree != NULL) {
        //getch();
        gotoxy(width, height);
        printf("%2i", tree->value);

        if (node == tree) {
            printSquare(width-2, height-1, true);
        } else {
            printSquare(width-2, height-1);
        }
        //printLine(width+1, height-1, width, height, 0);

        level *= 2;

        printNodesV(tree->left, width - (base / level), height + 3, base, level, node);
        printNodesV(tree->right, width + (base / level), height + 3, base, level, node);
    }
}

void addNode(Node *tree, int value) {
    if (*tree == NULL) {
        *tree = (Node) malloc(sizeof(node));

        if (*tree != NULL) {
            (*tree)->value = value;
            (*tree)->left = NULL;
            (*tree)->right = NULL;
            (*tree)->FE = 0;
            (*tree)->heightLeft = 0;
            (*tree)->heightRight = 0;
            //            printf("Se crea %i\n", value);
        } else {
            printf("No posible\n");
        }
    } else {
        if (value < (*tree)->value) {
            addNode(&((*tree)->left), value);
        } else if (value > (*tree)->value) {
            addNode(&((*tree)->right), value);
        }
    }
}

void RSD (Node *node) {
    Node R = *node;
    Node root = R->root;
    Node I = R->left;
    Node ID = I->right;

    if (root != NULL) {
        if (root->left == R) {
            root->left = I;
        } else {
            root->right = I;
        }
    } else {
        *node = I;
    }

    R->left = ID;
    I->right = R;
    R->root = I;//
    I->root = root;//

    if (ID != NULL) {
        ID->root = R;
    }
}

void RSI (Node *node) {
    Node R = *node;
    Node root = R->root;
    Node D = R->right;
    Node DI = D->left;

    if (root != NULL) {
        if (root->left == R) {
            root->left = D;
        } else {
            root->right = D;
        }
    } else {
        *node = D;
    }

    R->right = DI;
    D->left = R;
    R->root = D;//
    D->root = root;//

    if (DI != NULL) {
        DI->root = R;
    }

}

int updateHeight(Node *node) {
    if (*node == NULL) {
        return 0;
    } else {
        (*node)->heightLeft = updateHeight(&((*node)->left));
        (*node)->heightRight = updateHeight(&((*node)->right));
        (*node)->FE = (*node)->heightRight - (*node)->heightLeft;

        if ((*node)->heightLeft > (*node)->heightRight) {
            return (*node)->heightLeft + 1;
        } else {
            return (*node)->heightRight + 1;
        }
    }
}

void checkBalance(Node *tree, Node *node) {
    if (*node != NULL) {
        checkBalance(&(*tree), &((*node)->left));
        checkBalance(&(*tree), &((*node)->right));

        if ((*node)->FE == 2) {
            if ((*node)->right->FE == -1) {
//                RDI()
                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RDI");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSD(&((*node)->right));

                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RDI");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSI(&(*node));
            } else if ((*node)->right->FE == 1) {
                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RSI");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSI(&(*node));
            }

            updateHeight(tree);
        } else if ((*node)->FE == -2) {
            if ((*node)->left->FE == 1) {
//                RDD()
                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RDD");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSI(&((*node)->left));

                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RDD");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSD(&(*node));
            } else if ((*node)->left->FE == -1) {
                if (showAnimation) {
                    printNodesV(*tree, 59, 5, 60, 1, (*node));
                    gotoxy(0, 0);
                    printf("Se necesita rotacion RSD");

                    if (animationPause) {
                        fflush(stdin);
                        getch();
                    } else {
                        Sleep(timeSleepList[timeSleep]);
                    }
                }

                RSD(&(*node));
            }

            updateHeight(tree);
        }
    }
}

void addNodeAVL(Node *tree, int value) {
    Node root = NULL;
    Node actual = *tree;

    while (actual != NULL && value != actual->value) {
        root = actual;

        if (actual->value > value) {
            actual = actual->left;
        } else if (actual->value < value) {
            actual = actual->right;
        }
    }

    if (actual == NULL) {
        if (root == NULL) {
            (*tree) = (Node) malloc(sizeof(node));
            (*tree)->value = value;
            (*tree)->left = NULL;
            (*tree)->right = NULL;
            (*tree)->root = NULL;
            (*tree)->FE = 0;
            (*tree)->heightLeft = 0;
            (*tree)->heightRight = 0;
        } else if (root->value != value) {
            actual = (Node) malloc(sizeof(node));
            actual->value = value;
            actual->left = NULL;
            actual->right = NULL;
            actual->root = root;
            actual->FE = 0;
            actual->heightLeft = 0;
            actual->heightRight = 0;

            if (root->value > value) {
                root->left = actual;
            } else if (root->value < value) {
                root->right = actual;
            }

            updateHeight(tree);
            checkBalance(tree, tree);
        }
    }
}

Node searchNode(Node tree, int value) {
    Node actual = tree;
    Node node = NULL;

    while (actual != NULL && node == NULL) {
        if (actual->value == value) {
            node = actual;
        } else {
            if (value < actual->value) {
                actual = actual->left;
            } else {
                actual = actual->right;
            }
        }
    }

    return node;
}

void clearNodes(Node *tree) {
    if (*tree != NULL) {
        clearNodes(&(*tree)->left);
        clearNodes(&(*tree)->right);
        free(*tree);
        *tree = NULL;
    }
}

void auxNumberNodes(Node tree, int *i) {
    (*i)++;

    if (tree->left != NULL) {
        auxNumberNodes(tree->left, i);
    }

    if (tree->right != NULL) {
        auxNumberNodes(tree->right, i);
    }
}

int numberNodes(Node tree) {
    int i = 0;

    auxNumberNodes(tree, &i);

    return i;
}

void inOrder(Node tree) {
    if (tree->left != NULL) {
        inOrder(tree->left);
    }

    printf("%i ", tree->value);

    if (tree->right != NULL) {
        inOrder(tree->right);
    }
}

void printNodesH(Node tree, int level = 0) {
    int i;

    if (tree != NULL) {
        printNodesH(tree->right, level + 1);

        for (i = 0; i < level; i++) {
            printf("\t");
        }

        printf("%3i", tree->value);
//        printf(" (%i %i)", tree->heightRight, tree->heightLeft);
//        printf(" (%i)", tree->FE);
        printf("\n");
        printNodesH(tree->left, level + 1);
    } else {
        //        for (i = 0; i < level; i++) {
        //            printf("\t");
        //        }
        //
        //        printf("  x\n");
    }
}

int randomNumber(int min, int max) {
    return rand() % (max + min + 1) + min;
}

int main() {
    srand(time(NULL));
    bool start = true, startAction, exitSubMenu;
    int optionMainMenu, optionMenu, key, i, number;
    Node ABB = NULL, ABBAVL = NULL;

    while (start) {
        //do {
            system("cls");
            printf("DEMO - Arboles Binario\n\n");
            printf("// Animaciones: %i\n", showAnimation);
            printf("// Animaciones Pausa: %i\n", animationPause);
            printf("// Velocidad: %i\n", timeSleepList[timeSleep]);

            printf("\n1- Generar nodos aleatoriamente");
            printf("\n2- Generar nodos AVL aleatoriamente");

            printf("\n3- Generar nodos manualmente");
            printf("\n4- Generar nodos AVL manualmente");

            printf("\n5- Generar nodos 1 al 31");
            printf("\n6- Generar nodos AVL 1 al 31");

            /*printf("\n- Generar arbol AVL");
            printf("\n- Generar arbol");*/
            printf("\n0- Salir");
            printf("\n");
            fflush(stdin);
            optionMainMenu = getch();
            /*printf("%i\n", optionMainMenu);
            system("pause");*/
        //} while ((optionMainMenu < 48 || optionMainMenu > 57) && optionMainMenu != 97);

        if (optionMainMenu == 97) {
            /** A **/
            showAnimation = !showAnimation;
        } else if (optionMainMenu == 112) {
            /** P **/
            animationPause = !animationPause;
        } else if (optionMainMenu == 48) {
            /** 0 **/
            start = false;
        }  else if (optionMainMenu == 72) {
            /** UP **/
            if (timeSleep > 0) {
                timeSleep--;
            }
        } else if (optionMainMenu == 80) {
            /** DOWN **/
            if (timeSleep < 4) {
                timeSleep++;
            }
        } else if (optionMainMenu == 49 || optionMainMenu == 50) {
            /** 1 & 2 **/
            printf("Cuantos numeros aleatorios quieres insertar? ");
            fflush(stdin);
            scanf("%i", &optionMenu);

            i = 0;
            startAction = true;

            while (startAction) {
                while (!kbhit() && startAction) {
                    system("cls");

                    if (optionMainMenu == 49) {
                        /** 1 **/
                        do {
                            number = randomNumber(0, 99);
                        } while (searchNode(ABB, number) != NULL);

                        addNode(&ABB, number);
                        printNodesV(ABB, 59, 5, 60, 1);
                    } else {
                        /** 2 **/
                        do {
                            number = randomNumber(0, 99);
                        } while (searchNode(ABBAVL, number) != NULL);

                        addNodeAVL(&ABBAVL, number);
                        printNodesV(ABBAVL, 59, 5, 60, 1);
                    }

                    //printNodesV(ABBAVL, 88, 5, 88, 1);
                    Sleep(timeSleepList[timeSleep]);
                    i++;

                    if (i == optionMenu) {
                        startAction = false;
                    }
                }

                if (startAction) {
                    fflush(stdin);
                    key = getch();

                    if (key == 97) {
                        /** A **/
                        showAnimation = !showAnimation;
                    } else if (key == 112) {
                        /** P **/
                        animationPause = !animationPause;
                    } else if (key == 32) {
                        /** SPACE **/
                        fflush(stdin);
                        getch();
                    } else if (key == 72) {
                        /** UP **/
                        if (timeSleep > 0) {
                            timeSleep--;
                        }
                    } else if (key == 80) {
                        /** DOWN **/
                        if (timeSleep < 4) {
                            timeSleep++;
                        }
                    }
                }
            }

            fflush(stdin);
            getch();
            clearNodes(&ABB);
            clearNodes(&ABBAVL);
        } else if (optionMainMenu == 51 || optionMainMenu == 52) {
            /** 3 & 4 **/
            startAction = true;

            while (startAction) {
                do {
                    system("cls");
                    printf("Numero a insertar (666 para salir): ");
                    fflush(stdin);
                    scanf("%i", &number);

                    if (number == 666) {
                        exitSubMenu = true;
                    } else if (number < -99 || number > 99 || searchNode(ABBAVL, number) != NULL) {
                        exitSubMenu = false;
                    } else {
                        exitSubMenu = true;
                    }
                } while (!exitSubMenu);

                if (number == 666) {
                    startAction = false;
                } else {
                    if (optionMainMenu == 51) {
                        /** 3 **/
                        addNode(&ABB, number);
                        printNodesV(ABB, 59, 5, 60, 1);
                    } else {
                        /** 4 **/
                        addNodeAVL(&ABBAVL, number);
                        printNodesV(ABBAVL, 59, 5, 60, 1);
                    }

                    fflush(stdin);
                    getch();
                }
            }

            /*fflush(stdin);
            getch();*/
            clearNodes(&ABB);
            clearNodes(&ABBAVL);
        } else if (optionMainMenu == 53 || optionMainMenu == 54) {
            /** 5 & 6 **/
            i = 1;
            startAction = true;

            while (startAction) {
                while (!kbhit() && startAction) {
                    system("cls");

                    if (optionMainMenu == 53) {
                        /** 5 **/
                        addNode(&ABB, i);
                        printNodesV(ABB, 59, 5, 60, 1);
                    } else {
                        /** 6 **/
                        addNodeAVL(&ABBAVL, i);
                        printNodesV(ABBAVL, 59, 5, 60, 1);
                    }

                    //printNodesV(ABBAVL, 88, 5, 88, 1);
                    Sleep(timeSleepList[timeSleep]);
                    i++;

                    if (i == 32) {
                        startAction = false;
                    }
                }

                if (startAction) {
                    fflush(stdin);
                    key = getch();

                    if (key == 97) {
                        /** A **/
                        showAnimation = !showAnimation;
                    } else if (key == 112) {
                        /** P **/
                        animationPause = !animationPause;
                    } else if (key == 32) {
                        /** SPACE **/
                        fflush(stdin);
                        getch();
                    } else if (key == 72) {
                        /** UP **/
                        if (timeSleep > 0) {
                            timeSleep--;
                        }
                    } else if (key == 80) {
                        /** DOWN **/
                        if (timeSleep < 4) {
                            timeSleep++;
                        }
                    }
                }
            }

            fflush(stdin);
            getch();
            clearNodes(&ABB);
            clearNodes(&ABBAVL);
        }
    }

    return 0;
}
