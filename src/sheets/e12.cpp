/**---------------------------------------------------------------------------
 *
 * @file    e12.cpp
 * @brief   Draw a table of the resistor E12 series
 *
 * Not super usefull.
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "e12.hpp"
#include "ui_e12.h"
#include <QLabel>
#include <resistor.hpp>


/*--- Implementation -------------------------------------------------------*/


CE12::CE12(CSettings &settings, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::E12)
    , m_settings( settings )
{
   ui->setupUi(this);
   QLabel *label;
   
   for( int y=0; y<E12.count()/12; y++ )
   {
      for( int x=0; x<12; x++ )
      {
         label = new QLabel( this );
         label->setObjectName("label");
         label->setFrameShape( QFrame::Shape::Box );
         label->setAlignment( Qt::AlignmentFlag::AlignCenter );
         label->setText( QString("%1").arg(E12[ ( y* 12 ) + x ].value() ) );
         ui->gridLayout->addWidget(label, y, x, 1, 1);
      }
   }
}


CE12::~CE12()
{
   delete ui;
}


/*--- Fin ------------------------------------------------------------------*/
