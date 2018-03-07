#include "detailsdialog.h"

DetailsDialog::DetailsDialog(QString type, QWidget* parent):
    QDialog(parent){
        setWindowTitle("Dettagli");

        //macro distruzione widget
        #define DELETE_LATER(widget) \
            connect(this, SIGNAL(destroyed()), widget, SLOT(deleteLater()))

        //widget comuni a tutte le assicurazioni
        NomeLbl = new QLabel("Nome: ");
        NomeEdit = new QLineEdit();
        DataStLbl = new QLabel("Data Stipula: ");
        DataStCal = new QDateEdit();
        DataStCal->setCalendarPopup(true);

        //widget per Casa
        AnnoCostrLbl = new QLabel("Anno Costruzione:");
        AnnoCostrSpin = new QSpinBox();
        AnnoCostrSpin->setRange(1940, 2016);

        AnnoRistLbl = new QLabel("Anno Ristrutturazione:");
        AnnoRistSpin = new QSpinBox();
        AnnoRistSpin->setRange(1941, 2015);

        SpeseLbl = new QLabel("Spese Legali:");
        SpeseSpin = new QSpinBox();
        SpeseSpin->setRange(1000, 10000);
        SpeseSpin->setSingleStep(100);//per saltare di 100

        ProvLbl = new QLabel("Provincia di Residenza:");
        Prov = new QComboBox();
        Prov->addItem("PD", "PD");
        Prov->addItem("BL", "BL");
        Prov->addItem("RO", "RO");
        Prov->addItem("TV", "TV");
        Prov->addItem("VE", "VE");
        Prov->addItem("VR", "VR");
        Prov->addItem("VI", "VI");

        CheckFurto = new QCheckBox("Furto");
        CheckInce = new QCheckBox("Incendio");
        CheckCalam = new QCheckBox("Calamità");

        //widget per RCAuto (MassLbl e MassSpin sono in comune anche con Sanitaria)
        MassLbl = new QLabel("Massimale: (espresso in milioni di euro)");
        MassSpin = new QSpinBox();
        MassSpin->setRange(5, 60);

        CavFiscLbl = new QLabel("Cavalli Fiscali:");
        CavFisc = new QComboBox();
        for(int i=1; i<=50; ++i)
            CavFisc->addItem(QString::number(i));

        EtaLbl = new QLabel("Età:");
        Eta = new QComboBox();
        for(int i=18; i<=70; ++i)
            Eta->addItem(QString::number(i));

        connect(Eta, SIGNAL(currentIndexChanged(int)),this, SLOT(warning()));

        ClassMeritoLbl = new QLabel("Classe di merito");
        ClassMerito = new QComboBox();
        for(int i=1; i<=22; ++i)
            ClassMerito->addItem(QString::number(i));

        //widget per Sanitaria
        RadioInd = new QRadioButton("Individuale");
        RadioNuc = new QRadioButton("Nucleo familiare");

        CheckAmb = new QCheckBox("Ambulanza");
        CheckDom = new QCheckBox("Domicilio");

        okButton = new QPushButton("Ok");

        DELETE_LATER(AnnoCostrLbl);
        DELETE_LATER(AnnoCostrSpin);
        DELETE_LATER(AnnoRistLbl);
        DELETE_LATER(AnnoRistSpin);
        DELETE_LATER(SpeseLbl);
        DELETE_LATER(SpeseSpin);
        DELETE_LATER(ProvLbl);
        DELETE_LATER(Prov);
        DELETE_LATER(CheckFurto);
        DELETE_LATER(CheckInce);
        DELETE_LATER(CheckCalam);
        DELETE_LATER(MassLbl);
        DELETE_LATER(MassSpin);
        DELETE_LATER(CavFiscLbl);
        DELETE_LATER(CavFisc);
        DELETE_LATER(EtaLbl);
        DELETE_LATER(Eta);
        DELETE_LATER(ClassMeritoLbl);
        DELETE_LATER(ClassMerito);
        DELETE_LATER(RadioInd);
        DELETE_LATER(RadioNuc);
        DELETE_LATER(CheckAmb);
        DELETE_LATER(CheckDom);

        //creazione griglia in cui verranno inseriti i widget, inizialmente vengono inseriti quelli in comune con tutti
        //e poi a seconda del tipo di assicurazione
        QGridLayout* gLay = new QGridLayout;

        gLay->addWidget(NomeLbl, 0, 0);
        gLay->addWidget(NomeEdit, 0, 1);
        gLay->addWidget(DataStLbl, 1, 0);
        gLay->addWidget(DataStCal, 1, 1);

        if(type == "Casa"){
            gLay->addWidget(AnnoCostrLbl, 2, 0);
            gLay->addWidget(AnnoCostrSpin, 2, 1);
            gLay->addWidget(AnnoRistLbl, 3, 0);
            gLay->addWidget(AnnoRistSpin, 3, 1);
            gLay->addWidget(SpeseLbl, 4, 0);
            gLay->addWidget(SpeseSpin, 4, 1);
            gLay->addWidget(ProvLbl, 5, 0);
            gLay->addWidget(Prov, 5, 1);
            gLay->addWidget(CheckFurto, 6, 0);
            gLay->addWidget(CheckInce, 7, 0);
            gLay->addWidget(CheckCalam, 8, 0);
        }
        if(type == "RCAuto"){
            gLay->addWidget(MassLbl, 2, 0);
            gLay->addWidget(MassSpin, 2, 1);
            gLay->addWidget(CavFiscLbl, 3, 0);
            gLay->addWidget(CavFisc, 3, 1);
            gLay->addWidget(EtaLbl, 4, 0);
            gLay->addWidget(Eta, 4, 1);
            gLay->addWidget(ClassMeritoLbl, 5, 0);
            gLay->addWidget(ClassMerito, 5, 1);
        }
        if(type == "Sanitaria"){
            gLay->addWidget(MassLbl, 2, 0);
            gLay->addWidget(MassSpin, 2, 1);
            gLay->addWidget(RadioInd, 3, 0);
            gLay->addWidget(RadioNuc, 3, 1);
            gLay->addWidget(CheckAmb, 4, 0);
            gLay->addWidget(CheckDom, 5, 0);
        }

        gLay->addWidget(okButton, 9, 0);

        setLayout(gLay);

        connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    }

//slot che gestisce il caso in cui l'assicurazione sia di tipo RCAuto e l'età viene impostata a 18
void DetailsDialog::warning(){
    int indEt18= Eta->findText(QString::number(18));
    if(Eta->currentIndex() == indEt18){
        QMessageBox* warn= new QMessageBox(this);
        warn->open();
        warn->setWindowTitle("ATTENZIONE");
        warn->setText("Selezionando i 18 anni la selezione dei Cavalli Fiscali viene impostata a 11 dovuta alla limitazione per i neopatentati");
        int indCv= CavFisc->findText(QString::number(11));
        CavFisc->setCurrentIndex(indCv);
        CavFisc->setDisabled(true);
    }
    else
        CavFisc->setDisabled(false);
}
