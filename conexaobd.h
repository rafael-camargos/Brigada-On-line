#ifndef CONEXAOBD_H
#define CONEXAOBD_H
#include <QObject>
#include <bancodados.h>
#include <QtSql>
#include <QStandardItemModel>
#include <usuario.h>

class MainWindow;

class ConexaoBD : public QObject
{
    Q_OBJECT
public:
    ConexaoBD(MainWindow *mainwindow);
    ~ConexaoBD();
    bool cadastrarOcorrencia(QString pr, QString gravidade, QString descricao);
    bool encerrarOcorrencia(int id);
    bool cadastrarUsuario(QString nome, QString np, QString usuario, QString senha, QString tel, int area, bool brigadista, bool cadastro);
    bool apagarUsuario(int np);
    bool reiniciarBD();
    void atualizaDados();
    Usuario getUsuario(QString np);
    QStringList getAreas();

public slots:
    void verificaConexao();
signals:
    void finished();
    void error(QString err);
private:
    // add your variables here
    BDBrigada *BD;
    QString tbl_usuarios = "usuarios";
    QString tbl_ocorrencias = "ocorrencias";
    QString tbl_areas = "areas";
    MainWindow *mainwin;
    bool conectado;
    QStandardItemModel *model_tbl_usuarios, *model_tbl_ocorrencias;
    int n_ocorrencias = 0, n_usuarios = 0;
};

#endif // CONEXAOBD_H
