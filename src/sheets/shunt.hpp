#ifndef SHUNT_HPP
#define SHUNT_HPP
/**---------------------------------------------------------------------------
 *
 * @file    shunt.hpp
 * @brief   Calculate voltages on shunt resistor depending on current
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <QWidget>
#include <common.hpp>


/*--- Declarations ---------------------------------------------------------*/


namespace Ui {
class Shunt;
}

class CShunt : public CCommon
{
    Q_OBJECT

public:
   explicit CShunt(CSettings &settings, QWidget *parent = nullptr);
   ~CShunt();

private:
   Ui::Shunt *ui;

   enum class ECalculationSource
   {
      Voltage,
      Resistor,
   };

   void updateAll();
   void highlightCalculationSource( ECalculationSource calcSource );

private slots:
   void slotVoltageChanged(double);
   void slotResistorChanged(double);
};


/*--- Fin ------------------------------------------------------------------*/
#endif // SHUNT_HPP
