/**
 *  @brief Constructor from parameters for delayed fission spectrum
 * 
 *  @param[in]  mt          the section number
 *  @param[in]  zaid        the ZAID identifier
 *  @param[in]  awr         the atomic weight ration
 *  @param[in]  lr          the break-up identifier flag
 *  @param[in]  temp        the temperature 
 *  @param[in]  ng2         number of secondary positions (needed for clipped records)
 *  @param[in]  chi         the delayed neutron spectrum  
 *  @param[in]  lambda      the time constants
 */
GType( int mt, int zaid, double awr, int lr, double temp, int ng2,
       std::vector< std::vector< double > > chi,
       std::vector< double > lambda ) :
    Base( zaid, awr, mt ),
    lr_( lr ),
    temp_( temp ),
    ng2_( ng2 ),
    lambda_( std::move( lambda ) ),
    chi_( std::move( chi ) ) {}

/**
 *  @brief Constructor from parameters for prompt fission spectrum
 *  
 *  @param[in]  mt          the section number
 *  @param[in]  zaid        the ZAID identifier
 *  @param[in]  awr         the atomic weight ration
 *  @param[in]  lr          the break-up identifier flag
 *  @param[in]  temp        the temperature 
 *  @param[in]  ng2         the number of secondary positions (needed for clipped records)
 *  @param[in]  chi         the prompt neutron spectrum 
 */
GType( int mt, int zaid, double awr, int lr, double temp, int ng2,
       std::vector< std::vector< double > > chi ) :
    Base( zaid, awr, mt ),
    lr_( lr ),
    temp_( temp ),
    ng2_( ng2 ),
    chi_( std::move( chi ) ) {}

private:

GType( int mt, int zaid, double awr, int lr,
       std::tuple< double,
                   int,
                   std::vector< std::vector< double > >,
                   std::vector< double > >&& data ) :
    GType( mt, zaid, awr, lr,
           std::move( std::get<0>( data ) ),        // temp
           std::move( std::get<1>( data ) ),        // ng2
           std::move( std::get<2>( data ) ),        // chi
           std::move( std::get<3>( data ) ) ) {}    // lambda
    
GType( int mt, int zaid, double awr, int nt, int lr, int ngn,
       DataRecord&& record ) :
    GType( mt, zaid, awr, lr,
           makeVectors( record, nt, ngn ) ) {}

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
template<typename Iterator>
GType(const HEAD& head,
      Iterator& begin,
      const Iterator& end,
      long& lineNumber,
      int MAT)
    try:
        GType( head.MT(), head.ZA(), head.AWR(), head.L1(),
               head.N1(), head.N2(),
        readRecord( begin, end, lineNumber, head.MAT(), head.MF(),
                    head.MT() ) ) {
        this->readSEND( begin, end, lineNumber, MAT, head.MF() );
    }
    catch(std::exception& e) {
        Log::info("Encountered error while reading section {} of file {} fo material {}"
                  " in GENDF file.", head.MT(), head.MF(), head.MAT());
        throw e;
    }
    
