#include "accesstimesdialog.h"
#include "ui_accesstimesdialog.h"

/*
 * This window will be used to display the Acecess Times to the user after they click Track Satellite.
 */


AccessTimesDialog::AccessTimesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccessTimesDialog)
{
    ui->setupUi(this);
}

AccessTimesDialog::~AccessTimesDialog()
{
    delete ui;
}
