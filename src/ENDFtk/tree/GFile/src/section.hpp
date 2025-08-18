/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MT number of the section to be returned
 */
const GSection& section( int mt ) const {

  auto iter = this->find( mt );
  if ( iter != this->sections_.end() ) {

    return *iter;
  }

  Log::error( "The requested section (MF{} MT{}) is not present "
              "in the GENDF file tree",
              this->fileNumber(), mt );
  throw std::exception();
}

/**
 *  @brief Return the section with the requested MT number
 *
 *  @param[in]   mt   the MF number of the section to be returned
 */
GSection& section( int mt ) {

  return const_cast< GSection& >
         ( const_cast< const GFile& >( *this ).section( mt ) );
}
