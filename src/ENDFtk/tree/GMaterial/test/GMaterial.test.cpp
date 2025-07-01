// include Catch2
#include <catch2/catch_test_macros.hpp>

// what we are testing
#include "ENDFtk/tree/GMaterial.hpp"

// other includes

// convenience typedefs
using namespace njoy::ENDFtk;

std::string chunkMF1();
std::string chunkMF3MT16();
std::string chunkMF3MT17();
std::string chunkMF3();
std::string chunk();
std::string validMEND();

SCENARIO( "tree::Material" ) {

  GIVEN( "an empty tree::Material" ) {

    WHEN( "it is created" ) {

      tree::GMaterial material( 9228 );

      THEN( "it is empty except for the MAT and MF" ) {

        CHECK( 9228 == material.MAT() );
        CHECK( 9228 == material.materialNumber() );

        auto fileNumbers = material.fileNumbers();
        CHECK( 0 == material.size() );
        CHECK( 0 == fileNumbers.size() );

        CHECK( "" == material.content() );
      }
    } // WHEN
  } // GIVEN

  GIVEN( "valid data for a tree::Material" ) {

    std::string materialString = chunk() + validMEND();

    WHEN( "the data is read from a string/stream with a valid MEND" ) {

      auto position = materialString.begin();
      auto start = materialString.begin();
      auto end = materialString.end();
      long lineNumber = 0;

      HeadRecord head( position, end, lineNumber );
      tree::GMaterial material( head, start, position, end, lineNumber );

      THEN( "the Material is populated correctly" ) {

        CHECK( 9228 == material.MAT() );
        CHECK( 9228 == material.materialNumber() );

        CHECK( true == material.hasFile( 1 ) );
        CHECK( true == material.hasMF( 1 ) );
        CHECK( true == material.file( 1 ).hasSection( 451 ) );
        CHECK( true == material.MF( 1 ).hasMT( 451 ) );
        CHECK( 1 == material.file( 1 ).size() );
        CHECK( 1 == material.MF( 1 ).size() );
        CHECK( chunkMF1() == material.file( 1 ).content() );
        CHECK( chunkMF1() == material.MF( 1 ).content() );
        CHECK( chunkMF1() == material.file( 1 ).section( 451 ).content() );
        CHECK( chunkMF1() == material.MF( 1 ).section( 451 ).content() );

        CHECK( false == material.hasFile( 2 ) );
        CHECK( false == material.hasMF( 2 ) );

        CHECK( true == material.hasFile( 3 ) );
        CHECK( true == material.hasMF( 3 ) );
        CHECK( true == material.file( 3 ).hasSection( 16 ) );
        CHECK( true == material.MF( 3 ).hasMT( 16 ) );
        CHECK( true == material.hasSection( 3, 16 ) );
        CHECK( true == material.hasMFMT( 3, 16 ) );
        CHECK( true == material.file( 3 ).hasSection( 17 ) );
        CHECK( true == material.MF( 3 ).hasMT( 17 ) );
        CHECK( true == material.hasSection( 3, 17 ) );
        CHECK( true == material.hasMFMT( 3, 17 ) );
        CHECK( false == material.file( 3 ).hasSection( 3 ) );
        CHECK( false == material.MF( 3 ).hasMT( 3 ) );
        CHECK( false == material.hasSection( 3, 3 ) );
        CHECK( false == material.hasMFMT( 3, 3 ) );
        CHECK( 2 == material.file( 3 ).size() );
        CHECK( 2 == material.MF( 3 ).size() );
        CHECK( chunkMF3() == material.file( 3 ).content() );
        CHECK( chunkMF3() == material.MF( 3 ).content() );
        CHECK( chunkMF3MT16() == material.file( 3 ).section( 16 ).content() );
        CHECK( chunkMF3MT16() == material.MF( 3 ).section( 16 ).content() );
        CHECK( chunkMF3MT17() == material.file( 3 ).section( 17 ).content() );
        CHECK( chunkMF3MT17() == material.MF( 3 ).section( 17 ).content() );

        CHECK( false == material.hasFile( 5 ) );
        CHECK( false == material.hasMF( 5 ) );

        CHECK( false == material.hasFile( 6 ) );
        CHECK( false == material.hasMF( 6 ) );

        auto fileNumbers = material.fileNumbers();
        CHECK( 2 == material.size() );
        CHECK( 2 == fileNumbers.size() );

        auto iter = std::begin( fileNumbers );
        CHECK( 1 == *iter ); ++iter;
        CHECK( 3 == *iter ); ++iter;

        CHECK( materialString == material.content() );
      } // THEN

      THEN( "the iterators advanced correctly" ) {

        CHECK( materialString.end() == position );
        CHECK( materialString.begin() == start );
        CHECK( materialString.end() == end );
        CHECK( 36 == lineNumber ); // last line read is the MEND record
      } // THEN
    } // WHEN
  } // GIVEN

//  GIVEN( "invalid data for a tree::File" ) {
//
//    WHEN( "the data is read from a string/stream that abruptly ends (no END record)" ) {
//
//      std::string materialString = chunk();
//      auto position = materialString.begin();
//      auto start = materialString.begin();
//      auto end = materialString.end();
//      long lineNumber = 1;
//      HeadRecord head( position, end, lineNumber );
//
//      THEN( "an exception is thrown upon construction" ) {
//
//        CHECK_THROWS( tree::Material( head, start, position, end, lineNumber ) );
//      } // THEN
//    } // WHEN
//
//    WHEN( "the data contains a duplicate file" ) {
//
//      std::string materialString = chunk() + chunk() + validMEND();
//      auto position = materialString.begin();
//      auto start = materialString.begin();
//      auto end = materialString.end();
//      long lineNumber = 1;
//      HeadRecord head( position, end, lineNumber );
//
//      THEN( "an exception is thrown upon construction" ) {
//
//        CHECK_THROWS( tree::Material( head, start, position, end, lineNumber ) );
//      } // THEN
//    } // WHEN
//  } // GIVEN
} // SCENARIO

