/**---------------------------------------------------------------------------
 *
 * @file    common.cpp
 * @brief   Base class for all sheets
 *
 * Holds the settings
 *
 * @date   20260322
 * @author Maximilian Seesslen <mes@seesslen.net>
 * @copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include "common.hpp"
#include <resistor.hpp>


/*--- Implementation -------------------------------------------------------*/


CCommon::CCommon(CSettings &settings, QWidget *parent)
    : QWidget(parent)
    , m_settings( settings )
{
}


CCommon::~CCommon()
{
}


/*--- Fin ------------------------------------------------------------------*/
