# Release Notes&mdash;ENDFtk
Given here are some release notes for ENDFtk.

## [ENDFtk v1.1.0](https://github.com/njoy/ENDFtk/pull/198)
This update adds additional interface functions to complete the human readable and ENDF speak interface for many objects:
  - the NBT() and INT() interface functions to complement the boundaries() and interpolants() functions already present in TAB1 and TAB2 style components
  - the numberInterpolationRegions() functions to complement the NR() function already present in TAB1 and TAB2 style components.

This update fixes the following issues:
  - Older versions of ENDFtk sometimes read numbers like '2.0000000+0' as 1.999999999 instead of 2. The disco library was replaced with a new version included in the tools library that fixes this issue. In addition to fixing this issue, parsing ENDF files is now 10-20% faster.

## [ENDFtk v1.0.1](https://github.com/njoy/ENDFtk/pull/195)
This update does not add any additional functionality.

This update fixes the following issues:
  - A compilation issue in a unit test that still used the old catch-adapter (see issue #193).
  - Macros for pybind11 were added where required so that other pybind11 bond libraries can accept ENDFtk components as input arguments on the python side (e.g. covariance matrice blocks). This is currently limited to all ENDFtk section components.

## [ENDFtk v1.0.0](https://github.com/njoy/ENDFtk/pull/192)
This release of ENDFtk has the following changes:
  - All ZA values in the interface (the ZA value in the HEAD records, the ZAP values in the MF6 and MF26 reaction products, etc.) are now changed to integer types instead of a floating point type
  - MF6 and MF26 now have additional functions that allow a user to look for specific reaction products
  - MF9 and MF10 now have additional functions that allow a user to look for specific excited states

The CMake files have also been updated to simplify adding new unit tests.

This release cleans up some of the dependencies and updates most of the dependencies to more recent versions. In particular the Catch2 unit testing framework was updated to version 3.3.2. All unit tests were updated to use better floating point comparison available in this version of Catch2. A number of NJOY dependencies have also been consolidated into a single new dependency (the NJOY tools library) to reduce the number of dependencies to a more manageable level.
