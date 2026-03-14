#ifndef E12_H
#define E12_H

#include <QWidget>
#include <settings.hpp>

namespace Ui {

class E12;

}

class CE12 : public QWidget
{
   Q_OBJECT

   public:
   explicit CE12(CSettings &settings, QWidget *parent = nullptr);
   ~CE12();

   private:
   Ui::E12 *ui;
   CSettings &m_settings;
};

#endif // E12_H
