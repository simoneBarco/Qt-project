#ifndef CONTAINERTABLEMODEL_H
#define CONTAINERTABLEMODEL_H

#include <QAbstractTableModel>
#include "staticcont.h"
#include "assicurazione.h"
#include "casa.h"
#include "rcauto.h"
#include "sanitaria.h"
#include "Container.h"

class ContainerTableModel : public QAbstractTableModel{
    Q_OBJECT
private:
    bool insertAssicurazione(Assicurazione* ass);
public:
    explicit ContainerTableModel(QObject* parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    bool insertCasa();
    bool insertRCAuto();
    bool insertSanit();

    bool removeRows(int pos, int rig, const QModelIndex& index);
    void updateView(const QModelIndex& ind1, const QModelIndex& ind2);
signals:

public slots:
};

#endif // CONTAINERTABLEMODEL_H
