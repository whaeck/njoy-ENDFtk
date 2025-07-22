// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/gsection/5g.hpp"
#include "definitions.hpp"

// namespace aliases
namespace python = pybind11;

void wrapGSection_5( python::module& module, python::module& ) {

    // type alias
    using GSection = njoy::ENDFtk::section::GType< 5 >;

    // create the section
    python::class_< GSection > gsection(
        module,
        "GSection",
        "MF5 gsection - neutron spectra"
    );

    // wrap section
    gsection
    .def(

        python::init< int, int, double, int, double, int,
                      std::vector< std::vector< double > >&&,
                      std::vector< double >&& >(),
        python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lr" ) = 0,
        python::arg( "temp" ), python::arg( "ng2" ), python::arg( "chi" ), python::arg( "time_constants" ),
        "Initialise the section\n\n"
        "Arguments:\n"
        "   self            the section\n"
        "   mt              the MT number\n"
        "   zaid            the ZA identifier\n"
        "   awr             the atomic weight ratio\n"
        "   lr              the complex breakup flag\n"
        "   temp            the temperature\n"
        "   ng2             number of secondary positions\n"
        "   time_constants  delayed neutron time constants (nt)\n"
        "   chi             delayed neutron spectra (nt, ngn)"
    )
    .def(

        python::init< int, int, double, int, double, int,
                      std::vector< std::vector< double > >&& >(),
        python::arg( "mt" ), python::arg( "zaid" ), python::arg( "awr" ), python::arg( "lr" ) = 0,
        python::arg( "temp" ), python::arg( "ng2" ), python::arg( "chi" ),
        "Initialise the section\n\n"
        "Arguments:\n"
        "   self        the section\n"
        "   mt          the MT number\n"
        "   zaid        the ZA identifier\n"
        "   awr         the atomic weight ratio\n"
        "   lr          the complex breakup flag\n"
        "   temp        the temperature\n"
        "   ng2         number of secondary positions\n"
        "   chi         prompt fission neutron spectra (1, ngn)"
    )
    .def_property_readonly(

        "NT",
        &GSection::NT,
        "The number of time constants"
    )
    .def_property_readonly(

        "number_time_constants",
        &GSection::numberTimeConstants,
        "The number of time constants"
    )
    .def_property_readonly(

        "NZ",
        &GSection::NZ,
        "The number of dilutions"
    )
    .def_property_readonly(

        "number_dilutions",
        &GSection::numberDilutions,
        "The number of dilutions"
    )
    .def_property_readonly(

        "LR",
        &GSection::LR,
        "The complex breakup flag"
    )
    .def_property_readonly(

        "break_up",
        &GSection::breakUp,
        "The complex breakup flag"
    )
    .def_property_readonly(

        "TEMP",
        &GSection::TEMP,
        "The temperature"
    )
    .def_property_readonly(

        "temperature",
        &GSection::temperature,
        "The temperature"
    )
    .def_property_readonly(

        "NGN",
        &GSection::NGN,
        "The number of neutron groups"
    )
    .def_property_readonly(

        "number_neutron_groups",
        &GSection::numberNeutronGroups,
        "The number of neutron groups"
    )
    .def_property_readonly(

        "time_constants",
        &GSection::lambda,
        "The delayed time constants"
    )
    .def(

        "chi",
        &GSection::chi,
        python::arg( "time_constant" ),
        "The neutron spectra for a given time constant. For prompt, time constant is 0."
    );

    addStandardGSectionDefinitions< GSection >( gsection );

}