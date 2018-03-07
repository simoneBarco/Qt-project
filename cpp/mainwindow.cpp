#include <QDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QStandardItem>
#include <QItemSelectionModel>
#include <QString>
#include <QDebug>
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent){
        setWindowTitle(QString("Assicurazioni"));

        createAct();
        createMenu();

        ricerca = new QLineEdit();
        ricerca->setPlaceholderText("Cerca un nome assicurazione");

        CasaLbl = new QLabel("Casa:");
        tabCasa = new QTableView;
        RCAutoLbl = new QLabel("RCAuto:");
        tabRCAuto = new QTableView;
        SanitLbl = new QLabel("Sanitaria:");
        tabSanit = new QTableView;

        //creo i modelli per le 3 tabelle
        tabModelC = new ContainerTableModel(this);
        tabModelC->setObjectName("tabModelC");
        tabModelR = new ContainerTableModel(this);
        tabModelR->setObjectName("tabModelR");
        tabModelS = new ContainerTableModel(this);
        tabModelS->setObjectName("tabModelS");

        vLayout = new QVBoxLayout;
        hLayout = new QHBoxLayout;
        //creo i pulsanti per le 3 tabelle
        detailBtnC = new QPushButton("Vedi/Modifica");
        detailBtnR = new QPushButton("Vedi/Modifica");
        detailBtnS = new QPushButton("Vedi/Modifica");
        deleteBtnC = new QPushButton("Elimina");
        deleteBtnR = new QPushButton("Elimina");
        deleteBtnS = new QPushButton("Elimina");

        setCentralWidget(new QWidget);

        centralWidget()->setLayout(vLayout);

        tabCasa->setModel(tabModelC);
        tabRCAuto->setModel(tabModelR);
        tabSanit->setModel(tabModelS);

        //creo la QTableView per CASA
        tabCasa->setSelectionBehavior(QAbstractItemView::SelectRows);

        tabCasa->verticalHeader()->setVisible(false);
        tabCasa->setAlternatingRowColors(true);
        tabCasa->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tabCasa->setMinimumSize(700,100);

        //creo la QTableView per RCAUTO
        tabRCAuto->setSelectionBehavior(QAbstractItemView::SelectRows);

        tabRCAuto->verticalHeader()->setVisible(false);
        tabRCAuto->setAlternatingRowColors(true);
        tabRCAuto->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tabRCAuto->setMinimumSize(700,100);

        //creo la QTableView per SANITARIA
        tabSanit->setSelectionBehavior(QAbstractItemView::SelectRows);

        tabSanit->verticalHeader()->setVisible(false);
        tabSanit->setAlternatingRowColors(true);
        tabSanit->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        tabSanit->setMinimumSize(700,100);

        vLayout->addWidget(ricerca);
        vLayout->addWidget(CasaLbl);
        vLayout->addWidget(tabCasa);
        vLayout->addWidget(RCAutoLbl);
        vLayout->addWidget(tabRCAuto);
        vLayout->addWidget(SanitLbl);
        vLayout->addWidget(tabSanit);
        hLayout->addWidget(detailBtnC);
        hLayout->addWidget(detailBtnR);
        hLayout->addWidget(detailBtnS);
        hLayout->addWidget(deleteBtnC);
        hLayout->addWidget(deleteBtnR);
        hLayout->addWidget(deleteBtnS);

        selectionModelC = tabCasa->selectionModel();
        selectionModelR = tabRCAuto->selectionModel();
        selectionModelS = tabSanit->selectionModel();

        //connect per visualizzare i bottoni "vedi/modifica" e "elimina" nella selezione di Casa
        connect(selectionModelC, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(viewBtnsC()));
        //connect per visualizzare i bottoni "vedi/modifica" e "elimina" nella selezione di RCAuto
        connect(selectionModelR, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(viewBtnsR()));
        //connect per visualizzare i bottoni "vedi/modifica" e "elimina" nella selezione di Sanitaria
        connect(selectionModelS, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
                this, SLOT(viewBtnsS()));

        //connect per visualizzare i dettagli di un'assicurazione Casa
        connect(detailBtnC, SIGNAL(clicked()), this, SLOT(openDetailsC()));
        //connect per visualizzare i dettagli di un'assicurazione RCAuto
        connect(detailBtnR, SIGNAL(clicked()), this, SLOT(openDetailsR()));
        //connect per visualizzare i dettagli di un'assicurazione Sanitaria
        connect(detailBtnS, SIGNAL(clicked()), this, SLOT(openDetailsS()));
        //connect per eliminare la selezione tabCasa
        connect(deleteBtnC, SIGNAL(clicked()), this, SLOT(deleteObjC()));
        //connect per eliminare la selezione tabRCauto
        connect(deleteBtnR, SIGNAL(clicked()), this, SLOT(deleteObjR()));
        //connect per eliminare la selezione tabSanitaria
        connect(deleteBtnS, SIGNAL(clicked()), this, SLOT(deleteObjS()));
        //connect per la ricerca
        connect(ricerca, SIGNAL(returnPressed()), this, SLOT(search()));

}

