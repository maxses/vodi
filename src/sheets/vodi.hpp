#ifndef VODI_HPP
#define VODI_HPP

#include <QWidget>
#include <QSettings>
#include <settings.hpp>

namespace Ui {
class Vodi;
}

class CVodi : public QWidget
{
   Q_OBJECT

public:
   explicit CVodi(CSettings &settings, QWidget *parent = nullptr);
   ~CVodi();

private:
   Ui::Vodi *ui;
   CSettings &m_settings;

private slots:
   void slotVoltageChanged();
   void slotResistorChanged();
   void slotConfigChanged();
   
private:
   void updateReadonly();
   
};

#endif // VODI_HPP
