#include "shunt.hpp"
#include "ui_shunt.h"
#include <resistor.hpp>
#include <uri.hpp>


CShunt::CShunt(CSettings &settings, QWidget *parent) :
   QWidget(parent),
   m_settings(settings),
   ui(new Ui::Shunt)
{
   ui->setupUi(this);

   m_settings.append( { { "shunt/r_shunt", ui->spinRShunt, EType::EDouble, 0.030 },
                        { "shunt/i_total", ui->spinITotal, EType::EDouble, 1.5 },
                        { "shunt/u1", ui->spinU1, EType::EDouble, 24.0 },
                      } );
   
   connect( ui->spinRShunt, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   connect( ui->spinITotal, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   connect( ui->spinU2, SIGNAL( valueChanged(double) ), this, SLOT( slotVoltageChanged(double) ) );
   connect( ui->spinU1, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   
   slotResistorChanged( 0.0 );
}

CShunt::~CShunt()
{
   delete ui;
}


void CShunt::slotResistorChanged(double)
{
   double U = ui->spinRShunt->value() * ui->spinITotal->value();
   ui->spinU2->setValue( U );
   ui->spinPTotal->setValue( ui->spinU1->value() * ui->spinITotal->value() );
}


void CShunt::slotVoltageChanged(double)
{
   ui->spinITotal->setValue(
       CURI( ui->spinU2->value(), ui->spinRShunt->value(), ui->spinITotal->value() ).calcCurrent()
       );
}