MainWindow::~MainWindow(){
    if(hLayout->parent() == 0){
        delete detailBtnC;
        delete detailBtnR;
        delete detailBtnS;
        delete deleteBtnC;
        delete deleteBtnR;
        delete deleteBtnS;
        delete hLayout;
    }
}

//azioni del menu
void MainWindow::createAct(){
    addCasaAct = new QAction("Casa", this);
    connect(addCasaAct, SIGNAL(triggered()), this, SLOT(insCasa()));

    addRCAct = new QAction("RCAuto", this);
    connect(addRCAct, SIGNAL(triggered()), this, SLOT(insRCAuto()));

    addSanAct = new QAction("Sanitaria", this);
    connect(addSanAct, SIGNAL(triggered()), this, SLOT(insSanit()));
}

//per creare il menu
void MainWindow::createMenu(){
    editMenu = menuBar()->addMenu(tr("&Modifica"));
    addRMenu = editMenu->addMenu(tr("&Aggiungi riga"));
    addRMenu->addAction(addCasaAct);
    addRMenu->addAction(addRCAct);
    addRMenu->addAction(addSanAct);
}

void MainWindow::insCasa(){
    tabModelC->insertCasa();
    if(selectionModelR->currentIndex().isValid() || selectionModelS->currentIndex().isValid()){
        selectionModelR->clearSelection();
        selectionModelS->clearSelection();
    }
    tabCasa->selectRow(0);
}

void MainWindow::insRCAuto(){
    tabModelR->insertRCAuto();
    if(selectionModelC->currentIndex().isValid() || selectionModelS->currentIndex().isValid()){
        selectionModelC->clearSelection();
        selectionModelS->clearSelection();
    }
    tabRCAuto->selectRow(0);
}

void MainWindow::insSanit(){
    tabModelS->insertSanit();
    if(selectionModelR->currentIndex().isValid() || selectionModelC->currentIndex().isValid()){
        selectionModelR->clearSelection();
        selectionModelC->clearSelection();
    }
    tabSanit->selectRow(0);
}

void MainWindow::viewBtnsC(){
    if(selectionModelR->currentIndex().isValid() || selectionModelS->currentIndex().isValid()){
        selectionModelR->clearSelection();
        selectionModelS->clearSelection();
    }

    if(selectionModelC->hasSelection()){
        QModelIndexList indxListC = selectionModelC->selectedRows();

        if(indxListC.size() == 1){
            if(hLayout->parent() == 0)
                vLayout->addLayout(hLayout);
            detailBtnC->setVisible(true);
            detailBtnR->setVisible(false);
            detailBtnS->setVisible(false);
            deleteBtnC->setVisible(true);
            deleteBtnR->setVisible(false);
            deleteBtnS->setVisible(false);
        }
        if(indxListC.size() > 1){
            detailBtnC->setVisible(false);
            detailBtnR->setVisible(false);
            detailBtnS->setVisible(false);
            deleteBtnC->setVisible(true);
            deleteBtnR->setVisible(false);
            deleteBtnS->setVisible(false);
        }
    }
    else{
        vLayout->removeItem(hLayout);
        detailBtnC->setVisible(false);
        detailBtnR->setVisible(false);
        detailBtnS->setVisible(false);
        deleteBtnC->setVisible(false);
        deleteBtnR->setVisible(false);
        deleteBtnS->setVisible(false);
        hLayout->setParent(0);
    }
}

