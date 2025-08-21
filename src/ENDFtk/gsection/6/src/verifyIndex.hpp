void verifyIndex( std::size_t moment, std::size_t dilution ) const {

  auto nmoments = this->matrix_.size();
  auto ndilutions = this->matrix_.front().size();

  if ( ( nmoments <= moment ) || ( ndilutions <= dilution ) ) {

    Log::error( "The moment and/or dilution index are out of range" );
    Log::info( "Total number of moments: {}, requested index: {}", nmoments, moment );
    Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
    throw std::exception();
  }
}

void verifyIndex( std::size_t dilution ) const {

  auto ndilutions = this->matrix_.front().size();

  if ( ndilutions <= dilution ) {

    Log::error( "The dilution index is out of range" );
    Log::info( "Total number of dilutions: {}, requested index: {}", ndilutions, dilution );
    throw std::exception();
  }
}
