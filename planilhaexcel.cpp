#include "planilhaexcel.h"
#include "mainwindow.h"

#include <QDebug>
#include <iostream>
#include <libxl.h>

using namespace libxl;

PlanilhaExcel::PlanilhaExcel(MainWindow *mainwindow)
{
    mainwin = mainwindow;
}

void PlanilhaExcel::lerUsuarios(wchar_t array[])
{
    Book* book = xlCreateXMLBook();
    //wchar_t *array[9];
    //nome_arquivo.toWCharArray(array);
    //if(book->load(L"D:\TREINAMENTO BRIGADISTAS.xlsx"))
        if(book->load(array))
    {
        qDebug() << "Lendo usuarios";
        Sheet* sheet = book->getSheet(0);
        if(sheet)
        {
            for(int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
            {
                QString nome;
                int np;
                for(int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
                {
                    CellType cellType = sheet->cellType(row, col);
                    qDebug() << "(" << row << ", " << col << ") = ";
                    if(sheet->isFormula(row, col))
                    {
                        const wchar_t* s = sheet->readFormula(row, col);
                        qDebug() << (s ? s : L"null") << " [formula]";
                    }
                    else
                    {
                        switch(cellType)
                        {
                        case CELLTYPE_EMPTY: qDebug() << "[empty]"; break;
                        case CELLTYPE_NUMBER:
                        {
                            int d = sheet->readNum(row, col);
                            qDebug() << d << " [number]";

                            np = d;
                            break;
                        }
                        case CELLTYPE_STRING:
                        {
                            const QString s = QString::fromWCharArray(sheet->readStr(row, col));
                            //qDebug() << (s ? s : L"null") << " [string]";

                            nome = s;
                            qDebug() << s;
                            break;
                        }
                        case CELLTYPE_BOOLEAN:
                        {
                            bool b = sheet->readBool(row, col);
                            qDebug() << (b ? "true" : "false") << " [boolean]";
                            break;
                        }
                        case CELLTYPE_BLANK: qDebug() << "[blank]"; break;
                        case CELLTYPE_ERROR: qDebug() << "[error]"; break;
                        }
                    }
                    qDebug() << endl;

                    if(col == 2)
                        if(nome.size() > 0)
                            mainwin->cadastrarUsuario(nome, QString::number(np), "", "123", "", 0, true, true);
                }
            }
        }
    }
    else
    {
        qDebug() << "erro: " << book->errorMessage();
    }

    book->release();
}
