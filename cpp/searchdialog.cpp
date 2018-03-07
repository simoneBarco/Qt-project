#include "searchdialog.h"
#include <QHeaderView>
#include <QDebug>

SearchDialog::SearchDialog(QList<int>& indxList, QWidget* parent):
    QDialog(parent){

            //viene creata una nuova tabella con objectName=tabModelRis e il model che dovrà gestirla e vengono nascoste
            //le righe che non soddisfano i requisiti della ricerca
            risLbl= new QLabel("Risultati");

            tabRis= new QTableView;

            tabModelRis= new ContainerTableModel(this);
            tabModelRis->setObjectName("tabModelRis");

            selectBtn= new QPushButton("Seleziona");

            tabRis->setModel(tabModelRis);

            tabRis->setSelectionBehavior(QAbstractItemView::SelectRows);
            tabRis->setSelectionMode(QAbstractItemView::SingleSelection);
            tabRis->verticalHeader()->setVisible(false);
            tabRis->setAlternatingRowColors(true);
            tabRis->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            tabRis->setMinimumSize(700,100);

            QGridLayout* gLay= new QGridLayout;

            gLay->addWidget(risLbl,0,0);
            gLay->addWidget(tabRis,1,0);


            gLay->addWidget(selectBtn,2,0);

            selectionModelRis = tabRis->selectionModel();

            setLayout(gLay);

            int k=0;
            for(int i=0; i<StaticCont::getDb().size(); i++){
                if(i != indxList.at(k)){
                        tabRis->setRowHidden(i, true);
                }
                else if(k<indxList.size()-1)
                    ++k;

            }
            connect(selectBtn, SIGNAL(clicked()), this, SLOT(accept()));
    }







