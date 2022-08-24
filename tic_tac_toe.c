#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

/*
     ===============================================
    | 0 = X                                         |
    | 1 = O                                         |
    | 4 = empty                                     |
    | Sum in row or column or diagonal = 0 => X won |
    | Sum in row or column or diagonal = 3 => O won |
    | Board full = Draw                             |
     ===============================================
*/

typedef struct node
{
    /* data */
    int board[3][3];
    int result;
    int depth;
    int moveMade;
    int numChilds;
    int turn;
    struct node **childNode;
} node;

node *rootState = NULL;

void takeInput(int board[][3], int turn, int gameTurn);
void showBoard(int board[][3]);
void addToBoard(int board[][3], int pos, int turn, int gameTurn);
int checkWin(int board[][3]);
node *generateTree(int board[][3], int turn, int depth, int moveMade);
node *getLeastDepth(node *root);
int getMove(node *root);
int getMoveMade(int i, int j);
void copyBoard(int newBoard[3][3], int board[][3]);

node *rootNode = NULL;

int prevMove;
int main(int argc, char const *argv[])
{

    srand(time(NULL));

    int i, result;
    int board[][3] = {{4, 4, 4}, {4, 4, 4}, {4, 4, 4}};

    for (i = 0; i < 9; i += 1)
    {
        system("cls");
        showBoard(board);
        if (i > 3)
        {
            result = checkWin(board);
            if (result == 1)
            {
                printf("X has won..!\n");

                exit(0);
            }
            else if (result == -1)
            {
                printf("O has won..!!\n");

                exit(0);
            }
        }

        int turn = i % 2;
        takeInput(board, turn, i);
    }

    result = checkWin(board);
    system("cls");
    showBoard(board);
    if (result == 1)
    {
        printf("X won..!!");

        exit(0);
    }
    else if (result == -1)
    {
        printf("O has won..!!");

        exit(0);
    }
    else
    {
        printf("It's a tie.");
    }

    return 0;
}
void takeInput(int board[][3], int turn, int gameTurn)
{
    int x;

    if (turn == 0)
    {
        if (gameTurn > 2)
        {
            rootNode = generateTree(board, turn, gameTurn, prevMove);
            if (rootNode == NULL)
            {
                printf("TREE WAS NOT GENEREATED.");
            }
            if (rootNode->numChilds == 0)
            {

                // No way to win.
                x = (rand() % (9)) + 1;
            }
            else
            {
                // TODO OPTIMIZE THE CHILD NODE HERE TO ENSURE VICTORY EVERY TIME.
                // int bestChildIndex = getBestChild(rootNode)1;
                x = (rootNode->childNode[rand() % rootNode->numChilds])->moveMade;
            }
        }
        else
        {
            printf("Player X's turn : ");
            x = (rand() % (9)) + 1;
        }
    }
    else
    {
        printf("Player O's turn : ");
        x = getch() - 48;
        // TODO change rootNode to the childNode where the board is same as the currentBoard.
    }
    addToBoard(board, turn, x, gameTurn);
    prevMove = x;
}
node *generateTree(int board[][3], int turn, int depth, int moveMade)
{
    int i, j;
    turn = turn % 2;
    node *newNode = malloc(sizeof(node));
    copyBoard(newNode->board, board);
    newNode->depth = depth;
    newNode->moveMade = moveMade;
    newNode->numChilds = 0;
    newNode->result = checkWin(board);
    newNode->turn = turn;
    newNode->childNode = malloc(sizeof(node *) * 7);
    if (newNode->result == 1)
    {
        return (newNode);
    }
    for (i = 0; i < 3; i += 1)
    {
        for (j = 0; j < 3; j += 1)
        {
            if (board[i][j] == 4)
            {
                int newBoard[3][3];
                copyBoard(newBoard, board);
                newBoard[i][j] = turn;
                int winState = checkWin(newBoard);
                if (winState == -1 || (depth == 0 && winState != 1))
                {
                    return (NULL);
                }
                else
                {
                    node *childNode = generateTree(newBoard, turn + 1, depth - 1, getMoveMade(i, j));
                    if (childNode != NULL)
                    {
                        newNode->childNode[newNode->numChilds] = childNode;
                        newNode->numChilds += 1;
                    }
                }
            }
        }
    }
    return (newNode);
}

int getBestMoveIndex(node *root)
{
    
}

