/**
 *  @brief Constructor from parameters for prompt fission spectrum
 *
 *  @param[in]  zaid        the ZAID identifier
 *  @param[in]  awr         the atomic weight ration
 *  @param[in]  lr          the break-up identifier flag
 *  @param[in]  temp        the temperature
 *  @param[in]  chi         the prompt neutron spectrum
 */
GType( int zaid, double awr, int lr, double temp,
       std::vector< double > chi ) :
    BaseWithoutMT( zaid, awr ),
    lr_( lr ),
    temp_( temp ),
    chi_( std::move( chi ) ) {}

private:

GType( int zaid, double awr, int lr,
       std::tuple< double,
       std::vector< double > >&& data ) :
    GType( zaid, awr, lr,
           std::move( std::get< 0 >( data ) ),        // temp
           std::move( std::get< 1 >( data ) ) ) {}    // chi

GType( int zaid, double awr, int lr, int ngn,
       DataRecord&& record ) :
    GType( zaid, awr, lr,
           makeVectors( record, ngn ) ) {}

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
  try: GType( head.ZA(), head.AWR(), head.N1(), head.N2(),
              DataRecord( begin, end, lineNumber, head.MAT(), head.MF(), 18 ) ) {

    this->readSEND( begin, end, lineNumber, MAT, head.MF() );
  }
  catch(std::exception& e) {

    Log::info( "Encountered error while reading section {} of file {} fo material {}"
               " in GENDF file.", 18, head.MF(), head.MAT() );
    throw e;
  }