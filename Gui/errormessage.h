#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include <QDialog>
namespace Ui {
class ErrorMessage;
}
/**
 * @brief The ErrorMessage class implements an error window opened when an error occurs
 */
class ErrorMessage : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief ErrorMessage: Constructor for error message
     * @param parent
     */
    explicit ErrorMessage(QWidget *parent = nullptr);
    ~ErrorMessage();

private:
    Ui::ErrorMessage *ui;
};

#endif // ERRORMESSAGE_H
