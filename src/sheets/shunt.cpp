/**---------------------------------------------------------------------------
 *
 * @file    shunt.cpp
 * @brief   Calculate voltages on shunt resistor depending on current
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "shunt.hpp"
#include "ui_shunt.h"
#include <resistor.hpp>
#include <uri.hpp>


/*--- Implementation -------------------------------------------------------*/


CShunt::CShunt(CSettings &settings, QWidget *parent)
   :CCommon( settings, parent)
   , ui(new Ui::Shunt)
{
   ui->setupUi(this);

   m_settings.append( { { "shunt/r_shunt", ui->spinRShunt, EType::EDouble, 0.030 },
                        { "shunt/i_total", ui->spinITotal, EType::EDouble, 1.5 },
                        { "shunt/u_shunt", ui->spinU_Shunt, EType::EDouble, 24.0 },
                      } );
   
   connect( ui->spinRShunt, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   connect( ui->spinITotal, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   connect( ui->spinU_Total, SIGNAL( valueChanged(double) ), this, SLOT( slotTotalVoltageChanged(double) ) );
   connect( ui->spinU_Shunt, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged(double) ) );
   
   slotResistorChanged( 0.0 );
}

CShunt::~CShunt()
{
   delete ui;
}


void CShunt::updateAll()
{
   double U_Shunt = CURI( ui->spinU_Total->value(), ui->spinRShunt->value(),
                          ui->spinITotal->value()).calcVoltage();

   ui->spinU_Shunt->setValue( U_Shunt );
   ui->spinPTotal->setValue( ui->spinU_Total->value() * ui->spinITotal->value() );

   ui->spinU_Load->setValue( ui->spinU_Total->value() - U_Shunt);
   ui->spinPShunt->setValue( U_Shunt * ui->spinITotal->value() );
   ui->spinPLoad->setValue( ui->spinU_Load->value() * ui->spinITotal->value() );
}


void CShunt::slotResistorChanged(double)
{
   double U_Shunt = ui->spinRShunt->value() * ui->spinITotal->value();
   
   highlightCalculationSource( ECalculationSource::Resistor );
       
   ui->spinU_Shunt->setValue( U_Shunt );
   ui->spinPTotal->setValue( ui->spinU_Total->value() * ui->spinITotal->value() );

   updateAll();
}


void CShunt::slotTotalVoltageChanged(double)
{
   highlightCalculationSource( ECalculationSource::Voltage );
   
   ui->spinITotal->setValue(
       CURI( ui->spinU_Shunt->value(), ui->spinRShunt->value(), ui->spinITotal->value() ).calcCurrent()
       );

   updateAll();
}


void CShunt::highlightCalculationSource( ECalculationSource calcSource )
{
   ui->spinU_Load->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPTotal->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPShunt->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPLoad->setStyleSheet("color: rgb(0,0,128); ");
}


/*--- Fin ------------------------------------------------------------------*/
