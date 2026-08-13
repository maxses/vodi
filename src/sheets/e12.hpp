#ifndef E12_H
#define E12_H
/**---------------------------------------------------------------------------
 *
 * @file    e12.hpp
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


#include <QWidget>
#include <common.hpp>


/*--- Declarations ---------------------------------------------------------*/


namespace Ui {

class E12;

}

class CE12 : public CCommon
{
   Q_OBJECT

   public:
      explicit CE12(CSettings &settings, QWidget *parent = nullptr);
      ~CE12();

   private:
      Ui::E12 *ui;

   private slots:
      void updateFields();

   private:
      void clearFields();
};


/*--- Fin ------------------------------------------------------------------*/
#endif // E12_H
