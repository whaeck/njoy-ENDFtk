// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "ENDFtk/tree/GTape.hpp"
#include "variants.hpp"

// namespace aliases
namespace python = pybind11;

void wrapTreeGSection( python::module& module, python::module& ) {

  // type aliases
  using Section = njoy::ENDFtk::tree::GSection;


  // wrap views created by this component

  // create the tree component
  python::class_< Section > tree(

    module,
    "GSection",
    "GENDF tree section"
  );

  // wrap the tree component
  // only copy is allowed since we do not want to create this object in python
  tree
  .def(

    python::init< const Section& >(),
    python::arg( "section" ),
    "Initialise the section with another section\n\n"
    "Arguments:\n"
    "    self       the section\n"
    "    section    the section to be copied"
  )
  .def_property_readonly(

    "MAT",
    &Section::MAT,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "material_number",
    &Section::materialNumber,
    "The MAT number of the section"
  )
  .def_property_readonly(

    "MF",
    &Section::MF,
    "The MF number of the section"
  )
  .def_property_readonly(

    "file_number",
    &Section::fileNumber,
    "The MF number of the section"
  )
  .def_property_readonly(

    "MT",
    &Section::MT,
    "The MT number of the section"
  )
  .def_property_readonly(

    "section_number",
    &Section::sectionNumber,
    "The MT number of the section"
  )
  .def_property_readonly(

    "content",
    &Section::content,
    "The content of the section"
  )
  .def_property_readonly(

    "NC",
    &Section::NC,
    "The number of lines in this section"
  )
  .def(

    "clean",
    &Section::clean,
    "Clean up the section\n\n"
    "This function removes the sequence numbers from the section."
  );
}
