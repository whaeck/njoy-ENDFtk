#ifndef NJOY_ENDFTK_GSECTION_1_451
#define NJOY_ENDFTK_GSECTION_1_451

// system includes

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 1, 451 > : protected BaseWithoutMT< GType< 1, 451 > > {

    friend BaseWithoutMT< GType< 1, 451 > >;

    /* fields */
    int nz_;
    ListRecord parameters_;

    /* auxiliary functions */
    #include "ENDFtk/gsection/1/451/src/makeParameters.hpp"

  public:

    /* constructor */
    #include "ENDFtk/gsection/1/451/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of dilution values
     */
    int NZ() const { return this->nz_; }

    /**
     *  @brief Return the number of dilution values
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the temperature
     */
    double TEMPIN() const { return this->parameters_.C1(); }

    /**
     *  @brief Return the temperature
     */
    double temperature() const {return this->TEMPIN();}

    /**
     *  @brief Return the number of neutron energy groups
     */
    int NGN() const { return this->parameters_.L1(); }

    /**
     *  @brief Return the number of neutron energy groups
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the number of photon energy groups
     */
    int NGG() const { return this->parameters_.L2(); }

    /**
     *  @brief Return the number of photon energy groups
     */
    int numberPhotonGroups() const { return this->NGG(); }

    /**
     *  @brief Return the dilution values
     */
    auto SIGZ() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( 1 )
                                      | std20::views::take( this->NZ() );
    }

    /**
     *  @brief Return the dilution values
     */
    auto dilutionValues() const { return this->SIGZ(); }

    /**
     *  @brief Return the neutron energy edges
     */
    auto EGN() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( 1 + this->NZ() )
                                      | std20::views::take( this->NGN() + 1 );
    }

    /**
     *  @brief Return the neutron energy edges
     */
    auto neutronStructure() const { return this->EGN(); }

    /**
     *  @brief Return the photon energy edges
     */
    auto EGG() const {

      using namespace njoy::tools;
      return this->parameters_.list() | std20::views::drop( 1 + this->NZ() + this->NGN() + 1 )
                                      | std20::views::take( this->NGG() + 1 );
    }

    /**
     *  @brief Return the photon energy edges
     */
    auto photonStructure() const { return this->EGG(); }

    #include "ENDFtk/gsection/1/451/src/print.hpp"

    /**
     *  @brief Return the section number
     */
    static constexpr int sectionNumber() { return 451; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // gsection namespace
} // ENDFtk namespace
} // njoy namespace

#endif