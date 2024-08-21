//*************************************************************************//
//                                                                         //
//                               tic tac toe                               //
//                                                                         //
//*************************************************************************//
#include<iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

int checkWinner(const std::vector<std::vector<char>>& board, char x, char o, int countLoops);
void chooseF(std::vector<std::vector<char>>& board, char& choose, int& winner, int& countLoops);
void printBoard(const std::vector<std::vector<char>> board);
void clearBoard(std::vector<std::vector<char>>& board);
void clearScreen();

std::vector<std::vector<char>> allocBoard();

int main()
{
    int row, col, flag = 0, winner = 0, countLoops = 0;
    char player, computer, choose;
    std::vector<std::vector<char>> board;
    std::srand(std::time(0));
    board = allocBoard();
    std::cout << "wich character do you want to be? X/O" << std::endl << "Enter letter:  ";
    while (flag != 1)
    {
        std::cin >> player;
  
        if ((player != 'X' && player != 'x') && (player != 'O' && player != 'o'))
            std::cout << "invalid letter, choose another one:  ";
        else {
            if (player == 'x')
                player = 'X';
            else if (player == 'o')
                player = 'O';
            flag = 1;
        }
    }
    computer = (player == 'X') ? 'O' : 'X';
    flag = 0;
    do
    {
        ++countLoops;
        if (winner == 0) {
            clearScreen();
            std::cout << "player is: " << player << std::endl << std::endl;
            printBoard(board);
            while (!flag)
            {
                std::cout << "Enter row(1 - 3): ";
                std::cin >> row;
                std::cout << "Enter col(1 - 3): ";
                std::cin >> col;
                if ((row >= 1 && row <= 3) && (col >= 1 && col <= 3) && board[row - 1][col - 1] == '#')
                    flag = 1;
                else {
                    std::cout << "invalid input, try again:  ";
                }
            }
            flag = 0;
            board[--row][--col] = player;
            while (!flag)
            {
                row = rand() % 3;
                col = rand() % 3;
                if (board[row][col] == '#' || countLoops == 5)
                {
                    flag = 1;
                    board[row][col] = computer;
                }
            }
            flag = 0;
            winner = checkWinner(board, player, computer, countLoops);
            if (winner != 0)
                chooseF(board, choose, winner, countLoops);
            
            
        }
    }while (winner == 0);
    return 0;
}

int checkWinner(const std::vector<std::vector<char>>& board, char player, char computer, int countLoops)
{
    int i = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == player)
                return 1;
            else if (board[i][0] == computer)
                return -1;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == player)
                return 1;
            else if (board[0][i] == computer)
                return -1;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == player)
            return 1;
        else if (board[0][0] == computer)
            return -1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == player)
            return 1;
        else if (board[0][2] == computer)
            return -1;
    }
    if (countLoops >= 5) {
        return 2;
    }
    return 0;
}

void printBoard(const std::vector<std::vector<char>> board)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            std::cout << board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<char>> allocBoard()
{

    std::vector<std::vector<char>> board;
    std::vector<char> vec;
        
    for (int i = 0; i < 3; ++i)
        vec.push_back('#');
    

    for (int i = 0; i < 3; ++i)
        board.push_back(vec);

    return board;
}

void clearBoard(std::vector<std::vector<char>>& board)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = '#';        
}

void chooseF(std::vector<std::vector<char>>& board, char& choose, int& winner, int& countLoops)
{
    int flag = 0;
    clearScreen();
    printBoard(board);
    if (winner == 1)
    {
        std::cout << "You are the winner!" << std::endl;
    }
    else if (winner == -1)
    {
        std::cout << "you are the loser" << std::endl;
    }
    else if(winner == 2){
        std::cout << "Its a tie!" << std::endl;
    }
    std::cout << "Do you want to play again? Y/y / N/n:   ";
    while(flag != 1)
    {
        std::cin >> choose;
        if (choose == 'Y' || choose == 'y')
        {
            clearBoard(board);
            winner = 0;
            flag = 1;
            countLoops = 0;
        }
        else if (choose == 'N' || choose == 'n')
            flag = 1;
        
        else
            std::cout << "invalid input, try again:   ";
        
    }
}

void clearScreen() 
{
#ifdef _WIN32
    system("cls");

#else
    system("clear");

#endif
}