void MainWindow::viewBtnsR(){
    if(selectionModelC->currentIndex().isValid() || selectionModelS->currentIndex().isValid()){
        selectionModelC->clearSelection();
        selectionModelS->clearSelection();
    }

    if(selectionModelR->hasSelection()){
        QModelIndexList indxListR = selectionModelR->selectedRows();

        if(indxListR.size() == 1){
            if(hLayout->parent() == 0)
                vLayout->addLayout(hLayout);
            detailBtnR->setVisible(true);
            detailBtnC->setVisible(false);
            detailBtnS->setVisible(false);
            deleteBtnC->setVisible(false);
            deleteBtnR->setVisible(true);
            deleteBtnS->setVisible(false);
        }
        if(indxListR.size() > 1){
            detailBtnR->setVisible(false);
            detailBtnC->setVisible(false);
            detailBtnS->setVisible(false);
            deleteBtnC->setVisible(false);
            deleteBtnR->setVisible(true);
            deleteBtnS->setVisible(false);
        }
    }
    else{
        vLayout->removeItem(hLayout);
        detailBtnR->setVisible(false);
        detailBtnC->setVisible(false);
        detailBtnS->setVisible(false);
        deleteBtnC->setVisible(false);
        deleteBtnR->setVisible(false);
        deleteBtnS->setVisible(false);
        hLayout->setParent(0);
    }
}

void MainWindow::viewBtnsS(){
    if(selectionModelC->currentIndex().isValid() || selectionModelR->currentIndex().isValid()){
        selectionModelC->clearSelection();
        selectionModelR->clearSelection();
    }

    if(selectionModelS->hasSelection()){
        QModelIndexList indxListS = selectionModelS->selectedRows();

        if(indxListS.size() == 1){
            if(hLayout->parent() == 0)
                vLayout->addLayout(hLayout);
            detailBtnS->setVisible(true);
            detailBtnC->setVisible(false);
            detailBtnR->setVisible(false);
            deleteBtnC->setVisible(false);
            deleteBtnR->setVisible(false);
            deleteBtnS->setVisible(true);
        }
        if(indxListS.size() > 1){
            detailBtnS->setVisible(false);
            detailBtnC->setVisible(false);
            detailBtnR->setVisible(false);
            deleteBtnC->setVisible(false);
            deleteBtnR->setVisible(false);
            deleteBtnS->setVisible(true);
        }
    }
    else{
        vLayout->removeItem(hLayout);
        detailBtnS->setVisible(false);
        detailBtnC->setVisible(false);
        detailBtnR->setVisible(false);
        deleteBtnC->setVisible(false);
        deleteBtnR->setVisible(false);
        deleteBtnS->setVisible(false);
        hLayout->setParent(0);
    }
}

