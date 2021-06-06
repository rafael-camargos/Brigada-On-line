#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <planilhaexcel.h>
#include <worker.h>
#include <delegateocorrencias.h>

#include <QMessageBox>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //BD = new BDBrigada("QMYSQL", "sql10.freesqldatabase.com", "sql10223867", "sql10223867", "ycH2B4Ijab");


    QTimer *refresher = new QTimer(this);
    refresher->start(500);
    connect(refresher, SIGNAL(timeout()), this, SLOT(refresh()));

    //model_tbl_usuarios = new QStandardItemModel(this);
    //model_tbl_ocorrencias = new QStandardItemModel(this);

    tbl_item_usuarios = new QList<QList<QStandardItem>>();

    //ui->listaUsuarios->setModel(model_tbl_usuarios);
    //ui->listaOcorrencias->setModel(model_tbl_ocorrencias);

    ui->listaUsuarios->verticalHeader()->hide();
    ui->listaUsuarios->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->listaUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listaOcorrencias->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listaOcorrencias->verticalHeader()->hide();
    ui->listaOcorrencias->setSelectionBehavior(QAbstractItemView::SelectRows);

    //DelegateOcorrencias dl;

    ui->listaOcorrencias->setItemDelegate(new DelegateOcorrencias);

    for(int i = 1 ; i <= 17 ; i++)
    {
        ui->prBox->addItem("PR" + QString::number(i));
    }
    ui->gravidadeBox->addItem("Leve");
    ui->gravidadeBox->addItem("Média");
    ui->gravidadeBox->addItem("Grave");
    ui->gravidadeBox->addItem("Gravíssima");

    setWindowTitle("Brigada On-line");
    setFixedSize(geometry().width(), geometry().height());

    planilha = new PlanilhaExcel(this);

    conexBD = new ConexaoBD(this);
    tela_cadastro = new CadastroUsers(this, conexBD);

    thread_conexao = new QThread;
    thread_popula = new QThread;
    conexBD->moveToThread(thread_conexao);

    //conexBD->moveToThread(thread_popula);
    connect(thread_conexao, SIGNAL (started()), conexBD, SLOT (verificaConexao()));
    connect(conexBD, SIGNAL (finished()), thread_conexao, SLOT (quit()));

    on_refresh_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    thread_conexao->start();
}
void MainWindow::on_cadastrarUser_clicked()
{
    if(!erroServidor())
        tela_cadastro->show();
}

void MainWindow::cadastrarUsuario(QString nome, QString np, QString usuario, QString senha, QString tel, int area, bool brigadista, bool cadastro)
{
    conexBD->cadastrarUsuario(toCamelCase(nome), np, usuario, senha, tel, area, brigadista, cadastro);
}

void MainWindow::on_regOcorrencia_clicked()
{
    if(!erroServidor())
    {
        conexBD->cadastrarOcorrencia(ui->prBox->currentText(), ui->gravidadeBox->currentText(), ui->descOcorrencia->toPlainText());
        //TO DO Cadastrado com sucesso?
    }
}

bool MainWindow::erroServidor()
{
    if(!BD->getConectado())
    {
        QMessageBox messageBox;
        messageBox.critical(this, "Erro", "Não há conexão com o servidor!");
        messageBox.setFixedSize(500, 200);
        return true;
    }
    else
        return false;
}
void MainWindow::populaRegistros(QStandardItemModel *model_tbl_usuarios, QStandardItemModel *model_tbl_ocorrencias)
{
    ui->listaUsuarios->setModel(model_tbl_usuarios);
    ui->listaUsuarios->resizeColumnsToContents();

    ui->listaOcorrencias->setModel(model_tbl_ocorrencias);
    ui->listaOcorrencias->resizeColumnsToContents();
}

void MainWindow::on_teste_query_clicked()
{
    conexBD->reiniciarBD();
    planilha->lerUsuarios(L"D:\TREINAMENTO BRIGADISTAS.xlsx");
    planilha->lerUsuarios(L"D:\TREINAMENTO BRIGADISTAS2.xlsx");
    conexBD->atualizaDados();

}

void MainWindow::on_descOcorrencia_textChanged() //Limita o texto da descrição para 200 caracteres
{
    if (ui->descOcorrencia->toPlainText().length() > 200)
    {
        QString text = ui->descOcorrencia->toPlainText();
        text.chop(text.length() - 200);
        ui->descOcorrencia->setPlainText(text);

        QTextCursor cursor = ui->descOcorrencia->textCursor();
        cursor.setPosition(ui->descOcorrencia->document()->characterCount() - 1);
        ui->descOcorrencia->setTextCursor(cursor);
    }
}


void MainWindow::on_listaOcorrencias_doubleClicked(const QModelIndex &index)
{
    //qDebug() << ui->listaOcorrencias->model()->index(index.row(), 0).data();
    QString dth_encerramento = ui->listaOcorrencias->model()->index(index.row(), 5).data().toString();
    if(dth_encerramento == 0)
    {
        QString id_ocorrencia = ui->listaOcorrencias->model()->index(index.row(), 0).data().toString();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Encerramento de ocorrência", "Deseja encerrar a ocorrência " + id_ocorrencia + "?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            conexBD->encerrarOcorrencia(id_ocorrencia.toInt());
            {
                QMessageBox msgBox;
                msgBox.setText("Ocorrência encerrada");
                msgBox.exec();
            }
        }
    }
}

void MainWindow::on_listaUsuarios_doubleClicked(const QModelIndex &index)
{
    if(!erroServidor())
    {

        tela_cadastro->setUsuario(conexBD->getUsuario(ui->listaUsuarios->model()->index(index.row(), 1).data().toString()));
        tela_cadastro->show();
        //qDebug() << conexBD->getUsuario(ui->listaUsuarios->model()->index(index.row(), 1).data().toString()).getNome();
    }
}

void MainWindow::conectadoBD(bool conectado)
{
    if(conectado)
    {
        ui->conectado->setText("Conectado");
        ui->conectado->setStyleSheet("QLabel {color : green;}");
    }
    else
    {
        ui->conectado->setText("Desconectado");
        ui->conectado->setStyleSheet("QLabel {color : red;}");
    }
}

QString MainWindow::toCamelCase(const QString& s)
{
    QStringList parts = s.toLower().split(' ', QString::SkipEmptyParts);

    qDebug() << parts.size();
    for (int i = 0 ; i < parts.size() ; i++)
        parts[i].replace(0, 1, parts[i][0].toUpper());

    return parts.join(" ");
}

void MainWindow::on_refresh_clicked()
{
    conexBD->atualizaDados();
    conexBD->getAreas();
}
