#include "chess.h"

std::vector<int> Chess::possibleMove(int nb)
{
    std::vector<int> poMoves;
    int x, y;
    decode(nb, x, y);
    Type piece = board[x][y].type;
    switch (piece) {
        case BAUER:
            qDebug() << "bauer in pos" ;
            moveBauer(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case SPRINGER:
            qDebug() << "Springer in pos" ;
            moveSpringer(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case TURM:
            qDebug() << "Turm in pos" ;
            moveTurm(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case LAUFER:
            qDebug() << "Laufer in pos" ;
            moveLaufer(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case DAME:
            qDebug() << "Dame in pos" ;
            moveDame(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case KONIG:
            qDebug() << "Konig in pos" ;
            moveKonig(x, y, poMoves);
            //showFelds(poMoves, x, y);
            break;
        case NONE:
        default:
            qDebug() << "nicht erlaubt in pos" ;
            throw("clicked on something vide");
    }
    return poMoves;
}

const Piece& Chess::getKing(const Color& color) const {
    for(int i=0; i<8;i++)
        for(int j=0; j<8; j++)
            if(board[j][i].type == KONIG && board[j][i].color == color)
                return board[j][i];
    qDebug() << "something is wrong with find king. See implementation" ;
    throw("something called get King with NOCOL");
}

void Chess::showFelds(const std::vector<int>& poMoves, int x, int y) {
    if (poMoves.empty())
        qDebug() << "empty " ;
    for (auto k : poMoves) {
        decode(k, x, y);
    }
}

bool Chess::canMove(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8)
        return true;
    else
        return false;
}

bool Chess::initialise() {
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j) {
        if (i==1)
            board[j][i] = Piece(j, i, BAUER, WHITE);
        else if (i == 6)
            board[j][i] = Piece(j, i, BAUER, BLACK);
        else if((j==0 || j==7) && i == 0)
            board[j][i] = Piece(j, i, TURM, WHITE);
        else if ((j == 0 || j == 7) && i == 7)
            board[j][i] = Piece(j, i, TURM, BLACK);
        else if ((j == 1 || j == 6) && i == 0)
            board[j][i] = Piece(j, i, SPRINGER, WHITE);
        else if ((j == 1 || j == 6) && i == 7)
            board[j][i] = Piece(j, i, SPRINGER, BLACK);
        else if ((j == 2 || j == 5) && i == 0)
            board[j][i] = Piece(j, i, LAUFER, WHITE);
        else if ((j == 2 || j == 5) && i == 7)
            board[j][i] = Piece(j, i, LAUFER, BLACK);
        else if (j == 4  && i == 0)
            board[j][i] = Piece(j, i, KONIG, WHITE);
        else if (j == 4  && i == 7)
            board[j][i] = Piece(j, i, KONIG, BLACK);
        else if (j == 3 && i == 0)
            board[j][i] = Piece(j, i, DAME, WHITE);
        else if (j == 3 && i == 7)
            board[j][i] = Piece(j, i, DAME, BLACK);
        else
            board[j][i] = Piece(j, i, NONE, NOCOL);


        }
    return true;


}

void Chess::show() {

    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j)
            //std::cout << board[j][i].color << " "; // std::endl;

            if (board[j][i].type == BAUER)
                std::cout << " B ";
            else if (board[j][i].type == TURM)
                std::cout << " T ";
            else if (board[j][i].type == SPRINGER)
                std::cout << " S ";
            else if (board[j][i].type == LAUFER)
                std::cout << " L ";
            else if (board[j][i].type == KONIG)
                std::cout << " K ";
            else if (board[j][i].type == DAME)
                std::cout << " D ";
            else
                std::cout << " . ";
    std::cout << std::endl;
    }
}

void Chess::decode(int nb, int& x, int& y) {
    x = nb % 8;
    y = nb / 8;
}

int Chess::encode(int x, int y) {
    return x + y * 8;
}

Color Chess::getOpposite(const Piece& piece) const {
    Color col = (piece.color == WHITE )? BLACK :  WHITE;
    return col;
}

void Chess::moveBauer(int x, int y, std::vector<int>& poMoves) {
    Piece piece = board[x][y];
    if (piece.color == WHITE) {
        if (board[x][y + 1].type == NONE)
            poMoves.push_back(encode(x, y + 1));
        if (canMove(x+1,y+1) && board[x+1][y+1].color == BLACK)
                poMoves.push_back(encode(x + 1, y + 1));
        if (canMove(x -1 , y + 1) && board[x-1][y+1].color == BLACK)
                poMoves.push_back(encode(x - 1, y + 1));
        if (y == 1 && board[x][y + 2].type == NONE && board[x][y + 1].type == NONE)
                poMoves.push_back(encode(x, y + 2));
        //enPassant:
        if(canMove(x+1,y) && lastEnPassant.first == encode(x+1,y) && lastEnPassant.second == 1 && board[x+1][y].color == BLACK &&
                board[x+1][y].type == BAUER && canMove(x+1,y+1) && board[x+1][y+1].type ==NONE)
                poMoves.push_back(encode(x+1,y+1));
        if(canMove(x-1,y) && lastEnPassant.first == encode(x-1,y) && lastEnPassant.second == 1 && board[x-1][y].color == BLACK &&
                board[x-1][y].type == BAUER && canMove(x-1,y+1) && board[x-1][y+1].type ==NONE)
                poMoves.push_back(encode(x-1,y+1));
    }else if (piece.color == BLACK){
        if (board[x][y - 1].type == NONE)
                poMoves.push_back(encode(x, y - 1));
        if (canMove(x-1,y-1) && board[x-1][y-1].color == WHITE)
                poMoves.push_back(encode(x - 1, y - 1));
        if (canMove(x+1,y-1) && board[x+1][y-1].color == WHITE)
                poMoves.push_back(encode(x + 1, y - 1));
        if (y == 6 && board[x][y - 2].type == NONE && board[x][y - 1].type == NONE)
                poMoves.push_back(encode(x, y - 2));
        //enPassant:
        if(canMove(x+1,y) && lastEnPassant.first == encode(x+1,y) && lastEnPassant.second == 1 && board[x+1][y].color == WHITE &&
                board[x+1][y].type == BAUER && canMove(x+1,y-1) && board[x+1][y-1].type ==NONE)
                poMoves.push_back(encode(x+1,y-1));
        if(canMove(x-1,y) && lastEnPassant.first == encode(x-1,y) && lastEnPassant.second == 1 && board[x-1][y].color == WHITE &&
                board[x-1][y].type == BAUER && canMove(x-1,y-1) && board[x-1][y-1].type ==NONE)
                poMoves.push_back(encode(x-1,y-1));
    }
    else {
        qDebug() << "problem in move Bauer" ;
    }
}

void Chess::moveSpringer(int x, int y, std::vector<int>& poMoves) {

    if (canMove(x + 1, y + 2) &&
        (board[x + 1][y + 2].type == NONE ||
            getOpposite(board[x + 1][y + 2]) == board[x][y].color))
        poMoves.push_back(encode(x + 1, y + 2));

    if (canMove(x - 1, y + 2) &&
        (board[x - 1][y + 2].type == NONE ||
            getOpposite(board[x - 1][y + 2]) == board[x][y].color))
        poMoves.push_back(encode(x - 1, y + 2));


    if (canMove(x - 1, y - 2) &&
        (board[x - 1][y - 2].type == NONE ||
            getOpposite(board[x - 1][y - 2]) == board[x][y].color))
        poMoves.push_back(encode(x - 1, y - 2));

    if (canMove(x + 1, y - 2) &&
        (board[x + 1][y - 2].type == NONE ||
            getOpposite(board[x + 1][y - 2]) == board[x][y].color))
        poMoves.push_back(encode(x + 1, y - 2));

    if (canMove(x + 2, y + 1) &&
        (board[x + 2][y + 1].type == NONE ||
            getOpposite(board[x + 2][y + 1]) == board[x][y].color))
        poMoves.push_back(encode(x + 2, y + 1));

    if (canMove(x + 2, y - 1) &&
        (board[x + 2][y - 1].type == NONE ||
            getOpposite(board[x + 2][y - 1]) == board[x][y].color))
        poMoves.push_back(encode(x + 2, y - 1));


    if (canMove(x - 2, y + 1) &&
        (board[x - 2][y + 1].type == NONE ||
            getOpposite(board[x - 2][y + 1]) == board[x][y].color))
        poMoves.push_back(encode(x - 2, y + 1));


    if (canMove(x - 2, y - 1) &&
        (board[x - 2][y - 1].type == NONE ||
            getOpposite(board[x - 2][y - 1]) == board[x][y].color))
        poMoves.push_back(encode(x - 2, y - 1));
}

void Chess::moveTurm(int x, int y, std::vector<int>& poMoves) {
    //horizental RIGHT
    for (int i = x + 1; i < 8; ++i)
        if (board[i][y].type == NONE)
            poMoves.push_back(encode(i, y));
        else if (board[x][y].color == getOpposite(board[i][y])) {
            poMoves.push_back(encode(i, y));
            break;
        }
        else
            break;
    //horizental LEFT
    for (int i = x - 1; i >= 0; --i)
        if (board[i][y].type == NONE)
            poMoves.push_back(encode(i, y));
        else if (board[x][y].color == getOpposite(board[i][y])) {
            poMoves.push_back(encode(i, y));
            break;
        }
        else
            break;
    //vertical UP
    for (int i =y + 1; i <8; ++i)
        if (board[x][i].type == NONE)
            poMoves.push_back(encode(x, i));
        else if (board[x][y].color == getOpposite(board[x][i])) {
            poMoves.push_back(encode(x, i));
            break;
        }
        else
            break;
    //vertical DOWN
    for (int i = y - 1; i >= 0; --i)
        if (board[x][i].type == NONE)
            poMoves.push_back(encode(x, i));
        else if (board[x][y].color == getOpposite(board[x][i])) {
            poMoves.push_back(encode(x, i));
            break;
        }
        else break;
}

void Chess::moveLaufer(int x, int y, std::vector<int>& poMoves) {
    //diagonal RIGHT-up
    for (int i = x + 1; i < 8; ++i){
        if (canMove(i, y + i - x)) {
            if (board[i][y + i - x].type == NONE)
                poMoves.push_back(encode(i, y + i - x));
            else if (board[x][y].color == getOpposite(board[i][y + i - x])) {
                poMoves.push_back(encode(i, y + i - x));
                break;
            }
            else break;
        }
        else break;
}
//diagonal LEFT-down
    for (int i = x - 1; i >= 0; --i) {
        if (canMove(i, y - x + i)) {
            if (board[i][y - x + i].type == NONE)
                poMoves.push_back(encode(i, y - x + i));
            else if (board[x][y].color == getOpposite(board[i][y - x + i])) {
                poMoves.push_back(encode(i, y - x + i));
                break;
            }
            else
                break;
        }
        else break;
    }
    //diagonal left UP
    for (int i = y + 1; i < 8; ++i) {
        if (canMove(x - i + y, i)) {
            if (board[x - i + y][i].type == NONE)
                poMoves.push_back(encode(x - i + y, i));
            else if (board[x][y].color == getOpposite(board[x - i + y][i])) {
                poMoves.push_back(encode(x - i + y, i));
                break;
            }
            else
                break;
        }
        else break;
    }
    //vertical right down
    for (int i = y - 1; i >= 0; --i){
        if (canMove(x+y-i, i) ){
            if (board[x + y - i][i].type == NONE)
                poMoves.push_back(encode(x + y - i, i));
            else if (board[x][y].color == getOpposite(board[x + y - i][i])) {
                poMoves.push_back(encode(x + y - i, i));
                break;
            }
            else break;
        }
        else break;
    }
}

void Chess::moveDame(int x, int y, std::vector<int>& poMoves) {
    moveLaufer(x,y,poMoves);
    moveTurm(x, y, poMoves);
}

bool Chess::isFree (int x,int y) const{
    return board[x][y].type == NONE;
}

void Chess::moveKonig(int x, int y, std::vector<int>& poMoves) {
    std::vector<int> angreifer;
    int moves[8][2] = { {x + 1,y + 1}, {x,y + 1}, {x,y - 1}, {x - 1,y - 1},
                        {x + 1,y - 1}, {x - 1,y + 1},{x + 1,y},{x - 1,y} };
    for (int i = 0; i < 8; ++i) {
        int _x = moves[i][0];
        int _y = moves[i][1];
        if (canMove(_x, _y) && (board[_x][_y].type == NONE || board[_x][_y].color == getOpposite(board[x][y]))) {
            //Überprüfe ob es ein check gibt wenn du den Konig bewegst
            Piece tmp = board[_x][_y];
            board[_x][_y].color = board[x][y].color;
            board[_x][_y].type = board[x][y].type;
            board[x][y] = Piece(x, y, NONE, NOCOL);
            if(!check(board[_x][_y], angreifer))
                poMoves.push_back(encode(_x, _y));
            board[x][y].color = board[_x][_y].color;
            board[x][y].type = board[_x][_y].type;
            board[_x][_y].color = tmp.color;
            board[_x][_y].type = tmp.type;
        }
    }
    if(x == 4 && y == 0){
        Piece toBeChecked6 = Piece(6, 0, NONE, WHITE);
        Piece toBeChecked5 = Piece(5, 0, NONE, WHITE);
        Piece toBeChecked3 = Piece(3, 0, NONE, WHITE);
        Piece toBeChecked2 = Piece(2, 0, NONE, WHITE);
        Piece toBeChecked1 = Piece(1, 0, NONE, WHITE);
        if(board[7][0].type == TURM && board[7][0].color == WHITE && isFree(6,0) && isFree(5,0) && rochadeDR
                &&!check(toBeChecked6,angreifer) &&!check(toBeChecked5,angreifer))
            poMoves.push_back(encode(6,0));
        else if(board[0][0].type == TURM && board[0][0].color == WHITE && isFree(3,0) && isFree(2,0) && isFree(1,0) && rochadeDL
                &&!check(toBeChecked3,angreifer) &&!check(toBeChecked2,angreifer) &&!check(toBeChecked1,angreifer))
            poMoves.push_back(encode(2,0));
    }else if(x == 4 && y == 7){
        Piece toBeChecked6 = Piece(6, 7, NONE, BLACK);
        Piece toBeChecked5 = Piece(5, 7, NONE, BLACK);
        Piece toBeChecked3 = Piece(3, 7, NONE, BLACK);
        Piece toBeChecked2 = Piece(2, 7, NONE, BLACK);
        Piece toBeChecked1 = Piece(1, 7, NONE, BLACK);
        if(board[7][7].type == TURM && board[7][7].color == BLACK && isFree(6,7) && isFree(5,7) && rochadeUR
             &&!check(toBeChecked6,angreifer) &&!check(toBeChecked5,angreifer))
            poMoves.push_back(encode(6,7));
        else if(board[0][7].type == TURM && board[0][7].color == BLACK && isFree(3,7) && isFree(2,7) && isFree(1,7) && rochadeUL
                &&!check(toBeChecked3,angreifer) &&!check(toBeChecked2,angreifer) &&!check(toBeChecked1,angreifer))
            poMoves.push_back(encode(2,7));
    }
}

bool Chess::check(const Piece& piece, std::vector<int>& angreiferVec) {
    //check horizentally
    bool okHL = checkHorizentalLeft(piece, angreiferVec);
    bool okHR = checkHorizentalRight(piece, angreiferVec);
    //check Vertically
    bool okVU = checkVerticalUp(piece, angreiferVec);
    bool okVD = checkVerticalDown(piece, angreiferVec);
    //check diagonal_up
    bool okDRU = checkDiagonalRightUp(piece, angreiferVec);
    bool okDLU = checkDiagonalLeftUp(piece, angreiferVec);
    //check diagonal_down
    bool okDRD = checkDiagonalRightDown(piece, angreiferVec);
    bool okDLD = checkDiagonalLeftDown(piece, angreiferVec);
    //check Springer
    bool okS = checkSpringer(piece, angreiferVec);

    return okHL||okHR||okVU||okVD||okDRU||okDLU||okDRD||okDLD||okS;
}

bool Chess::checkHorizentalRight(const Piece& piece, std::vector<int>& angreifer)  {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x + 1; i < 8; ++i) {
        if (board[i][y].type == NONE) {
            continue;
        }
        if (board[i][y].color == piece.color)
            break;
        else if (board[i][y].type == DAME || board[i][y].type == TURM) {
            angreifer.push_back(encode(i, y));
            return true;
        }
        else break;

    }
    return false;
}

