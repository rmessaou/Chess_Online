#ifndef CHESSSPACE_H
#define CHESSSPACE_H
#include <QWidget>
#include "game.h"

/**
 * @brief The ChessSpace class:
 */
class ChessSpace: public Game
{
    Q_OBJECT
public:
    /**
     * @brief ChessSpace: Constructor for ChessSpace
     * @param parent
     */
    ChessSpace(QWidget *parent = nullptr);
};

#endif // CHESSSPACE_H
