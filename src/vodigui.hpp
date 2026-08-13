#ifndef CVodiGui_H
#define CVodiGui_H
/**---------------------------------------------------------------------------
 *
 * @file    vodigui.hpp
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


#include <vodigui.hpp>
#include <QSettings>
#include <led.hpp>
#include <vodi.hpp>
#include <shunt.hpp>
#include <e12.hpp>
#include <ui_vodigui.h>
#include <settings.hpp>


/*--- Declarations ---------------------------------------------------------*/


QT_BEGIN_NAMESPACE
namespace Ui { class Led; }
QT_END_NAMESPACE

class CVodiGui: public QMainWindow
{
   Q_OBJECT

public:
   CVodiGui(QWidget *parent = nullptr);
   ~CVodiGui();

private:
   Ui::VoDi *ui;
   CSettings m_settings;

   CLed *m_led;
   CVodi *m_vodi;
   CShunt *m_shunt;
   CE12 *m_e12;

   void setBold( bool bold );
   void setItalic( bool italic );
   void setUnderline( bool underline );
   void setSubscript( bool subscript );

private slots:
   void slotQuit();
   void slotBoldToggled( /*bool checked*/ );
   void slotItalicToggled( );
   void slotUnderlineToggled( );
   void slotSubscriptToggled( );
   void slotBoldToggledShortCut( );
   void slotItalicToggledShortCut( );
   void slotUnderlineToggledShortCut( );
   // void slotSubscriptToggledShortCut( );
   void slotCursorMoved( );
   void slotReset( );
   void slotUpdateSetting( );

};


/*--- Fin ------------------------------------------------------------------*/
#endif // CVodiGui_H
