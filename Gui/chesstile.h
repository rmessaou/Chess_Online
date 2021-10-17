#ifndef CHESSTILE_H
#define CHESSTILE_H
#include <QString>
#include <QPushButton>
#include <QPixmap>
#include <iostream>
/**
 * @brief The ChessTile class implements a ChessTiles instance which inherits from QPushButton, can be clicked, colored, send its own identifier and color
 */
class ChessTile: public QPushButton
{ Q_OBJECT
public:
    /**
     * @brief ChessTile constructor of ChessTile
     * @param text  Text to be set onto ChessTile
     * @param color color of ChessTile, according to overall color code
     * @param identifier    identifies each ChessTile with single number, 0 to 63, left bottom to top right
     * @param parent    for memory management
     * @param _2identifier  used for pawn transformation to store which type of figure is put on ChessTile
     * @param isHighlighted
     * @param iconSize  size of icon
     * @param disabled
     */
    ChessTile(QString text, bool color, int identifier=0, QWidget* parent=nullptr, int _2identifier=0, bool isHighlighted=false, int iconSize=60, bool disabled=false);
    /**
     * @brief disable   Disables ChessTile for clicks
     */
    void disable();//maybe slot
    /**
     * @brief enable    Makes ChessTile clickable
     */
    void enable();//maybe slot
    /**
     * @brief highlight Highlights ChessTiles
     */
    void highlight();//maybe Slot
    /**
     * @brief defaultColor sets ChessTile back to default color
     * @param color according to color code
     */
    void defaultColor(bool color);
    /**
     * @brief getIdentifier
     * @return
     */
    int getIdentifier(){return _identifier;}
    ~ChessTile(){
        std::cout<<"D of Tile"<<std::endl;
    }
    /**
     * @brief highlightCheck different color to hightlight wenn figure on ChessTile puts King into check
     */
    void highlightCheck();
    /**
     * @brief highlightKingCheck    different color to highlight king when in check
     */
    void highlightKingCheck();
    /**
     * @brief getColor: getter function for color
     * @return
     */
    bool getColor(){return _color;}
    /**
     * @brief highlightTurn: higlights the players pieces on turn
     */
    void highlightTurn();
signals:
    /**
     * @brief toggled emits identifier
     * @param identifier
     */
    void toggled(int identifier);//sends identifier
    /**
     * @brief transformationToggle  used for pawn transformation
     * @param identifier    identifier
     * @param color color according to color code
     * @param _2identifier  type of figure on ChessTile
     */
    void transformationToggle(int identifier, int color, int _2identifier);
    /**
     * @brief hovered   emitted if mouse hovers over ChessTile
     */
    void hovered();
    /**
     * @brief left  emitted if mouse leaves ChessTile
     */
    void left();
    /**
     * @brief checkedClick
     */
    void checkedClick();
public slots:
    /**
     * @brief clickedReaction   used to emit toggled signal
     */
    void clickedReaction();//used to send identifier
    /**
     * @brief clickedTransformation used to emit transformationToggle
     */
    void clickedTransformation();
    /**
     * @brief enterEvent    overwrite enterEvent of QPushButton
     * @param e
     */
    virtual void enterEvent(QEvent *e);
    /**
     * @brief colorWhenHover color ChessTile when hovered
     */
    void colorWhenHover();
    /**
     * @brief uncolorWhenleave sets color to normal when unhovered
     */
    void uncolorWhenleave();
    /**
     * @brief leaveEvent    overwrite leaveEvent of QPushButton
     * @param e
     */
    virtual void leaveEvent(QEvent *e);
    /**
     * @brief checkEnabled Checks if button is enabled, if enabled emits clicked signal
     */
    void checkEnabled();
private:
    int _identifier;
    bool _color;
    int _2_identifier;
    bool _isHighlighted;
    bool _disabled;
    int _size;
    bool _checks;
};

#endif // CHESSTILE_H
