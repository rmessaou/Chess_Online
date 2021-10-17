#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QVector>
#include "chesstile.h"
//#include "game.h"
#include <QGridLayout>
#include <QWidget>
//#include "ui_game.h"
//#include "chessspace.h"
#include "chesspieces.h"
#include <vector>
#include <memory>

/**
 * @brief The ChessBoard class implements supervisor of ChessTiles, constructed once
 */
class ChessBoard: public QWidget
{
    Q_OBJECT
public:
    //class Game;
    /**
     * @brief ChessBoard    constructs ChessBoard instance with parent pointer
     * @param parent
     */
    ChessBoard(QWidget* parent=nullptr);
    /**
     * @brief setup     used to set attributes of ChessBoard
     * @param grid      pointer tocentral Grid Layout to house ChessBoard
     * @param counter   counts how often game has been started
     * @param yourColor 1->black, 0->white
     * @param leftGraveyard pointer to leftGraveyardGrid
     * @param rightGraveyard    pointer to rightGravayardGrid
     * @param texturePacket 1->animal Package 0->normal Package
     */
    void setup(QGridLayout* grid, int counter=0, bool yourColor=0, QGridLayout *leftGraveyard=nullptr, QGridLayout *rightGraveyard=nullptr, int texturePacket=0);//maybe slot
    /**
     * @brief placeChessTiles   places ChessTiles, pointers to each ChessTile are stored in _chessTiles Vector attribute of ChessBoard
     * @param grid  pointer to central Grid that houses ChessBoard
     * @param parent    give this pointer to each ChessTile instance for QT memory management
     */
    void placeChessTiles(QGridLayout* grid, QWidget* parent=nullptr);
    /**
     * @brief placeChessTileRow helper function for placeChessTiles to place entire row of ChessTiles
     * @param row   row number from 1
     * @param grid  same as above
     * @param parent same as above
     */
    void placeChessTileRow(int row, QGridLayout* grid ,QWidget* parent=nullptr);
    /**
     * @brief _chessTiles stores pointers pointing to ChessTile instances
     */
    QVector<ChessTile*> _chessTiles;//WICHTIG FALLS SHARED PTR NICHT WOLLEN!!!!!!!!!!!!!!!
    //ChessTile _chessTiles[64];
    //QVector<std::shared_ptr<ChessTile> > _chessTiles;
    /**
     * @brief disableAll disables all ChessTiles
     */
    void disableAll();//maybe Slot
    /**
     * @brief enableAll enables all ChessTiles
     */
    void enableAll();//maybe SLot
    /**
     * @brief enable enables ChessTiles specified in yourTiles vector
     * @param yourTiles holds identifiers of ChessTiles that should be activated
     */
    void enable(std::vector<int> yourTiles);//maybe Slot
    /**
     * @brief moveTest Test function for moves
     */
    void moveTest();
    /**
     * @brief rochade Implements rochade Function
     * @param pos1  Position King
     * @param pos2  Position Tower
     * @param type  1->long Rochade 0->short Rochade
     */
    void rochade(int pos1, int pos2, bool type);//maybe Slot
    /**
     * @brief setChoice used set _choiceLayout pointer to point on ChoiceLayout which contains choices for pawnTransformation
     * @param choiceLayout  pointer to choiceLayout
     */
    void setChoice(QHBoxLayout *choiceLayout/*, QWidget*choiceWidget*/);
    /**
     * @brief setTurn   set whose Turn it is, 1->our turn, 0->opponent turn
     * @param ourTurn   bool 1->our turn, 0->opponent turn
     */
    void setTurn(bool ourTurn){
        _ourTurn=ourTurn;
    };
    /**
     * @brief destroyGraveyards Destroys ChessTiles in left and right graveyards
     */
    void destroyGraveyards();
public slots:
    /**
     * @brief receivePawnTransformation used to receive pawn transformation from own Gui
     * @param pos   position of pawn
     * @param color which color 1->dark, 0->light
     * @param type  which type of figure, according to protocoll, 1->bishop, 2->knight, 3->tower, 4->queen
     */
    void receivePawnTransformation(int pos, int color, int type);//connected
    /**
     * @brief showPossible show Possible moves and enable all tiles that we own
     * @param possible  std::vector that holds all possible move locations
     * @param yourTiles std::vector that holds locations of all ChessTiles we own
     */
    void showPossible(std::vector<int> possible, std::vector<int> yourTiles);//connected
    /**
     * @brief move used for all move sent by logic
     * @param start startposition of move
     * @param end   endposition of move
     * @param strike    1->strike, 0->no Strike
     */
    void move(int start, int end, bool strike=0);//connected
    /**
     * @brief enPassant used for enPassant striking
     * @param pos   position of pawn that is being striked
     */
    void enPassant(int pos);//connected
    /**
     * @brief pawnTransformation    used for own pawn transformation
     * @param pos   position of pawn
     */
    void pawnTransformation(int pos);//connected
    /**
     * @brief receivePawnTransformationOpp  receive pawn transformation from opponent
     * @param pos   position of pawn
     * @param color  1->dark, 0->light
     * @param type  which figure
     */
    void receivePawnTransformationOpp(int pos, int color, int type);
    /**
     * @brief checkHighlight    highlight figures that put king into check
     * @param possible  position of figures that put king into check
     * @param posKing   position of king
     */
    void checkHighlight(std::vector<int> possible, int posKing);
signals:
    /**
     * @brief bauernumwandlung  emitted when Gui selects what pawn should be transformed to
     * @param type  type of figure
     */
    void bauernumwandlung(int type);
private:
    //std::shared_ptr<ChessBoard> _chessBoard;
    ChessPieces _chessPieces;
    /**
     * @brief showPossibleOff   disable highlighting and ChessTiles
     */
    void showPossibleOff();//maybe Slot
    /**
     * @brief defaultColorAll   set all ChessTiles to defaultColor
     */
    void defaultColorAll();
     QHBoxLayout *_choiceLayout;
     bool _yourColor;
     QGridLayout *_leftGraveyard;
     QGridLayout *_rightGraveyard;
     bool _ourTurn;
     int _texturePacket;//0->normale, 1->animals
     //QVector<ChessTile*> _transformationVector;
     //QWidget *_choiceWidget;
};




#endif // CHESSBOARD_H
