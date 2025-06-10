template <typename OutputIterator >
void print(OutputIterator& it, int MAT, int MF, int MT) const {
    ControlRecord(this->ZA(), this->AWR(), this->NL(), this->NZ(),
                  this->LRFLAG(), this->NGN()).print(it, MAT, MF, MT);
    for (const auto record: records_) {
        record.print(it, MAT, MF, MT);
    }
    SEND(MAT, MF).print(it);
}