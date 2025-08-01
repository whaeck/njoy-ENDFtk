static auto
makeRecords( double temp,
             const std::vector< std::vector< std::vector< double > > >& flux,
             const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix) {

    size_t nmoments = flux.size();
    size_t ndilutions = 0;
    size_t ngroups = 0;
    size_t max_gg = 0;
    if ( nmoments > 0 ) {
        ndilutions = flux.front().size();
        if ( flux.front().size() > 0 ) {
            ngroups = flux.front().front().size();

            if ( matrix.front().front().front().size() > 0 ) {
                max_gg = matrix.front().front().front().size();
            }
        }
    }

    std::vector< DataRecord > records;
    for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {
        std::vector< double > list;
        std::vector< double > yield;
        auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(),
                        [] (auto && val ) { return val != 0.0; } );
        int ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
        int ng2 = 1;
        for ( size_t g_o = 0; g_o < max_gg; ++g_o ) {

            for ( size_t l = 0; l < nmoments; ++l ) {
                for ( size_t z = 0; z < ndilutions; ++z ) {

                    if ( g_o == 0 ) {
                        list.emplace_back( flux[l][z][g_i] );
                    }
                    
                    if ( g_o >= ( ig2lo ) && matrix[l][z][g_i][g_o] != 0 ) {
                        yield.emplace_back( matrix[l][z][g_i][g_o] );
                    }

                } // dilutions
            } // moments
        } // g_o
        ng2 += ( (g_i + 1) - ig2lo);
        ig2lo += 1;
        list.insert( list.end(), yield.begin(), yield.end() );
        if ( list.size() != 0 ) {
            records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ) );
        }
    } // g_i

    return records;
}