void copyBoard(int newBoard[3][3], int board[][3])
{
    int i, j;
    for (i = 0; i < 3; i += 1)
    {
        for (j = 0; j < 3; j += 1)
        {
            newBoard[i][j] = board[i][j];
        }
    }
}
int getMoveMade(int i, int j)
{
    if (i == 0)
    {
        if (j == 0)
        {
            return (7);
        }
        else if (j == 1)
        {
            return (8);
        }
        else if (j == 2)
        {
            return (9);
        }
    }
    else if (i == 1)
    {
        if (j == 0)
        {
            return (4);
        }
        else if (j == 1)
        {
            return (5);
        }
        else if (j == 2)
        {
            return (6);
        }
    }
    else if (i == 2)
    {
        if (j == 0)
        {
            return (1);
        }
        else if (j == 1)
        {
            return (2);
        }
        else if (j == 2)
        {
            return (3);
        }
    }
}
void showBoard(int board[][3])
{
    char out;
    for (int k = 0; k < 3; k++)
    {
        for (int m = 0; m < 3; m++)
        {
            switch (board[k][m])
            {
            case 0:
                out = 'X';
                break;
            case 1:
                out = 'O';
                break;
            case 4:
                out = '-';
                break;
            }
            printf("%c ", out);
        }
        printf("\n");
    }
}
void addToBoard(int board[][3], int turn, int pos, int gameTurn)
{
    int i = turn;
    switch (pos)
    {
    case 7:
        if (board[0][0] == 4)
        {
            if (i == 0)
            {
                board[0][0] = 0;
            }
            if (i == 1)
            {
                board[0][0] = 1;
            }
        }
        else
        {
            goto wrong;
        }
        break;
    case 8:
        if (board[0][1] == 4)
        {
            if (i == 0)
            {
                board[0][1] = 0;
            }
            if (i == 1)
            {
                board[0][1] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 9:
        if (board[0][2] == 4)
        {
            if (i == 0)
            {
                board[0][2] = 0;
            }
            if (i == 1)
            {
                board[0][2] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 4:
        if (board[1][0] == 4)
        {
            if (i == 0)
            {
                board[1][0] = 0;
            }
            if (i == 1)
            {
                board[1][0] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 5:
        if (board[1][1] == 4)
        {
            if (i == 0)
            {
                board[1][1] = 0;
            }
            if (i == 1)
            {
                board[1][1] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 6:
        if (board[1][2] == 4)
        {
            if (i == 0)
            {
                board[1][2] = 0;
            }
            if (i == 1)
            {
                board[1][2] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 1:
        if (board[2][0] == 4)
        {
            if (i == 0)
            {
                board[2][0] = 0;
            }
            if (i == 1)
            {
                board[2][0] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 2:
        if (board[2][1] == 4)
        {
            if (i == 0)
            {
                board[2][1] = 0;
            }
            if (i == 1)
            {
                board[2][1] = 1;
            }
        }
        else
            goto wrong;
        break;
    case 3:
        if (board[2][2] == 4)
        {
            if (i == 0)
            {
                board[2][2] = 0;
            }
            if (i == 1)
            {
                board[2][2] = 1;
            }
        }
        else
            goto wrong;
        break;
    wrong:
    default:
        printf("\nInvalid Input : %d\n", pos);
        takeInput(board, turn, gameTurn);
        break;
    }
}


/*
		Takes in a boardState 
		Returns 1 if X is winning
		Returns -1 if O is winning
		else returns 0

*/
int checkWin(int board[][3])
{
    int i, j, r1, r2, r3, c1, c2, c3, d1, d2;

    // Row
    r1 = board[0][0] + board[0][1] + board[0][2];
    r2 = board[1][0] + board[1][1] + board[1][2];
    r3 = board[2][0] + board[2][1] + board[2][2];

    c1 = board[0][0] + board[1][0] + board[2][0];
    c2 = board[0][1] + board[1][1] + board[2][1];
    c3 = board[0][2] + board[1][2] + board[2][2];

    d1 = board[0][0] + board[1][1] + board[2][2];
    d2 = board[2][0] + board[1][1] + board[0][2];

    if (r1 == 0 || r2 == 0 || r3 == 0 || c1 == 0 || c2 == 0 || c3 == 0 || d1 == 0 || d2 == 0)
    {
        // X wins
        return 1;
    }

    if (r1 == 3 || r2 == 3 || r3 == 3 || c1 == 3 || c2 == 3 || c3 == 3 || d1 == 3 || d2 == 3)
    {
        // O wins
        return -1;
    }
    else
    {
        return 0;
    }
}