#include "conexaobd.h"
#include "mainwindow.h"
#include <QProgressDialog>

ConexaoBD::ConexaoBD(MainWindow *mainwindow)
{
    BD = new BDBrigada("QMYSQL", "sql10.freesqldatabase.com", "sql10223867", "sql10223867", "ycH2B4Ijab");
    mainwin = mainwindow;

    model_tbl_usuarios = new QStandardItemModel(this);
    model_tbl_ocorrencias = new QStandardItemModel(this);
}

ConexaoBD::~ConexaoBD()
{
    //free resources
}

bool ConexaoBD::reiniciarBD()
{
    BD->execQuery("DROP TABLE usuarios");
    BD->execQuery("DROP TABLE ocorrencias");
    BD->execQuery("DROP TABLE areas");
    BD->execQuery("DROP TABLE usuarios_ocorrencias");

    BD->execQuery("CREATE TABLE usuarios (nome VARCHAR(30), np INT PRIMARY KEY, login VARCHAR(20), senha VARCHAR(20), tel VARCHAR(20), status TINYINT, tipo TINYINT, area INT, atualizacao DATETIME)");
    BD->execQuery("CREATE TABLE ocorrencias (id INT AUTO_INCREMENT PRIMARY KEY, pr INT, gravidade VARCHAR(20), descricao VARCHAR(200), dth DATETIME, dth_fech DATETIME)");
    BD->execQuery("CREATE TABLE areas (id INT AUTO_INCREMENT PRIMARY KEY, area VARCHAR(30), ramal VARCHAR(20))");
    BD->execQuery("CREATE TABLE usuarios_ocorrencias (usuario_id INT, ocorrencia_id INT, participando TINYINT, dth DATETIME)");

    BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('admin', 0, 'admin', 'adminbrigadaonline', '(00) 00000-0000', 0, 2)");
    BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('Rafael Lucas Camargos', 37089292, 'rcamarg1', 123, '(37) 99865-0217', 1, 0)");
    BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('Harley Sanio', 200, 'hsanio', 123, '(31) 99771-6309', 1, 0)");
    //BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('Lucas Seguranca', 250, 'lseguranca', 123, '(37) 99991-0612', 2, 1)");
    BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('Pedro Henrique', 300, 'phenrique1', 123, '(37) 98800-7185', 2, 0)");
    BD->execQuery("INSERT INTO usuarios (nome, np, login, senha, tel, status, tipo) VALUES ('Leandro Rodrigues', 350, 'lrodig1', 123, '(37) 99983-8102', 2, 0)");

    BD->execQuery("INSERT INTO ocorrencias (pr, gravidade, descricao, dth) VALUES (1, 'Leve', 'Acidente na Aciaria envolvendo ...', '" + QDateTime::currentDateTime().toString(Qt::ISODate) + "')");
    BD->execQuery("INSERT INTO ocorrencias (pr, gravidade, descricao, dth) VALUES (5, 'Média', 'Acidente no LC envolvendo ...', '" + QDateTime::currentDateTime().toString(Qt::ISODate) + "')");
    BD->execQuery("INSERT INTO ocorrencias (pr, gravidade, descricao, dth) VALUES (10, 'Grave', 'Acidente no pátio de sucata ...', '" + QDateTime::currentDateTime().toString(Qt::ISODate) + "')");
    BD->execQuery("INSERT INTO ocorrencias (pr, gravidade, descricao, dth) VALUES (17, 'Gravíssima', 'Explosão no AF1', '" + QDateTime::currentDateTime().toString(Qt::ISODate) + "')");

    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-ACI-APOIO/PROCESSOS', '9327-7167')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-LAM-APOIO/PROCESSO', '9320-1801')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-MAN-ENGENHARIA', '')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-MAN-MANUT PONTES', '9320-1535')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-PA-ADMINISTRACAO', '9320-1625')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-PA-ADMINISTRACAO', '9320-1709')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GAB-DIV-TG-TECNOLOGIA GESTAO', '9320-1521')");
    BD->execQuery("INSERT INTO areas (area, ramal) VALUES ('GBB-TI-IT MINAS', '9320-1766')");

}

