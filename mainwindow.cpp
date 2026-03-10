#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   
   connect( ui->spinLsrU1, SIGNAL( valueChanged(double) ), this, SLOT( slotLsrU1Changed(double) ) );
   connect( ui->spinLsrULed, SIGNAL( valueChanged(double) ), this, SLOT( slotLsrU1Changed(double) ) );
   connect( ui->spinLsrILed, SIGNAL( valueChanged(double) ), this, SLOT( slotLsrU1Changed(double) ) );
   
   slotLsrU1Changed( ui->spinLsrU1->value() );
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::slotLsrU1Changed(double)
{
   // Rvor = ( V - Vf ) / If
   double r_led = ( ui->spinLsrU1->value() - ui->spinLsrULed->value() )
                     / ( ui->spinLsrILed->value() / 1000.0 );
   
   qDebug() << "U1:" << ui->spinLsrU1->value();
   qDebug() << "U_LED:" << ui->spinLsrULed->value();
   qDebug() << "I_LED:" << ui->spinLsrILed->value();
   qDebug() << "R_LED:" << r_led;
   
   ui->spinLsrRLed->setValue( r_led );
   ui->spinPower->setValue( ui->spinLsrU1->value( ) * ui->spinLsrILed->value() );
}
