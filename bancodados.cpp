#include "bancodados.h"
#include <log.h>

BDBrigada::BDBrigada(QString driver, QString host, QString db_name, QString user, QString password)
{
    this->driver = driver;
    this->host = host;
    this->db_name = db_name;
    this->user = user;
    this->password = password;

    abrirBD();
    log = new Log();
}

BDBrigada::~BDBrigada()
{
    fecharBD();
}
bool BDBrigada::abrirBD()
{
    QSqlDatabase::addDatabase(driver, "DBBrigada");
    banco = QSqlDatabase::addDatabase(driver);
    banco.setHostName(host);
    banco.setDatabaseName(db_name);
    banco.setUserName(user);
    banco.setPassword(password);

    qDebug() << "Conectando ao Banco de Dados...";
    log->escreve("Conectando ao Banco de Dados...");

    if (!banco.open())
    {
        qDebug() << "Erro ao abrir BD: " << banco.lastError().text();
        log->escreve("Erro ao abrir BD: " + banco.lastError().text());
        conectado = false;
        return false;
    }
    else
    {
        qDebug() << "Conectado ao BD";
        log->escreve("Conectado ao BD");
        conectado = true;
        return true;
    }
}

void BDBrigada::fecharBD()
{
    banco.close();
}

QSqlQuery BDBrigada::execQuery(QString query)
{
    QSqlQuery sqlQuery;
    sqlQuery.exec(query);
    //qDebug() << sqlQuery.lastError().text();
    QString erro = sqlQuery.lastError().text();
    if(erro.size() > 1)
    //Log.escreve("Erro na query: " + erro);
        qDebug() << "Erro na query: " + erro;
    return sqlQuery;
}

QSqlQuery BDBrigada::execQuery(QSqlQuery query)
{
    query.exec();
    QString erro = query.lastError().text();
    return query;
}

bool BDBrigada::apagarTabela(QString tabela)
{
    execQuery("DROP TABLE " + tabela);
}

bool BDBrigada::getConectado() const
{
    QSqlQuery resultado;
    resultado.exec("SELECT 1 FROM usuarios");
    if(resultado.size() != -1)
        return true;
    else
        return false;
}

int registroExiste(QString tabela, QString coluna, QString registro)
{
    QSqlQuery sqlQuery("SELECT * FROM " + tabela);
    int i = 0;
    while(sqlQuery.next())
    {
        if(QString::compare(sqlQuery.value(coluna).toString(), registro) == 0)
            return i;
    }
    return -1;
}
