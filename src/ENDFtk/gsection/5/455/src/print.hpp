template < typename OutputIterator >
void print( OutputIterator& it, int MAT, int MF ) const {
    int MT = 455;
    ControlRecord( this->ZA(), this->AWR(), this->NT(), this->NZ(),
                   this->LR(), this->NGN() ).print( it, MAT, MF, MT );
    auto record = makeRecord( this->temp_, this->ng2_, this->lambda_, this->chi_ );
    record.print( it, MAT, MF, MT );
    SEND( MAT, MF ).print( it );
}