static std::vector< double >
generateList( std::vector< double >&& energies,
              std::vector< double >&& spins,
              std::vector< double >&& gn,
              std::vector< double >&& gg,
              std::vector< double >&& gfa,
              std::vector< double >&& gfb,
              std::vector< double >&& der,
              std::vector< double >&& dgn,
              std::vector< double >&& dgg,
              std::vector< double >&& dgfa,
              std::vector< double >&& dgfb ) {

  unsigned int nrs = energies.size();
  if ( ( spins.size() != nrs ) or
       ( gn.size() != nrs ) or ( gg.size() != nrs ) or
       ( gfa.size() != nrs ) or ( gfb.size() != nrs ) or
       ( der.size() != nrs ) or ( dgn.size() != nrs ) or
       ( dgg.size() != nrs ) or ( dgfa.size() != nrs ) or
       ( dgfb.size() != nrs ) ) {

    Log::info( "The number of resonances and the resonance parameters are not "
               "consistent" );
    Log::info( "NRSA value: {}", nrs );
    Log::info( "energies.size(): {}", energies.size() );
    Log::info( "spins.size(): {}", spins.size() );
    Log::info( "gn.size(): {}", gn.size() );
    Log::info( "gg.size(): {}", gg.size() );
    Log::info( "gfa.size(): {}", gfa.size() );
    Log::info( "gfb.size(): {}", gfb.size() );
    Log::info( "der.size(): {}", der.size() );
    Log::info( "dgn.size(): {}", dgn.size() );
    Log::info( "dgg.size(): {}", dgg.size() );
    Log::info( "dgfa.size(): {}", dgfa.size() );
    Log::info( "dgfb.size(): {}", dgfb.size() );
    throw std::exception();
  }

  std::vector< double > list;
  for ( unsigned int i = 0; i < nrs; ++i ) {

    list.push_back( energies[i] );
    list.push_back( spins[i] );
    list.push_back( gn[i] );
    list.push_back( gg[i] );
    list.push_back( gfa[i] );
    list.push_back( gfb[i] );
    list.push_back( der[i] );
    list.push_back( 0. );
    list.push_back( dgn[i] );
    list.push_back( dgg[i] );
    list.push_back( dgfa[i] );
    list.push_back( dgfb[i] );
  }
  return list;
}
