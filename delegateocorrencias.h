#ifndef DELEGATEOCORRENCIAS_H
#define DELEGATEOCORRENCIAS_H
#include <QItemDelegate>

class DelegateOcorrencias : public QItemDelegate
{
     Q_OBJECT
public:
    DelegateOcorrencias(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATEOCORRENCIAS_H
