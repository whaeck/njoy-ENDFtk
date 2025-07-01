/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the file to be returned
 */
const GFile& file( int mf ) const {

  auto iter = this->find( mf );
  if ( iter != this->files_.end() ) {

    return *iter;
  }

  Log::error( "The requested file (MF{}) is not present "
              "in the GENDF file tree", mf );
  throw std::exception();
}

/**
 *  @brief Return the file with the requested MF number
 *
 *  @param[in]   mf   the MF number of the file to be returned
 */
GFile& file( int mf ) {

  return const_cast< GFile& >
         ( const_cast< const GMaterial& >( *this ).file( mf ) );
}
