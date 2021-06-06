#include <QtGui>
#include <QApplication>
#include <QDialog>
#include "delegateocorrencias.h"

DelegateOcorrencias::DelegateOcorrencias(QObject *parent)
    : QItemDelegate(parent)
{

}


void DelegateOcorrencias::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QItemDelegate::paint(painter , option , index);

    if(index.column() == 5 && index.model()->data(index, Qt::EditRole).toString().size() == 0)
    {
        QPixmap pixmap;
        pixmap.load(QDir::currentPath() + "/icon/no.png");
        pixmap = pixmap.scaled(option.rect.width() - 8, option.rect.height() - 8, Qt::KeepAspectRatio);

       // Position our pixmap
       const int x = option.rect.center().x() - pixmap.rect().width() / 2;
       const int y = option.rect.center().y() - pixmap.rect().height() / 2;

       if (option.state & QStyle::State_Selected) {
           painter->fillRect(option.rect, option.palette.highlight());
       }

       painter->drawPixmap(QRect(x, y, pixmap.rect().width(), pixmap.rect().height()), pixmap);
    }
}
