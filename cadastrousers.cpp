#include "cadastrousers.h"
#include "ui_cadastrousers.h"
#include <mainwindow.h>
#include <qmessagebox.h>
#include <conexaobd.h>
//#include <usuario.h>

CadastroUsers::CadastroUsers(QWidget *parent, ConexaoBD *conex) :
    QDialog(parent),
    ui(new Ui::CadastroUsers)
{
    ui->setupUi(this);
    ui->line_nome->setMaxLength(30);
    //ui->line_np->setInputMask("99999999999999999999");
    ui->line_np->setValidator(new QIntValidator(0, 999999999, this));

    //ui->line_user->setInputMask("NNNNNNNNNNNNNNNNNNNN");
    ui->line_user->setMaxLength(20);
    ui->line_senha->setMaxLength(20);

    ui->celular_telefone->addItem("Celular");
    ui->celular_telefone->addItem("Telefone Fixo");

    ui->brigadista->setChecked(true);

    setWindowTitle("Cadastro de usuário");
    setFixedSize(geometry().width(), geometry().height());
    conexBD = conex;

    ui->excluirButton->hide();
    ui->atualizarButton->hide();
    //user_atual = new Usuario("","","","",0,0,0,0);

    ui->area->addItems(conexBD->getAreas());
}

CadastroUsers::~CadastroUsers()
{
    delete ui;
}

void CadastroUsers::on_cadastrarButton_clicked()
{
    if(conexBD->cadastrarUsuario(ui->line_nome->text(), ui->line_np->text(), ui->line_user->text(), ui->line_senha->text(), ui->line_telefone->text(), ui->area->currentIndex(), ui->brigadista->isChecked(), true))
    {
        //TO DO Cadastrado com sucesso?

        QMessageBox msgBox;
        msgBox.setText("Usuário cadastrado com sucesso");
        msgBox.exec();
        close();
    }
    conexBD->atualizaDados();
}

void CadastroUsers::on_atualizarButton_clicked()
{
    if(conexBD->cadastrarUsuario(ui->line_nome->text(), ui->line_np->text(), ui->line_user->text(), ui->line_senha->text(), ui->line_telefone->text(), ui->area->currentIndex(), ui->brigadista->isChecked(), false))
    {
        QMessageBox msgBox;
        msgBox.setText("Cadastro atualizado com sucesso");
        msgBox.exec();
        close();
    }
    conexBD->atualizaDados();
}

void CadastroUsers::on_celular_telefone_currentIndexChanged(int index)
{
    if(index == 0)
        ui->line_telefone->setInputMask("(99) 99999-9999;_");
    else
        ui->line_telefone->setInputMask("(99) 9999-9999;_");
}

void CadastroUsers::setUsuario(Usuario user)
{
    ui->line_nome->setText(user.getNome());
    ui->line_np->setText(QString::number(user.getNp()));
    ui->line_user->setText(user.getLogin());
    ui->line_senha->setText(user.getSenha());
    ui->line_telefone->setText(user.getTel());

    ui->brigadista->setChecked(user.getTipo() == 1 ? true : false);
    ui->area->setCurrentIndex(user.getArea());
    ui->excluirButton->show();
    ui->atualizarButton->show();
    ui->cadastrarButton->hide();

    ui->area->setCurrentIndex(user.getArea());
    user_atual = user;
}

void CadastroUsers::limparTela()
{
    ui->line_nome->clear();
    ui->line_np->clear();
    ui->line_user->clear();
    ui->line_senha->clear();
    ui->line_telefone->clear();
    ui->excluirButton->hide();
    ui->atualizarButton->hide();
    ui->cadastrarButton->show();
}
void CadastroUsers::closeEvent(QCloseEvent *event)
{
    limparTela();
}

void CadastroUsers::on_excluirButton_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exclusão de usuário", "Deseja realmente excluir esse usuário?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        if(conexBD->apagarUsuario(user_atual.getNp()))
        {
            QMessageBox msgBox;
            msgBox.setText("Usuário apagado com sucesso");
            msgBox.exec();

            close();
        }

        conexBD->atualizaDados();
    }
}
