#include "led.hpp"
#include "ui_led.h"
#include <resistor.hpp>

CLed::CLed(CSettings &settings, QWidget *parent) :
   QWidget(parent),
   m_settings(settings),
   ui(new Ui::Led)
{
   ui->setupUi(this);

   m_settings.append( { { "led/u1", ui->spinU1, EType::EDouble, 3.0 },
                        { "led/led_v", ui->spinULed, EType::EDouble, 2.0 },
                        { "led/led_i", ui->spinILed, EType::EDouble, 0.02 },
                      } );
   
   
   ui->labelILed->setUpdatesEnabled(true);
   ui->labelR1Match->setUpdatesEnabled(true);
   
   
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
   
   #if 1
   QFont font;
   font.setBold(true);
   ui->labelILed->setFont(font);
   ui->labelILed->repaint();
   font.setBold(false);
   ui->labelR1User->setFont(font);
   ui->labelR1User->repaint();
   #endif
   
   ui->spinR1->setValue( r_led );
   ui->spinR1Match->setValue( CResistor( r_led ).bestMatch().value() );
   updateILedReal();
   
   double power_r1=( ui->spinU1->value( ) - ui->spinULed->value( ) )
                     * ui->spinILed->value();
   double power_led=ui->spinULed->value( ) * ui->spinILed->value();
   
   ui->spinPowerLed->setValue( power_led );
   ui->spinPowerR1->setValue( power_r1 );
   
   // LED; 20mA@2V == 40mW 
   if( power_led > 0.040 )
   {
      ui->spinPowerLed->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerLed->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerLed->setText("Power seems to be too high for simple indicator LED.\n"
                                "Ignore message if its a high power LED." );
      ui->labelPowerLed->setFrameStyle( QFrame::Box );
   }
   else
   {
      ui->spinPowerLed->setStyleSheet("");
      ui->labelPowerLed->setText("");
      ui->labelPowerLed->setFrameStyle( QFrame::NoFrame );
   }
   
   // Resistor
   if( power_r1 > 0.100 )
   {
      ui->spinPowerR1->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerR1->setStyleSheet("color: rgb(161,0,0); ");
      ui->labelPowerR1->setText("Power seems to be too high for usual footprint 0603.\n"
                                "Use bigger footprint or put multiple resistors in series.\n"
                                "Divide resistors values accordingly." );
      ui->labelPowerR1->setFrameStyle( QFrame::Box );
   }
   else
   {
      ui->spinPowerR1->setStyleSheet("");
      ui->labelPowerR1->setText("");
      ui->labelPowerR1->setFrameStyle( QFrame::NoFrame );
   }
}


void CLed::slotR1Changed(double)
{
   #if 1
   QFont font;
   font.setBold(true);
   ui->labelR1User->setFont(font);
   ui->labelR1User->repaint();
   font.setBold(false);
   ui->labelILed->setFont(font);
   ui->labelILed->repaint();
   #endif
   
   ui->spinR1Match->setValue( ui->spinR1User->value() );
   updateILedReal();
}


void CLed::updateILedReal()
{
   double r_led=ui->spinULed->value() / ui->spinILed->value();
   ui->spinRLed->setValue( r_led );
   
   ui->spinILedReal->setValue( ui->spinU1->value() / ( r_led + ui->spinR1Match->value() ) );
}

