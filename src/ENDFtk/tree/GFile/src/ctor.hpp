/**
 *  @brief Constructor
 *
 *  @param[in] mat    the MAT number of the file
 *  @param[in] mf     the MF number of the file
 */
GFile( unsigned int mat, unsigned int mf,
       std::list< GSection >&& sections ) :
  mat_( mat ), mf_( mf ), sections_( std::move( sections ) ) {}