void MainWindow::openDetailsC(){
    /*prendo l'indice dal modello di selezione di tabCasa, lo converto nell'indice dello SmartP
    all'interno del contenitore, prendo i valori dall'elemento della tabCasa selezionato
    e creo la dialog con i vari dati*/
    QModelIndex index = selectionModelC->currentIndex();
    int row;
    row = StaticCont::indexC(index.row());

    SmartP& ass = StaticCont::get_Ass(row);

    QString Nome;
    QDate DataStipula;

    //CASA
    int AnnoCostru;
    int AnnoRistru;
    double Spese;
    bool Furto;
    bool Incendio;
    bool Calamita;
    QString Provi;

    QModelIndex nomIndex = tabModelC->index(index.row(), 0, QModelIndex());
    QVariant varNom = tabModelC->data(nomIndex, Qt::DisplayRole);
    Nome = varNom.toString();

    QModelIndex dstIndex = tabModelC->index(index.row(), 1, QModelIndex());
    QVariant varDst = tabModelC->data(dstIndex, Qt::DisplayRole);
    DataStipula = QDate::fromString(varDst.toString(), "dd/MM/yyyy");

    Casa* c = dynamic_cast<Casa*>(&(*ass));


    DetailsDialog dialog("Casa", this);

    dialog.NomeEdit->setText(Nome);
    dialog.DataStCal->setDate(DataStipula);

    AnnoCostru= c->getAnnoCostr();
    dialog.AnnoCostrSpin->setMinimum(AnnoCostru);

    AnnoRistru= c->getAnnoRist();
    dialog.AnnoRistSpin->setMinimum(AnnoRistru);

    Spese= c->getSpese();
    dialog.SpeseSpin->setMinimum(Spese);

    Provi= c->getProv();
    int indPr= dialog.Prov->findText(Provi);
    dialog.Prov->setCurrentIndex(indPr);

    Furto= c->getFurto();
    dialog.CheckFurto->setChecked(c->getFurto());

    Incendio= c->getIncendio();
    dialog.CheckInce->setChecked(c->getIncendio());

    Calamita= c->getCalam();
    dialog.CheckCalam->setChecked(c->getCalam());
    //se è stato cambiato qualcosa
    if(dialog.exec()){
        if(dialog.NomeEdit->text() != Nome){
            if(dialog.NomeEdit->text().isEmpty())
                ass->setNome("NoNameC");
            else
                ass->setNome(dialog.NomeEdit->text());
        }
        if(dialog.DataStCal->date() != DataStipula){
            if(dialog.DataStCal->date().isNull())
                ass->setDataSt(QDate(1970, 1, 1));
            else{
                ass->setDataSt(dialog.DataStCal->date());
                QDate dataScM= QDate(dialog.DataStCal->date().year()+1, dialog.DataStCal->date().month(), dialog.DataStCal->date().day());
                ass->setDataSc(dataScM);
            }
        }
        if(dialog.AnnoCostrSpin->value() != AnnoCostru){
            c->setAnnoCost(dialog.AnnoCostrSpin->value());
        }
        if(dialog.AnnoRistSpin->value() != AnnoRistru){
            c->setAnnoRist(dialog.AnnoRistSpin->value());
        }
        if(dialog.SpeseSpin->value() != Spese){
            c->setSpese(dialog.SpeseSpin->value());
        }
        if(dialog.Prov->currentIndex() != indPr){
            c->setProv(dialog.Prov->currentText());
        }
        if(dialog.CheckFurto->isChecked() != Furto){
            c->setFurto(dialog.CheckFurto->isChecked());
        }
        if(dialog.CheckInce->isChecked() != Incendio){
            c->setIncendio(dialog.CheckInce->isChecked());
        }
        if(dialog.CheckCalam->isChecked() != Calamita){
            c->setCalam(dialog.CheckCalam->isChecked());
        }
    }

    QModelIndex ind1 = tabModelC->index(index.row(), 0, QModelIndex());
    QModelIndex ind2 = tabModelC->index(index.row(), 1, QModelIndex());
    tabModelC->updateView(ind1, ind2);
}

