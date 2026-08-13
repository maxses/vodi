#ifndef VODI_HPP
#define VODI_HPP
/**---------------------------------------------------------------------------
 *
 * @file    vodi.hpp
 * @brief   Calculate voltages divider resistors
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
class Vodi;
}

class CVodi : public CCommon
{
   Q_OBJECT

public:
   explicit CVodi(CSettings &settings, QWidget *parent = nullptr);
   ~CVodi();

private:
   Ui::Vodi *ui;

private slots:
   void slotVoltageChanged();
   void slotResistorChanged();
   void slotConfigChanged();
   
private:
   void updateReadonly();
    void highlightCalculationSource( bool base );
};


/*--- Fin ------------------------------------------------------------------*/
#endif // VODI_HPP
