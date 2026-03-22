/**---------------------------------------------------------------------------
 *
 * @file    main.cpp
 * @brief   Main file for VoDi
 *
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "vodigui.hpp"
#include <QApplication>


/*--- Implementation -------------------------------------------------------*/


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


/*--- Fin ------------------------------------------------------------------*/
