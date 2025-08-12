void verifyIndex( std::size_t moment, std::size_t dilution ) const {

  auto nmoments = this->sigma_.size();
  auto ndilutions = this->sigma_.front().size();

  if ( ( nmoments <= moment ) || ( ndilutions <= dilution ) ) {

    Log::error( "The moment and/or dilution index are out of range" );
    Log::info( "Total number of moments: {}, requested index: {}", nmoments, moment );
    Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
    throw std::exception();
  }
}