#include "preferencedialog.h"
#include "ui_preferencedialog.h"

PreferenceDialog::PreferenceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceDialog)
{
    ui->setupUi(this);
}

PreferenceDialog::~PreferenceDialog()
{
    delete ui;
}

int PreferenceDialog::getPoolInterval ()
{
    int result;
    result = this->ui->poolIntervalLineEdit->text().toInt();
    if ( result < 5000 )
        result = 5000;
    return result;
}

void PreferenceDialog::setPoolInterval ( int pool )
{
    if ( pool < 5000 )
        this->ui->poolIntervalLineEdit->setText( "5000" );
    else
        this->ui->poolIntervalLineEdit->setText( QString::number ( pool ) );
}

QString PreferenceDialog::getSecret ()
{
    return this->ui->secretLineEdit->text ();
}

QString PreferenceDialog::getKey ()
{
    return this->ui->keyLineEdit->text ();
}

void PreferenceDialog::setSecret ( QString newSecret )
{
    this->ui->secretLineEdit->setText( newSecret );
}

void PreferenceDialog::setKey ( QString newKey )
{
    this->ui->keyLineEdit->setText ( newKey );
}

QString PreferenceDialog::getSavePassword()
{
    return this->ui->savePasswordLineEdit->text ();
}

float PreferenceDialog::getFee()
{
    return ui->feeLineEdit->text().toFloat();
}

void PreferenceDialog::setFee( float fee )
{
    ui->feeLineEdit->setText( QString::number ( fee ) );
}
