#ifndef NJOY_ENDFTK_GSECTION_6
#define NJOY_ENDFTK_GSECTION_6

#include "ENDFtk/macros.hpp"
#include "tools/std20/views.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "tools/Log.hpp"
#include "ENDFtk/section.hpp"
#include <numeric>
#include <algorithm>
#include <iostream>

namespace njoy {
namespace ENDFtk {
namespace section {

    template < >
    class ENDFTK_PYTHON_EXPORT GType< 6 > :
        protected Base {

        /* fields */
        int nl_;
        int nz_;
        int lrflag_;
        int ngn_;
        double temp_;
        std::vector< unsigned int > groups_;
        std::vector< std::vector< std::vector< double > > > flux_;
        std::vector< std::vector< std::vector< std::vector< double > > > > matrix_;
        std::vector< std::vector< std::vector< double > > > probability_;
        
        /* auxiliary functions */
        #include "ENDFtk/gsection/6/src/makeMatrices.hpp"
        #include "ENDFtk/gsection/6/src/makeRecords.hpp"
        #include "ENDFtk/gsection/6/src/readRecords.hpp"

    public:

        /* constructor */
        #include "ENDFtk/gsection/6/src/ctor.hpp"
        
        /* methods */

        /**
         *  @brief Return the number of legendre moments.
         */
        int NL() const { return this->nl_; }

        /**
         *  @brief Return the number of legendre moments.
         */
        int numberMoments() const { return this->NL(); }

        /**
         *  @brief Return the number of dilution values.
         */
        int NZ() const { return this->nz_; }

        /**
         *  @brief Return the number of dilution values.
         */        
        int numberDilutions() const { return this->NZ(); }

        /**
         *  @brief Return the break up identifier flag.
         */
        int LRFLAG() const { return this->lrflag_; }

        /**
         *  @brief Return the break up identifier flag.
         */
        int breakUpID() const { return this->LRFLAG(); }

        /**
         *  @brief Return the number of neutron energy bins
         */
        int NGN() const { return this->ngn_; }

        /**
         *  @brief Return the number of neutron energy bins
         */
        int numberNeutronGroups() const { return this->NGN(); }

        /**
         *  @brief Return the temperature
         */
        double TEMP() const { return this->temp_; }
        
        /**
         *  @brief Return the temperature
         */
        double temperature() const { return this->TEMP(); }

        /**
         *  @brief Return the group indices
         */
        decltype(auto) groups() const { return this->groups_; }

        /**
         *  @brief Return the matrix for a given moment and dilution
         * 
         *  @param[in] moment   the legendre moment requested
         *  @param[in] diltuion the dilution index requested
         */
        decltype(auto) matrix(int moment, int dilution) const {
            return this->matrix_[moment][dilution];
        }
        
        /**
         *  @brief Return the flux
         * 
         *  @param[in] moment   the legendre moment requested
         *  @param[in] dilution the dilution index requested 
         */
        decltype(auto) flux(int moment, int dilution) const {
            return this->flux_[moment][dilution];
        }

        /**
         *  @brief Return the probabilities
         * 
         *  @param[in] moment   the legendre moment requested
         *  @param[in] dilution the dilution index requested 
         */
        decltype(auto) probability(int moment, int dilution) const {
            if ( this->probability_.size() != 0 ) {
                return this->probability_[moment][dilution];
            } else {
                throw std::runtime_error("Requested probabilities when they are not present!");
            }
        }
        #include "ENDFtk/gsection/6/src/print.hpp"

        using Base::MT;
        using Base::sectionNumber;
        using Base::ZA;
        using Base::targetIdentifier;
        using Base::AWR; 
        using Base::atomicWeightRatio;

        };

} // section
} // ENDFtk
} // njoy


#endif // NJOY_ENDFTK_GSECTION_6