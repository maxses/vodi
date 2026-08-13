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
   
   highlightCalculationSource( true );
       
   ui->spinU2->setValue( U );
   ui->spinPTotal->setValue( ui->spinU1->value() * ui->spinITotal->value() );
}


void CShunt::slotVoltageChanged(double)
{
   highlightCalculationSource( false );
   
   ui->spinITotal->setValue(
       CURI( ui->spinU2->value(), ui->spinRShunt->value(), ui->spinITotal->value() ).calcCurrent()
       );
}


void CShunt::highlightCalculationSource( ECalculationSource calcSource )
{
   ui->spinU_Load->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPTotal->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPShunt->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPLoad->setStyleSheet("color: rgb(0,0,128); ");
}


/*--- Fin ------------------------------------------------------------------*/
