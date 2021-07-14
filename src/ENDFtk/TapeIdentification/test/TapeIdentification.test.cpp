#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ENDFtk/TapeIdentification.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

void verifyChunk( const TapeIdentification& );

SCENARIO( "TapeIdentification" ) {

  GIVEN( "valid data for a section::Type< 1, 451 >" ) {

    std::string record{ " $Rev:: 1056     $  $Date:: 2017-01-26#$                             1 0  0     \n" };

    WHEN( "the data is given explicitly" ) {

      std::string text = " $Rev:: 1056     $  $Date:: 2017-01-26#$";
      int tape = 1;

      TapeIdentification chunk( std::move( text ), tape );

      THEN( "a TapeIdentification can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1, 0, 0 );

        REQUIRE( buffer == record );
      } // THEN
    } // WHEN

    WHEN( "the data is read from a string/stream with a valid SEND" ) {

      auto begin = record.begin();
      auto end = record.end();
      long lineNumber = 1;

      TapeIdentification chunk( begin, end, lineNumber );

      THEN( "a TapeIdentification can be constructed and members can be "
            "tested" ) {

        verifyChunk( chunk );
      } // THEN

      THEN( "it can be printed" ) {

        std::string buffer;
        auto output = std::back_inserter( buffer );
        chunk.print( output, 1, 0, 0 );

        REQUIRE( buffer == record );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "invalid tape IDs" ) {

    std::string ID{" $Rev:: 1056     $  $Date:: 2017-01-26#$                            -1 1  0     \n"};

    THEN( "an exception is thrown" ) {

      long lineNumber{0};
      auto begin = ID.begin();
      auto end = ID.end();

      REQUIRE_THROWS( TapeIdentification( begin, end, lineNumber ) );
    }
  }
}

void verifyChunk( const TapeIdentification& chunk ) {

  REQUIRE( " $Rev:: 1056     $  $Date:: 2017-01-26#$                          "
           == chunk.text() );
  REQUIRE( 1 == chunk.tapeNumber() );
  REQUIRE( 1 == chunk.NTAPE() );
  REQUIRE( 1 == chunk.NC() );
}
