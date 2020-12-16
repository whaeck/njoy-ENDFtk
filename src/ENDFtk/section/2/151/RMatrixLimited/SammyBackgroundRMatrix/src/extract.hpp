static std::array< double, 7 >
extract( ListRecord&& record ) {

  std::array< double, 7 > values;
  values[0] = record.C1();
  values[1] = record.C2();

  if ( record.NPL() != 5 ) {

    Log::info( "Expected NPL = 5 for the SAMMY parametrisation" );
    Log::info( "Found NPL value: {}", record.NPL() );
    throw std::exception();
  }

  auto list = record.list();
  std::copy_n( ranges::begin( list ), 5, values.begin() + 2 );

  return values;
}
