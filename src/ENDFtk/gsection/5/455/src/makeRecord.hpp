static auto
makeRecord( double temp,
            int ng2,
            const std::vector< double >& lambda,
            const std::vector< std::vector< double > >& chi ) {

    // int nz is always one for this section
    int nz = 1;
    int ig2lo = 1;
    auto ntimes = lambda.size();
    unsigned int ngroups = chi.front().size();

    std::vector < double > list;
    list = std::move( lambda );
    for  ( unsigned int g = 0; g < ( ng2 - 1 ); ++g ) {
        for ( unsigned int t = 0; t < ntimes; ++t ) {
            list.emplace_back( chi[t][g] );

        }
    }
    
    return DataRecord( temp, ng2, ig2lo, ngroups, std::move ( list ) );
}