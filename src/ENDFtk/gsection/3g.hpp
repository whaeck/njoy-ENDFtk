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
        std::vector<DataRecord> records_;

        /* auxiliary functions */
        #include "ENDFtk/gsection/3/src/makeRecords.hpp"
        
        /**
         *  @brief template function to extract data
         * 
         *  @tparam Functor     the lambda expression for the fluxes and sigmas.
         */
        template < typename Functor > 
        auto data( Functor functor ) const {
            using namespace njoy::tools;
            return this->records_ | std20::views::transform( functor ); 
            }

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
         *  @brief Return a group's DataRecord
         * 
         *  @param[in] group    the group index
         */
        const auto groupRecord(int group) const {
            return this->records_.at(group);
        }

        /**
         *  @brief Return the temperature of the material
         */
        double temperature() const { return this->groupRecord(0).TEMP(); }

        /**
         *  @brief Return the number of words contained in the DataRecord's list
         */
        int numberWords() const { return this->groupRecord(0).NW(); }

        /**
         *  @brief Return the group indices
         */
        auto groups() const {

            return this->data( [] ( auto&& record ) { return record.IG(); } ); 
        }

        /**
         *  @brief Return the group cross-sections
         *  
         *  @param[in] moment   the legendre moment requested
         *  @param[in] diltuion the dilution index requested
         */
        auto crossSection( int moment, int dilution ) const {
            int numMoments = this->NL();
            int block;
            if (this->numberWords() == 3) {
                block = this->numberWords() * 2 / 3;
            } else {
                block = this->numberWords() / 2;
            }
            int position = block + dilution * numMoments + moment;
            return this->data( [ position ] ( auto&& record) {
                return record.list()[ position ];
            });
        }

        auto ratio( int moment, int dilution ) const {
            if (this->numberWords() != 3) {
                throw std::runtime_error("Requested ratio for non-ratio qunatity!");
            } else {
                int numMoments = this->NL();
                int block = this->numberWords() / 2;
                int position = block + dilution * numMoments + moment;
            return this->data( [ position ] (auto&& record ) {
                return record.list()[ position ];
                }); 
            }
            
        }

        /**
         *  @brief Return the group fluxes
         */
        auto flux( int moment, int dilution ) const {
            int numMoments = this->NL();
            int position = dilution * numMoments + moment;
            return this->data( [ position ] ( auto&& record ) { 
                return record.list()[position];
            });
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