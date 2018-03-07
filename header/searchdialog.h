#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H
#include <QDialog>
#include <QMessageBox>
#include <QLabel>
#include "mainwindow.h"
#include "containertablemodel.h"

class SearchDialog: public QDialog{
    Q_OBJECT
public:
    explicit SearchDialog(QList<int>& indxList,QWidget* parent= 0);

    QLabel* risLbl;
    QTableView* tabRis;
    ContainerTableModel* tabModelRis;
    QItemSelectionModel* selectionModelRis;

    QPushButton* selectBtn;
};

#endif // SEARCHDIALOG_H
