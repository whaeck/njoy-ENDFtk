static auto
makeRecords(double temp, 
            std::vector< unsigned int >& ig, const std::vector< std::vector< std::vector< double > > >& flux,  
            const std::vector< std::vector< std::vector< double > > >& sigma ) {

    // ng2 is 2 for cross-sections
    int ng2 = 2; 

    // get sizes
    auto nmoments = flux.size();
    auto ndilutions = 0;
    auto ngroups = ig.size();
    if ( flux.size() > 0 ) {

        ndilutions = flux.front().size();
    }

    // verify sizes
    if ( nmoments != sigma.size() ) {

        // ! @todo log error
        throw std::exception();
    }
    for ( unsigned int l = 0; l < nmoments; ++l ) {

        if ( ndilutions != flux[l].size() && ndilutions != sigma[l].size() ) {

            // ! @todo log error
            throw std::exception();
        }
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
    
            if ( ngroups != flux[l][z].size() && ndilutions != sigma[l][z].size() ) {
    
                // ! @todo log error
                throw std::exception();
            }
        }
    }

    std::vector< DataRecord > records;
    records.reserve( ngroups );
    for ( unsigned int g = 0; g < ngroups; ++g ) {

        std::vector< double > list;
        std::vector< double > xs;
        list.reserve( 2 * nmoments * ndilutions );
        xs.reserve( nmoments * ndilutions );
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
 
            for ( unsigned int l = 0; l < nmoments; ++l ) {
                list.push_back( flux[l][z][g] );
                xs.push_back( sigma[l][z][g] );
            }
        }
        list.insert( list.end(), xs.begin(), xs.end() );
        records.emplace_back( temp, ng2, ig.front(), ig[g], std::move( list ) );
    }

    return records;
}

static auto
makeRecords(double temp, 
            std::vector< unsigned int >& ig, const std::vector< std::vector< std::vector< double > > >& flux,  
            const std::vector< std::vector< std::vector< double > > >& sigma, 
            const std::vector< std::vector< std::vector<double> > >& ratio) {

    // ng2 is 3 for ratio quantities
    int ng2 = 3; 

    // get sizes
    auto nmoments = flux.size();
    auto ndilutions = 0;
    auto ngroups = ig.size();
    if ( flux.size() > 0 ) {

        ndilutions = flux.front().size();
    }

    // verify sizes
    if ( nmoments != sigma.size() ) {

        // ! @todo log error
        throw std::exception();
    }
    for ( unsigned int l = 0; l < nmoments; ++l ) {

        if ( ndilutions != flux[l].size() && ndilutions != sigma[l].size() && ndilutions != ratio[l].size() ) {

            // ! @todo log error
            throw std::exception();
        }
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
    
            if ( ngroups != flux[l][z].size() && ngroups != sigma[l][z].size() && ngroups != ratio[l][z].size() ) {
    
                // ! @todo log error
                throw std::exception();
            }
        }
    }

    std::vector< DataRecord > records;
    records.reserve( ngroups );
    for ( unsigned int g = 0; g < ngroups; ++g ) {

        std::vector< double > list;
        std::vector< double > xs;
        std::vector< double > ratios;
        list.reserve( 3 * nmoments * ndilutions );
        xs.reserve( nmoments * ndilutions );
        ratios.reserve(nmoments * ndilutions );
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
 
            for ( unsigned int l = 0; l < nmoments; ++l ) {

                list.push_back( flux[l][z][g] );
                xs.push_back( sigma[l][z][g] );
                ratios.push_back( ratio[l][z][g] );
            }
        }
        list.insert( list.end(), ratios.begin(), ratios.end() );
        list.insert( list.end(), xs.begin(), xs.end() );
        records.emplace_back( temp, ng2, ig.front(), ig[g], std::move( list ) );
    }

    return records;

}