bool ConexaoBD::cadastrarUsuario(QString nome, QString np, QString usuario, QString senha, QString tel, int area, bool brigadista, bool cadastro)
{
    QSqlQuery query;
    if(!cadastro)
        BD->execQuery("DELETE FROM usuarios WHERE np = " + np);

    query.prepare("INSERT INTO usuarios (nome, np, login, senha, tel, area, status, tipo) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(nome);
    query.addBindValue(np);
    query.addBindValue(usuario);
    query.addBindValue(senha);
    query.addBindValue(tel);
    query.addBindValue(area);
    query.addBindValue(0);
    query.addBindValue(brigadista ? 1 : 0);
    BD->execQuery(query);
    return true;
}

bool ConexaoBD::apagarUsuario(int np)
{
    qDebug() << BD->execQuery("DELETE FROM usuarios WHERE np = " + QString::number(np)).lastError();

    return true;
}
Usuario ConexaoBD::getUsuario(QString np)
{
    QSqlQuery query_usuario = BD->execQuery("SELECT * FROM " + tbl_usuarios + " WHERE np = " + np);
    query_usuario.first();

    return Usuario(query_usuario.value("nome").toString(),
                   query_usuario.value("login").toString(),
                   query_usuario.value("senha").toString(),
                   query_usuario.value("tel").toString(),
                   query_usuario.value("np").toInt(),
                   query_usuario.value("status").toInt(),
                   query_usuario.value("tipo").toInt(),
                   query_usuario.value("area").toInt());
}

QStringList ConexaoBD::getAreas()
{
    QSqlQuery query_areas = BD->execQuery("SELECT * FROM " + tbl_areas);
    int tam_tbl_areas = query_areas.size();

    qDebug() << "tam" << tam_tbl_areas;
    query_areas.first();
    QStringList lista;

    for(int i = 0 ; i < tam_tbl_areas ; i++)
    {
        lista.append(query_areas.value("area").toString());
        query_areas.next();
    }

    return lista;
}
bool ConexaoBD::cadastrarOcorrencia(QString pr, QString gravidade, QString descricao)
{
    QSqlQuery query;
    query.prepare("INSERT INTO ocorrencias (pr, gravidade, descricao, dth) VALUES (?, ?, ?, ?)");
    query.addBindValue(pr.replace("PR", ""));
    query.addBindValue(gravidade);
    query.addBindValue(descricao);
    query.addBindValue(QDateTime::currentDateTime());

    qDebug() << QDateTime::currentDateTime().toString();
    BD->execQuery(query);
    atualizaDados();
    return true;
}

bool ConexaoBD::encerrarOcorrencia(int id)
{
    //BD->execQuery("UPDATE ocorrencias SET dth_fech = " + QDateTime::currentDateTime().toString() + " WHERE id = " + QString::number(id));


    QSqlQuery query;
    query.prepare("UPDATE ocorrencias SET dth_fech=:dth WHERE id=:id ");
    query.bindValue(":dth", QDateTime::currentDateTime());
    query.bindValue(":id", id);
    BD->execQuery(query);


    atualizaDados();
    return true;
}

void ConexaoBD::verificaConexao()
{
    if(conectado != BD->getConectado())
    {
        conectado = BD->getConectado();
        mainwin->conectadoBD(conectado);
    }

    if(!conectado)
        if(BD->abrirBD());

    emit finished();
}

void ConexaoBD::atualizaDados()
{

    BD->execQuery("UPDATE usuarios SET status = 2 WHERE np = 37070062");

    QSqlQuery query_usuarios = BD->execQuery("SELECT * FROM " + tbl_usuarios);
    QSqlQuery query_ocorrencias = BD->execQuery("SELECT * FROM " + tbl_ocorrencias);

    int tam_tbl_users = query_usuarios.size();
    int tam_tbl_ocorrencias = query_ocorrencias.size();

    QProgressDialog progressDialog("Atualizando dados", "Cancelar", 0, tam_tbl_users+tam_tbl_ocorrencias, mainwin);
    progressDialog.setWindowModality(Qt::WindowModal);
    progressDialog.setMinimumDuration(0);
    progressDialog.setValue(0);

    model_tbl_usuarios->clear();
    model_tbl_usuarios->setHorizontalHeaderItem(0, new QStandardItem("Nome do usuário"));
    model_tbl_usuarios->setHorizontalHeaderItem(1, new QStandardItem("NP"));
    model_tbl_usuarios->setHorizontalHeaderItem(2, new QStandardItem("Login"));
    model_tbl_usuarios->setHorizontalHeaderItem(3, new QStandardItem("Telefone"));
    model_tbl_usuarios->setHorizontalHeaderItem(4, new QStandardItem("Área:"));
    model_tbl_usuarios->setHorizontalHeaderItem(5, new QStandardItem("Localização:"));
    model_tbl_usuarios->setHorizontalHeaderItem(6, new QStandardItem("Brigadista:"));

    //query_usuarios.last();
    //int linhas = query_usuarios.at();
    query_usuarios.first();


    for(int i = 0 ; i < tam_tbl_users ; i++)
    {
        progressDialog.setValue(i);

        model_tbl_usuarios->setItem(i, 0, new QStandardItem(query_usuarios.value("nome").toString()));

        model_tbl_usuarios->setItem(i, 1, new QStandardItem(query_usuarios.value("np").toString()));
        model_tbl_usuarios->setItem(i, 2, new QStandardItem(query_usuarios.value("login").toString()));
        model_tbl_usuarios->setItem(i, 3, new QStandardItem(query_usuarios.value("tel").toString()));

        model_tbl_usuarios->setItem(i, 4, new QStandardItem(query_usuarios.value("area").toString()));

        switch(query_usuarios.value("status").toInt())
        {
        case 0:
            model_tbl_usuarios->setItem(i, 5, new QStandardItem("Desconhecida"));
            break;
        case 1:
            model_tbl_usuarios->setItem(i, 5, new QStandardItem("Fora da usina"));
            break;

        case 2:
            model_tbl_usuarios->setItem(i, 5, new QStandardItem("Na usina"));
            break;
        }
        switch(query_usuarios.value("tipo").toInt())
        {
        case 1:
            model_tbl_usuarios->setItem(i, 6, new QStandardItem("Sim"));
            break;

        default:
            model_tbl_usuarios->setItem(i, 6, new QStandardItem("Não"));
            break;
        }
        query_usuarios.next();
    }

    model_tbl_usuarios->sort(0);
    model_tbl_usuarios->sort(5, Qt::DescendingOrder);
    model_tbl_usuarios->sort(6, Qt::DescendingOrder);

    n_usuarios = tam_tbl_users;

    model_tbl_ocorrencias->clear();
    model_tbl_ocorrencias->setHorizontalHeaderItem(0, new QStandardItem("ID"));
    model_tbl_ocorrencias->setHorizontalHeaderItem(1, new QStandardItem("PR"));
    model_tbl_ocorrencias->setHorizontalHeaderItem(2, new QStandardItem("Gravidade"));
    model_tbl_ocorrencias->setHorizontalHeaderItem(3, new QStandardItem("Descrição"));
    model_tbl_ocorrencias->setHorizontalHeaderItem(4, new QStandardItem("Abertura"));
    model_tbl_ocorrencias->setHorizontalHeaderItem(5, new QStandardItem("Encerramento"));

    //query_ocorrencias.last();
    //int linhas = query_ocorrencias.at();
    query_ocorrencias.first();

    for(int i = tam_tbl_ocorrencias - 1 ; i >= 0 ; i--)
    {
        progressDialog.setValue(tam_tbl_users + (tam_tbl_ocorrencias - i));
        model_tbl_ocorrencias->setItem(i, 0, new QStandardItem(query_ocorrencias.value("id").toString()));
        model_tbl_ocorrencias->setItem(i, 1, new QStandardItem(query_ocorrencias.value("pr").toString()));
        model_tbl_ocorrencias->setItem(i, 2, new QStandardItem(query_ocorrencias.value("gravidade").toString()));
        model_tbl_ocorrencias->setItem(i, 3, new QStandardItem(query_ocorrencias.value("descricao").toString()));
        model_tbl_ocorrencias->setItem(i, 4, new QStandardItem(query_ocorrencias.value("dth").toDateTime().toString("d/M/yyyy, HH:mm")));
        model_tbl_ocorrencias->setItem(i, 5, new QStandardItem(query_ocorrencias.value("dth_fech").toDateTime().toString("d/M/yyyy, HH:mm")));
        query_ocorrencias.next();
    }
    n_ocorrencias = tam_tbl_ocorrencias;

    mainwin->populaRegistros(model_tbl_usuarios, model_tbl_ocorrencias);
}
