#ifndef PLANILHAEXCEL_H
#define PLANILHAEXCEL_H
#include <QString>

class MainWindow;

class PlanilhaExcel
{
public:
    PlanilhaExcel(MainWindow *mainwindow);
    //PlanilhaExcel();
    void lerUsuarios(wchar_t array[]);
private:
    MainWindow *mainwin;
};

#endif // PLANILHAEXCEL_H
