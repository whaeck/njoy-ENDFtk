template< typename Iterator >
static auto
readRecord( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) {
    return DataRecord( it, end, lineNumber, MAT, MF, MT );
}