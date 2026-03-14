#include "e12.hpp"
#include "ui_e12.h"
#include <QLabel>
#include <resistor.hpp>

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
