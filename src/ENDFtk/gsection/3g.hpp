#ifndef NJOY_ENDFTK_GSECTION_3
#define NJOY_ENDFTK_GSECTION_3


// other includes (TODO: remove uneccessary headers)
#include "tools/std20/views.hpp"
#include <map>
#include "ENDFtk/section/Base.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/DataRecord.hpp"
#include "ENDFtk/section.hpp"
#include "ENDFtk/readSequence.hpp"

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
        // TODO: Make this a vector of Data Records
        std::map<unsigned int, DataRecord> records_;

// TODO: implement abstraction; read in the data but format everything as vectors.
// This entails reading in GENDF -> internally sotre as vectors -> write out GENDF
//   auto column( unsigned int i ) const {

//     using namespace njoy::tools;
//     return this->records_
//              | std20::views::transform( [] ( auto&& record ) { return record.list()[i]; } );
//   }

        /* auxiliary functions */

    public:

        /* constructor */
        #include "ENDFtk/gsection/3/src/mapRecords.hpp"
        #include "ENDFtk/gsection/3/src/readRecords.hpp"
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
         *  @brief Return a group's DataRecord
         * 
         *  @param[in] group    the group index
         */
        const auto& groupRecord(int group) const {
            return this->records_.at(group);
        }

        /**
         *  @brief Check if group has DataRecord
         * 
         *  @param[in] group    the group index
         */
        bool hasRecord(int group) const {
            return this->records_.find(group) != this->records_.end();
        }

        /**
         *  @brief Return view of record data
         */
        auto RECORD() const {
            using namespace njoy::tools;
            return std20::ranges::views::values(this->records_);}
        
        /**
         *  @brief Return rxn value for given energy, legendre order, and dilution value
         * 
         *  @param[in] block    the block index
         *  @param[in] group    the group index
         *  @param[in] order    the legendre order
         *  @param[in] sigz_idx the dilution index
         */
        double value( int block, int group, int order, int sigz_idx) const{
            if (!this->hasRecord(group)) {
                return 0.0;
            }

            // else grab value
            const auto& values = this->groupRecord(group).data(block);
            return values[this->nl_ * sigz_idx + order];
        }

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