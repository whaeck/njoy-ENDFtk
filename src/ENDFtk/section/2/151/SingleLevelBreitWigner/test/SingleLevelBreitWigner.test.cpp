// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// what we are testing
#include "ENDFtk/section/2/151.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using SingleLevelBreitWigner =
section::Type< 2, 151 >::SingleLevelBreitWigner;
using LValue = section::Type< 2, 151 >::SingleLevelBreitWigner::LValue;

std::string chunk();
void verifyChunk( const SingleLevelBreitWigner& );
std::string invalidSize();

SCENARIO( "SingleLevelBreitWigner" ) {

  GIVEN( "valid data for a SingleLevelBreitWigner" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly" ) {

      double spi = 1.0;
      double ap = 0.893;
      std::vector< LValue > lvalues =
        { { 1.982069e+1, 0.0, 0, false,
            { -1.470000e+5, 4.730000e+5 }, { 0.5, 0.5 },
            { 5.430695e+2, 1.072906e+5 }, { 3.680695e+2, 1.072900e+5 },
            { 1.750000e+2, 5.600000e-1 }, { 0., 0.04 } },
          { 1.982069e+1, 0.0, 1, false,
            { -2.060000e+0, 5.160000+0 }, { 0.5, 0.5 },
            { 3.006610e-2, 3.393822e-2 }, { 5.750000e-3, 3.920000e-3 },
            { 2.430000e-2, 3.000000e-2 }, { 1.610000e-5, 1.822000e-5 } } };

      SingleLevelBreitWigner chunk( spi, ap, std::move( lvalues ) );

      THEN( "a SingleLevelBreitWigner can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      SingleLevelBreitWigner chunk( begin, end, lineNumber, 1025, 2, 151 );

      THEN( "a SingleLevelBreitWigner can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      }

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1025, 2, 151 );

        CHECK( buffer == string );
      } // THEN
    } // GIVEN
  } // GIVEN

  GIVEN( "invalid data" ) {

    WHEN( "no l values are given" ) {

      double spi = 1.0;
      double ap = 0.893;
      std::vector< LValue > lvalues = {};

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( SingleLevelBreitWigner( spi, ap, std::move( lvalues ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string with no l values is used" ) {

      std::string string = invalidSize();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( SingleLevelBreitWigner( begin, end, lineNumber, 1025, 2, 151 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
    " 1.000000+0 8.930000-1          0          0          2          01025 2151     \n"
    " 1.982069+1 0.000000+0          0          0         12          21025 2151     \n"
    "-1.470000+5 5.000000-1 5.430695+2 3.680695+2 1.750000+2 0.000000+01025 2151     \n"
    " 4.730000+5 5.000000-1 1.072906+5 1.072900+5 5.600000-1 4.000000-21025 2151     \n"
    " 1.982069+1 0.000000+0          1          0         12          21025 2151     \n"
    "-2.060000+0 5.000000-1 3.006610-2 5.750000-3 2.430000-2 1.610000-51025 2151     \n"
    " 5.160000+0 5.000000-1 3.393822-2 3.920000-3 3.000000-2 1.822000-51025 2151     \n";
}

void verifyChunk( const SingleLevelBreitWigner& chunk ) {

  CHECK( 1 == chunk.LRU() );
  CHECK( 1 == chunk.type() );
  CHECK( 1 == chunk.LRF() );
  CHECK( 1 == chunk.representation() );
  CHECK( false == chunk.LFW() );
  CHECK( false == chunk.averageFissionWidthFlag() );

  CHECK_THAT( 1., WithinRel( chunk.SPI() ) );
  CHECK_THAT( 1., WithinRel( chunk.spin() ) );
  CHECK_THAT( 0.893, WithinRel( chunk.AP() ) );
  CHECK_THAT( 0.893, WithinRel( chunk.scatteringRadius() ) );

  CHECK( 2 == chunk.NLS() );
  CHECK( 2 == chunk.numberLValues() );

  CHECK( 2 == chunk.lValues().size() );

  auto lvalue1 = chunk.lValues()[0];
  CHECK_THAT( 1.982069e+1, WithinRel( lvalue1.AWRI() ) );
  CHECK_THAT( 1.982069e+1, WithinRel( lvalue1.atomicWeightRatio() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.QX() ) );
  CHECK_THAT( 0., WithinRel( lvalue1.competitiveQValue() ) );
  CHECK( 0 == lvalue1.L() );
  CHECK( 0 == lvalue1.orbitalMomentum() );
  CHECK( false == lvalue1.LRX() );
  CHECK( false == lvalue1.competitiveWidthFlag() );

  CHECK( 2 == lvalue1.NRS() );
  CHECK( 2 == lvalue1.numberResonances() );
  CHECK( 2 == lvalue1.ER().size() );
  CHECK( 2 == lvalue1.resonanceEnergies().size() );
  CHECK( 2 == lvalue1.AJ().size() );
  CHECK( 2 == lvalue1.spinValues().size() );
  CHECK( 2 == lvalue1.GT().size() );
  CHECK( 2 == lvalue1.totalWidths().size() );
  CHECK( 2 == lvalue1.GN().size() );
  CHECK( 2 == lvalue1.neutronWidths().size() );
  CHECK( 2 == lvalue1.GG().size() );
  CHECK( 2 == lvalue1.gammaWidths().size() );
  CHECK( 2 == lvalue1.GF().size() );
  CHECK( 2 == lvalue1.fissionWidths().size() );
  CHECK( 2 == lvalue1.GX().size() );
  CHECK( 2 == lvalue1.competitiveWidths().size() );
  CHECK( 2 == lvalue1.resonances().size() );

  CHECK_THAT( -1.470000e+5, WithinRel( lvalue1.ER()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( lvalue1.ER()[1] ) );
  CHECK_THAT( -1.470000e+5, WithinRel( lvalue1.resonanceEnergies()[0] ) );
  CHECK_THAT(  4.730000e+5, WithinRel( lvalue1.resonanceEnergies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.spinValues()[0] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue1.spinValues()[1] ) );
  CHECK_THAT( 5.430695e+2, WithinRel( lvalue1.GT()[0] ) );
  CHECK_THAT( 1.072906e+5, WithinRel( lvalue1.GT()[1] ) );
  CHECK_THAT( 5.430695e+2, WithinRel( lvalue1.totalWidths()[0] ) );
  CHECK_THAT( 1.072906e+5, WithinRel( lvalue1.totalWidths()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( lvalue1.GN()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( lvalue1.GN()[1] ) );
  CHECK_THAT( 3.680695e+2, WithinRel( lvalue1.neutronWidths()[0] ) );
  CHECK_THAT( 1.072900e+5, WithinRel( lvalue1.neutronWidths()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( lvalue1.GG()[0] ) );
  CHECK_THAT( 0.56, WithinRel( lvalue1.GG()[1] ) );
  CHECK_THAT( 1.750000e+2, WithinRel( lvalue1.gammaWidths()[0] ) );
  CHECK_THAT( 0.56, WithinRel( lvalue1.gammaWidths()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.GF()[0] ) );
  CHECK_THAT( 0.04, WithinRel( lvalue1.GF()[1] ) );
  CHECK_THAT( 0., WithinRel( lvalue1.fissionWidths()[0] ) );
  CHECK_THAT( 0.04, WithinRel( lvalue1.fissionWidths()[1] ) );
  CHECK_THAT( 0., WithinAbs( lvalue1.GX()[0], 1e-12 ) );
  CHECK_THAT( 0., WithinAbs( lvalue1.GX()[1], 1e-10 ) );
  CHECK_THAT( 0., WithinAbs( lvalue1.competitiveWidths()[0], 1e-12 ) );
  CHECK_THAT( 0., WithinAbs( lvalue1.competitiveWidths()[1], 1e-10 ) );

  auto lvalue2 = chunk.lValues()[1];
  CHECK_THAT( 1.982069e+1, WithinRel( lvalue2.AWRI() ) );
  CHECK_THAT( 1.982069e+1, WithinRel( lvalue2.atomicWeightRatio() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.QX() ) );
  CHECK_THAT( 0., WithinRel( lvalue2.competitiveQValue() ) );
  CHECK( 1 == lvalue2.L() );
  CHECK( 1 == lvalue2.orbitalMomentum() );
  CHECK( false == lvalue2.LRX() );
  CHECK( false == lvalue2.competitiveWidthFlag() );

  CHECK( 2 == lvalue2.NRS() );
  CHECK( 2 == lvalue2.numberResonances() );
  CHECK( 2 == lvalue2.ER().size() );
  CHECK( 2 == lvalue2.resonanceEnergies().size() );
  CHECK( 2 == lvalue2.AJ().size() );
  CHECK( 2 == lvalue2.spinValues().size() );
  CHECK( 2 == lvalue2.GT().size() );
  CHECK( 2 == lvalue2.totalWidths().size() );
  CHECK( 2 == lvalue2.GN().size() );
  CHECK( 2 == lvalue2.neutronWidths().size() );
  CHECK( 2 == lvalue2.GG().size() );
  CHECK( 2 == lvalue2.gammaWidths().size() );
  CHECK( 2 == lvalue2.GF().size() );
  CHECK( 2 == lvalue2.fissionWidths().size() );
  CHECK( 2 == lvalue2.GX().size() );
  CHECK( 2 == lvalue2.competitiveWidths().size() );
  CHECK( 2 == lvalue2.resonances().size() );

  CHECK_THAT( -2.060000e+0, WithinRel( lvalue2.ER()[0] ) );
  CHECK_THAT(  5.160000e+0, WithinRel( lvalue2.ER()[1] ) );
  CHECK_THAT( -2.060000e+0, WithinRel( lvalue2.resonanceEnergies()[0] ) );
  CHECK_THAT(  5.160000e+0, WithinRel( lvalue2.resonanceEnergies()[1] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue2.AJ()[0] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue2.AJ()[1] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue2.spinValues()[0] ) );
  CHECK_THAT( 0.5, WithinRel( lvalue2.spinValues()[1] ) );
  CHECK_THAT( 3.006610e-2, WithinRel( lvalue2.GT()[0] ) );
  CHECK_THAT( 3.393822e-2, WithinRel( lvalue2.GT()[1] ) );
  CHECK_THAT( 3.006610e-2, WithinRel( lvalue2.totalWidths()[0] ) );
  CHECK_THAT( 3.393822e-2, WithinRel( lvalue2.totalWidths()[1] ) );
  CHECK_THAT( 5.750000e-3, WithinRel( lvalue2.GN()[0] ) );
  CHECK_THAT( 3.920000e-3, WithinRel( lvalue2.GN()[1] ) );
  CHECK_THAT( 5.750000e-3, WithinRel( lvalue2.neutronWidths()[0] ) );
  CHECK_THAT( 3.920000e-3, WithinRel( lvalue2.neutronWidths()[1] ) );
  CHECK_THAT( 2.430000e-2, WithinRel( lvalue2.GG()[0] ) );
  CHECK_THAT( 3.000000e-2, WithinRel( lvalue2.GG()[1] ) );
  CHECK_THAT( 2.430000e-2, WithinRel( lvalue2.gammaWidths()[0] ) );
  CHECK_THAT( 3.000000e-2, WithinRel( lvalue2.gammaWidths()[1] ) );
  CHECK_THAT( 1.610000e-5, WithinRel( lvalue2.GF()[0] ) );
  CHECK_THAT( 1.822000e-5, WithinRel( lvalue2.GF()[1] ) );
  CHECK_THAT( 1.610000e-5, WithinRel( lvalue2.fissionWidths()[0] ) );
  CHECK_THAT( 1.822000e-5, WithinRel( lvalue2.fissionWidths()[1] ) );
  CHECK_THAT( 0., WithinAbs( lvalue2.GX()[0], 1e-12 ) );
  CHECK_THAT( 0., WithinAbs( lvalue2.GX()[1], 1e-12 ) );
  CHECK_THAT( 0., WithinAbs( lvalue2.competitiveWidths()[0], 1e-12 ) );
  CHECK_THAT( 0., WithinAbs( lvalue2.competitiveWidths()[1], 1e-12 ) );

  CHECK( 7 == chunk.NC() );
}

std::string invalidSize() {
  return
    " 1.000000+0 8.930000-1          0          0          0          01025 2151     \n";
}
