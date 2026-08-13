#ifndef LED_HPP
#define LED_HPP
/**---------------------------------------------------------------------------
 *
 * @file    led.hpp
 * @brief   Calculate series resistor for LEDs
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <QWidget>
#include <QSettings>
// #include <settings.hpp>
#include <common.hpp>


/*--- Declarations ---------------------------------------------------------*/


namespace Ui {
class Led;
}

class CLed : public CCommon
{
   Q_OBJECT

public:
   explicit CLed(CSettings &settings, QWidget *parent = nullptr);
   ~CLed();
   enum class ECalculationSource
   {
       I_LED,
       R1_USER
   };

private:
   Ui::Led *ui;
   ECalculationSource m_calculationSource=ECalculationSource::I_LED;
   
   void updateILedReal();
   void updateP();
   void highlightCalculationSource( ECalculationSource calcSource );
       
private slots:
   void slotU1Changed(double);
   void slotR1Changed(double);
   void slotSettingsChanged();

};


/*--- Fin ------------------------------------------------------------------*/
#endif // LED_HPP
