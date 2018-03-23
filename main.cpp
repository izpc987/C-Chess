#include <iostream>
#include <string>

using namespace std;

class Piece {
public:
    Piece(char c): color(c) {};
    char getColor() {
        return color;
    }
    virtual char getType() = 0;
    bool checkIfLegal(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        Piece *piecePointer = matrix[destRow][destCol];
        if ((piecePointer == NULL) || (color != piecePointer->getColor())) { // if this place is empty or has a piece with opposite color
            if (checkPieceMoves(row, col, destRow, destCol, matrix)) {
                return true;
            } else {
                return false;
            }
        }
    }
private:
    char color;
    virtual bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) = 0;
};

class Pawn: public Piece { //SHOULD WORK AS ASSUMED
public:
    Pawn(char c): Piece(c) {};
    virtual char getType() {
        return 'P';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        Piece *pPointer = matrix[destRow][destCol];
        if (matrix[row][col]->getColor() == 'W') {
            if (pPointer == NULL) {
                if (destRow == row - 1 && destCol == col) {
                    return true;
                }
            } else {
                if (destRow == row - 1 && (destCol == col + 1 || destCol == col - 1)) {
                    return true;
                }
            }
        } else {
            if (pPointer == NULL) {
                if (destRow == row + 1 && destCol == col) {
                    return true;
                }
            } else {
                if (destRow == row + 1 && (destCol == col + 1 || destCol == col - 1)) {
                    return true;
                }
            }
        }

        return false;
    }

};

class Rook: public Piece { //SHOULD WORK AS ASSUMED
public:
    Rook(char c): Piece(c) {};
    virtual char getType() {
        return 'R';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        Piece *pPointer = matrix[destRow][destCol];

        if (row == destRow) {
            int colOffset = (destCol - col > 0) ? 1 : -1;
            int startCol = col += colOffset;
            // cout << "col Offset: " << colOffset << " StartCol: " << startCol << endl;
            for (int i = startCol; i != destCol; i += colOffset) {
                if (matrix[row][i] != NULL) { // if there is a piece in the way return false
                    return false;
                }
            }
            return true;
        }

        if (col == destCol) {
            int rowOffset = (destRow - row > 0) ? 1 : -1;
            int startRow = row += rowOffset;
            for (int i = startRow; i != destRow; i += rowOffset) {
                if (matrix[i][col] != NULL) {
                    return false;
                }
            }
            return true;
        }

        //cout << "You cant move diagonally with ROOK!?" << endl;
        return false;

    }
};

class Knight: public Piece {
public:
    Knight(char c): Piece(c) {};
    virtual char getType() {
        return 'N';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        if ((destRow == row + 1 || destRow == row - 1) && (destCol == col + 2 || destCol == col - 2)) {
            return true;
        } else if ((destRow == row + 2 || destRow == row - 2) && (destCol == col + 1 || destCol == col - 1)) {
            return true;
        }
        return false;
    }
};

