static auto
makeVectors( const std::vector< DataRecord >& records, int nmoments,
             int ndilutions, int ngroups ) {

  std::vector< unsigned int > groups( ngroups );
  std::iota( groups.begin(), groups.end(), 1 );

  std::vector< std::vector< std::vector< double > > > flux;
  std::vector< std::vector< std::vector< double > > > sigma;
  std::vector< std::vector< std::vector< double > > > ratio;
  double temp;

  if ( records.size() != 0 ) {

    bool has_ratios = records.front().NG2() == 3 ? true : false;
    temp = records.front().TEMP();

    flux.resize( nmoments );
    sigma.resize( nmoments );
    if ( has_ratios ) {

      ratio.resize( nmoments );
    }

    for ( const auto& record : records ) {

      auto g = record.IG() - 1;
      for ( unsigned int l = 0; l < nmoments; ++l ) {

        if ( flux[l].size() == 0 ) {

          flux[l].resize( ndilutions );
          sigma[l].resize( ndilutions );
          if ( has_ratios ) { ratio[l].resize( ndilutions ); }
        }

        for ( unsigned int z = 0; z < ndilutions; ++z ) {

          if (flux[l][z].size() == 0 ) {

            flux[l][z] = std::vector< double >( ngroups, 0. );
            sigma[l][z] = std::vector< double >( ngroups, 0. );
            if ( has_ratios ) { ratio[l][z] = std::vector< double >( ngroups, 0.); }
          }

          std::size_t index = z * nmoments + l;
          flux[l][z][g] = record.list()[ index ];
          if ( has_ratios ) {

            ratio[l][z][g] = record.list()[ index + 1 ];
            sigma[l][z][g] = record.list()[ nmoments * ndilutions * 2 + index ];
          }
          else {

            sigma[l][z][g] = record.list()[ nmoments * ndilutions + index ];
          }
        }
      }
    }
  }

  return std::make_tuple( temp, std::move( groups ), std::move( flux ),
                          std::move( sigma ), std::move( ratio ) );

}