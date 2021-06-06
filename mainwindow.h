#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bancodados.h>
#include <conexaobd.h>

#include <QtSql>
#include <cadastrousers.h>
#include <QStandardItemModel>

class PlanilhaExcel;
class ConexaoBD;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void populaRegistros(QStandardItemModel *model_tbl_usuarios, QStandardItemModel *model_tbl_ocorrencias);
    bool erroServidor();
    void conectadoBD(bool conectado);
    void cadastrarUsuario(QString nome, QString np, QString usuario, QString senha, QString tel, int area, bool brigadista, bool cadastro);
    QString toCamelCase(const QString& s);

private slots:
    void on_cadastrarUser_clicked();
    void on_regOcorrencia_clicked();
    void on_teste_query_clicked();
    void refresh();
    void on_descOcorrencia_textChanged();
    void on_listaOcorrencias_doubleClicked(const QModelIndex &index);
    void on_listaUsuarios_doubleClicked(const QModelIndex &index);

    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;
    BDBrigada *BD;
    QString tbl_usuarios = "usuarios";
    QString tbl_ocorrencias = "ocorrencias";
    CadastroUsers *tela_cadastro;
    //QStandardItemModel *model_tbl_usuarios, *model_tbl_ocorrencias;
    QList<QList<QStandardItem>> *tbl_item_usuarios;
    int n_ocorrencias = 0, n_usuarios = 0;

    PlanilhaExcel *planilha;
    ConexaoBD *conexBD;
    QThread *thread_conexao, *thread_popula;
};

#endif // MAINWINDOW_H
