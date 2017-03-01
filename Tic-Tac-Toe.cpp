#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <tuple>
using namespace std;


int posmin_i = 0;
int posmin_j = 0;
int posmax_i = 0;
int posmax_j = 0;



int get_best_move(char board[3][3], int player, int n);
void clear_board();
void player_one(char board[3][3]);
void player_two(char board[3][3]);
void drawboard(char board[3][3]);
bool one_win(char board[3][3]);
bool two_win(char board[3][3]);
bool tie_check(char board[3][3]);
int main()
{
    char board [3][3] = {{' ', ' ', ' '},{' ', ' ', ' '},{' ', ' ', ' '}};
    cout << "WELCOME TO TIC-TAC-TOE!" << endl;

    int choice;
    cout << "Play another person (1)" << endl << "Play the computer (2)" << endl << "Watch the computer play itself (3)" << endl;
    cin >> choice;
    clear_board();
    if (choice == 1)
    {
        drawboard(board);
        int i = 0;
        while (!one_win(board) && !two_win(board) && i < 5)
        {
            player_one(board);
            clear_board();
            drawboard(board);
            if (!one_win(board) && i < 4)
            {
                player_two(board);

            }
            i++;
            clear_board();
            drawboard(board);
        }

        if (one_win(board))
        {
            cout << "Player One Wins!" << endl;
        }
        else if (two_win(board))
        {
            cout << "Player Two Wins!" << endl;
        }
        else if (i == 5)
        {
            cout << "Nobody Wins..." << endl;
        }

    }
    else if (choice == 2)
    {
        drawboard(board);
        int i = 0;
        while (!one_win(board) && !two_win(board) && i < 5)
        {
            player_one(board);
            clear_board();
            drawboard(board);
            if (!one_win(board) && i < 4)
            {
                get_best_move(board, 2, 0);
                board[posmin_i][posmin_j] = 'O';


            }
            i++;
            clear_board();
            drawboard(board);
        }

        if (one_win(board))
        {
            cout << "Player One Wins!" << endl;
        }
        else if (two_win(board))
        {
            cout << "The Computer Wins!" << endl;
        }
        else if (i == 5)
        {
            cout << "Nobody Wins..." << endl;
        }
    }
    else if (choice == 3)
    {
        drawboard(board);
        int i = 0;
        while (!one_win(board) && !two_win(board) && i < 5)
        {

            get_best_move(board, 1, 0);
            board[posmax_i][posmax_j] = 'X';
            clear_board();
            drawboard(board);
            if (!one_win(board) && i < 4)
            {
                get_best_move(board, 2, 0);
                board[posmin_i][posmin_j] = 'O';


            }
            i++;
            clear_board();
            drawboard(board);
        }

        if (one_win(board))
        {
            cout << "Player One Wins!" << endl;
        }
        else if (two_win(board))
        {
            cout << "The Computer Wins!" << endl;
        }
        else if (i == 5)
        {
            cout << "Nobody Wins..." << endl;
        }

    }



    return 0;
}
void drawboard(char board[3][3])
{
    cout << " 3 " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "   --+---+--" << endl;
    cout << " 2 " <<board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "   --+---+--" << endl;
    cout << " 1 " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
    cout << "   1   2   3" << endl;



}


int get_best_move(char board[3][3], int player, int n)
{
    int res;
    int one = 1;
    int cpu = 2;
    int max = -9999;
    int min = 9999;
    if (one_win(board))
    {
        return 1;
    }
    if (two_win(board))
    {
        return -1;
    }
    if (tie_check(board))
    {
        return 0;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                if (player == 2)
                {
                    board[i][j] = 'O';
                    res = get_best_move(board, one, n+1);

                    board[i][j] = ' ';
                                        if (res < min)
                    {
                        min = res;
                        if (n == 0)
                        {
                            posmin_i = i;
                            posmin_j = j;
                        }

                    }
                }
                else if (player == 1)
                {
                    board[i][j] = 'X';

                    res = get_best_move(board, cpu, n + 1);
                    board[i][j] = ' ';
                    if (res > max)
                    {
                        max = res;
                        if (n == 0)
                        {
                            posmax_i = i;
                            posmax_j = j;
                        }


                    }
                }
            }
        }
    }
    if (player == 1) return max;
    else return min;
}


void player_one(char board[3][3])
{
    bool proper = false;
    while (!proper)
    {
        int x,y = 0;
        cout << "PLAYER ONE" << endl << "Enter your move in coordinates seperated by a space" << endl;
        cin >> x >> y;
        if (y == 3) y = 0;
        else if (y == 2) y = 1;
        else if (y == 1) y = 2;
        if (board[y][x-1] == ' ')
        {
            board[y][x-1] = 'X';
            proper = true;
        }
        else cout << "Improper input, try again..." << endl;
    }
}
void player_two(char board[3][3])
{
    bool proper = false;
    while (!proper)
    {
        int x,y = 0;
        cout << "PLAYER TWO" << endl <<"Enter your move in coordinates seperated by a space" << endl;
        cin >> x >> y;
        if (y == 3) y = 0;
        else if (y == 2) y = 1;
        else if (y == 1) y = 2;
        if (board[y][x-1] == ' ')
        {
            board[y][x-1] = 'O';
            proper = true;
        }
        else cout << "Improper input, try again..." << endl;
    }
}
bool one_win(char board[3][3])
{
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] == 'X') return true;
    if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] == 'X') return true;
    if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] == 'X') return true;
    if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] == 'X') return true;
    if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] == 'X') return true;
    if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] == 'X') return true;
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'X') return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'X') return true;
    else return false;
}
bool two_win(char board[3][3])
{
    if (board[0][0] == board[0][1] && board[0][1] == board[0][2] && board[0][0] == 'O') return true;
    if (board[1][0] == board[1][1] && board[1][1] == board[1][2] && board[1][0] == 'O') return true;
    if (board[2][0] == board[2][1] && board[2][1] == board[2][2] && board[2][0] == 'O') return true;
    if (board[0][0] == board[1][0] && board[1][0] == board[2][0] && board[0][0] == 'O') return true;
    if (board[0][1] == board[1][1] && board[1][1] == board[2][1] && board[0][1] == 'O') return true;
    if (board[0][2] == board[1][2] && board[1][2] == board[2][2] && board[0][2] == 'O') return true;
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'O') return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'O') return true;
    else return false;
}


void clear_board()
{
    for (int i = 0; i < 20; i++) cout << endl;
}


bool tie_check(char board[3][3])
{
    if (board[0][0] != ' ' && board[0][1] != ' ' && board[0][2] != ' ' && board[1][0] != ' ' && board[1][1] != ' ' && board[1][2] != ' ' && board[2][0] != ' ' && board[2][1] != ' ' && board[2][2] != ' ')
    {
        return true;
    }
    else return false;
}
