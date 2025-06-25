#ifndef NJOY_ENDFTK_GSECTION_3
#define NJOY_ENDFTK_GSECTION_3


// other includes (TODO: remove uneccessary headers)
#include "tools/std20/views.hpp"
#include "ENDFtk/section/Base.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/section.hpp"
#include "tools/Log.hpp"
#include <numeric>

namespace njoy {
namespace ENDFtk {
namespace section {

    template<>
    class ENDFTK_PYTHON_EXPORT GType<3> :
        protected Base {

        /* fields */
        int nl_;
        int nz_;
        int lrflag_;
        int ngn_;
        double temp_;
        std::vector< unsigned int > groups_;
        std::vector< std::vector< std::vector< double > > > flux_;
        std::vector< std::vector< std::vector< double > > > sigma_;
        std::vector< std::vector< std::vector< double > > > ratio_;

        /* auxiliary functions */
        #include "ENDFtk/gsection/3/src/makeVectors.hpp"
        #include "ENDFtk/gsection/3/src/makeRecords.hpp"
        #include "ENDFtk/gsection/3/src/readRecords.hpp"

    public:

        /* constructor */
        #include "ENDFtk/gsection/3/src/ctor.hpp"
        
        /* methods */

        /**
         *  @brief Return the number of legendre moments.
         */
        int NL() const {return this->nl_;}

        /**
         *  @brief Return the number of legendre moments.
         */
        int numberMoments() const {return this->NL();}

        /**
         *  @brief Return the number of dilution values.
         */
        int NZ() const {return this->nz_;}

        /**
         *  @brief Return the number of dilution values.
         */        
        int numberDilutions() const {return this->NZ();}

        /**
         *  @brief Return the break up identifier flag.
         */
        int LRFLAG() const {return this->lrflag_;}

        /**
         *  @brief Return the break up identifier flag.
         */
        int breakUpID() const {return this->LRFLAG();}

        /**
         *  @brief Return the number of neutron energy bins
         */
        int NGN() const {return this->ngn_;}

        /**
         *  @brief Return the number of neutron energy bins
         */
        int numberNeutronGroups() const {return this->NGN();}

        /**
         *  @brief Return the temperature
         */
        double temperature() const {return this->temp_;}

        /**
         *  @brief Return the group indices
         */
        auto groups() const { return this->groups_;}

        /**
         *  @brief Return the group cross-sections
         *  
         *  @param[in] moment   the legendre moment requested
         *  @param[in] diltuion the dilution index requested
         */
        auto crossSection( int moment, int dilution ) const { 
            return this->sigma_[moment][dilution];
        }

        auto ratio( int moment, int dilution ) const {
            if (this->ratio_.size() != 0) {
                return this->ratio_[moment][dilution];
            } else {
                throw std::runtime_error("Requested ratio when ratios are not present!");
            }
        }

        /**
         *  @brief Return the group fluxes
         */
        auto flux( int moment, int dilution ) const {
            return this->flux_[moment][dilution];
        }

        #include "ENDFtk/gsection/3/src/print.hpp"

        using Base::MT;
        using Base::sectionNumber;
        using Base::ZA;
        using Base::AWR;
        using Base::atomicWeightRatio;

    };

} // section
} // ENDFtk
} // njoy

#endif