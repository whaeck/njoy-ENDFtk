#ifndef NJOY_ENDFTK_GSECTION_5_455
#define NJOY_ENDFTK_GSECTION_5_455

// system includes
#include <numeric>

// other includes
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/Log.hpp"


namespace njoy {
namespace ENDFtk {
namespace section {

  template <>
  class ENDFTK_PYTHON_EXPORT GType< 5, 455 > : protected BaseWithoutMT< GType< 5, 455 > > {

    friend BaseWithoutMT< GType< 5, 455 > >;

    /* fields */

    int lr_;
    double temp_;
    int ng2_;
    // for the delayed time constants (lambda) the size is nl which is the time index
    std::vector< double > lambda_;
    // for the neutron spectra, the size is ( nl, ng2 - 1 )
    std::vector< std::vector< double > > chi_;
    // NOTE: NZ is always 1 for MF5

    /* auxiliary functions */
    #include "ENDFtk/gsection/5/455/src/makeVectors.hpp"
    #include "ENDFtk/gsection/5/455/src/makeRecord.hpp"

  public:

    /* constructor */
    #include "ENDFtk/gsection/5/455/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return the number of time constants
     */
    int NT() const { return this->chi_.size(); }

    /**
     *  @brief Return the number of time constants
     */
    int numberTimeConstants() const { return this->NT(); }

    /**
     *  @brief Return the number of dilutions
     */
    int NZ() const { return 1; }

    /**
     *  @brief Return the number of dilutions
     */
    int numberDilutions() const { return this->NZ(); }

    /**
     *  @brief Return the break up identifier flag
     */
    int LR() const { return this->lr_; }

    /**
     *  @brief Return the break up identifier flag
     */
    int breakUp() const { return this->LR(); }

    /**
     *  @brief Return the temperature
     */
    double TEMP() const { return this->temp_; }

    /**
     *  @brief Return the temperature
     */
    double temperature() const { return this->TEMP(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int NGN() const { return this->chi_.front().size(); }

    /**
     *  @brief Return the number of neutron groups
     */
    int numberNeutronGroups() const { return this->NGN(); }

    /**
     *  @brief Return the delayed neutron time constants
     */
    const std::vector< double >& lambda() const { return this->lambda_;}

    /**
     *  @brief Return the delayed neutron spectra for a given time constant
     */
    const std::vector< double >& chi( int timeConstant ) const {
        return this->chi_[timeConstant];
    }

    #include "ENDFtk/gsection/5/455/src/print.hpp"

    /**
     *  @brief Return the section number
     */
    static constexpr int sectionNumber() { return 455; }

    using BaseWithoutMT::MT;
    using BaseWithoutMT::ZA;
    using BaseWithoutMT::targetIdentifier;
    using BaseWithoutMT::AWR;
    using BaseWithoutMT::atomicWeightRatio;
  };

} // section
} // ENDFtk
} // njoy

#endif