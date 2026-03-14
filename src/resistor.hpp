#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include <QList>


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
      bool operator <(const CResistor &other) const
      {
         return( m_value < other.m_value );
      }
      bool operator >(const CResistor &other) const
      {
         return( m_value > other.m_value );
      }
};

extern QList<CResistor> E12;
extern QList<CResistor> E12Limited;
extern QList<CResistor> EOpen;
extern QList<CResistor> E24;


/*--- Fin -------------------------------------------------------------------*/
#endif // ? ! RESISTOR_HPP
