#ifndef URI_HPP
#define URI_HPP

/*
 *          U
 *         ---
 *         R*I
 */

class CURI
{
   private:
      double m_voltage;
      double m_resistance;
      double m_current;
       
   public:
      CURI( double voltage, double resistance, double current )
           :m_voltage(voltage)
           ,m_resistance(resistance)
           ,m_current(current)
      {}
      double calcVoltage() const
      {
         return( m_resistance * m_current );
      }
      double calcCurrent() const
      {
         return( m_voltage / m_resistance );
      }
};


/*--- Fin -------------------------------------------------------------------*/
#endif // ? ! URI_HPP
