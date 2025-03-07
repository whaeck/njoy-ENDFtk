// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what we are testing
#include "ENDFtk/section/9.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;
using ReactionProduct = section::Type< 9 >::ReactionProduct;

std::string chunk();
void verifyChunk( const ReactionProduct& );
std::string invalidChunk();

SCENARIO( "ReactionProduct" ) {

  GIVEN( "valid data for a ReactionProduct" ) {

    std::string string = chunk();

    WHEN( "the data is given explicitly with boundaries and interpolants" ) {

      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      long za = 95242;
      long lfs = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > interpolants = { 5 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      ReactionProduct chunk( qm, qi, za, lfs,
                             std::move( boundaries ),
                             std::move( interpolants ),
                             std::move( x ),
                             std::move( y ) );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 9, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9534, 9, 102 );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 9, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is given explicitly with an interpolation type" ) {

      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      long za = 95242;
      long lfs = 2;
      long interpolant = 5;
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      ReactionProduct chunk( qm, qi, za, lfs, std::move( x ), std::move( y ),
                             interpolant );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 9, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream" ) {

      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      ReactionProduct chunk( begin, end, lineNumber, 9534, 9, 102 );

      THEN( "a ReactionProduct can be constructed and members can be tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 9534, 9, 102 );

        CHECK( buffer == string );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid data for a ReactionProduct" ) {

    WHEN( "inconsistent data is used" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      double qm = 2.224648e+6;
      double qi = 3.224648e+6;
      long za = 95242;
      long lfs = 2;
      std::vector< long > boundaries = { 2 };
      std::vector< long > wrongInterpolants = { 5, 2 };
      std::vector< double > x = { 1., 3. };
      std::vector< double > y = { 2., 4. };

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReactionProduct( qm, qi, za, lfs,
                                       std::move( boundaries ),
                                       std::move( wrongInterpolants ),
                                       std::move( x ),
                                       std::move( y ) ) );
      } // THEN
    } // WHEN

    WHEN( "a string representation with an error is given" ) {

      // no need to test every possibility (TAB1 takes care of tests)

      std::string string = invalidChunk();
      auto begin = string.begin();
      auto end = string.end();
      long lineNumber = 1;

      THEN( "an exception is thrown" ) {

        CHECK_THROWS( ReactionProduct( begin, end, lineNumber, 9534, 9, 102 ) );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO

std::string chunk() {
  return
  " 2.224648+6 3.224648+6      95242          2          1          29534 9102     \n"
  "          2          5                                            9534 9102     \n"
  " 1.000000+0 2.000000+0 3.000000+0 4.000000+0                      9534 9102     \n";
}

void verifyChunk( const ReactionProduct& chunk ) {

  CHECK_THAT( 2.224648e+6, WithinRel( chunk.QM() ) );
  CHECK_THAT( 2.224648e+6, WithinRel( chunk.massDifferenceQValue() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.QI() ) );
  CHECK_THAT( 3.224648e+6, WithinRel( chunk.reactionQValue() ) );
  CHECK( 95242 == chunk.IZAP() );
  CHECK( 95242 == chunk.productIdentifier() );
  CHECK( 2 == chunk.LFS() );
  CHECK( 2 == chunk.excitedLevel() );

  CHECK( 2 == chunk.NP() );
  CHECK( 2 == chunk.numberPoints() );
  CHECK( 1 == chunk.NR() );
  CHECK( 1 == chunk.numberInterpolationRegions() );
  CHECK( 1 == chunk.INT().size() );
  CHECK( 1 == chunk.NBT().size() );
  CHECK( 5 == chunk.INT()[0] );
  CHECK( 2 == chunk.NBT()[0] );
  CHECK( 1 == chunk.interpolants().size() );
  CHECK( 1 == chunk.boundaries().size() );
  CHECK( 5 == chunk.interpolants()[0] );
  CHECK( 2 == chunk.boundaries()[0] );
  CHECK( 2 == chunk.E().size() );
  CHECK( 2 == chunk.energies().size() );
  CHECK( 2 == chunk.x().size() );
  CHECK( 2 == chunk.Y().size() );
  CHECK( 2 == chunk.multiplicities().size() );
  CHECK( 2 == chunk.y().size() );
  CHECK_THAT( 1., WithinRel( chunk.E()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.E()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.energies()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.energies()[1] ) );
  CHECK_THAT( 1., WithinRel( chunk.x()[0] ) );
  CHECK_THAT( 3., WithinRel( chunk.x()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.Y()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.Y()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.multiplicities()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.multiplicities()[1] ) );
  CHECK_THAT( 2., WithinRel( chunk.y()[0] ) );
  CHECK_THAT( 4., WithinRel( chunk.y()[1] ) );

  CHECK( 3 == chunk.NC() );
}

std::string invalidChunk() {
  return
    " 2.224648+6 3.224648+6      95242          2          2          29534 9102     \n"
    "          2          2                                            9534 9102     \n"
    " 1.000000-5 8.579050+0 3.000000+7 1.487778+1                      9534 9102     \n";
}
