#ifndef NJOY_ENDFTK_TREE_FROMFILE
#define NJOY_ENDFTK_TREE_FROMFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "tools/Log.hpp"
#include "ENDFtk/tree/Tape.hpp"

namespace njoy {
namespace ENDFtk {
namespace tree {

  /**
   *  @brief Factory function to make a tape from a file
   *
   *  @param[in] filename   the file name
   */
  inline auto fromFile( const std::string& filename ) {

    std::string content;
    std::ifstream in( filename,
                      std::ios::in | std::ios::binary | std::ios::ate );
    if ( not in ) {

      Log::error( "Could not open file \'{}\'", filename );
      throw std::exception();
    }

    const auto file_size = in.tellg();
    in.seekg( 0, std::ios::beg );
    content.resize( file_size / sizeof( char ) );
    in.read( &( content[ 0 ] ), file_size );
    return njoy::ENDFtk::tree::Tape( content );
  }

} // tree namespace
} // ENDFtk namespace
} // njoy namespace

#endif
