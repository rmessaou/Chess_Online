#ifndef CHESSPIECES_H
#define CHESSPIECES_H
#include <QIcon>
#include <QPixmap>
#include <QVector>
#include <QVector>
/**
 * @brief The ChessPieces class stores all resource links of ChessFigure in an array
 */
class ChessPieces
{
public:
    ChessPieces();
    //QVector<QIcon*> _chessPieces;
    //QIcon  _chessPieces[12];
    QIcon   _chessPieces[24];
private:
};

#endif // CHESSPIECES_H