bool Chess::checkHorizentalLeft(const Piece& piece, std::vector<int>& angreifer)  {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x - 1; i >= 0; --i) {
        if (board[i][y].type == NONE) {
            continue;
        }
        if (board[i][y].color == piece.color)
            break;
        else if (board[i][y].type == DAME || board[i][y].type == TURM) {
            angreifer.push_back(encode(i, y));
            return true;
        }
        else break;

    }
    return false;
}

bool Chess::checkVerticalUp(const Piece& piece, std::vector<int>& angreifer)  {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = y + 1; i < 8; ++i) {
        if (board[x][i].type == NONE) {
            continue;
        }
        if (board[x][i].color == piece.color)
            break;
        else if (board[x][i].type == DAME || board[x][i].type == TURM) {
            angreifer.push_back(encode(x, i));
            return true;
        }
        else break;

    }
        return false;
    }

bool Chess::checkVerticalDown(const Piece & piece, std::vector<int> & angreifer)  {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = y - 1; i >= 0; --i) {
        if (board[x][i].type == NONE) {
            continue;
        }
        if (board[x][i].color == piece.color)
            break;
        else if (board[x][i].type == DAME || board[x][i].type == TURM) {
            angreifer.push_back(encode(x, i));
            return true;
        }
        else break;

    }
    return false;
}

