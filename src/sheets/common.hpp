#ifndef SHEET_COMMON_HPP
#define SHEET_COMMON_HPP
/**---------------------------------------------------------------------------
 *
 * @file    common.hpp
 * @brief   Base class for sheets
 *
 * Holds the settings
 *
 * @date   20260322
 * @author Maximilian Seesslen <src@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <QWidget>
#include <settings.hpp>
#include <resistor.hpp>


/*--- Declarations ---------------------------------------------------------*/


class CCommon : public QWidget
{
   Q_OBJECT

   protected:
      CSettings &m_settings;
      int m_seriesCount=0;


   public:
   explicit CCommon(CSettings &settings, QWidget *parent = nullptr);
   ~CCommon();
   const QList<CResistor>& getSeries()
   {
      int index=m_settings.value("series").toInt();
      switch( index )
      {
         case 0:
            m_seriesCount=1;
            return( E1 );
            break;
         case 1:
            m_seriesCount=12;
            return( E12 );
         break;
         case 2:
            m_seriesCount=24;
            return( E24 );
            break;
         case( 3 ):
            m_seriesCount=48;
            return( E48 );
            break;
         default:
            qWarning("Unknown series index: %d", index);
            break;
      }
      m_seriesCount=12;
      return( E12 );
   }

   int getSeriesCount()
   {
      return( m_seriesCount );
   }
};


/*--- Fin ------------------------------------------------------------------*/
#endif // SHEETS_COMMON_HPP
