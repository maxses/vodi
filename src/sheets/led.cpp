/**---------------------------------------------------------------------------
 *
 * @file    led.cpp
 * @brief   Calculate series resistor for LEDs
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "led.hpp"
#include "ui_led.h"
#include <resistor.hpp>
#include <QDebug>


/*--- Implementation -------------------------------------------------------*/


CLed::CLed(CSettings &settings, QWidget *parent)
   :CCommon( settings, parent )
   //m_settings(settings),
   ,ui(new Ui::Led)
{
   ui->setupUi(this);

   m_settings.append( { { "led/u1", ui->spinU1, EType::EDouble, 3.0 },
                        { "led/led_v", ui->spinULed, EType::EDouble, 2.0 },
                        { "led/led_i", ui->spinILed, EType::EDouble, 0.02 },
                      } );
   
   
   ui->labelILed->setUpdatesEnabled(true);
   ui->labelR1Match->setUpdatesEnabled(true);
   
   connect( &m_settings, SIGNAL( signalSettingsChanged() ), this, SLOT( slotSettingsChanged() ) );
   connect( ui->spinU1, SIGNAL( valueChanged(double) ), this, SLOT( slotU1Changed(double) ) );
   connect( ui->spinULed, SIGNAL( valueChanged(double) ), this, SLOT( slotU1Changed(double) ) );
   connect( ui->spinILed, SIGNAL( valueChanged(double) ), this, SLOT( slotU1Changed(double) ) );
   connect( ui->spinR1User, SIGNAL( valueChanged(double) ), this, SLOT( slotR1Changed(double) ) );
   
   slotU1Changed( ui->spinU1->value() );
}

CLed::~CLed()
{
   delete ui;
}


void CLed::slotU1Changed(double)
{
   // Rvor = ( V - Vf ) / If
   double r_led = ( ui->spinU1->value() - ui->spinULed->value() )
                  / ui->spinILed->value();
   
   qDebug() << "U1:" << ui->spinU1->value();
   qDebug() << "U_LED:" << ui->spinULed->value();
   qDebug() << "I_LED:" << ui->spinILed->value();
   qDebug() << "R_LED:" << r_led;
   
   #if 0
   QFont font;
   font.setBold(true);
   ui->labelILed->setFont(font);
   ui->labelILed->repaint();
   font.setBold(false);
   ui->labelR1User->setFont(font);
   ui->labelR1User->repaint();
   #endif
   highlightCalculationSource( ECalculationSource::I_LED );
   
   const QList<CResistor> &listAll = getSeries();
   ui->spinR1->setValue( r_led );
   ui->spinR1Match->setValue( CResistor( r_led ).bestMatch( listAll ).value() );
   updateILedReal();
   updateP();
}


void CLed::slotSettingsChanged()
{
   if( m_calculationSource == ECalculationSource::I_LED )
   {
      slotU1Changed( ui->spinU1->value() );
   }
   else
   {
      slotR1Changed( ui->spinR1User->value() );
   }
}


void CLed::updateP()
{
   double r1=ui->spinR1Match->value( );
   double rlED=ui->spinRLed->value( );
   double iTotal=ui->spinU1->value( ) / ( r1 + rlED );
   double uR1=r1*iTotal;
   double uLed=rlED*iTotal;
   
   double power_r1=uR1*iTotal;
   double power_led=uLed*iTotal;
   
   ui->spinPLed->setValue( power_led );
   ui->spinPR1->setValue( power_r1 );
   
   // LED; 20mA@2V == 40mW 
   if( power_led > 0.040 )
   {
      ui->spinPLed->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerLed->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerLed->setText("Power seems to be too high for simple indicator LED.\n"
                                "Ignore message if its a high power LED." );
      ui->labelPowerLed->setFrameStyle( QFrame::Box );
   }
   else
   {
      //ui->spinPLed->setStyleSheet("");
      ui->labelPowerLed->setText("");
      ui->labelPowerLed->setFrameStyle( QFrame::NoFrame );
   }
   
   // Resistor
   if( power_r1 > 0.100 )
   {
      ui->spinPR1->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerR1->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerR1->setText("Power seems to be too high for usual footprint 0603.\n"
                                "Use bigger footprint or put multiple resistors in series.\n"
                                "Divide resistors values accordingly." );
      ui->labelPowerR1->setFrameStyle( QFrame::Box );
   }
   else
   {
      //ui->spinPR1->setStyleSheet("");
      ui->labelPowerR1->setText("");
      ui->labelPowerR1->setFrameStyle( QFrame::NoFrame );
   }
}


void CLed::slotR1Changed(double)
{
   #if 0
   QFont font;
   font.setBold(true);
   ui->labelR1User->setFont(font);
   ui->labelR1User->repaint();
   font.setBold(false);
   ui->labelILed->setFont(font);
   ui->labelILed->repaint();
   #endif
   
   highlightCalculationSource( ECalculationSource::R1_USER );
       
   ui->spinR1Match->setValue( ui->spinR1User->value() );
   updateILedReal();
   updateP();
}


void CLed::updateILedReal()
{
   double r_led=ui->spinULed->value() / ui->spinILed->value();
   ui->spinRLed->setValue( r_led );
   
   ui->spinILedReal->setValue( ui->spinU1->value() / ( r_led + ui->spinR1Match->value() ) );
}


void CLed::highlightCalculationSource( ECalculationSource calcSource )
{
    // base=true: calculate by I_LED
    // base=false: calculate by R1_User
   QFont font;

   m_calculationSource = calcSource;

   font.setBold( calcSource == ECalculationSource::I_LED );
   ui->labelILed->setFont(font);
   
   font.setBold( calcSource == ECalculationSource::R1_USER );
   ui->labelR1User->setFont(font);
   
   font=QFont();
   font.setStrikeOut( calcSource == ECalculationSource::I_LED );
   ui->spinR1User->setFont(font);
   
   font.setStrikeOut( calcSource == ECalculationSource::R1_USER );
   ui->spinR1->setFont(font);
   
   ui->spinR1->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinR1Match->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinRLed->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinILedReal->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPLed->setStyleSheet("color: rgb(0,0,128); ");
   ui->spinPR1->setStyleSheet("color: rgb(0,0,128); ");
}


/*--- Fin ------------------------------------------------------------------*/