bool Chess::checkDiagonalRightUp(const Piece& piece, std::vector<int>& angreifer)  {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; ++i, ++j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == piece.color)
            break;
        else if ((board[i][j].type == BAUER && piece.color == WHITE && i == x + 1)
            || board[i][j].type == DAME || board[i][j].type == LAUFER) {
            angreifer.push_back(encode(i, j));
            return true;
        }
        else break;
    }
    return false;
}

bool Chess::checkDiagonalRightDown(const Piece& piece, std::vector<int>& angreifer){
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; ++i, --j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == piece.color)
            break;
        else if ((board[i][j].type == BAUER && piece.color == BLACK && i == x + 1)
            || board[i][j].type == DAME || board[i][j].type == LAUFER) {
            angreifer.push_back(encode(i, j));
            return true;
        }
        else break;
    }
    return false;
}

bool Chess::checkDiagonalLeftUp(const Piece& piece, std::vector<int>& angreifer) {
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == piece.color)
            break;
        else if ((board[i][j].type == BAUER && piece.color == WHITE && i == x - 1)
            || board[i][j].type == DAME || board[i][j].type == LAUFER) {
            angreifer.push_back(encode(i, j));
            return true;
        }
        else break;
    }
    return false;
}

bool Chess::checkDiagonalLeftDown(const Piece& piece, std::vector<int>& angreifer){
    int x = piece.positionX;
    int y = piece.positionY;
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == piece.color)
            break;
        else if ((board[i][j].type == BAUER && piece.color == BLACK && i == x - 1)
            || board[i][j].type == DAME || board[i][j].type == LAUFER) {
            angreifer.push_back(encode(i, j));
            return true;
        }
        else break;
    }
    return false;
}

