#ifndef SHUNT_HPP
#define SHUNT_HPP

#include <QWidget>
#include <QSettings>
#include <settings.hpp>

namespace Ui {
class Shunt;
}

class CShunt : public QWidget
{
   Q_OBJECT

public:
   explicit CShunt(CSettings &settings, QWidget *parent = nullptr);
   ~CShunt();

private:
   Ui::Shunt *ui;
   CSettings &m_settings;

private slots:
   void slotVoltageChanged(double);
   void slotResistorChanged(double);
};

#endif // SHUNT_HPP
