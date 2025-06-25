// version for flux, sigma and ratios
static auto
makeRecords(double temp,
            const std::vector< std::vector < std::vector < double > > >& flux,
            const std::vector< std::vector < std::vector < double > > >& sigma, 
            const std::vector< std::vector < std::vector < double > > >& ratio) {

    // ng2 is 3 for ratio quantities, and ig2lo appaers to be 1 for MF3
    int ng2 = 3;
    int ig2lo = 1; 
    // get sizes
    auto nmoments = flux.size();
    auto ndilutions = 0;
    unsigned int ngroups = 0;

    if (nmoments > 0) {
        ndilutions = flux.front().size();
        if (flux.front().size() > 0) {
            ngroups = flux.front().front().size();
        }
    }

    if ( nmoments != sigma.size() ) {
        // TODO: log error
        throw std::exception();
    }

    // check for correct dimensions
    for ( unsigned int l = 0; l < nmoments; ++l ) {
        if ( ndilutions != flux[l].size() && ndilutions != sigma[l].size() && ndilutions != ratio[l].size() ) {
            // TODO: log error
            throw std::exception();
        }
        for ( unsigned int z = 0; z < ndilutions; ++z) {
            if ( ngroups != flux[l][z].size() && ngroups != sigma[l][z].size() && ngroups!= ratio[l][z].size() ) {
                // TODO: log error
                throw std::exception();
            }
        }
    }

    // search for zeros and select what gets written
    std::vector< DataRecord > records;
    for ( int g = 0; g < ngroups; ++g ) {
        std::vector< double > list;
        std::vector< double > xs;
        std::vector< double > ratios;
        list.reserve( 3 * nmoments * ndilutions);
        xs.reserve( nmoments * ndilutions);
        ratios.reserve( nmoments * ndilutions);
        // verify that all moments, dilutions have a group g that is zero
        bool allzero = false;
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
            for ( unsigned int l = 0; l < nmoments; ++l ) {
                if (sigma[l][z][g] != 0.0 || g == ngroups) {
                    list.push_back( flux[l][z][g] );
                    xs.push_back( sigma[l][z][g] );
                    ratios.push_back( ratio[l][z][g]);
                }
            }
        }
        list.insert( list.end(), ratios.begin(), ratios.end() );
        list.insert( list.end(), xs.begin(), xs.end() );
        if (list.size() != 0) {
            records.emplace_back( temp, ng2, ig2lo, g + 1, std::move( list ));
        }
    }

    return records;

}

// version for flux and sigma
static auto
makeRecords(double temp,
            const std::vector< std::vector < std::vector < double > > >& flux,
            const std::vector< std::vector < std::vector < double > > >& sigma) {

    // ng2 is 2 for cross-sections and ig2lo appears to be 1 for MF3
    int ng2 = 2;
    int ig2lo = 1;
    // get sizes
    auto nmoments = flux.size();
    auto ndilutions = 0;
    unsigned int ngroups = 0;


    if (flux.size() > 0) {
        ndilutions = flux.front().size();
        if (flux.front().size() > 0) {
            ngroups = flux.front().front().size();
        }
    }

    if ( nmoments != sigma.size() ) {
        // TODO: log error
        throw std::exception();
    }

    // check for correct dimensions
    for ( unsigned int l = 0; l < nmoments; ++l ) {
        if ( ndilutions != flux[l].size() && ndilutions != sigma[l].size() ) {
            // TODO: log error
            throw std::exception();
        }
        for ( unsigned int z = 0; z < ndilutions; ++z) {
            if ( ngroups != flux[l][z].size() && ngroups != sigma[l][z].size() ) {
                // TODO: log error
                throw std::exception();
            }

        }
    }

    // search for zeros and record their indices
    std::vector< DataRecord > records;
    for ( int g = 0; g < ngroups; ++g ) {
        std::vector< double > list;
        std::vector< double > xs;
        list.reserve( 3 * nmoments * ndilutions);
        xs.reserve( nmoments * ndilutions);
        // verify that all moments, dilutions have a group g that is zero
        bool allzero = false;
        for ( unsigned int z = 0; z < ndilutions; ++z ) {
            for ( unsigned int l = 0; l < nmoments; ++l ) {
                if (sigma[l][z][g] != 0.0 || g == ngroups) {
                    list.push_back( flux[l][z][g] );
                    xs.push_back( sigma[l][z][g] );
                }
            }
        }
        list.insert( list.end(), xs.begin(), xs.end() );
        if (list.size() != 0) {
            records.emplace_back( temp, ng2, ig2lo, g + 1, std::move( list ));
        }
    }

    return records;

}
