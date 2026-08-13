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
   :CCommon( settings, parent )
   , ui(new Ui::E12)
{
   ui->setupUi(this);

   connect( &m_settings, SIGNAL( signalSettingsChanged() ), this, SLOT( updateFields() ) );

   updateFields();
}


CE12::~CE12()
{
   delete ui;
}


void CE12::updateFields()
{
   clearFields();

   const QList<CResistor>& series=getSeries();

   QLabel *label;

   if( getSeriesCount() >= 48 )
   {
       label = new QLabel( this );
       label->setObjectName("label");
       //label->setFrameShape( QFrame::Shape::Box );
       label->setAlignment( Qt::AlignmentFlag::AlignCenter );
       label->setText( QString("Will only show series up to E24") );
       ui->gridLayout->addWidget(label, 0, 0, 1, 1);
   }
   else
   {
       for( int y=0; y < series.count() / getSeriesCount(); y++ )
       {
          for( int x=0; x < getSeriesCount(); x++ )
          {
             label = new QLabel( this );
             label->setObjectName("label");
             label->setFrameShape( QFrame::Shape::Box );
             label->setAlignment( Qt::AlignmentFlag::AlignCenter );
             QFont font = label->font();
             font.setPointSize(5);
             label->setFont(font);
             double value=series[ ( y* getSeriesCount() ) + x ].value();
             if( value < 1000 )
             {
                label->setText( QString("%1").arg( value ) );
             }
             else
             {
                label->setText( QString("%1K").arg( value / 1000.0 ) );
             }
             ui->gridLayout->addWidget(label, y, x, 1, 1);
          }
       }
   }
}


void CE12::clearFields()
{
   while (QLayoutItem *item = ui->gridLayout->takeAt(0))
   {
      if (QWidget *widget = item->widget())
      {
         delete widget;
      }

      if (QLayout *layout = item->layout())
      {
         delete layout;  // falls verschachtelte Layouts vorkommen
      }

      delete item;
   }
}


/*--- Fin ------------------------------------------------------------------*/
