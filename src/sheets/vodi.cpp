/**---------------------------------------------------------------------------
 *
 * @file    vodi.cpp
 * @brief   Calculate voltages divider resistors
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "vodi.hpp"
#include "ui_vodi.h"
#include <resistor.hpp>
#include <uri.hpp>


/*--- Implementation -------------------------------------------------------*/


CVodi::CVodi(CSettings &settings, QWidget *parent)
   :CCommon( settings, parent)
   ,ui(new Ui::Vodi)
{
   ui->setupUi(this);

   m_settings.append( { { "vodi/u1", ui->spinU1, EType::EDouble, 3.3 },
                        { "vodi/u2_target", ui->spinU2Target, EType::EDouble, 1.5 },
                        { "vodi/r1", ui->spinR1, EType::EDouble, 120.0 },
                        { "vodi/r2", ui->spinR2, EType::EDouble, 120.0 },
                        { "vodi/r1_2", ui->spinR1_2, EType::EDouble, 120.0 },
                        { "vodi/r2_2", ui->spinR2_2, EType::EDouble, 120.0 },
                        { "vodi/r1_2_e", ui->checkR1_2, EType::EBoolean, false },
                        { "vodi/r2_2_e", ui->checkR2_2, EType::EBoolean, true },
                        { "vodi/pmax", ui->spinPMax, EType::EDouble, 0.1 },
                      } );

   connect( &m_settings, SIGNAL( signalSettingsChanged() ), this, SLOT( slotVoltageChanged() ) );
   connect( ui->spinU1, SIGNAL( valueChanged(double) ), this, SLOT( slotVoltageChanged() ) );
   connect( ui->spinU2Target, SIGNAL( valueChanged(double) ), this, SLOT( slotVoltageChanged() ) );
   connect( ui->spinPMax, SIGNAL( valueChanged(double) ), this, SLOT( slotVoltageChanged() ) );
   connect( ui->spinR1, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged() ) );
   connect( ui->spinR2, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged() ) );
   connect( ui->spinR1_2, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged() ) );
   connect( ui->spinR2_2, SIGNAL( valueChanged(double) ), this, SLOT( slotResistorChanged() ) );
   // The signal "checkStateChanged(Qt::CheckState)" was introduced in Qt 6.7
   //connect( ui->checkR1_2, SIGNAL( checkStateChanged(Qt::CheckState) ), this, SLOT( slotConfigChanged() ) );
   //connect( ui->checkR2_2, SIGNAL( checkStateChanged(Qt::CheckState) ), this, SLOT( slotConfigChanged() ) );
   connect( ui->checkR1_2, SIGNAL( stateChanged( int )), this, SLOT( slotConfigChanged() ) );
   connect( ui->checkR2_2, SIGNAL( stateChanged( int )), this, SLOT( slotConfigChanged() ) );

   slotConfigChanged( );
   slotVoltageChanged( );
}

CVodi::~CVodi()
{
   delete ui;
}


void CVodi::slotResistorChanged()
{
   highlightCalculationSource( false );
   updateReadonly();
}


void CVodi::slotVoltageChanged()
{
   double totalVoltage=ui->spinU1->value();
   double target=ui->spinU2Target->value();
   CResistor bestR1(-1);
   CResistor bestR1_2(-1);
   CResistor bestR2(-1);
   CResistor bestR2_2(-1);
   double bestVoltage=1000000;
   const QList<CResistor> &listR1_2 = ui->checkR1_2->isChecked() ? E12Limited : EOpen;
   const QList<CResistor> &listR2_2 = ui->checkR2_2->isChecked() ? E12Limited : EOpen;
   const QList<CResistor> &listAll = getSeries();

   for(auto& r1:listAll)
   {
      for(auto& r1_2:listR1_2)
      {
         #if(1)
         if( ( r1_2 > 0 ) && ( r1_2 < r1 ) )
         {
            continue;
         }
         #endif
         for(auto& r2:listAll)
         {
            for( auto& r2_2:listR2_2 )
            {
               #if(1)
               if( ( r2_2 > 0 ) && ( r2_2 < r2) )
               {
                  continue;
               }
               #endif
               double volt;
               volt=( r1 || r1_2 ).voltageDivider( totalVoltage, r2 || r2_2 );
               if( qAbs( target - volt ) < qAbs( target - bestVoltage ) )
               {
                  double i=CURI( ui->spinU1->value(), ( (r1 || r1_2) | (r2 || r2_2) ).value(), 0).calcCurrent();
                  double p=ui->spinU1->value() * i;
                  if( p <= ui->spinPMax->value() )
                  {
                     bestR1=r1;
                     bestR2=r2;
                     bestR2_2=r2_2;
                     bestR1_2=r1_2;
                     bestVoltage=volt;
                  }
               }
            }
         }
      }
   }
   
   ui->spinR1->setValue( bestR1.value() );
   ui->spinR2->setValue( bestR2.value() );
   ui->spinR1_2->setValue( bestR1_2.value() );
   ui->spinR2_2->setValue( bestR2_2.value() );
   ui->spinU2Real->setValue( bestVoltage );
   
   highlightCalculationSource( true );
   updateReadonly();
}


