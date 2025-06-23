template <typename OutputIterator >
void print(OutputIterator& it, int MAT, int MF, int MT) const {
    ControlRecord(this->ZA(), this->AWR(), this->NL(), this->NZ(),
                  this->LRFLAG(), this->NGN()).print(it, MAT, MF, MT);
    if ( this->ratio_.size() != 0  ) {
        auto records = vectorToRecords( this->temp_, this->flux_, this->sigma_, this->ratio_  );
        for (const auto record: records) {
            record.print(it, MAT, MF, MT);
        }
    }
    else {

    auto records = vectorToRecords( this->temp_, this->flux_, this->sigma_  );
        for (const auto record: records) {
            record.print(it, MAT, MF, MT);
        }
    }
    SEND(MAT, MF).print(it);
}