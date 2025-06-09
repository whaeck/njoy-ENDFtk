#ifndef NJOY_ENDFTK_GSECTION_1_451
#define NJOY_ENDFTK_GSECTION_1_451

#include "tools/std20/views.hpp"
#include "ENDFtk/macros.hpp"
#include "ENDFtk/TextRecord.hpp"
#include "ENDFtk/HeadRecord.hpp"
#include "ENDFtk/ControlRecord.hpp"
#include "ENDFtk/ListRecord.hpp"
#include "ENDFtk/readSequence.hpp"
#include "ENDFtk/section.hpp"

namespace njoy {
namespace ENDFtk {
namespace section {

    template<>
    class ENDFTK_PYTHON_EXPORT gType< 1, 451> :
        protected BaseWithoutMT<gType<1,451>> {

        friend BaseWithoutMT<gType<1, 451>>;

        /* fields */
        int nz_;
        int gid_;
        int ntw_;
        ListRecord parameters_;

        /* auxiliary functions */
        #include "ENDFtk/gsection/1/451/src/makeParameters.hpp"
        #include "ENDFtk/gsection/1/451/src/readParameters.hpp"
        

    public:

        /* constructor */
        #include "ENDFtk/gsection/1/451/src/ctor.hpp"

        /* methods */

        /**
         *  @brief Return the number of dilution values
         */
        int NZ() const {return this->nz_;}
        
        /**
         *  @brief Return the number of dilution values
         */
        int getNumberDilutions() const {return this->NZ();}

        /**
         *  @brief Return the GENDF file ID
         */
        int GID() const {return this->gid_;}

        /**
         *  @brief Return the GENDF file ID
         */        
        int getGendfId() const {return this->GID();}

        /**
         *  @brief Return the number of title words (deprecated?)
         */
        int NTW() const {return this->ntw_;}

        /**
         *  @brief Return the number of title words 
         */
        int getNumberTitleWords() const {return this->NTW();}

        /**
         *  @brief Return the temperature
         */
        double TEMPIN() const {return this->parameters_.C1();}

        /**
         *  @brief Return the temperature
         */
        double getEvaluatedTemperature() const {return this->TEMPIN();}

        /**
         *  @brief Return the number of neutron energy groups
         */   
        int NGN() const {return this->parameters_.L1();}

        /**
         *  @brief Return the number of neutron energy groups
         */        
        int getNumberNeutronGroups() const {return this->NGN();}

        /**
         *  @brief Return the number of photon energy groups
         */        
        int NGG() const {return this->parameters_.L2();}

        /**
         *  @brief Return the number of photon energy groups
         */        
        int getNumberPhotonGroups() const {return this->NGG();}

        /**
         *  @brief Return the number of words in list
         */        
        int NW() const {return this->parameters_.NPL();}

        /**
         *  @brief Return the number of words in list
         */        
        int getNumberWords() const {return this->NW();}

        /**
         *  @brief Return the dilution values
         */        
        std::vector<double> SIGZ() const {
            using namespace njoy::tools;
            auto range = this->parameters_.list() | std20::views::drop(1) | std20::views::take(this->nz_);
            return std::vector<double>(range.begin(), range.end());
        }

        /**
         *  @brief Return the dilution values
         */   
        std::vector<double> getDilutionValues() const {return this->SIGZ();}

        /**
         *  @brief Return the neutron energy edges
         */   
        std::vector<double> EGN() const {
            using namespace njoy::tools;
            auto range = this->parameters_.list() | std20::views::drop(this->nz_ + 1 ) | std20::views::take(this->NGN() + 1);
            return std::vector<double>(range.begin(), range.end());
        }

        /**
         *  @brief Return the neutron energy edges
         */   
        std::vector<double> getNeutronEnergyEdges() const {return this->EGN();}

        /**
         *  @brief Return the photon energy edges
         */   
        std::vector<double> EGG() const {
            using namespace njoy::tools;
            auto range = this->parameters_.list() | std20::views::drop(this->nz_ + this->NGN() + 2)
            | std20::views::take(this->NGG() + 1);
            return std::vector<double>(range.begin(), range.end());
        }

        /**
         *  @brief Return the photon energy edges
         */   
        std::vector<double> getPhotonEnergyEdges() const {return this->EGG();}
        
        // /** 
        //  *  @brief Return the index of available files and sections
        //  */
        // auto index() const{
        //     using namespace njoy::tools;
        //     return std20::views::all( this->index_);
        // }

        #include "ENDFtk/gsection/1/451/src/print.hpp"

        /**
         *  @brief Return the section number
         */   
        // static constexpr int getSectionNumber() {return 451;}
        

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