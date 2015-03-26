#include "encryption.h"
#include "ui_encryption.h"

char *Encryption::key1 = const_cast<char*>("QOUDpKJAmsdfserfs");
char *Encryption::key2 = const_cast<char*>("SDMEKpdgtkgzzjfoK");

Encryption::Encryption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Encryption)
{
    ui->setupUi(this);

    QString str =  QString::fromLatin1(key1);
    QString str1 = QString::fromLatin1(key2);

    ui->plainTextEdit_3->appendPlainText(str);
    ui->plainTextEdit_4->appendPlainText(str1);
}

Encryption::~Encryption()
{
    delete ui;
}

void Encryption::on_buttonBox_accepted()
{
    QString str_key1 = ui->plainTextEdit_3->toPlainText();
    QString str_key2 = ui->plainTextEdit_4->toPlainText();
    QByteArray ba, ba1;

    ba = str_key1.toLocal8Bit();
    ba1 = str_key2.toLocal8Bit();

    key1 = ba.data();
    key2 = ba1.data();
}

void Encryption::encryptt(char *buffer)
{
    enc::encrypt_text(buffer, strlen(buffer), Encryption::key1, strlen(Encryption::key1), Encryption::key2, strlen(Encryption::key2));
}

void Encryption::decrypt(char *buffer)
{
    encryptt(buffer);
}
