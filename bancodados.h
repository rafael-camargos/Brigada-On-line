#ifndef BANCODADOS_H
#define BANCODADOS_H
#include <QtSql>
#include <QDebug>
#include <log.h>

class BDBrigada
{
public:
    BDBrigada(QString driver, QString host, QString db_name, QString user, QString password);
    ~BDBrigada();
    bool abrirBD();
    void fecharBD();
    QSqlQuery execQuery(QString query);
    QSqlQuery execQuery(QSqlQuery query);
    bool apagarTabela(QString tabela);
    bool getConectado() const;

private:
    QSqlDatabase banco;
    QString driver, host, db_name, user, password;
    bool conectado;
    Log *log;

};

#endif // BANCODADOS_H
