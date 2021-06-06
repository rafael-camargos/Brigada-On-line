#ifndef CADASTROUSERS_H
#define CADASTROUSERS_H

#include <QDialog>
#include <usuario.h>

class ConexaoBD;
namespace Ui {
class CadastroUsers;
}

class CadastroUsers : public QDialog
{
    Q_OBJECT

public:
    CadastroUsers(QWidget *parent = 0, ConexaoBD *conex = 0);
    ~CadastroUsers();
    void setUsuario(Usuario user);
    void limparTela();

private slots:
    void on_cadastrarButton_clicked();
    void on_celular_telefone_currentIndexChanged(int index);
    void on_atualizarButton_clicked();
    void on_excluirButton_clicked();

private:
    Ui::CadastroUsers *ui;
    ConexaoBD *conexBD;
    void closeEvent(QCloseEvent *event);
    Usuario user_atual;
};

#endif // CADASTROUSERS_H
