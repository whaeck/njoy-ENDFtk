// include Catch2
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
using Catch::Matchers::WithinRel;

// what is being tested
#include "ENDFtk/gsection/1/451g.hpp"

// other includes
#include "ENDFtk/tree/Section.hpp"
#include "tools/std20/algorithm.hpp"

// useful aliasing
using namespace njoy::ENDFtk;
using gsection1451 = section::gType<1, 451>;

std::string chunk();
std::string validFEND();
void verifyChunk( const section::gType<1 , 451>& );

SCENARIO("section::gType<1, 451>") {
    GIVEN("valid data for a section::gType<1,451>") {
        
        std::string sectionString = chunk() + validFEND(); 

        WHEN("the data is provided explicitly") {
            // expected data for U235 (30G-n)
            int zaid = 92235;
            double awr = 233.0248;
            int zero1 = 0;
            int nz = 1;
            int gid = -1;
            int ntw = 1;
            double temp = 293.6;
            int zero2 = 0;
            int ngn = 30;
            int ngg = 12;
            int nw = 46;
            int zero3 = 0;
            int zero4 = 0;
            std::vector<double> sigz = {1e10};
            std::vector<double> egn = 
            {1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000,
             3.060000, 8.320000, 2.260000e1, 6.140000e1, 1.670000e2, 4.540000e2,
             1.235000e3, 3.350000e3, 9.120000e3, 2.480000e4, 6.760000e4, 1.840000e5,
             3.030000e5, 5.000000e5, 8.230000e5, 1.353000e6, 1.738000e6, 2.232000e6,
             2.865000e6, 3.680000e6, 6.070000e6, 7.790000e6, 1.000000e7, 1.200000e7,
             1.350000e7, 1.500000e7, 1.700000e7};
             std::vector<double> egg = 
            {1.000000e4, 1.000000e5, 5.000000e5, 1.000000e6, 2.000000e6, 3.000000e6,
             4.000000e6, 5.000000e6, 6.000000e6, 7.000000e6, 8.000000e6, 9.000000e6, 
             2.000000e7};

            section::gType<1, 451> chunk(zaid, awr, zero1, nz, gid, ntw, temp, zero2,
                                        ngn, ngg, nw, zero3, zero4, sigz, egn, egg);
            THEN( "a section::gType<1,451> can be constructed and "
                 "members can be tested") {
                verifyChunk(chunk);
            } // THEN

            THEN("it can be printed") {
                std::string buffer;
                auto output = std::back_inserter(buffer);
                chunk.print(output, 9228, 1);

                CHECK(buffer == sectionString);
            } // THEN
        } // WHEN
            
        WHEN( "the data is being read from a string/stream with a valid FEND") {

            auto begin = sectionString.begin();
            auto end = sectionString.end();
            long lineNumber = 1;
            HeadRecord head(begin, end, lineNumber);

            section::gType<1, 451> chunk(head, begin, end, lineNumber, 9228);

            THEN("a section gType<1,451> can be constructed and "
                 "members can be tested") {
                verifyChunk(chunk);
            } // THEN

            THEN("it can be printed") {
                std::string buffer;
                auto output = std::back_inserter(buffer);
                chunk.print(output, 9228, 1);
                
                CHECK(buffer == sectionString);
            } // THEN
        } // WHEN
    } // GIVEN
} // SCENARIO

std::string chunk() {

    return
    " 9.223500+4 2.330248+2          0          1         -1          19228 1451     \n"
    " 2.936000+2 0.000000+0         30         12         46          09228 1451     \n"
    " 0.000000+0 1.00000+10 1.390000-4 1.520000-1 4.140000-1 1.130000+09228 1451     \n"
    " 3.060000+0 8.320000+0 2.260000+1 6.140000+1 1.670000+2 4.540000+29228 1451     \n"
    " 1.235000+3 3.350000+3 9.120000+3 2.480000+4 6.760000+4 1.840000+59228 1451     \n"
    " 3.030000+5 5.000000+5 8.230000+5 1.353000+6 1.738000+6 2.232000+69228 1451     \n"
    " 2.865000+6 3.680000+6 6.070000+6 7.790000+6 1.000000+7 1.200000+79228 1451     \n"
    " 1.350000+7 1.500000+7 1.700000+7 1.000000+4 1.000000+5 5.000000+59228 1451     \n"
    " 1.000000+6 2.000000+6 3.000000+6 4.000000+6 5.000000+6 6.000000+69228 1451     \n"
    " 7.000000+6 8.000000+6 9.000000+6 2.000000+7                      9228 1451     \n";
}

std::string validFEND() {
  return
    "                                                                  9228 0  0     \n";
}

void verifyChunk(const section::gType<1,451>& chunk) {
    // CHECK(451 == chunk.MT());
    CHECK(92235 == chunk.ZA());
    CHECK(30 == chunk.NGN());
    CHECK(12 == chunk.NGG());
    CHECK(46 == chunk.NW());
    CHECK(-1 == chunk.GID());
    CHECK(1 == chunk.NZ());
    CHECK_THAT(1e10, WithinRel(chunk.SIGZ()[0]));
    std::vector<double> egn = 
            {1.390000e-4, 1.520000e-1, 4.140000e-1, 1.130000,
             3.060000, 8.320000, 2.260000e1, 6.140000e1, 1.670000e2, 4.540000e2,
             1.235000e3, 3.350000e3, 9.120000e3, 2.480000e4, 6.760000e4, 1.840000e5,
             3.030000e5, 5.000000e5, 8.230000e5, 1.353000e6, 1.738000e6, 2.232000e6,
             2.865000e6, 3.680000e6, 6.070000e6, 7.790000e6, 1.000000e7, 1.200000e7,
             1.350000e7, 1.500000e7, 1.700000e7};
    std::vector<double> egg = 
            {1.000000e4, 1.000000e5, 5.000000e5, 1.000000e6, 2.000000e6, 3.000000e6,
             4.000000e6, 5.000000e6, 6.000000e6, 7.000000e6, 8.000000e6, 9.000000e6, 
             2.000000e7};
    for (size_t i = 0; i < chunk.NGN() + 1; i++) {
        CHECK_THAT(egn[i], WithinRel(chunk.EGN()[i]));
    }
    for (size_t i = 0; i < chunk.NGG() + 1; i++) {
        CHECK_THAT(egg[i], WithinRel(chunk.EGG()[i]));
    }
    CHECK(46 == chunk.SIGZ().size() + chunk.EGN().size() + chunk.EGG().size() + 1);

}
