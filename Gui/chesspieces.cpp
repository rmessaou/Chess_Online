#include "chesspieces.h"
/**
 * @brief ChessPieces::ChessPieces Füllt Array mit den FigurRessourcen, erst schwarz, dann weiß, jeweils könig, dame, läufer, springer, turm, bauer
 */
ChessPieces::ChessPieces()
{
    _chessPieces[0]=QIcon(":/king_black.png");//____-_-----__-_-__-_-__--_-__-__-
    _chessPieces[1]=QIcon("://queen_black.png");
    _chessPieces[2]=QIcon(":/bishop_black.png");
    _chessPieces[3]=QIcon(":/knight_black.png");//_________
    _chessPieces[4]=QIcon(":/Tower_black.png");
    _chessPieces[5]=QIcon(":/Pawn_black.png");
    _chessPieces[6]=QIcon(":/new/prefix1/king_white.png");
    _chessPieces[7]=QIcon(":/new/prefix1/queen_white.png");
    _chessPieces[8]=QIcon(":/new/prefix1/bishop_white.png");
    _chessPieces[9]=QIcon(":/new/prefix1/knight_white.png");
    _chessPieces[10]=QIcon(":/new/prefix1/tower_white.png");
    _chessPieces[11]=QIcon(":/new/prefix1/pawn_white.png");

    //####################normal#########################

    _chessPieces[12]=QIcon(":/new/prefix1/king_black_normal.png");//____-_-----__-_-__-_-__--_-__-__-
    _chessPieces[13]=QIcon(":/new/prefix1/queen_black_normal.png");
    _chessPieces[14]=QIcon(":/new/prefix1/bishop_black_normal.png");
    _chessPieces[15]=QIcon(":/new/prefix1/knight_black_normal.png");//_________
    _chessPieces[16]=QIcon(":/new/prefix1/tower_black_normal.png");
    _chessPieces[17]=QIcon(":/new/prefix1/pawn_black_normal.png");


    _chessPieces[18]=QIcon(":/new/prefix1/king_white_normal.png");
    _chessPieces[19]=QIcon(":/new/prefix1/queen_white_normal.png");
    _chessPieces[20]=QIcon(":/new/prefix1/bishop_white_normal.png");
    _chessPieces[21]=QIcon(":/new/prefix1/knight_white_normal.png");
    _chessPieces[22]=QIcon(":/new/prefix1/tower_white_normal.png");
    _chessPieces[23]=QIcon(":/new/prefix1/pawn_white_normal.png");
    /*QIcon *queen_black=new QIcon("://queen_black.png");
    QIcon *king_black=new QIcon(":/king_black.png");
    QIcon *knight_black=new QIcon(":/knight_black.png");//'''''
    QIcon *bishop_black=new QIcon(":/bishop_black.png");
    QIcon *tower_black=new QIcon(":/Tower_black.png");
    QIcon *pawn_black=new QIcon(":/Pawn_black.png");//''*'IKJIKJIO
    QIcon *queen_white=new QIcon(":/new/prefix1/queen_white.png");
    QIcon *king_white=new QIcon(":/new/prefix1/king_white.png");
    QIcon *bishop_white=new QIcon(":/new/prefix1/bishop_white.png");
    QIcon *tower_white=new QIcon(":/new/prefix1/tower_white.png");
     QIcon *knight_white=new QIcon(":/new/prefix1/knight_white.png");
    QIcon *pawn_white=new QIcon(":/new/prefix1/pawn_white.png");
    _chessPieces.append(king_black);//0
    _chessPieces.append(queen_black);//1
    _chessPieces.append(bishop_black);//2
    _chessPieces.append(knight_black);//3
    _chessPieces.append(tower_black);//4
    _chessPieces.append(pawn_black);//5
    _chessPieces.append(king_white);//6
    _chessPieces.append(queen_white);//7
    _chessPieces.append(bishop_white);//8
    _chessPieces.append(knight_white);//9
    _chessPieces.append(tower_white);//10
    _chessPieces.append(pawn_white);//11*/
}
