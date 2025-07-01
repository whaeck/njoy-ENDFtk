/**
 *  @brief Constructor for an empty file
 *
 *  @param[in] mat    the MAT number of the file
 *  @param[in] mf     the MF number of the file
 */
GFile( unsigned int mat, unsigned int mf ) :
  mat_( mat ), mf_( mf ), sections_() {}

/**
 *  @brief Constructor
 *
 *  @param[in] mat        the MAT number of the file
 *  @param[in] mf         the MF number of the file
 *  @param[in] sections   the sections of the file
 */
GFile( unsigned int mat, unsigned int mf,
       std::list< GSection >&& sections ) :
  mat_( mat ), mf_( mf ), sections_( std::move( sections ) ) {}
