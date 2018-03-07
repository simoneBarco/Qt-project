#ifndef DETAILSDIALOG_H
#define DETAILSDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QDateEdit>
#include <QRadioButton>
#include <QButtonGroup>
#include "mainwindow.h"
#include "containertablemodel.h"

class DetailsDialog: public QDialog{
    Q_OBJECT
public:
    explicit DetailsDialog(QString type, QWidget* parent= 0);

    //elementi globali (Assicurazione)
    QLabel* NomeLbl;
    QLineEdit* NomeEdit;
    QLabel* DataStLbl;
    QDateEdit* DataStCal;

    //elementi Casa
    QLabel* AnnoCostrLbl;
    QSpinBox* AnnoCostrSpin;
    QLabel* AnnoRistLbl;
    QSpinBox* AnnoRistSpin;
    QLabel* SpeseLbl;
    QSpinBox* SpeseSpin;
    QLabel* ProvLbl;
    QComboBox* Prov;
    QCheckBox* CheckFurto;
    QCheckBox* CheckInce;
    QCheckBox* CheckCalam;

    //elementi RCAuto
    QLabel* MassLbl;
    QSpinBox* MassSpin;
    QLabel* CavFiscLbl;
    QComboBox* CavFisc;
    QLabel* EtaLbl;
    QComboBox* Eta;
    QLabel* ClassMeritoLbl;
    QComboBox* ClassMerito;

    //elementi Sanitaria
    QRadioButton* RadioInd;
    QRadioButton* RadioNuc;
    QCheckBox* CheckAmb;
    QCheckBox* CheckDom;

    QPushButton* okButton;
public slots:
    void warning();

};

#endif // DETAILSDIALOG_H
