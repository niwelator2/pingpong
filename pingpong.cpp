#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
int ballX, ballY;
int paddle1Y, paddle2Y;
int ballDirectionX, ballDirectionY;
bool gameRunning;

void Setup();
void Draw();
void Input();
void Logic();
void Menu();

void Setup()
{
    gameRunning = true;
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    paddle1Y = HEIGHT / 2 - 2;
    paddle2Y = HEIGHT / 2 - 2;
    ballDirectionX = -1;
    ballDirectionY = 0;
}

void Menu()
{
    int choice;
    bool menuRunning = true;

    while (menuRunning)
    {
        system("cls"); // Clear the console screen

        cout << "Ping-Pong Game Menu" << endl;
        cout << "-------------------" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                Setup();
                gameRunning = true;
                while (gameRunning)
                {
                    Draw();
                    Input();
                    Logic();
                    Sleep(10); // Pause for a short while to slow down the game
                }
                break;
            case 2:
                menuRunning = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        // Wait for user to press a key before clearing the console screen
        cout << endl << "Press any key to continue...";
        _getch();
    }
}

void Draw()
{
    system("cls"); // Clear the console screen

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (x == 0 || x == WIDTH - 1)
                cout << "#";
            else if (x == ballX && y == ballY)
                cout << "O";
            else if (x == 1 && y >= paddle1Y && y < paddle1Y + 4)
                cout << "|";
            else if (x == WIDTH - 2 && y >= paddle2Y && y < paddle2Y + 4)
                cout << "|";
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Controls:" << endl;
    cout << "Player 1: 'w' (up), 's' (down)" << endl;
    cout << "Player 2: 'i' (up), 'k' (down)" << endl;
    cout << "Quit: 'q'" << endl;
}

void Input()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'w' && paddle1Y > 0)
            paddle1Y--;
        if (key == 's' && paddle1Y + 4 < HEIGHT)
            paddle1Y++;
        if (key == 'i' && paddle2Y > 0)
            paddle2Y--;
        if (key == 'k' && paddle2Y + 4 < HEIGHT)
            paddle2Y++;
        if (key == 'q')
            gameRunning = false;
    }
}

void Logic()
{
    ballX += ballDirectionX;
    ballY += ballDirectionY;

    if (ballY == 0 || ballY == HEIGHT - 1)
        ballDirectionY = -ballDirectionY;

    if (ballX == 1 && ballY >= paddle1Y && ballY < paddle1Y + 4)
    {
        ballDirectionX = -ballDirectionX;
        ballDirectionY = -1;
    }

    if (ballX == WIDTH - 2 && ballY >= paddle2Y && ballY < paddle2Y + 4)
    {
        ballDirectionX = -ballDirectionX;
        ballDirectionY = 1;
    }

    if (ballX == 0 || ballX == WIDTH - 1)
    {
        gameRunning = false;
        cout << "Game Over!" << endl;
    }
}

int main()
{
    Menu();

    return 0;
}
