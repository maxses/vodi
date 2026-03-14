#include "vodigui.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QCoreApplication::setOrganizationName("minutnik");
   QCoreApplication::setOrganizationDomain("minutnik.de");
   QCoreApplication::setApplicationName("vodi");
   
   CVodiGui w;
   w.show();
   return a.exec();
}
