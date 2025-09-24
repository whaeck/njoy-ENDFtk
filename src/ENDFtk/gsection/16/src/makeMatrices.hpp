static auto
makeMatrices( const std::vector< DataRecord > records,
              int nmoments, int ndilutions, int ngroups, int max_gg ) {

  std::vector< std::vector< std::vector< double > > > flux( nmoments );
  std::vector< std::vector< std::vector < std::vector< double > > > > matrix( nmoments );

  double temp;
  if ( records.size() != 0 ) {

    temp = records.front().TEMP();
  }
  else {

    throw std::runtime_error( "Vector of DataRecord is empty!" );
  }

  for ( const auto& record : records ) {

    int g_i = record.IG() - 1;
    int group_block = 1;
    for ( size_t g_o = record.IG2LO() - 1; g_o < max_gg; ++g_o ) {

      for ( size_t l = 0; l < nmoments; ++l ) {

          if ( flux[l].size() == 0 ) {

            flux[l].resize( ndilutions );
            matrix[l].resize( ndilutions );
          } // endif
          for ( size_t z = 0; z < ndilutions; ++z ) {

            if ( flux[l][z].size() == 0 ) {

              flux[l][z] = std::vector< double >( ngroups,  0. );
              matrix[l][z] = std::vector< std::vector< double > >
                          ( ngroups, std::vector< double >( max_gg, 0. ) );
            }
            if ( g_o == record.IG2LO() - 1 ) {

              flux[l][z][g_i] = record.list()[ z * nmoments + l ];
            }
            if ( g_o >= ( record.IG2LO() - 1 ) && g_o < ( record.IG2LO() + record.NG2() - 2 ) ) {

              matrix[l][z][g_i][g_o] = record.list()[ group_block * ndilutions * nmoments + z * nmoments + l ];
            }
          } // dilutions
      } // moments
      group_block += 1;
    } // outgoing erg
  } // records

  return std::make_tuple( temp, flux, matrix );
}