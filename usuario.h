#ifndef USUARIO_H
#define USUARIO_H
#include <QString>

class Usuario
{
public:
    Usuario();
    Usuario(QString nome, QString login, QString senha, QString tel, int np, int status, int tipo, int area);
    QString getNome() const;
    QString getLogin() const;
    QString getSenha() const;
    QString getTel() const;
    int getNp() const;
    int getStatus() const;
    int getTipo() const;
    int getArea() const;

private:
    QString nome, login, senha, tel;
    int np, status, tipo, area;
};

#endif // USUARIO_H
