// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/4.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using LegendreCoefficients = section::Type< 4 >::LegendreCoefficients;

std::string chunk();
void verifyChunk( const LegendreCoefficients& );
std::string invalidChunk();

SCENARIO( "LegendreCoefficients" ) {

  GIVEN( "valid data for a LegendreCoefficients" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double energy = 1e-5;
      std::vector< double > coefficients = { 7.392510e-5, 8.477139e-9,
                                             1.17106e-13 };

      LegendreCoefficients chunk( energy, std::move( coefficients ) );

      THEN( "an LegendreCoefficients can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      LegendreCoefficients chunk( begin, end, lineNumber, 9228, 4, 2 );

      THEN( "a LegendreCoefficients can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9228, 4, 2 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a LegendreCoefficients" ) {

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (LIST takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( LegendreCoefficients( begin, end, lineNumber,
                                              9228, 4, 2 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 0.000000+0 1.000000-5          0          0          3          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n";
}

void verifyChunk( const LegendreCoefficients& chunk ) {

  CHECK_THAT( 1e-5, WithinRel( chunk.E() ) );
  CHECK_THAT( 1e-5, WithinRel( chunk.incidentEnergy() ) );
  CHECK( 3 == chunk.NL() );
  CHECK( 3 == chunk.legendreOrder() );
  CHECK( 3 == chunk.coefficients().size() );
  CHECK( 3 == chunk.A().size() );
  CHECK_THAT( 7.392510e-5 , WithinRel( chunk.A()[0] ) );
  CHECK_THAT( 8.477139e-9, WithinRel( chunk.A()[1] ) );
  CHECK_THAT( 1.17106e-13, WithinRel( chunk.A()[2] ) );
  CHECK_THAT( 7.392510e-5 , WithinRel( chunk.coefficients()[0] ) );
  CHECK_THAT( 8.477139e-9, WithinRel( chunk.coefficients()[1] ) );
  CHECK_THAT( 1.17106e-13, WithinRel( chunk.coefficients()[2] ) );

  CHECK( 2 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 0.000000+0 1.000000-5          0          0          2          09228 4  2     \n"
    " 7.392510-5 8.477139-9 1.17106-13                                 9228 4  2     \n";
}