bool Chess::checkSpringer(const Piece& piece, std::vector<int>& angreifer) {
    bool ok = false;
    int x = piece.positionX;
    int y = piece.positionY;
    int moves[8][2] = { {x + 1,y + 2}, {x + 1,y - 2}, {x - 2,y + 1}, {x - 2,y - 1},
                        {x + 2,y - 1}, {x + 2,y + 1}, {x - 1,y + 2},{x - 1,y - 2}};
    for (int i = 0; i < 8; ++i) {

        int _x = moves[i][0];
        int _y = moves[i][1];
        if (canMove(_x, _y)) {
            if (board[_x][_y].type == NONE)
                continue;
            if (board[_x][_y].color == piece.color)
                continue;
            else if (board[_x][_y].type == SPRINGER) {
                angreifer.push_back(encode(_x, _y));
                ok = true;
            }
            else continue;
        }
    }
    return ok;
}

bool Chess::checkMate(const Piece& king)
{

    std::vector<int> angreiferZahl;
    bool checkMate = false;
    int x = king.positionX;
    int y = king.positionY;

    //can the king move
    if (false == check(king, angreiferZahl)){
        return false;
    }
    std::vector<int> canMove;
    moveKonig(x, y, canMove);
    for (auto n : canMove)
        qDebug()<< n << " ";
    if (!canMove.empty()){
        return false;
    }
    int attX = 0, attY = 0;

    //can take down the piece
    if (angreiferZahl.size() == 1) {
        decode(angreiferZahl[0], attX, attY);
        if (check(board[attX][attY], angreiferZahl))
            return false;

    //see if it can be blocked
        switch (board[attX][attY].type)
        {
        case BAUER:
        case SPRINGER:
            checkMate = true;
            break;
        case LAUFER:
        case TURM:
        case DAME:
            checkMate = !canBlock(board[attX][attY], king);
            break;
        default:
            std::cout << "in check mate: should not be here or type is NONE which is not logic" << std::endl;
        break;
        }
    }else {
        checkMate = true;
        gameEnd = true;
    }
    qDebug() << "is it check mate " << checkMate ;
    return checkMate;
}

bool Chess::canBeReached(int x, int y, const Color& col) {
    Piece toBeChecked = Piece(x, y, NONE, col);
    std::vector<int> dummie;

    //check in the diagonal
    //right up
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; ++i, ++j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == col)
            break;
        else if (board[i][j].type == DAME || board[i][j].type == LAUFER)
            return true;
        else break;
    }
    // right down
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; ++i, --j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == col)
            break;
        else if (board[i][j].type == DAME || board[i][j].type == LAUFER)
            return true;
        else break;
    }
    //left UP
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; --i, ++j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == col)
            break;
        else if (board[i][j].type == DAME || board[i][j].type == LAUFER)
            return true;
        else break;
    }
    //left DOWN
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j].type == NONE)
            continue;
        if (board[i][j].color == col)
            break;
        else if (board[i][j].type == DAME || board[i][j].type == LAUFER)
            return true;
        else break;
    }
    if (checkHorizentalRight(toBeChecked, dummie) ||
        checkHorizentalLeft(toBeChecked, dummie) ||
        checkVerticalUp(toBeChecked, dummie) ||
        checkVerticalDown(toBeChecked, dummie) ||
        checkSpringer(toBeChecked,dummie))
        return true;

    //check BAUERN
    if ((canMove(x, y + 1) && board[x][y + 1].type == BAUER && board[x][y + 1].color == BLACK && col == WHITE) ||
        (canMove(x, y - 1) && board[x][y - 1].type == BAUER && board[x][y - 1].color == WHITE && col == BLACK))
        return true;

    return false;
}

bool Chess::canBlock(const Piece& attacker, const Piece& king) {
    Color col = attacker.color;
//    qDebug() << "entered here color ->" << col << "attacker ->" << attacker.positionX << " " << attacker.positionY ;
//    qDebug() << "entered here color ->" << king.color << "king->" << king.positionX << " " << king.positionY ;

    if (attacker.positionY == king.positionY) {
        //horizental move
        if (attacker.positionX < king.positionX){
            for (int i = attacker.positionX + 1; i < king.positionX; ++i)
                if (canBeReached(i,attacker.positionY,col))
                    return true;
        }
        else {
            for (int i = attacker.positionX - 1; i > king.positionX; --i)
                if (canBeReached(i,attacker.positionY, col))
                    return true;
        }
    }
    else if (attacker.positionX == king.positionX) {
        //Vertical move
        if (attacker.positionY < king.positionY) {
            for (int i = attacker.positionY + 1; i < king.positionY; ++i)
                if (canBeReached(attacker.positionX, i, col))
                    return true;
        }
        else {
            qDebug() << "entered here vertical ";
            for (int i = attacker.positionY - 1; i > king.positionY; --i)
                if (canBeReached(attacker.positionX,i, col))
                    return true;
        }
    }
    else if (attacker.positionX < king.positionX) {
        //diagonal right up
        if (attacker.positionY < king.positionY) {
            for (int i = 1; i < std::abs(attacker.positionX - king.positionX); ++i)
                if (canBeReached(attacker.positionX + i, attacker.positionY + i, col))
                    return true;
        //diagonal right down
        }else if(attacker.positionY > king.positionY)
            for (int i = 1; i < std::abs(attacker.positionX - king.positionX); ++i)
                if (canBeReached(attacker.positionX + i, attacker.positionY - i, col))
                    return true;
    }
    else if (attacker.positionX > king.positionX) {
        //diagonal left up
        if (attacker.positionY < king.positionY) {
            for (int i = 1; i < std::abs(attacker.positionX - king.positionX); ++i)
                if (canBeReached(attacker.positionX - i, attacker.positionY + i, col))
                    return true;

        }
        //diagonal left down
        else if (attacker.positionY > king.positionY)
            for (int i = 1; i < std::abs(attacker.positionX - king.positionX); ++i)
                if (canBeReached(attacker.positionX - i, attacker.positionY - i, col))
                    return true;
    }
    else {
        qDebug() << "error in can be blocked .. case unmöglisch";
    }
    return false;
}

