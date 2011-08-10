#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

namespace Ui {
    class PreferenceDialog;
}

class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceDialog(QWidget *parent = 0);
    ~PreferenceDialog();
    int getPoolInterval ();
    void setPoolInterval ( int );
    QString getSecret ();
    QString getKey ();
    QString getSavePassword ();
    float getFee ();
    void setSecret ( QString );
    void setKey ( QString );
    void setFee ( float );

private:
    Ui::PreferenceDialog *ui;
};

#endif // PREFERENCEDIALOG_H
