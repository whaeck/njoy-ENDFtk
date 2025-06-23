// version for flux, sigma and ratios
static auto
vectorToRecords(double temp,
            std::vector< std::vector < std::vector < double > > > flux,
            std::vector< std::vector < std::vector < double > > > sigma, 
            std::vector< std::vector < std::vector < double > > > ratio) {

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

    // search for zeros and record their indices
    std::vector< unsigned int > indices = {ngroups};
    for ( int g = ngroups - 2; g >= 0; --g ) {

        // verify that all moments, dilutions have a group g that is zero
        bool allzero = true;
        for ( unsigned int l = 0; l < nmoments; ++l ) {
            for ( unsigned int z = 0; z < ndilutions; ++z ) {
                if (sigma[l][z][g] != 0.0) {
                    allzero = false;
                    break;
                }
            }
            if ( ! allzero ) {

                break;
            } 
        }

        // if they are all zero: erase it
        if ( allzero ) {

            for ( unsigned int l = 0; l < nmoments; ++l ) {
                for ( unsigned int z = 0; z < ndilutions; ++z ) {
                    
                    sigma[l][z].erase( sigma[l][z].begin() + g );
                    flux[l][z].erase( flux[l][z].begin() + g );
                    ratio[l][z].erase( ratio[l][z].begin() + g );
                } 
            }
        }

        indices.insert( indices.begin(), g + 1 );
    }


    return makeRecords(temp, indices, flux, sigma, ratio);

}

// version for flux and sigma
static auto
vectorToRecords(double temp,
            std::vector< std::vector < std::vector < double > > > flux,
            std::vector< std::vector < std::vector < double > > > sigma) {

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
    std::vector< unsigned int > indices = {ngroups};
    for ( int g = ngroups - 2; g >= 0; --g ) {

        // verify that all moments, dilutions have a group g that is zero
        bool allzero = true;
        for ( unsigned int l = 0; l < nmoments; ++l ) {
            for ( unsigned int z = 0; z < ndilutions; ++z ) {
                if (sigma[l][z][g] != 0.0) {
                    allzero = false;
                    break;
                }
            }
            if ( ! allzero ) {

                break;
            } 
        }

        // if they are all zero: erase it
        if ( allzero ) {

            for ( unsigned int l = 0; l < nmoments; ++l ) {
                for ( unsigned int z = 0; z < ndilutions; ++z ) {
                    
                    sigma[l][z].erase( sigma[l][z].begin() + g );
                    flux[l][z].erase( flux[l][z].begin() + g );

                } 
            }
        }

        indices.insert( indices.begin(), g + 1 );
    }

    return makeRecords(temp, indices, flux, sigma);

}
