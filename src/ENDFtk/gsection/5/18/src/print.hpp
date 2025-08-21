template < typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {

  int MT = 18;
  ControlRecord( this->ZA(), this->AWR(), 1, this->NZ(),
                 this->LR(), this->NGN() ).print( it, MAT, MF, MT );
  auto record = makeRecord( this->temp_, this->chi_ );
  record.print( it, MAT, MF, MT );
  SEND( MAT, MF ).print( it );
}