static auto
makeMatrices(const std::vector< DataRecord > records,
             int nmoments, int ndilutions, int ngroups) {
    std::vector< unsigned int > groups( ngroups );
    std::iota(groups.begin(), groups.end(), 1);
    std::vector< std::vector < std::vector< double > > > flux( nmoments );
    std::vector< std::vector< std::vector < std::vector< double > > > >
    matrix( nmoments );
    std::vector< std::vector < double > > chi;
    double temp;
    int cutoff_ig;
    bool is_fission = records.front().IG() == 0 ? true: false;
    if ( records.size() != 0 ) {
        temp = records.front().TEMP();
    }
    else {
        throw std::runtime_error("Vector of DataRecords is empty!");
    }
    if ( is_fission ) {
        for ( const auto& record : records) {
            // prompt fission ( MT18 )
            if ( record.IG() == 0 ) {
                chi.resize( ndilutions );
                for ( size_t z = 0; z < ndilutions; ++z ) {
                    if ( chi[z].size() == 0 ) {
                        chi[z] = std::vector< double > (ngroups, 0. );
                    } // endif
                    for ( size_t g = 0; g < ngroups; ++g ) {
                        chi[z][g] = record.list()[ g * ndilutions + z];
                    }
                }
                continue;
            } // chi

            // entering compressed format
            if ( record.IG2LO() == 0 ) {
                // nl is 1 for MT 18
                flux[0].resize( ndilutions );
                matrix[0].resize( ndilutions );
                auto g_i = record.IG() - 1;
                cutoff_ig = record.IG();
                for ( size_t z = 0; z < ndilutions; ++z ) {
                    if ( flux[0][z].size() == 0) {
                        flux[0][z] = std::vector< double >( ngroups, 0. );
                        matrix[0][z] = std::vector< std::vector< double > >
                                (ngroups, std::vector< double >(ngroups, 0.));
                    }
                    flux[0][z][g_i] = record.list()[ z ];
                    for ( size_t g_o = 0; g_o < ngroups; ++g_o ) {
                        matrix[0][z][g_i][g_o] = record.list()[ ndilutions + z ] * chi[z][g_o];
                    } // outgoing erg
                } // dilutions
                continue;
            } // compressed format

            // uncompressed format of fission matrix
            else {
                auto g_i = record.IG() - 1; // g_i = incident_erg
                int group_block = 1;
                for ( size_t g_o = 0; g_o < ngroups; ++g_o ) { // g_o = outgoing_erg
                    for ( size_t z = 0; z < ndilutions; ++z ) {
                        if ( g_i == g_o ) {
                            flux[0][z][g_i] = record.list()[ z * nmoments];
                        }

                        matrix[0][z][g_i][g_o] = record.list()[group_block  * ndilutions * nmoments + z * nmoments ];
                    } // dilutions
                    group_block += 1;
                } // outgoing erg
            } // uncompressed format
        } // records
    } // is_fission

    // standard MF6 matrix
    else {
        for ( const auto& record : records) {
            auto g_i = record.IG() - 1; // g_i = incident_erg
            int group_block = 1;
            for ( size_t g_o = record.IG2LO() - 1; g_o <= g_i; ++g_o ) { // g_o = outgoing_erg
                for ( size_t l = 0; l < nmoments; ++l ) {
                    if ( flux[l].size() == 0 ) {
                        flux[l].resize( ndilutions );
                        matrix[l].resize( ndilutions );
                    } // endif
                    for ( size_t z = 0; z < ndilutions; ++z ) {
                        if ( flux[l][z].size() == 0 ) {
                            flux[l][z] = std::vector< double > (ngroups, 0. );
                            matrix[l][z] = std::vector< std::vector< double > >
                            (ngroups, std::vector< double >(ngroups, 0.));
                        } // endif
                        if ( g_i == g_o ) {
                            flux[l][z][g_i] = record.list()[ z * nmoments + l];
                        }
                        matrix[l][z][g_i][g_o] = record.list()[group_block  * ndilutions * nmoments + z * nmoments + l];
                    } // dilutions
                } // moments
                group_block += 1;
            } // outgoing erg
        } // records
    } // standard matrix


    return std::make_tuple(temp, groups, flux, matrix, cutoff_ig, chi);
}