void CVodi::updateReadonly()
{
   CResistor r1(ui->spinR1->value());
   CResistor r1_2(ui->spinR1_2->value());
   CResistor r2(ui->spinR2->value());
   CResistor r2_2(ui->spinR2_2->value());
   if(!ui->checkR1_2->isChecked())
   {
      r1_2=-1;
   }
   if(!ui->checkR2_2->isChecked())
   {
      r2_2=-1;
   }
   double volt;
   double totalVoltage=ui->spinU1->value();
   volt=( r1 || r1_2 ).voltageDivider( totalVoltage, r2 || r2_2 );
   ui->spinU2Real->setValue(volt);
   ui->spinU3->setValue( ui->spinU1->value() - volt );
   
   double r_total= ( ( r1 || r1_2 ) | ( r2 || r2_2 ) ).value();
   double i_total=ui->spinU1->value() / r_total;
   
   ui->spinRTotal->setValue( r_total );
   ui->spinI_Total->setValue( i_total );
   ui->spinP->setValue( ui->spinU1->value() * i_total );
}

void CVodi::slotConfigChanged()
{
   if( ui->checkR1_2->isChecked() && ui->checkR2_2->isChecked() )
   {
      ui->label->setPixmap(QPixmap(QString::fromUtf8(":/pic/pic/vodi_r1_2_r2_2.png")));
      ui->spinR1_2->setEnabled(true);
      ui->spinR2_2->setEnabled(true);
   }
   else if( ui->checkR1_2->isChecked() )
   {
      ui->label->setPixmap(QPixmap(QString::fromUtf8(":/pic/pic/vodi_r1_2.png")));
      ui->spinR1_2->setEnabled(true);
      ui->spinR2_2->setEnabled(false);
   }
   else if( ui->checkR2_2->isChecked() )
   {
      ui->label->setPixmap(QPixmap(QString::fromUtf8(":/pic/pic/vodi_r2_2.png")));
      ui->spinR1_2->setEnabled(false);
      ui->spinR2_2->setEnabled(true);
   }
   else
   {
      ui->label->setPixmap(QPixmap(QString::fromUtf8(":/pic/pic/vodi.png")));
      ui->spinR1_2->setEnabled(false);
      ui->spinR2_2->setEnabled(false);
   }
   
   slotVoltageChanged();
}


void CVodi::highlightCalculationSource( bool base )
{
   QFont font;
   
   font.setBold( true );
   ui->labelU1->setFont(font);
   ui->labelPMax->setFont(font);
   
   font.setBold( base );
   ui->labelU2Target->setFont(font);
   
   font.setBold( ! base );
   ui->labelR1->setFont(font);
   ui->labelR1_2->setFont(font);
   ui->labelR2->setFont(font);
   ui->labelR2_2->setFont(font);
   
   font=QFont();
   font.setStrikeOut(!base);
   ui->spinU2Target->setFont(font);
   
   QString style=base ? "color: rgb(0,0,128); " : "";
   ui->spinR1->setStyleSheet( style );
   ui->spinR1_2->setStyleSheet( style );
   ui->spinR2->setStyleSheet( style );
   ui->spinR2_2->setStyleSheet( style );
   
   ui->spinP->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinU3->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinRTotal->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinU2Real->setStyleSheet("color: rgb(0,0,128); ");
}


/*--- Fin ------------------------------------------------------------------*/
