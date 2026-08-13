#ifndef RESISTOR_HPP
#define RESISTOR_HPP
/**---------------------------------------------------------------------------
 *
 * @file    resistor.hpp
 * @brief   Class for calulation combination of resistors
 *
 * Resistors can be connected in series or parallel.
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <QList>


/*--- Declarations ---------------------------------------------------------*/


class CResistor
{
   private:
      double m_value;
       
   public:
      CResistor( double value )
           :m_value(value)
      {}
      
      double value() const
      {
         return( m_value );
      }
      
      double voltageDivider(double voltage, const CResistor& r2) const
      {
         return( ( voltage * r2.value() ) / ( value() + r2.value() ) );
      }
      
      CResistor operator ||(const CResistor& r2) const
      {
         if( value() < 0 )
         {
            return( r2 );
         }
         if( r2.value() < 0 )
         {
            return( *this );
         }
         return( CResistor( ( value() * r2.value() )
                           / ( value() + r2.value() ) ) );
      }
      
      CResistor operator |(const CResistor& r2) const
      {
         if( ( value() < 0) || ( r2.value() < 0 ) )
         {
            return(-1);
         }
         
         return( CResistor( value() + r2.value() ) );
      }
      
      double amps( double voltage ) const
      {
         return( voltage / m_value );
      }
      
      CResistor bestMatch();
      CResistor bestMatch(const QList<CResistor>& series);
      bool operator <(const CResistor &other) const
      {
         return( m_value < other.m_value );
      }
      bool operator >(const CResistor &other) const
      {
         return( m_value > other.m_value );
      }
};

extern const QList<CResistor> E1;
extern const QList<CResistor> E12;
extern const QList<CResistor> E12Limited;
extern const QList<CResistor> EOpen;
extern const QList<CResistor> E24;
extern const QList<CResistor> E48;
extern const QList<CResistor> E96;


/*--- Fin -------------------------------------------------------------------*/
#endif // ? ! RESISTOR_HPP
