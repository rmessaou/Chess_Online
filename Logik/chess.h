#ifndef CHESS_H
#define CHESS_H

#include <QObject>
//#include <QWidget>
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <QDataStream>
#include <QByteArray>

/**
 * @brief The Type enum: determines the type of a piece
 */
enum Type { NONE , BAUER, TURM, SPRINGER, LAUFER, DAME, KONIG, OUTSIDE };
/**
 * @brief The Color enum: determines the color of a piece
 */
enum Color { NOCOL, WHITE, BLACK };

/**
 * @brief The Piece struct: construct a piece with a type, x and y position and a color
 */
struct Piece {
    Piece() = default;

    /**
     * @brief Piece: Constructor of Piece
     * @param x
     * @param y
     * @param t
     * @param col
     */
    Piece(int x, int y, Type t, Color col):positionX(x),positionY(y),type(t),color(col) {}

    /**
     * @brief setToNone: Function to set the color and type to none and delete the piece on the board
     */
    void setToNone(){
        color = NOCOL;
        type = NONE;
    }
    int positionX = 0;
    int positionY = 0;
    Type type = NONE;
    Color color = NOCOL;
};

/*!
 * \brief The Chess class: main class for the logic functions
 */
class Chess : public QObject
{
    Q_OBJECT
public:

    Chess() = default;
    ~Chess() = default;

    /*!
     * \brief showFelds: Function for debugging to show the possible fields
     * \param poMoves: vector containing the possible moves
     * \param x: x coordinates of start piece
     * \param y: y coordinates of start piece
     */
    void showFelds(const std::vector<int>& poMoves, int x, int y);

    /*!
     * \brief show: Function for debugging to show the board
     */
    void show(); // zur debug

    //############### UTILS FUNKTION ##########################//
    /*!
     * \brief initialise: Function to initialise the board matrix
     * \return true if initialisation is succeded
     */
    bool initialise();

    /*!
     * \brief decode: Function to convert from the button number to x abd y coordinates
     * \param nb
     * \param x
     * \param y
     */
    void decode(int nb, int& x, int& y);

    /*!
     * \brief encode: Function to convert from x and y coordinates to the button number
     * \return button number
     */
    int encode(int, int); //getestet

    //############### MOVE FUNKTION ##########################//
    /*!
     * \brief possibleMove: Function to determine the possible moves of a piece
     * \param nb: button number
     * \return vector of possible moves
     */
    std::vector<int> possibleMove(int nb);

    /*!
     * \brief canMove: Function to test if the coordinates are on the board
     * \return true if coordinates on board
     */
    bool canMove(int, int);

    /*!
     * \brief getOpposite: Function that returns the opposite color of a piece
     * \param piece
     * \return
     */
    Color getOpposite(const Piece& piece) const;

    /*!
     * \brief moveBauer: Function to get possible move of a BAUER
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveBauer(int x, int y, std::vector<int>& moves);

    /*!
     * \brief moveSpringer: Function to get possible move of a SPRINGER
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveSpringer(int x, int y, std::vector<int>& moves);

    /*!
     * \brief moveTurm: Function to get possible move of a TURM
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveTurm(int x, int y, std::vector<int>& moves);

    /*!
     * \brief moveLaufer: Function to get possible move of a LAUFER
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveLaufer(int x, int y, std::vector<int>& moves);

    /*!
     * \brief moveDame: Function to get possible move of a DAME
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveDame(int x,int y,std::vector<int>& moves);

    /*!
     * \brief moveKonig: Function to get possible move of a KONIG
     * \param x: coordinates
     * \param y: coordinates
     * \param moves: stores the possible moves
     */
    void moveKonig(int x, int y, std::vector<int>& moves);

    //############### CHECK FUNKTION ##########################//

    /**
     * @brief check: Function to check if a piece is in check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool check(const Piece& piece, std::vector<int>& angreiferVec); // alle checks wurden getestet // übergibt ob ein check da gibt

    /**
     * @brief checkHorizentalRight: Function to check if a piece is in horizental right check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkHorizentalRight (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkHorizentalLeft: Function to check if a piece is in horizental left check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkHorizentalLeft (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkVerticalUp: Function to check if a piece is in vertical up check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkVerticalUp (const Piece& piece , std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkVerticalDown: Function to check if a piece is in vertical down check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkVerticalDown (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkDiagonalRightUp: Function to check if a piece is in diagonal right up check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkDiagonalRightUp (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkDiagonalRightDown: Function to check if a piece is in diagonal right down check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkDiagonalRightDown (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkDiagonalLeftUp: Function to check if a piece is in diagonal left up check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkDiagonalLeftUp (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkDiagonalLeftDown: Function to check if a piece is in diagonal left down check and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkDiagonalLeftDown (const Piece& piece, std::vector<int>& angreiferVec) ;// getestet

    /**
     * @brief checkSpringer: Function to check if a piece is in check by a Springer and deliver the attacker vector
     * @param piece
     * @param angreiferVec
     * @return
     */
    bool checkSpringer(const Piece& piece, std::vector<int>& angreiferVec);// getestet

