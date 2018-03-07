#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QVBoxLayout>
#include <QAction>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QItemSelection>
#include "staticcont.h"
#include "containertablemodel.h"
#include "detailsdialog.h"
#include "searchdialog.h"


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QMenu* editMenu;
    QMenu* addRMenu;
    QAction* addCasaAct;
    QAction* addRCAct;
    QAction* addSanAct;

    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;

    QLineEdit* ricerca;

    QLabel* CasaLbl;
    QTableView* tabCasa;

    QLabel* RCAutoLbl;
    QTableView* tabRCAuto;

    QLabel* SanitLbl;
    QTableView* tabSanit;

    QPushButton* detailBtnC;
    QPushButton* detailBtnR;
    QPushButton* detailBtnS;
    QPushButton* deleteBtnC;//SISTEMARE QUESTI<---
    QPushButton* deleteBtnR;//SISTEMARE QUESTI<---
    QPushButton* deleteBtnS;//SISTEMARE QUESTI<---


    ContainerTableModel* tabModelR;
    ContainerTableModel* tabModelC;
    ContainerTableModel* tabModelS;

    QItemSelectionModel* selectionModelC;
    QItemSelectionModel* selectionModelR;
    QItemSelectionModel* selectionModelS;

    void createAct();
    void createMenu();


private slots:
    void insCasa();
    void insRCAuto();
    void insSanit();
    void viewBtnsC();
    void viewBtnsR();
    void viewBtnsS();
    void openDetailsC();
    void openDetailsR();
    void openDetailsS();
    void search();
    //void deleteObj();//SISTEMARE QUESTI<---
    void deleteObjC();//SISTEMARE QUESTI<---
    void deleteObjR();//SISTEMARE QUESTI<---
    void deleteObjS();//SISTEMARE QUESTI<---

};

#endif // MAINWINDOW_H
