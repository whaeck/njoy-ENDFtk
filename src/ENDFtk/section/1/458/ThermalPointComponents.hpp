/**
 *  @class
 *  @brief Thermal point evaluation for fission energy release components
 *
 *  The thermal point evaluation for fission energy release components uses
 *  analytical functions to model dependence on incident neutron energy.
 *
 *  See ENDF102, section 1.5 for more information.
 */
class ThermalPointComponents : protected ListRecord {

  /* auxiliary functions */
  #include "ENDFtk/section/1/458/ThermalPointComponents/src/verify.hpp"

public:

  /* constructor */
  #include "ENDFtk/section/1/458/ThermalPointComponents/src/ctor.hpp"

  /* methods */

  static constexpr int LFC() { return 0; }
  static constexpr int NPLY() { return 0; }
  static constexpr int NFC() { return 0; }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto E() const {

    return ListRecord::list() | ranges::view::chunk( 2 );
  }

  /**
   *  @brief Return the energy release values and their uncertainties
   *
   *  This returns a range of pairs (the energy release value and its
   *  uncertainty)
   */
  auto energyRelease() const { return this->E(); }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto EFR() const { return this->E()[0]; }

  /**
   *  @brief Return the kinetic energy of the fission fragments and its
   *         uncertainty
   */
  auto fissionFragments() const { return this->E()[0]; }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto ENP() const { return this->E()[1]; }

  /**
   *  @brief Return the kinetic energy of the prompt fission neutrons and its
   *         uncertainty
   */
  auto promptNeutrons() const { return this->E()[1]; }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto END() const { return this->E()[2]; }

  /**
   *  @brief Return the kinetic energy of the delayed fission neutrons and its
   *         uncertainty
   */
  auto delayedNeutrons() const { return this->E()[2]; }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto EGP() const { return this->E()[3]; }

  /**
   *  @brief Return the energy release by prompt gammas and its uncertainty
   */
  auto promptGammas() const { return this->E()[3]; }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto EGD() const { return this->E()[4]; }

  /**
   *  @brief Return the energy release by delayed gammas and its uncertainty
   */
  auto delayedGammas() const { return this->E()[4]; }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto EB() const  { return this->E()[5]; }

  /**
   *  @brief Return the energy release by delayed betas and its uncertainty
   */
  auto delayedBetas() const  { return this->E()[5]; }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto ENU() const { return this->E()[6]; }

  /**
   *  @brief Return the energy release by neutrinos and its uncertainty
   */
  auto neutrinos() const { return this->E()[6]; }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto ER() const  { return this->E()[7]; }

  /**
   *  @brief Return the total energy release minus the neutrino energy and its
   *         uncertainty
   */
  auto totalMinusNeutrinos() const  { return this->E()[7]; }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto ET() const  { return this->E()[8]; }

  /**
   *  @brief Return the total energy release and its uncertainty
   */
  auto total() const  { return this->E()[8]; }

  using ListRecord::NC;
  using ListRecord::print;
};