void MainWindow::openDetailsR(){
    /*prendo l'indice dal modello di selezione di tabRCAuto, lo converto nell'indice dello SmartP
    all'interno del contenitore, prendo i valori dall'elemento della tabRCAuto selezionato
    e creo la dialog con i vari dati*/
    QModelIndex index = selectionModelR->currentIndex();

    int row;
    row = StaticCont::indexR(index.row());

    SmartP& ass = StaticCont::get_Ass(row);

    QString Nome;
    QDate DataStipula;

    //RCAUTO
    int Cavalli;
    int EtaC;
    int Mass;
    int ClasseM;


    QModelIndex nomIndex = tabModelR->index(index.row(), 0, QModelIndex());
    QVariant varNom = tabModelR->data(nomIndex, Qt::DisplayRole);
    Nome = varNom.toString();

    QModelIndex dstIndex = tabModelR->index(index.row(), 1, QModelIndex());
    QVariant varDst = tabModelR->data(dstIndex, Qt::DisplayRole);
    DataStipula = QDate::fromString(varDst.toString(), "dd/MM/yyyy");

    RCAuto* r = dynamic_cast<RCAuto*>(&(*ass));

    DetailsDialog dialog("RCAuto", this);

    dialog.NomeEdit->setText(Nome);
    dialog.DataStCal->setDate(DataStipula);

    Mass= r->getMass();
    dialog.MassSpin->setValue(Mass);

    Cavalli= r->getCv();
    int indCv= dialog.CavFisc->findText(QString::number(Cavalli));
    dialog.CavFisc->setCurrentIndex(indCv);

    EtaC= r->getEtaC();
    int indEt= dialog.Eta->findText(QString::number(EtaC));
    if(EtaC == 18){
        indCv= dialog.CavFisc->findText(QString::number(11));
        dialog.CavFisc->setCurrentIndex(indCv);
        dialog.CavFisc->setDisabled(true);
    }
    dialog.Eta->setCurrentIndex(indEt);

    ClasseM= r->getClasse();
    int indCl= dialog.ClassMerito->findText(QString::number(ClasseM));
    dialog.ClassMerito->setCurrentIndex(indCl);

    //se è stato cambiato qualcosa
    if(dialog.exec()){
        if(dialog.NomeEdit->text() != Nome){
            if(dialog.NomeEdit->text().isEmpty())
                ass->setNome("NoNameR");
            else
                ass->setNome(dialog.NomeEdit->text());
        }
        if(dialog.DataStCal->date() != DataStipula){
            if(dialog.DataStCal->date().isNull())
                ass->setDataSt(QDate(1970, 1, 1));
            else{
                ass->setDataSt(dialog.DataStCal->date());
                QDate dataScM= QDate(dialog.DataStCal->date().year()+1, dialog.DataStCal->date().month(), dialog.DataStCal->date().day());
                ass->setDataSc(dataScM);
            }
        }

        if(dialog.MassSpin->value() != Mass){
            r->setMass(dialog.MassSpin->value());
        }
        if(dialog.Eta->currentIndex() != indEt){
            r->setEtaC(dialog.Eta->currentText().toInt());
        }
        if(dialog.CavFisc->currentIndex() != indCv){
            r->setCv(dialog.CavFisc->currentText().toInt());
        }
        if(dialog.ClassMerito->currentIndex() != indCl){
            r->setClasse(dialog.ClassMerito->currentText().toInt());
        }
    }

    QModelIndex ind1 = tabModelR->index(index.row(), 0, QModelIndex());
    QModelIndex ind2 = tabModelR->index(index.row(), 1, QModelIndex());
    tabModelR->updateView(ind1, ind2);
}

void MainWindow::openDetailsS(){
    /*prendo l'indice dal modello di selezione di tabSanit, lo converto nell'indice dello SmartP
    all'interno del contenitore, prendo i valori dall'elemento della tabSanit selezionato
    e creo la dialog con i vari dati*/
    QModelIndex index = selectionModelS->currentIndex();

    int row;
    row = StaticCont::indexS(index.row());

    SmartP& ass = StaticCont::get_Ass(row);

    QString Nome;
    QDate DataStipula;

    //SANITARIA
    int Mass;
    bool Indi;
    bool Amb;
    bool Dom;


    QModelIndex nomIndex = tabModelS->index(index.row(), 0, QModelIndex());
    QVariant varNom = tabModelS->data(nomIndex, Qt::DisplayRole);
    Nome = varNom.toString();

    QModelIndex dstIndex = tabModelS->index(index.row(), 1, QModelIndex());
    QVariant varDst = tabModelS->data(dstIndex, Qt::DisplayRole);
    DataStipula = QDate::fromString(varDst.toString(), "dd/MM/yyyy");


    Sanitaria* s = dynamic_cast<Sanitaria*>(&(*ass));

    DetailsDialog dialog("Sanitaria", this);


    dialog.NomeEdit->setText(Nome);
    dialog.DataStCal->setDate(DataStipula);

    Mass= s->getMass();
    dialog.MassSpin->setValue(Mass);

    Indi= s->getInd();
    if(Indi){
        dialog.RadioInd->setChecked(true);
        dialog.RadioNuc->setChecked(false);
    }
    else{
        dialog.RadioInd->setChecked(false);
        dialog.RadioNuc->setChecked(true);
    }
    Amb= s->getAmb();
    dialog.CheckAmb->setChecked(Amb);
    Dom= s->getDom();
    dialog.CheckDom->setChecked(Dom);
    //se è stato cambiato qualcosa
    if(dialog.exec()){
        if(dialog.NomeEdit->text() != Nome){
            if(dialog.NomeEdit->text().isEmpty())
                ass->setNome("NoNameS");
            else
                ass->setNome(dialog.NomeEdit->text());
        }
        if(dialog.DataStCal->date() != DataStipula){
            if(dialog.DataStCal->date().isNull())
                ass->setDataSt(QDate(1970, 1, 1));
            else{
                ass->setDataSt(dialog.DataStCal->date());
                QDate dataScM= QDate(dialog.DataStCal->date().year()+1, dialog.DataStCal->date().month(), dialog.DataStCal->date().day());
                ass->setDataSc(dataScM);
            }
        }
        if(dialog.MassSpin->value() != Mass){
            s->setMass(dialog.MassSpin->value());
        }
        if(dialog.RadioInd->isChecked() != Indi){
            s->setInd(dialog.RadioInd->isChecked());
            if(!dialog.RadioInd->isChecked()){
                dialog.RadioNuc->setChecked(true);
            }
        }
        if(dialog.CheckAmb->isChecked() != Amb){
            s->setAmb(dialog.CheckAmb->isChecked());
        }
        if(dialog.CheckDom->isChecked() != Dom){
            s->setDom(dialog.CheckDom->isChecked());
        }
    }

    QModelIndex ind1 = tabModelS->index(index.row(), 0, QModelIndex());
    QModelIndex ind2 = tabModelS->index(index.row(), 1, QModelIndex());
    tabModelS->updateView(ind1, ind2);
}

