static auto
makeRecords( double temp, 
             const std::vector< std::vector< std::vector< double > > >& flux,
             const std::vector< std::vector< std::vector< std::vector< double > > > >& matrix) {
    
    size_t nmoments = flux.size();
    size_t ndilutions = 0;
    size_t ngroups = 0;

    if ( nmoments > 0 ) {
        ndilutions = flux.front().size();
        if ( flux.front().size() > 0 ) {
            ngroups = flux.front().front().size();
        }
    }

    if ( nmoments != matrix.size() ) {
        // TODO: log error
        throw std::exception();
    }
    
    // check for correct dimensions
    for ( unsigned int l = 0; l < nmoments; ++ l) {
        if ( ndilutions != flux[l].size() &&
             ndilutions != matrix[l].size() ) {
                // TODO: log error
                throw std::exception(); 
        }
        for ( unsigned int z = 0; z < ndilutions; ++z) {
            if ( ngroups != flux[l][z].size() && 
                 ngroups != matrix[l][z].size() ){
                    // TODO: log error
                    throw std::exception();
            }
        }
    }

    // search and find what gets written
    std::vector< DataRecord > records;
    for ( size_t g_i = 0; g_i < ngroups; ++g_i ) {

        std::vector< double > list;
        std::vector< double > xs;

        auto it = std::find_if( matrix[0][0][g_i].begin(), matrix[0][0][g_i].end(), 
                                [] ( auto&& val ) { return val != 0.0; } );

        int ig2lo = std::distance( matrix[0][0][g_i].begin(), it );
        int ng2 = 1;
        for ( size_t g_o = 0; g_o < ngroups; ++g_o ) {
            for ( size_t z = 0; z < ndilutions; ++z ) {
                for ( size_t l = 0; l < nmoments; ++l ) {

                    if ( flux[l][z][g_i] != 0.0 && g_o == g_i ) {
                        list.emplace_back( flux[l][z][g_i] );
                    } // endif

                    if ( g_o <= g_i && g_o >= ig2lo) {
                        xs.emplace_back( matrix[l][z][g_i][g_o] );
                    } // endif
                } // moments 
            } // dilutions
        } // outgoing erg
        ng2 += ( (g_i + 1) - ig2lo );
        ig2lo += 1; // need to correct from array index to GENDF index value.
        list.insert( list.end(), xs.begin(), xs.end() );
        if (list.size() != 0 ) {
            records.emplace_back( temp, ng2, ig2lo, g_i + 1, std::move( list ));
        }
    } // incident erg

    return records;
}
