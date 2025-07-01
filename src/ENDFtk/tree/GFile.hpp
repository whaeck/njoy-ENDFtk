#ifndef NJOY_ENDFTK_TREE_FILE
#define NJOY_ENDFTK_TREE_FILE

// system includes
#include <list>

// other includes
#include "tools/std20/views.hpp"
#include "ENDFtk/tree/GSection.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @class
   *  @brief The GENDF tree file to index and access GENDF section data
   *
   *  This class represents a single file in a GENDF tape and contains the
   *  indexed GENDF sections from that file. It is created by the GENDF tree
   *  Material class and should not be directly constructed by a user.
   */
  class File {

    /* fields */
    int mat_;
    int mf_;
    std::list< GSection > sections_;

    /* auxiliary functions */

    // blatantly stolen from tree File
    #include "ENDFtk/tree/File/src/find.hpp"

  public:

    /* constructor */
    #include "ENDFtk/tree/GFile/src/ctor.hpp"

    /* methods */

    /**
     *  @brief Return MAT number of the file
     */
    int MAT() const { return this->mat_; }

    /**
     *  @brief Return MAT number of the file
     */
    int materialNumber() const { return this->MAT(); }

    /**
     *  @brief Return MF number of the file
     */
    int MF() const { return this->mf_; }

    /**
     *  @brief Return MF number of the file
     */
    int fileNumber() const { return this->MF(); }

    /**
     *  @brief Return all section numbers in the file
     */
    auto sectionNumbers() const {

      using namespace njoy::tools;
      return this->sections_ | std20::views::transform(
                                   [] ( auto&& section )
                                      { return section.sectionNumber(); } );
    }

    #include "ENDFtk/tree/GFile/src/section.hpp"

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    const Section& MT( int mt ) const { return this->section( mt ); }

    /**
     *  @brief Return the section with the requested MT number
     *
     *  @param[in]   mt   the MT number of the section to be returned
     */
    Section& MT( int mt ) { return this->section( mt ); }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasMT( int mt ) const {

      return this->find( mt ) != this->sections_.end();
    }

    /**
     *  @brief Return whether or not the file has a section with the given MT
     *         number
     *
     *  @param[in]   mt   the MT number of the section
     */
    bool hasSection( int mt ) const {  return this->hasMT( mt ); }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() const {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return all sections in the file
     */
    auto sections() {

      using namespace njoy::tools;
      return std20::views::all( this->sections_ );
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() const {

      return this->sections().begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() const {

      return this->sections().end();
    }

    /**
     *  @brief Return a begin iterator to all sections
     */
    auto begin() {

      return this->sections().begin();
    }

    /**
     *  @brief Return an end iterator to all sections
     */
    auto end() {

      return this->sections().end();
    }

    /**
     *  @brief Return the number of files in the materials
     */
    std::size_t size() const { return this->sections_.size(); }

    /**
     *  @brief Return the file's content
     */
    auto content() const {

      std::string content;
      for ( const auto& section : this->sections() ) {

        content += section.content();
      }

      return content;
    }

//    #include "ENDFtk/tree/File/src/remove.hpp"
//    #include "ENDFtk/tree/File/src/insertOrReplace.hpp"
//    #include "ENDFtk/tree/File/src/insert.hpp"

//    #include "ENDFtk/tree/File/src/parse.hpp"

    // blatantly copied from tree File
    #include "ENDFtk/tree/File/src/clean.hpp"
  };

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