class Bishop: public Piece { // SHOULD WORK AS ASSUMED
public:
    Bishop(char c): Piece(c) {};
    virtual char getType() {
        return 'B';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        Piece *pPointer = matrix[destRow][destCol];

        if (row != destRow || col != destCol) {
            if (abs(row - destRow) == abs(col - destCol)) {
                int rowOffset = (destRow - row > 0) ? 1 : -1;
                int colOffset = (destCol - col > 0) ? 1 : -1;
                int startRow = row += rowOffset;
                int startCol = col += colOffset;
                int iRow;
                int jCol = startCol;
                for (iRow = startRow; iRow != destRow; iRow += rowOffset, jCol += colOffset) {
                    if (matrix[iRow][jCol] != NULL) {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        return false;

    }

};

class Queen: public Piece {
public:
    Queen(char c): Piece(c) {};
    virtual char getType() {
        return 'Q';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        if (row == destRow) { // IF ITS THE SAME ROW, you can move
            int colOffset = (destCol - col > 0) ? 1 : -1;
            int startCol = col += colOffset;
            for (int i = startCol; i != destCol; i += colOffset) {
                if (matrix[row][i] != NULL) {
                    return false;
                }
            }
            return true;
        } else if (col == destCol) { // IF ITS THE SAME COLUMN, you can move
            int rowOffset = (destRow - row > 0) ? 1 : -1;
            int startRow = row += rowOffset;
            for (int i = startRow; i != destRow; i += rowOffset) {
                if (matrix[i][col] != NULL) {
                    return false;
                }
            }
            return true;
        } else if (abs(row - destRow) == abs(col - destCol)) { // IF ITS DIAGONAL MOVE, you can move
            //cout << abs(row - destRow) << " -> "<< abs(col - destCol) << endl;
            int rowOffset = (destRow - row > 0) ? 1 : -1;
            int colOffset = (destCol - col > 0) ? 1 : -1;
            int startRow = row += rowOffset;
            int startCol = col += colOffset;
            int iRow;
            int jCol = startCol;
            for (iRow = startRow; iRow != destRow; iRow += rowOffset, jCol += colOffset) {
                if (matrix[iRow][jCol] != NULL) {
                    return false;
                }
            }
            return true;
        }
        return false; // IF ITS NOT DIAGONAL or SAME ROW or SAME COLUMN MOVE, return false
    }
};

class King: public Piece {
public:
    King(char c): Piece(c) {};
    virtual char getType() {
        return 'K';
    }
private:
    bool checkPieceMoves(int row, int col, int destRow, int destCol, Piece *matrix[8][8]) {
        Piece *pPointer = matrix[destRow][destCol];
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (destRow == row + i && destCol == col + j ) {
                        return true;
                }
            }
        }
        return false;
    }
};

class Board {
public:

    Board() {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                matrix[row][col] = NULL;
            }
        }

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (row == 1) {
                    matrix[row][col] = new Pawn('B');
                } else if (row == 6) {
                    matrix[row][col] = new Pawn('W');
                }
            }
        }

        matrix[0][0] = new Rook('B');
        matrix[0][7] = new Rook('B');
        matrix[7][0] = new Rook('W');
        matrix[7][7] = new Rook('W');
        matrix[0][1] = new Knight('B');
        matrix[0][6] = new Knight('B');
        matrix[7][6] = new Knight('W');
        matrix[7][1] = new Knight('W');
        matrix[7][2] = new Bishop('W');
        matrix[7][5] = new Bishop('W');
        matrix[0][2] = new Bishop('B');
        matrix[0][5] = new Bishop('B');
        matrix[0][4] = new Queen('B');
        matrix[0][3] = new King('B');
        matrix[7][4] = new King('W');
        matrix[7][3] = new Queen('W');
    }

    int rowMultiply = 3;
    int colMultiply = 4;
    void printMap() {
        for (int row = 0; row < 8 * rowMultiply; row++) {

            if (row % 3 == 1) {
                cout << " " << 8 - row/3 << " ";
            } else {
                cout << "   ";
            }

            for (int col = 0; col < 8 * colMultiply; col++) {
                int currentRow = row / 3;
                int currentCol = col / 4;

                if (row % 3 == 1) {
                    if (matrix[currentRow][currentCol] != NULL) {
                        if (col % 4 == 1) {
                            cout << matrix[currentRow][currentCol]->getColor();
                        } else if (col % 4 == 2) {
                            cout << matrix[currentRow][currentCol]->getType();
                        } else {
                            if ((currentRow + currentCol) % 2 == 0) {
                                cout << " ";
                            } else {
                                cout << "*";
                            }
                        }
                    } else {

                        if ((currentRow + currentCol) % 2 == 0) {
                                cout << " ";
                            } else {
                                cout << "*";
                            }
                    }

                } else {
                    if ((currentRow + currentCol) % 2 == 0) {
                        cout << " ";
                    } else {
                        cout << "*";
                    }
                }
            }
            cout << endl;

        }

       // A = 65

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 36; col++) {
                int currentCol = col / 4;
                int charKey = 64 + currentCol;
                if (row % 3 == 1) {
                    if (col % 4 == 1 && currentCol > 0) {
                        cout << (char)charKey;
                    } else {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    Piece *matrix[8][8];

};

class Logic {
public:
    Logic(char c): playersTurn(c) {};
    Board boardMap;

    void changeTurn() {
        playersTurn = (playersTurn == 'W') ? 'B' : 'W';
    }

    char oppositeTurn(char c) {
        return (c == 'W') ? 'B' : 'W';
    }

    bool isInCheck(char color) { // (color) = preglejuje se barva trenutnega igralca, ki je na potezi
        int kingRow; // function returns true if king is in check or not
        int kingCol;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (boardMap.matrix[row][col] != NULL) {
                    if (boardMap.matrix[row][col]->getColor() == color && boardMap.matrix[row][col]->getType() == 'K') {
                        kingRow = row;
                        kingCol = col;
                    }
                }
            }
        }
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (boardMap.matrix[row][col] != NULL) {
                    if (boardMap.matrix[row][col]->getColor() != color) {
                        if (boardMap.matrix[row][col]->checkIfLegal(row, col, kingRow, kingCol, boardMap.matrix)) { // THIS LINE BREAKS!
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }

    bool canMove(char color) { // checks if a players king is in check

        for(int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (boardMap.matrix[i][j] != NULL) {
                    if (boardMap.matrix[i][j]->getColor() == color) {
                        for (int x = 0; x < 8; x++) {
                            for (int y = 0; y < 8; y++) {
                                if (boardMap.matrix[i][j]->checkIfLegal(i, j, x, y, boardMap.matrix)) {
                                    Piece *tempPiece = boardMap.matrix[x][y];
                                    boardMap.matrix[x][y] = boardMap.matrix[i][j];
                                    boardMap.matrix[i][j] = NULL;
                                    bool bCanMove = !isInCheck(color); // runs isInCheck function, which return true if the king is in check
                                    //undo the move
                                    boardMap.matrix[i][j] = boardMap.matrix[x][y];
                                    boardMap.matrix[x][y] = tempPiece;
                                    if (!bCanMove) {
                                        cout << "Player " << color << " has lost the game!" << endl;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    bool movePiece(int row, int col, int destRow, int destCol) {
        bool validMove = false;
        if (row < 8 && row >= 0 && col < 8 && col >= 0) {
            if (boardMap.matrix[row][col] != NULL) {
                if (boardMap.matrix[row][col]->getColor() == playersTurn) {
                    if (boardMap.matrix[row][col]->checkIfLegal(row, col, destRow, destCol, boardMap.matrix)) {
                        Piece *tempPiece = boardMap.matrix[destRow][destCol];
                        boardMap.matrix[destRow][destCol] = boardMap.matrix[row][col];
                        boardMap.matrix[row][col] = NULL;
                        if (!isInCheck(playersTurn)) {
                            delete tempPiece;
                            validMove = true;
                        } else {
                            boardMap.matrix[row][col] = boardMap.matrix[destRow][destCol];
                            boardMap.matrix[destRow][destCol] = tempPiece;
                        }
                    }
                }
            }
        }

        if (validMove == true) {
            return true;
        } else {
            cout << "Invalid move!" << endl;
            return false;
        }
    }

    void gameStart() {
        if (firstRound) {
            boardMap.printMap();
            firstRound = false;
        }

        string startingPiece;
        string location;
        cout << playersTurn  << "'s Turn:" << endl;
        cin >> startingPiece;
        cout << "Write move location coordinates:" << endl;
        cin >> location;

        int row = abs(startingPiece[0] - 56);
        int col = (int)startingPiece[1] - 65;
        int destRow = abs(location[0] - 56);
        int destCol = (int)location[1] - 65;

        /*cout << row << col << endl;
        cout << destRow << destCol << endl;*/

        if (movePiece(row, col, destRow, destCol)) {
            changeTurn();
            boardMap.printMap();
        }
    }

    string startingPiece;
    string location;

    bool checkMate = false;
    char playersTurn;
private:
    bool firstRound = true;
};

int main()
{
    Logic l('W');
    while (true) {
        if (!l.canMove(l.playersTurn)) {
            break;
        }
        l.gameStart();
    }

}
