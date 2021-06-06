#include "usuario.h"
Usuario::Usuario()
{
    this->nome = "";
    this->login = "";
    this->senha = "";
    this->tel = "";
    this->np = 0;
    this->status = 0;
    this->tipo = 0;
    this->area = 0;
}
Usuario::Usuario(QString nome, QString login, QString senha, QString tel, int np, int status, int tipo, int area)
{
    this->nome = nome;
    this->login = login;
    this->senha = senha;
    this->tel = tel;
    this->np = np;
    this->status = status;
    this->tipo = tipo;
    this->area = area;
}

QString Usuario::getNome() const
{
    return nome;
}

QString Usuario::getLogin() const
{
    return login;
}

QString Usuario::getSenha() const
{
    return senha;
}

QString Usuario::getTel() const
{
    return tel;
}

int Usuario::getNp() const
{
    return np;
}

int Usuario::getStatus() const
{
    return status;
}

int Usuario::getTipo() const
{
    return tipo;
}

int Usuario::getArea() const
{
    return area;
}