void MainWindow::deleteObjC(){
    QModelIndexList indxListC = selectionModelC->selectedRows();
    qSort(indxListC.begin(), indxListC.end());
    for(int i = indxListC.size()-1; i >= 0; --i){
        int row = indxListC[i].row();
        tabModelC->removeRows(row, 1, QModelIndex());
    }
    selectionModelC->clearSelection();
}

void MainWindow::deleteObjR(){
    QModelIndexList indxListR = selectionModelR->selectedRows();
    qSort(indxListR.begin(), indxListR.end());
    for(int i = indxListR.size()-1; i >= 0; --i){
        int row = indxListR[i].row();
        tabModelR->removeRows(row, 1, QModelIndex());
    }
    selectionModelR->clearSelection();
}

void MainWindow::deleteObjS(){
    QModelIndexList indxListS = selectionModelS->selectedRows();
    qSort(indxListS.begin(), indxListS.end());
    for(int i = indxListS.size()-1; i >= 0; --i){
        int row = indxListS[i].row();
        tabModelS->removeRows(row, 1, QModelIndex());
    }
    selectionModelS->clearSelection();
}

bool Compare(const SmartP& s1, const SmartP& s2) {
    return s1->getNome().toLower() == s2->getNome().toLower();
}

//slot per effettuare la ricerca, se non si trovano risultati viene visualizzato un messaggio di errore, altrimenti
//viene creata una nuova finestra con i risultati
void MainWindow::search(){
    selectionModelC->clearSelection();
    selectionModelR->clearSelection();
    selectionModelS->clearSelection();

    QString searchStr= ricerca->text();

    SmartP aux(new Casa);
    aux->setNome(searchStr);
    QList<int> indxList;
    indxList= StaticCont::getDb().findIndex(&Compare, StaticCont::getDb(), aux);

    if(indxList.isEmpty()){
        QMessageBox* notFoundMsg = new QMessageBox(this);
        notFoundMsg->open();
        notFoundMsg->setWindowTitle("ERRORE");
        notFoundMsg->setText("Assicurazione non trovata!");
    }
    else{
        SearchDialog provasearch(indxList, this);
        if(provasearch.exec()){
            QModelIndex indxRis= provasearch.selectionModelRis->currentIndex();
            SmartP& aux2= StaticCont::get_Ass(indxRis.row());
            int i= StaticCont::getRig(aux2);
            if(dynamic_cast<Casa*>(&(*aux2))){
                tabCasa->selectRow(StaticCont::getIndC(i, StaticCont::countC()));
            }
            else if(dynamic_cast<RCAuto*>(&(*aux2))){
                tabRCAuto->selectRow(StaticCont::getIndR(i, StaticCont::countR()));
            }
            else if(dynamic_cast<Sanitaria*>(&(*aux2))){
                tabSanit->selectRow(StaticCont::getIndS(i, StaticCont::countS()));
            }

        }
    }
    ricerca->clear();
}





















