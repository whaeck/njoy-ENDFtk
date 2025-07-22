template< typename Iterator >
static auto
readRecord( Iterator& it, const Iterator& end, long& lineNumber, int MAT, int MF, int MT ) {
    // DataRecord record;
    // record( it, end, lineNumber, MAT, MF, MT);
    return DataRecord( it, end, lineNumber, MAT, MF, MT );
}