const std::vector<int> Chess::getPieces(const Color& col) {
    std::vector<int> pieces;
    for (int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            if(board[j][i].color == col)
                pieces.push_back(static_cast<int>(encode(j,i)));
    return pieces;
}

void Chess::changeTurn(){
    turn = (turn == BLACK ? WHITE : BLACK);
    if (turn == myColor)
        emit whoseTurn(true);
    else
        emit whoseTurn(false);
}

void Chess::changeMatrix(int start, int end){
    int sX,sY,zX,zY;
    decode(start,sX,sY);
    decode(end,zX,zY);
    board[zX][zY].color = board[sX][sY].color;
    board[zX][zY].type = board[sX][sY].type;
    board[sX][sY].setToNone();
    qDebug() << "";
    qDebug() << " in change matrix";
    qDebug() <<"";
    show();
    std::cout << std::endl;

}

void Chess::setColors(int we, int beginnender, int gegnerNummer){
    std::vector<int> dump;
    _we = we;
    _gegnerNummer = gegnerNummer;
    _beginnender = beginnender;
    if((beginnender == 0 && we == 0) || (beginnender == 1 && we == 1)){ // we begin we hilight our teils
            qDebug() << "I begin " << "we "<< we << "beginnender " << beginnender ;
            myColor = turn = WHITE;
            otherColor = BLACK;
            initialise();
            auto myPieces = getPieces(myColor);
            emit startGui(static_cast<int>(myColor)-1);
            emit whereToMove(dump,myPieces);
            emit whoseTurn(true);
        }
     else if((beginnender == 1 && we == 0) || (beginnender == 0 && we == 1)){ //we are not beginning we wait
            qDebug() << "I wait " << "we "<< we << "beginnender " << beginnender ;
            otherColor = turn = WHITE;
            myColor = BLACK;
            initialise();
            emit startGui(static_cast<int>(myColor)-1);
            emit whoseTurn(false);
            emit whereToMove(dump,dump);
        }else{
            qDebug() << "start symbols are not right";
            emit errorState();
    }
    emit sendOppData(gegnerNummer,static_cast<int>(otherColor)-1);
}

void Chess::moveFromGUI(int nb){
    int x,y;
    decode(nb,x,y);
    std::vector<int> fields,dummie;
    std::vector<int> pieces = getPieces(myColor); //change to myColor
    if(click == 0){
            fields = possibleMove(nb);
            emit whereToMove(fields, pieces);
            startClick = nb;
            ++click;
    }else if(click == 1){
        if(std::find(pieces.begin(),pieces.end(),nb) != pieces.end()){
            qDebug() << "clicked on a piece of me on second click";
            fields = possibleMove(nb);
            emit whereToMove(fields, pieces);
            startClick = nb;
        }else{
            quint8 status;
            endClick = nb;
            int sX,sY,zX,zY;
            decode(startClick,sX,sY);
            decode(endClick,zX,zY);

            qDebug() <<"your clicks " << "click 1 : " << sX << " " << sY << "click 2 : "<< zX << " " << zY;

            // to debug
            fields = possibleMove(startClick);
            if(std::find(fields.begin(),fields.end(),endClick) == fields.end())
            {
                qDebug() << "retry ...";
                click = 0;
                return;
            }
            //
            bool matrixChanged = false;
            auto startp = board[sX][sY];
            auto endp = board[zX][zY];
            // check for no check
            auto myKing = getKing(myColor);

            changeMatrix(startClick,endClick);
            if(check(getKing(myColor),dummie)){
                qDebug() << "first highlight ";
                std::vector<int> empt;
                emit whereToMove(empt,pieces);
                emit hilightCheck(dummie,encode(myKing.positionX,myKing.positionY));
                click = 0;
                reverseModifyMatrix(startp,endp);
                return;
            }
            reverseModifyMatrix(startp,endp);

            if(check(getKing(myColor),dummie)){
                changeMatrix(startClick,endClick);
                matrixChanged = true;
                if(check(getKing(myColor),dummie)){
                    qDebug() << "my king in check move it ";
                // emit checkMyKing(encode(myKing.positionX,myKing.positionY));
                    std::vector<int> empt;
                    emit whereToMove(empt,pieces);
                    emit hilightCheck(dummie,encode(myKing.positionX,myKing.positionY));
                    click = 0;
                    reverseModifyMatrix(startp,endp);
                    return;
                }
            }
            if(matrixChanged){
                qDebug() << "matrix changed ";
                reverseModifyMatrix(startp,endp);
            }
            Type zielType = board[zX][zY].type ;
            qDebug() << "ziel " <<zielType;
                if(zielType==NONE)
                    emit modifyGui(startClick,endClick,0);
                else
                    emit modifyGui(startClick,endClick,1);
            qDebug() << "Was GUI erhält " << startClick << endClick;
            click = 0;
            std::vector<quint8> myMove;
            myMove.push_back(0x03);
            myMove.push_back(0x05);
            myMove.push_back(static_cast<quint8>(sX));
            myMove.push_back(static_cast<quint8>(sY));
            myMove.push_back(static_cast<quint8>(zX));
            myMove.push_back(static_cast<quint8>(zY));
            Piece king = getKing(otherColor);
            if (zielType== NONE)
                status = 0x00;
            else
                status = 0x01;
            if(board[sX][sY].type == BAUER && bauerUmwandlung(startClick,endClick)){
                qDebug() << "umwandlung!!!!!!  1";
                emit myBauerUmwandlung(endClick, static_cast<int>(myColor)-1); //so that white is 0 and black is 1
                qDebug() << "GUI gets " << endClick << " " << static_cast<int>(myColor)-1 ;
                return;
            }
            if(board[sX][sY].type == BAUER && checkEnPassant(startClick,endClick)){
                    lastEnPassant.first = endClick;
                    lastEnPassant.second = 0;
            }else if(board[sX][sY].type == BAUER && attackEnPassant(startClick,endClick,true)){ //changes matrix and sends signal
                    lastEnPassant.first = endClick;
                    lastEnPassant.second = 1;
                    status = 0x01;
            }

            if(board[sX][sY].type == KONIG && checkForRochade(startClick,endClick)){
                changeMatrixRochade(startClick,endClick);
                status = 0x04;
            }

            changeMatrix(startClick,endClick);

            if(checkMate(king)){
                if(zielType == NONE)
                    status = 0x02;
                else
                    status = 0x03;
            }

            myMove.push_back(status);
            qDebug()<<"";
            for(auto i: myMove)
                qDebug() << "what server gets " << i;
            changeTurn();
            updateRochade(myColor);
            countPoints();
            ++lastEnPassant.second;
            emit ourMove(myMove);
        }
    }
}

bool Chess::isPossible(int sX, int sY, int zX, int zY){
    std::vector<int> moves = possibleMove(encode(sX,sY));
    int g = encode(sX,sY);
    qDebug() << "here in isPossible.. Piece : " << g ;
    bool empty = moves.empty();
    qDebug() << "empty ? " << empty;
    for (auto i: moves)
        qDebug() << i << " ";

    return std::find(moves.begin(),moves.end(),encode(zX,zY)) != moves.end();
}

void Chess::responseFromNetwork(quint8 response){
    switch(response){
        case 0x00:
        case 0x01:
            qDebug() << "alles ok " ;
            break;
        case 0x02:
            qDebug() << "we win";
            emit weWin();
             break;
        default:
        qDebug() << "something is wrong with other logic or received something wrong from server";
        emit errorState();
         break;
    }
}

bool Chess::checkForRochade(int start, int ziel){
    return std::abs(start-ziel) == 2;
}

void Chess::changeMatrixRochade(int start, int end){
    int sX,sY,zX,zY;
    decode(start,sX,sY);
    decode(end,zX,zY);
    if (start < end){
        if(end == 6){
            changeMatrix(7,5);
            emit modifyGui(7,5,0);
        }else{
            changeMatrix(63,61);
            emit modifyGui(63,61,0);
        }
    }else{
        if(end == 2){
            changeMatrix(0,3);
            emit modifyGui(0,3,0);
        }else{
            changeMatrix(56,59);
            emit modifyGui(56,59,0);
        }
       }
}

bool Chess::bauerUmwandlung(int start, int end) {
    int sX,sY,zX,zY;
    decode(start,sX,sY);
    decode(end,zX,zY);
    return ((sX==zX || sX == zX-1 || sX == zX+1) &&
            ((zY==7 && board[sX][sY].color == WHITE)||(zY==0 && board[sX][sY].color == BLACK)));
}

void Chess::myBauerChange(int piece){
    qDebug() << "in bauer change ";
    std::vector<quint8> myMove;
    myMove.push_back(0x03);
    myMove.push_back(0x05);
    int sX,sY,zX,zY;
    decode(startClick,sX,sY);
    decode(endClick,zX,zY);
    myMove.push_back(static_cast<quint8>(sX));
    myMove.push_back(static_cast<quint8>(sY));
    myMove.push_back(static_cast<quint8>(zX));
    myMove.push_back(static_cast<quint8>(zY));
    Piece neu;
    quint8 status = 0xFF;
    Type zielType = board[zX][zY].type ;
    switch(piece){
    case 1:
        neu=Piece(zX,zY,LAUFER,myColor);
        if (zielType== NONE)
            status = 0x10;
        else
            status = 0x11;
        changeMatrix(startClick,endClick);
        board[zX][zY] = neu;
        show();
        if(checkMate(getKing(otherColor))){
            if(zielType == NONE)
                status = 0x12;
            else
                status = 0x13;
        }
        break;
    case 2:
        neu=Piece(zX,zY,SPRINGER,myColor);
        if (zielType== NONE)
            status = 0x20;
        else
            status = 0x21;
        changeMatrix(startClick,endClick);
        board[zX][zY] = neu;
        show();
        if(checkMate(getKing(otherColor))){
            if(zielType == NONE)
                status = 0x23;
            else
                status = 0x23;
        }
        break;
    case 3:
        neu=Piece(zX,zY,TURM,myColor);
        if (zielType== NONE)
            status = 0x30;
        else
            status = 0x31;
        changeMatrix(startClick,endClick);
        board[zX][zY] = neu;
        show();
        if(checkMate(getKing(otherColor))){
            if(zielType == NONE)
                status = 0x32;
            else
                status = 0x33;
        }
        break;
    case 4:
        neu=Piece(zX,zY,DAME,myColor);
        if (zielType== NONE)
            status = 0x40;
        else
            status = 0x41;
        changeMatrix(startClick,endClick);
        board[zX][zY] = neu;
        show();
        if(checkMate(getKing(otherColor))){
            if(zielType == NONE)
                status = 0x42;
            else
                status = 0x43;
        }
        break;
    }
    myMove.push_back(status);
    std::cout << std::endl;
    for(auto i: myMove)
        qDebug() << "what server gets (bauer umwandlung) " << i;
    qDebug() << (status >> 4);
    qDebug() << (status & 0x0F);
    updateRochade(myColor);
    myMaxPoints += getValuePiece(neu)-1;
    countPoints();
    changeTurn();
    emit ourMove(myMove);
}

bool Chess::checkEnPassant(int start, int end){
        int sX,sY,zX,zY;
        decode(start,sX,sY);
        decode(end,zX,zY);
        switch(board[sX][sY].color){
             case WHITE:
                    if(std::abs(start-end) == 16 && start<16 && start>7){
                        return true;
                 }else return false;
             case BLACK:
                    if(std::abs(start-end) == 16 && start<56 && start>47){
                        return true;
                 }else return false;
             default:
                    qDebug() << "should not be here check en passant must have color";
                            return false;

        }

}

bool Chess::attackEnPassant(int start,int end, bool schlag){
    int sX,sY,zX,zY;
    decode(start,sX,sY);
    decode(end,zX,zY);
    bool ok = false;
    if(board[sX][sY].type == BAUER){
    switch (board[sX][sY].color) {
    case WHITE:
            if((zX == sX+1 && zY == sY +1 && board[zX][zY].type == NONE) ||
                   (zX == sX-1 && zY == sY +1 && board[zX][zY].type == NONE)){
                if(schlag){
                board[zX][sY].type = NONE;
                board[zX][sY].color= NOCOL;
                emit enPassant(end-8);
                qDebug() << " GUI gets enPassant " << end-8;}
                ok = true;
            }
        break;
    case BLACK:
        if((zX == sX+1 && zY == sY -1 && board[zX][zY].type == NONE) ||
               (zX == sX-1 && zY == sY -1 && board[zX][zY].type == NONE)){
            if(schlag){
            board[zX][sY].type = NONE;
            board[zX][sY].color= NOCOL;
            emit enPassant(end+8);
            qDebug() << " GUI gets enPassant " << end+8;}
            ok = true;
        }
    break;
    default:
        qDebug() << "darf nicht hier sein da bauer ein color hat (attack en passant)";
        throw("attack en passant");

    }
    }else
        ok = false;
    return ok;
}

void Chess::moveFromNetwork(int sX, int sY, int zX, int zY, int status, int piece){
    quint8 typ = 0x05;
    std::vector<quint8> response;
    int start = encode(sX,sY);
    int end = encode(zX,zY);
    //if the positions are false
    if(!canMove(sX,sY) || !canMove(zX,zY)){
        qDebug() << "Piece or ziel outside the board";
        emit errorState();
    }else if(turn != otherColor){ //nicht an der Reihe
        qDebug() << "i am here";
        typ = 0x07;
    }
    else if(board[sX][sY].type == NONE){ //nicht your piece
        qDebug() << "nichts here";
        typ = 0x03;
    }
    else if(board[sX][sY].color == myColor){
        qDebug() <<"nicht dein color";
        typ = 0x04;
    }
    else if(isPossible(sX,sY,zX,zY)){
        Color zielcolor = board[zX][zY].color;
        //send signal to gui if there is a bauerumwandlung
        if((piece>0 )){
            qDebug() << "piece > 0 .. ";
            if(board[sX][sY].type == BAUER && bauerUmwandlung(start,end)){
                if(zielcolor == myColor)
                    emit modifyGui(start,end,1);
                else
                    emit modifyGui(start,end,0);
                emit bauerUmwandlungOpp(end,static_cast<int>(otherColor)-1,piece);

                qDebug() << "bauernumwandlung ...  " << end << " " << static_cast<int>(otherColor)-1 << " " << piece;
            //check for schlag or nicht schlag
            }else{
                qDebug() << " no umwandlung or no such piece ";
                response.push_back(0x04);
                response.push_back(0x01);
                response.push_back(0x04);
                emit ourResponse(response);
                qDebug() << "response " << (response[2] >> 4) << " " << (response[2] & 0x0F);
                changeTurn();
                emit errorState();
                return;
            }
        }


        switch (status) {
            case 1:{
            //with enpassant ,, no rochade
                if((zielcolor == myColor || attackEnPassant(start,end,true)) &&
                        !(board[sX][sY].type == KONIG && std::abs(zX-sX)==2) &&
                         !(board[sX][sY].type == BAUER && (zY == 7 || zY == 0) && piece == 0)){
                    qDebug() << "move schlagt.. ";
                    typ = 0x01;
                }
                else{
                    typ = 0x06;
                    qDebug() << "recieved geschlagen aber nicht geschlagen";
                }
        }
                break;
            case 0:{
            if(board[zX][zY].color == NOCOL && !(board[sX][sY].type == KONIG && std::abs(zX-sX)==2)
                        && !attackEnPassant(start,end,false) &&
                        !(board[sX][sY].type == BAUER && (zY == 7 || zY == 0) && piece == 0) ){
                    qDebug() << "move nicht schlagt  ";
                    typ = 0x00;
                    if(board[sX][sY].type == BAUER && checkEnPassant(start,end)){
                        qDebug()<<"wooooooooorked ";
                        lastEnPassant.first = encode(zX,zY);
                        lastEnPassant.second = 0;
                    }
                }
                else{
                    qDebug() << "nicht ok << schlagt nicht recieved aber schlagt oder versucht rochade ohne richtiges code"
                                "oder da muss ein Bauer umwandlung da sein recieved aber without Bauerumwandlung";
                    emit errorState();}
        }
                break;
            case 2:{
            if(!(board[sX][sY].type == KONIG && std::abs(zX-sX)==2)){
                changeMatrix(start,end);
                if(piece>0){ //if there is umwandlung
                    Piece neu = getNeuPiece(zX,zY,piece);
                    board[zX][zY].color = neu.color;
                    board[zX][zY].type = neu.type;
                }
                if(checkMate(getKing(myColor)) && zielcolor == NOCOL){
                    qDebug() << "in checkmate ";
                    typ = 0x02;
                }else{
                    bool test = checkMate(getKing(myColor));
                    qDebug() << " is it checkmate .... : " << test;
                    typ = 0x08;
                    qDebug() << "recieved schachmate oder schahmate ohne schlag aber nich schachmate oder nicht shachmate ohne schlag";
                    }
            }else{
                    typ = 0x04;
                    qDebug() << "recieved move of rochade but no rochade";
            }
        }
                break;
            case 3:{
            if(!(board[sX][sY].type == KONIG && std::abs(zX-sX)==2)){
                changeMatrix(start,end);
                if(piece>0){
                    Piece neu = getNeuPiece(zX,zY,piece);
                    board[zX][zY].color = neu.color;
                    board[zX][zY].type = neu.type;
                }
                if(checkMate(getKing(myColor)) && zielcolor == myColor)
                    typ = 0x02;
                else{
                    typ = 0x08;
                    qDebug() << "recieved schachmate und schlagt aber nich schachmate und schlagt";
                    }
            }else{
                qDebug() << "cant move king there .. muss uber rochade gehen";
                typ =0x04;
            }
                 }
                break;
            case 4:{
            qDebug() << "I m heeeeeere for check rochade";
            if(board[sX][sY].type == KONIG && checkForRochade(start,end)){
               qDebug() << "rochade ... ";
                typ = 0x00;
                changeMatrixRochade(start,end);
            }else{
                qDebug() << "no rochade ";
                typ = 0x04;
            }
        }
                break;
            default:{
            typ = 0x04;
                qDebug() << "recieved wrong value from netz";
        }
                break;
            }
    }
    else{
     qDebug() << "move not possible .. ";
        typ = 0x04;
    }


    if(checkKingBeforeMove(start,end)){
       typ = 0x04;
       qDebug() << "king in check";
    }

    bool enPassant = attackEnPassant(start,end,false);
    if((typ & 0x0F) == 0 || (typ & 0x0F) == 1){
        qDebug() << " hey I changed matrix";
        changeMatrix(start,end);
        if(piece == 0)
        {
            if((typ & 0x0F) == 0|| enPassant)

                emit modifyGui(start,end,0);
            else
                emit modifyGui(start,end,1);
        }else{
            qDebug() << "second cond";
            board[zX][zY] = getNeuPiece(zX,zY,piece);
            otherMaxPoints += getValuePiece(board[zX][zY])-1;
            if(checkMate(getKing(myColor)) && !(typ == 0x02)) // there is a checkmate but opponent didn't declare it
            {        typ = 0x08;
                qDebug() << "there is a checkmate but opponent didn't declare it";
            }
            show();
        }
        qDebug() << "second cond";
        std::vector<int> empty;
        auto myTiles = getPieces(myColor);
        emit whereToMove(empty,myTiles);
        changeTurn();
    }else if(typ == 0x02)
        emit weLose();

    updateRochade(otherColor);
    response.push_back(0x04);
    response.push_back(0x01);
    response.push_back(typ);
    ++lastEnPassant.second;
    countPoints();
   emit ourResponse(response);
    if(typ != 0x00 && typ != 0x01 && typ != 0x02 && typ != 0x07)
        emit errorState();
    qDebug() << "was server hat " << (typ >> 4) << " " << (typ & 0x0F);
}

const Piece Chess::getNeuPiece(int zX,int zY,int piece) const{
    switch (piece) {
    case 1:
        return Piece(zX,zY,LAUFER,otherColor);
    case 2:
        return Piece(zX,zY,SPRINGER,otherColor);
    case 3:
        return Piece(zX,zY,TURM,otherColor);
    case 4:
        return Piece(zX,zY,DAME,otherColor);
    default:
        return Piece();
    }

}

void Chess::reverseModifyMatrix(Piece start, Piece end){
    qDebug() << "in reverse matrix";
    qDebug() << "piece to move at end " << end.type;
    qDebug() << "piece to move at start " << start.type;
    board[end.positionX][end.positionY] = end;
    board[start.positionX][start.positionY] = start;
    show();
}

bool Chess::checkKingBeforeMove(int start,int end){
    int sX,sY,zX,zY;
    decode(start,sX,sY);
    decode(end,zX,zY);
    auto startp = board[sX][sY];
    auto endp = board[zX][zY];
    std::vector<int> dummie;
    bool matrixChanged = false;
    if(check(getKing(otherColor),dummie)){
        qDebug() << "i aM here 2";
        changeMatrix(start,end);
        matrixChanged = true;
        if(check(getKing(otherColor),dummie)){
            qDebug() << "king in check move it ";
            reverseModifyMatrix(startp,endp);
            return true;
        }
    }
    if(matrixChanged)
        reverseModifyMatrix(startp,endp);
    return false;
}

void Chess::mySurrender(){
    std::vector<quint8> aufg;
    aufg.push_back(0xFF);
    aufg.push_back(0x00);
    emit surrender(aufg);
    qDebug()<<"###########SURRENDER###########";
    emit weLoseSurrender();
}

void Chess::updateRochade(const Color &col){
   switch(col){
       case WHITE:{
             if(rochadeDL)
                if(!(board[0][0].type == TURM && board[4][0].type == KONIG))
                    rochadeDL=false;
            if(rochadeDR)
                if(!(board[7][0].type == TURM && board[4][0].type == KONIG))
                    rochadeDR = false;
                  }
       break;
   case BLACK:{
       if(rochadeUL)
           if(!(board[0][7].type == TURM && board[4][7].type == KONIG))
               rochadeUL=false;
       if(rochadeUR)
           if(!(board[7][7].type == TURM && board[4][7].type == KONIG))
               rochadeUR = false;
   }
       break;
   default:{
       qDebug() << " something wrong with update rochade bool";
   }
       break;
    }
}

void Chess::countPoints(){
    int myteils=0,otherTeils=0;
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            if(board[i][j].color == myColor)
            {
                myteils+=getValuePiece(board[i][j]);
            }else if(board[i][j].color == otherColor)
            {
                otherTeils+=getValuePiece(board[i][j]);
                qDebug() << "other pieces " << otherTeils;
            }
    myPoints = otherMaxPoints-otherTeils;
    otherPoints = myMaxPoints-myteils;
    qDebug() << " my Points " << myPoints << " your points " << otherPoints << "=================================";
    qDebug() << " my max Points " << myMaxPoints << " your max points " << otherMaxPoints << "=================================";

    emit pointsCounter(myPoints,otherPoints);
}

int Chess::getValuePiece(const Piece& piece){
    switch(piece.type){
    case BAUER:
        return 1;
    case SPRINGER:
    case LAUFER:
        return 3;
    case TURM:
        return 5;
    case DAME:
        return 9;
    default:
        return 0;
    }
}

void Chess::clearBoard(){
    for(int i=0; i<8; ++i)
        for(int j=0; j<8; ++j)
            board[i][j].setToNone();
}

void Chess::rematch(){
    clearBoard();
    setColors(_we,_beginnender,_gegnerNummer);
}

