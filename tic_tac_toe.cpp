#include<iostream>
#include<cstdlib>
#include<limits>

using namespace std;

int currentPlayer;
char currentMarker;
char board[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};

void drawBoard() {
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " \n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " \n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;
    if (board[row][col] != 'x' && board[row][col] != '0') {
        board[row][col] = currentMarker;
        return true;
    }
    return false;
}

int winner() {
    // rows ko check karo
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return currentPlayer;
        }
    }
    // columns ko check karo
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return currentPlayer;
        }
    }
    // diagonals ko check karo
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return currentPlayer;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return currentPlayer;
    }
    return 0;
}

void swapPlayerandMarker() {
    if (currentPlayer == 1) {
        currentPlayer = 2;
        currentMarker = (currentMarker == 'x') ? '0' : 'x';
    } else {
        currentPlayer = 1;
        currentMarker = (currentMarker == 'x') ? '0' : 'x';
    }
}

void game() {
    cout << "Player 1 choose your sign (x or o): ";
    char markerp1;
    cin >> markerp1;

    // Set the pahla player and marker
    currentPlayer = 1;
    currentMarker = markerp1;

    drawBoard();
    int playerwon = 0;
    for (int i = 0; i < 9; i++) {
        cout << "Player " << currentPlayer << "'s turn. Enter your slot (1-9): ";
        int slot;
        
        // Ensure that input is a valid integer
        while (true) {
            if (cin >> slot) {
                if (slot < 1 || slot > 9) {
                    cout << "Not a valid slot. Enter a number between 1 and 9: ";
                    continue;
                }
                break;
            } else {
                // agar input integer nahi hai ya limit se jayada hai to uske liye streamsize ka use karege
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number between 1 and 9: ";
            }
        }

        // Check karo slot pahle se occupied nahi na hai
        if (!placeMarker(slot)) {
            cout << "Slot already occupied! Try again.\n";
            i--;
            continue;
        }

        // board ko draw karo every me move ke baad
        drawBoard();

        //  winner ke liye check karo
        playerwon = winner();
        if (playerwon == 1) {
            cout << "Player 1 wins!\n";
            break;
        }
        if (playerwon == 2) {
            cout << "Player 2 wins!\n";
            break;
        }

        // Swap players and markers
        swapPlayerandMarker();
    }

    // If no winner and all slots are filled, it's a tie
    if (playerwon == 0) {
        cout << "It's a tie!\n";
    }
}

int main() {
    game();
    return 0;
}
