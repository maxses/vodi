#ifndef LED_HPP
#define LED_HPP

#include <QWidget>
#include <QSettings>
#include <settings.hpp>

namespace Ui {
class Led;
}

class CLed : public QWidget
{
   Q_OBJECT

public:
   explicit CLed(CSettings &settings, QWidget *parent = nullptr);
   ~CLed();

private:
   Ui::Led *ui;
   CSettings &m_settings;
   
   void updateILedReal();

private slots:
   void slotU1Changed(double);
   void slotR1Changed(double);

};

#endif // LED_HPP