std::string chunkMF1() {

  // this is a legal MF1
  return
    " 9.223500+4 2.330248+2          0          3         -1          19228 1451     \n"
    " 2.936000+2 0.000000+0         30         12         48          09228 1451     \n"
    " 0.000000+0 1.00000+10 1.000000+4 1.000000+2 1.390000-4 1.520000-19228 1451     \n"
    " 4.140000-1 1.130000+0 3.060000+0 8.320000+0 2.260000+1 6.140000+19228 1451     \n"
    " 1.670000+2 4.540000+2 1.235000+3 3.350000+3 9.120000+3 2.480000+49228 1451     \n"
    " 6.760000+4 1.840000+5 3.030000+5 5.000000+5 8.230000+5 1.353000+69228 1451     \n"
    " 1.738000+6 2.232000+6 2.865000+6 3.680000+6 6.070000+6 7.790000+69228 1451     \n"
    " 1.000000+7 1.200000+7 1.350000+7 1.500000+7 1.700000+7 1.000000+49228 1451     \n"
    " 1.000000+5 5.000000+5 1.000000+6 2.000000+6 3.000000+6 4.000000+69228 1451     \n"
    " 5.000000+6 6.000000+6 7.000000+6 8.000000+6 9.000000+6 2.000000+79228 1451     \n"
    "                                                                  9228 1  0     \n";
}

std::string chunkMF3MT16() {

  // this is a legal MF3 MT16
  return
    " 9.223500+4 0.000000+0          1          1          0         309228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         249228 3 16     \n"
    " 2.235493+5 1.047471-2                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         259228 3 16     \n"
    " 4.396216+4 3.690336-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         269228 3 16     \n"
    " 2.311833+4 6.475546-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         279228 3 16     \n"
    " 1.410474+4 8.511604-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3 16     \n"
    " 1.905167+4 7.647669-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3 16     \n"
    " 7.393531+4 5.483544-1                                            9228 3 16     \n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3 16     \n"
    " 3.724272+3 3.717841-1                                            9228 3 16     \n"
    "                                                                  9228 3  0     \n";
}

std::string chunkMF3MT17() {

  // this is a legal MF3 MT17
  return
    " 9.223500+4 0.000000+0          1          1          0         309228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         289228 3 17     \n"
    " 1.905167+4 3.145908-3                                            9228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         299228 3 17     \n"
    " 7.393531+4 3.879856-2                                            9228 3 17     \n"
    " 2.936000+2 0.000000+0          2          1          2         309228 3 17     \n"
    " 3.724272+3 1.593517-1                                            9228 3 17     \n"
    "                                                                  9228 3  0     \n";
}

std::string chunkMF3() {

  return chunkMF3MT16() + chunkMF3MT17();
}

std::string chunk() {

  return chunkMF1() + chunkMF3();
}

std::string validMEND(){

  return
    "                                                                     0 0  0     \n";
}
