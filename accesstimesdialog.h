#ifndef ACCESSTIMESDIALOG_H
#define ACCESSTIMESDIALOG_H

#include <QDialog>

namespace Ui {
class AccessTimesDialog;
}

class AccessTimesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AccessTimesDialog(QWidget *parent = 0);
    ~AccessTimesDialog();

private:
    Ui::AccessTimesDialog *ui;
};

#endif // ACCESSTIMESDIALOG_H