    /**
     * @brief canBeReached: Function to test if a block can be reached by another piece with the color `color`
     * @param x
     * @param y
     * @param color
     * @return
     */
    bool canBeReached(int x, int y, const Color& color);// getestet

    /**
     * @brief canBlock: Function to test if a check can be blocked
     * @param attacker
     * @param king
     * @return
     */
    bool canBlock(const Piece& attacker, const Piece& king);// getestet

    /**
     * @brief isPossible: Function to test if a move possible or not
     * @param sX
     * @param sY
     * @param zX
     * @param zY
     * @return
     */
    bool isPossible(int sX, int sY, int zX, int zY); // getestet

    /**
     * @brief checkMate: Function to check if a king is checkmate or not
     * @param king
     * @return
     */
    bool checkMate(const Piece& king); // getestet

    //############### Netz FUNKTION ##########################//
    /**
     * @brief getKing: Function that returns the kings piece of a player
     * @param color
     * @return
     */
    const Piece& getKing(const Color& color) const; //getestet

    /**
     * @brief getPieces: Function that returns the set of pieces of certain color
     * @param color
     * @return
     */
    const std::vector<int> getPieces(const Color& color); // getestet

    /**
     * @brief changeTurn: Function that changes the turns and signals the pieces available to move
     */
    void changeTurn(); //getestet

    /**
     * @brief changeMatrix: Function to update the matrix of pieces
     * @param start
     * @param end
     */
    void changeMatrix(int start, int end); // getestet

    /**
     * @brief checkForRochade: Function that checks if a rochade is taking place or not
     * @param start
     * @param end
     * @return
     */
    bool checkForRochade(int start,int end); //getestet

    /**
     * @brief isFree: function that checks if a block is empty or not
     * @param x
     * @param y
     * @return
     */
    bool isFree(int x,int y) const; //getestet

    /**
     * @brief changeMatrixRochade: Function that updates the matrix when there is a rochade
     * @param start
     * @param end
     */
    void changeMatrixRochade(int start, int end); //getestet

    /**
     * @brief bauerUmwandlung: Function that checks if there is a Bauerumwandlung
     * @param start
     * @param end
     * @return
     */
    bool bauerUmwandlung(int start , int end ) ; //getestet

    /**
     * @brief checkEnPassant: Function to check if there is a EnPassant move
     * @param start
     * @param end
     * @return
     */
    bool checkEnPassant(int start, int end); //getestet

    /**
     * @brief attackEnPassant: Function that changes the matrix when there is enPassant
     * @param start
     * @param end
     * @param schlag
     * @return
     */
    bool attackEnPassant(int start,int end,bool schlag); //getestet

    /**
     * @brief getNeuPiece: Function to deliver a new piece after a Bauerumwandlung
     * @param zX
     * @param zY
     * @param piece
     * @return
     */
    const Piece getNeuPiece(int zX,int zY, int piece) const; //getstet

    /**
     * @brief reverseModifyMatrix: Function to reverse a modification of a mtrix
     * @param startPiece
     * @param endPiece
     */
    void reverseModifyMatrix(Piece startPiece,Piece endPiece); //getstet

    /**
     * @brief checkKingBeforeMove: Check if king in check when recieved from network
     * @param start
     * @param end
     * @return
     */
    bool checkKingBeforeMove(int start,int end);

    /**
     * @brief updateRochade: Updates the booleans to check if the rochade is still possible
     * @param color
     */
    void updateRochade(const Color &color);

    /**
     * @brief countPoints: Counts the points of each player
     */
    void countPoints();

    /**
     * @brief getValuePiece: returns the value of a certain piece
     * @param piece
     * @return
     */
    int getValuePiece(const Piece& piece);

    /**
     * @brief clearBoard: clears the Piece matrix
     */
    void clearBoard();

//private:
    Color turn = BLACK;
    Color myColor = WHITE;
    Color otherColor = BLACK;
    Piece board[8][8];
    bool gameEnd = false;
    int click = 0;
    int startClick;
    int endClick;
    std::pair <int,int> lastEnPassant = std::make_pair( 64, 1) ;
    int grpNr = 0x06;
    int otherGrpNr;
    bool rochadeUR = true;
    bool rochadeUL = true;
    bool rochadeDR = true;
    bool rochadeDL = true;

    int myPoints = 0;
    int otherPoints = 0;
    int myMaxPoints = 39;
    int otherMaxPoints = 39;

    int _we;
    int _beginnender;
    int _gegnerNummer;


signals:
//    void checkMyKing(int); //when I try to move something else and king in check
    /**
     * @brief whereToMove: Signal to network to hilight the possible moves and the players pieces on the board
     * @param possible
     * @param yourPieces
     */
    void whereToMove(std::vector<int> possible, std::vector<int> yourPieces); //wenn gui auf eine davon

    /**
     * @brief ourMove: Signal to network to send the players move as vector
     * @param myMove
     */
    void ourMove(std::vector<quint8> myMove); //nach netzwerk damit mein Move broadcastet wird

    /**
     * @brief modifyGui: Signal to GUI to change the board
     * @param start
     * @param end
     */
    void modifyGui(int start,int end, bool schlagt); //sende start und Ziel clicks

    /**
     * @brief ourResponse: Signal that sends a response for the move to the network
     * @param myResponse
     */
    void ourResponse(std::vector<quint8> myResponse); //nach netzwerk um zu sagen ob es ok ist (GUI change) oder nicht (GUI Pause and wait for new orders)

    /**
     * @brief weWin: Signal for a win
     */
    void weWin(); //if recieved ok on a schachmatt

    /**
     * @brief weLose: Signal for lose
     */
    void weLose(); //if recieved show lose

    /**
     * @brief errorState: Signal when there is an error in the game
     */
    void errorState(); //if there is an error

    /**
     * @brief startGui: Signal to start the GUI when two players are connected
     * @param color
     */
    void startGui(int color); // so that gui starts when server/client ready

    /**
     * @brief myBauerUmwandlung: Signal for the GUI when the current player is making a Bauerumwandlung
     * @param position
     * @param color
     */
    void myBauerUmwandlung(int position, int color); //signal for gui to make a bauerumwandlung // getestet

    /**
     * @brief enPassant: Signal for the GUI to delete a piece when its attacked by enPassant
     * @param position
     */
    void enPassant(int position); // signalisiert en passant schlag;

    /**
     * @brief bauerUmwandlungOpp: Signal for GUI when there is a Bauerumwandlung from the other player
     * @param position
     * @param color
     * @param piece
     */
    void bauerUmwandlungOpp(int position,int color,int piece);

    /**
     * @brief ourSurrender: emits a signal for surrender
     * @param mySurrender
     */
    void surrender(std::vector<quint8> mySurrender);

    /**
     * @brief weLoseSurrender: Signals a surrender
     */
    void weLoseSurrender();

    /**
     * @brief hilightCheck: Sends a signal to GUI to hilight an attacker of the king
     * @param anfgreifer
     */
    void hilightCheck(std::vector<int> anfgreifer, int positionKing);

    /**
     * @brief sendOppData: send the opponent number and color to GUI
     * @param gegnerNummer
     * @param gegnerColor
     */
    void sendOppData(int gegnerNummer, int gegnerColor);

    /**
     * @brief whoseTurn: Sends turn Signal
     * @param turn
     */
    void whoseTurn(bool turn);

    /**
     * @brief pointsCounter: Signal to display the current score
     * @param myPoints
     * @param gegnerPoints
     */
    void pointsCounter(int myPoints, int gegnerPoints);

public slots:

    /**
     * @brief moveFromNetwork: Slot to handle a move from the network
     * @param sX
     * @param sY
     * @param zX
     * @param zY
     * @param status
     * @param piece: piece number when there is a Bauerumwandlung
     */
    void moveFromNetwork(int sX,int sY,int zX,int zY,int status,int piece); //Überprüfe Move und sende ourResponse (GUI und Netzwerk wenn es ok oder nur Netzwerk wenn es nicht ok)

    /**
     * @brief moveFromGUI: Slot to handle the click of the GUI
     * @param number
     */
    void moveFromGUI(int number); //getestet // Überprüfe Move und sende makeMove for GUI //if click = 0 send possible move else send modifyGui

    /**
     * @brief responseFromNetwork: Slot to handle a response from the network
     * @param otherResponse
     */
    void responseFromNetwork(quint8 otherResponse);//getestet //Überprüfe response if ok send Pause to GUI or endGame with error

    /**
     * @brief setColors: Slot to handle the colors of the two players and then emit the start Signal
     * @param weAre
     * @param beginnender
     * @param gegnerNummer
     */
    void setColors(int weAre,int beginnender, int gegnerNummer); // sollte gehen //connected mit init from network first param is beginneder second is othergrpnmr;

    /**
     * @brief myBauerChange: Slot to handle the chosen Piece of the current player after a Bauerumwandlung
     * @param chosenPiece
     */
    void myBauerChange(int chosenPiece); // aufgerufen from GUI um zu überteilen erlche neuer Piece hinzugefügt wurde

    /**
     * @brief mySurrender: Signalize that I surrendered
     */
    void mySurrender();

    /**
     * @brief rematch: initialises a new game
     */
    void rematch();

};


#endif // CHESS_H
