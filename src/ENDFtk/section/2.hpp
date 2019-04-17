template<>
class Type< 2 > : protected Base {
public:

  std::vector< resonanceParameters::Isotope > isotopes;
  #include "ENDFtk/section/2/src/readIsotopes.hpp"
  #include "ENDFtk/section/2/src/ctor.hpp"

  using Base::MT;
  using Base::ZA;
  using Base::atomicWeightRatio;

  #include "ENDFtk/section/2/src/print.hpp"
};
