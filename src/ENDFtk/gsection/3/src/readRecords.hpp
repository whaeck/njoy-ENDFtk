template< typename Iterator >
static auto readRecords( Iterator& it, const Iterator& end, long& lineNumber,
                         int MAT, int MF, int MT, int NGN ) {

  std::vector< DataRecord > records;
  do {

    records.emplace_back( it, end, lineNumber, MAT, MF, MT );
  }
  while ( records.back().IG() < NGN );

  return records;
}