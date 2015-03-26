#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QDialog>
#include "enc.h"

#define BUFSIZE 1024

namespace Ui {
class Encryption;
}

class Encryption : public QDialog
{
    Q_OBJECT

public:
    explicit Encryption(QWidget *parent = 0);
    ~Encryption();
    void encryptt(char *buffer);
    void decrypt(char *buffer);
    static char *key1;
    static char *key2;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Encryption *ui;
};

#endif // ENCRYPTION_H
