/**
 *  @brief Constructor from parameters with probabilities
 * 
 *  @param[in]  mt              the section number
 *  @param[in]  zaid            the ZAID identifier
 *  @param[in]  awr             the atomic weight ratio
 *  @param[in]  nl              the number of legendre moments
 *  @param[in]  nz              the number of dilution values
 *  @param[in]  lrflag          the break-up identifier flag
 *  @param[in]  ngn             the number of neutron energy groups
 *  @param[in]  temp            the temperature
 *  @param[in]  groups          the group index
 *  @param[in]  flux            the group-wise flux
 *  @param[in]  matrix           the transfer matrices 
 *  @param[in]  probability     the probabilities
 */
GType(int mt, int zaid, double awr, int nl, int nz, int lrflag,
      int ngn, double temp, std::vector< unsigned int > groups,
      std::vector < std::vector< std::vector< double > > > flux,
      std::vector < std::vector< std::vector< std::vector< double > > > > matrix,
      std::vector < std::vector< std::vector< double > > > probability )
      :
      Base(zaid, awr, mt),
      nl_(nl),
      nz_(nz),
      lrflag_(lrflag),
      ngn_(ngn),
      temp_(temp),
      groups_(groups),
      flux_( std::move(flux) ),
      matrix_( std::move(matrix ) ),
      probability_( std::move( probability ) ) {}


/**
 *  @brief Constructor from parameters with probabilities (Note: IG = 0)
 * 
 *  @param[in]  mt              the section number
 *  @param[in]  zaid            the ZAID identifier
 *  @param[in]  awr             the atomic weight ratio
 *  @param[in]  nl              the number of legendre moments
 *  @param[in]  nz              the number of dilution values
 *  @param[in]  lrflag          the break-up identifier flag
 *  @param[in]  ngn             the number of neutron energy groups
 *  @param[in]  temp            the temperature
 *  @param[in]  groups          the group index
 *  @param[in]  flux            the group-wise flux
 *  @param[in]  matrix          the transfer matrices 
 */
GType( int mt, int zaid, double awr, int nl, int nz, int lrflag,
        int ngn, double temp, std::vector< unsigned int > groups,
        std::vector < std::vector < std::vector < double > > > flux,
        std::vector < std::vector< std::vector< std::vector< double > > > > matrix )
        :
        Base( zaid, awr, mt ),
        nl_( nl ),
        nz_( nz ),
        lrflag_( lrflag ),
        ngn_( ngn ),
        temp_( temp ),
        groups_( groups ),
        flux_( std::move( flux ) ) ,
        matrix_(std::move ( matrix ) )  {}

private:

    GType( int mt, int zaid, double awr, int nl, int nz, int lrflag, int ngn,
           std::tuple< double, 
                       std::vector< unsigned int >,
                       std::vector< std::vector< std::vector< double > > >,
                       std::vector< std::vector< std::vector< std::vector< double > > > >,
                       std::vector< std::vector< std::vector< double > > > >&&data)
        :
        GType( mt, zaid, awr, nl, nz, lrflag, ngn,
               std::move( std::get<0>( data ) ),        // temp
               std::move( std::get<1>( data ) ),        // groups
               std::move( std::get<2>( data ) ),        // flux
               std::move( std::get<3>( data ) ),        // matrix
               std::move( std::get<4>( data ) ) ) {}    // probability   
    
    GType( int mt, int zaid, double awr, int nl, int nz, int lrflag, int ngn,
           std::tuple< double,
                       std::vector< unsigned int >,
                       std::vector< std::vector< std::vector< double > > >,
                       std::vector< std::vector< std::vector< std::vector< double > > > > > && data)
        :
        GType( mt, zaid, awr, nl, nz, lrflag, ngn,
               std::move( std::get<0>( data ) ),        // temp
               std::move( std::get<1>( data ) ),        // groups
               std::move( std::get<2>( data ) ),        // flux
               std::move( std::get<3>( data ) ) ) {}    // matrix

    GType( int mt, int zaid, double awr, int nl, int nz, int lrflag, int ngn,
           std::vector< DataRecord >&& records)
           :
           GType( mt, zaid, awr, nl, nz, lrflag, ngn,
                  makeMatrices(records, nl, nz, ngn)) {}

public:
   /**
     *  @brief Constructor from buffer/string
     * 
     *  @tparam Iterator        buffer iterator
     * 
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the start for the iterator
     *  @param[in] end          the end for the iterator
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template< typename Iterator >
    GType( const HEAD& head,
           Iterator& begin,
           const Iterator& end,
           long& lineNumber,
           int MAT )
        try:
            GType( head.MT(), head.ZA(), head.AWR(), head.L1(),
                   head.L2(), head.N1(), head.N2(),
                   readRecords( begin, end, lineNumber, head.MAT(), head.MF(),
                              head.MT(), head.N2() ) ) {
                   this->readSEND(begin, end, lineNumber, MAT, head.MF());
                }
        catch(std::exception& e) {
            Log::info("Encountered error while reading section {} of file {} fo material {}"
                      " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }