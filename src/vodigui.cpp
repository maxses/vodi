/**---------------------------------------------------------------------------
 *
 * @file    vodigui.cpp
 * @brief   Main Ui class for vodi
 *
 * Sheets can be inserted.
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "vodigui.hpp"
#include "./ui_vodigui.h"
#include "./ui_led.h"
#include <QShortcut>
#include <led.hpp>
#include <vodi.hpp>
#include <shunt.hpp>
#include <e12.hpp>


/*--- Implementation -------------------------------------------------------*/


CVodiGui::CVodiGui(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::VoDi)
{
   ui->setupUi(this);

   connect( qApp, SIGNAL( aboutToQuit() ), this, SLOT( slotQuit() ));

   m_settings.append( { { "notes", ui->textEdit, EType::EText, "Evaluation:\n" },
                      } );

   ui->pushBold->setMaximumWidth(24);
   ui->pushItalic->setMaximumWidth(24);
   ui->pushUnderline->setMaximumWidth(24);
   
   m_vodi = new CVodi( m_settings, parent);
   ui->tabWidget->addTab( m_vodi, QString("Voltage divider"));
   
   m_led = new CLed( m_settings, parent);
   ui->tabWidget->addTab( m_led, QString("LED"));
   
   m_shunt = new CShunt( m_settings, parent);
   ui->tabWidget->addTab( m_shunt, QString("Shunt"));
   
   m_e12 = new CE12( m_settings, parent);
   ui->tabWidget->addTab( m_e12, QString("E12"));
   
   m_settings.load();

   connect( ui->actionReset, SIGNAL( triggered() ), this, SLOT( slotReset( ) ) );

   //connect( ui->pushBold, SIGNAL( toggled( bool ) ), this, SLOT( slotBoldToggled( bool ) ));
   connect( ui->pushBold, SIGNAL( clicked( ) ), this, SLOT( slotBoldToggled( ) ));
   connect( ui->pushItalic, SIGNAL( clicked( ) ), this, SLOT( slotItalicToggled( ) ));
   connect( ui->pushUnderline, SIGNAL( clicked( ) ), this, SLOT( slotUnderlineToggled( ) ));
   connect( ui->pushSubscript, SIGNAL( clicked( ) ), this, SLOT( slotSubscriptToggled( ) ));
   connect( ui->textEdit, SIGNAL( cursorPositionChanged( ) ), this, SLOT( slotCursorMoved( ) ));

   QShortcut *shortcut;

   shortcut = new QShortcut(QKeySequence("Ctrl+B"), this);
      connect(shortcut, SIGNAL( activated( ) ), this, SLOT(slotBoldToggledShortCut( )));
   shortcut = new QShortcut(QKeySequence("Ctrl+I"), this);
      connect(shortcut, SIGNAL( activated( ) ), this, SLOT(slotItalicToggledShortCut( )));
   shortcut = new QShortcut(QKeySequence("Ctrl+U"), this);
      connect(shortcut, SIGNAL( activated( ) ), this, SLOT(slotUnderlineToggledShortCut( )));
}


CVodiGui::~CVodiGui()
{
   delete ui;
}


void CVodiGui::slotQuit()
{
   m_settings.save();
   // m_settings.setValue( "notes", ui->textEdit->toHtml() );
   // m_settings.setValue( "r1", ui->spinR1->value() );
}


void CVodiGui::setBold( bool bold )
{
   ui->textEdit->setFontWeight( bold ? QFont::Bold : QFont::Normal );
}


void CVodiGui::setItalic( bool italic )
{
   ui->textEdit->setFontItalic( italic );
}


void CVodiGui::setUnderline( bool underline )
{
   ui->textEdit->setFontUnderline( underline );
}


void CVodiGui::setSubscript( bool subscript )
{
   QTextCharFormat fmt=ui->textEdit->currentCharFormat();
   fmt.setVerticalAlignment(
       subscript ? QTextCharFormat::AlignSubScript : QTextCharFormat::AlignNormal );
   ui->textEdit->setCurrentCharFormat( fmt );
}


void CVodiGui::slotBoldToggled( /*bool checked*/ )
{
   setBold( /*checked*/ ui->pushBold->isChecked() );
   //ui->pushBold->previousInFocusChain()->setFocus();
   ui->textEdit->setFocus();

   return;
}


void CVodiGui::slotItalicToggled( /*bool checked*/ )
{
   setItalic( ui->pushItalic->isChecked() );
   //ui->pushBold->previousInFocusChain()->setFocus();
   ui->textEdit->setFocus();

   return;
}


void CVodiGui::slotUnderlineToggled( /*bool checked*/ )
{
   setUnderline( ui->pushUnderline->isChecked() );
   //ui->pushBold->previousInFocusChain()->setFocus();
   ui->textEdit->setFocus();

   return;
}


void CVodiGui::slotSubscriptToggled( /*bool checked*/ )
{
   setSubscript( ui->pushSubscript->isChecked() );
   ui->textEdit->setFocus();
   
   return;
}


void CVodiGui::slotBoldToggledShortCut( )
{
   QWidget* focus=qApp->focusWidget();

   ui->pushBold->setChecked( ! ui->pushBold->isChecked() );
   slotBoldToggled( );

   if(focus)
   {
      focus->setFocus();
   }
}


void CVodiGui::slotItalicToggledShortCut( )
{
   QWidget* focus=qApp->focusWidget();

   ui->pushItalic->setChecked( ! ui->pushItalic->isChecked() );
   slotItalicToggled( );

   if(focus)
   {
      focus->setFocus();
   }
}


void CVodiGui::slotUnderlineToggledShortCut( )
{
   QWidget* focus=qApp->focusWidget();

   ui->pushUnderline->setChecked( ! ui->pushUnderline->isChecked() );
   slotUnderlineToggled( );

   if(focus)
   {
      focus->setFocus();
   }
}


void CVodiGui::slotCursorMoved()
{
   QWidget* focus=qApp->focusWidget();

   ui->pushBold->setChecked( ui->textEdit->fontWeight() == QFont::Bold );
   ui->pushItalic->setChecked( ui->textEdit->fontItalic() );
   ui->pushUnderline->setChecked( ui->textEdit->fontUnderline() );
   ui->pushSubscript->setChecked( ui->textEdit->currentCharFormat().verticalAlignment() == QTextCharFormat::AlignSubScript );

   if(focus)
   {
      focus->setFocus();
   }
}


void CVodiGui::slotReset( )
{
   m_settings.reset();
}


/*--- Fin ------------------------------------------------------------------*/
