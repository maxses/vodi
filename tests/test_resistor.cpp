/**---------------------------------------------------------------------------
 *
 * @file       test_string.cpp
 * @brief      Test CString
 *
 * @date       20250915
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#if defined ( CATCH_V3 )
   #include <catch2/catch_test_macros.hpp>
#elif defined ( CATCH_V2 )
   #include <catch2/catch.hpp>
#elif defined ( CATCH_V1 )
   #include <catch/catch.hpp>
#else
   #error "Either 'catch' or 'catch2' has to be installed"
#endif

#include "../src/resistor.hpp"

#define TEST_ALL
#define STOP_ON_FAIL


/*--- Implementation -------------------------------------------------------*/


TEST_CASE( "Resistor", "[default]" )
{
   // R_GES=(R1*R2)/(R1+R2)
   SECTION( "Parallel" )
   {
      CResistor r1_1( 1000 );
      CResistor r2_1( 880 );
      REQUIRE( (int)( r1_1 || r2_1 ).value() == 468 );
      
      CResistor r1_2( 120 );
      CResistor r2_2( 880 );
      REQUIRE( (int)( r1_2 || r2_2 ).value() == 105 );
   }
   
   // R_GES=(R1+R2)
   SECTION( "Series" )
   {
      CResistor r1_1( 1000 );
      CResistor r2_1( 880 );
      REQUIRE( (int)( r1_1 | r2_1 ).value() == 1880 );
      
      CResistor r1_2( 120 );
      CResistor r2_2( 880 );
      REQUIRE( (int)( r1_2 | r2_2 ).value() == 1000 );
   }
}


/*--- Fin ------------------------------------------------------------------*/
