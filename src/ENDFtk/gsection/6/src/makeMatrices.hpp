static auto
makeMatrices(const std::vector< DataRecord > records, 
             int nmoments, int ndilutions, int ngroups) {
    std::vector< unsigned int > groups( ngroups );
    std::iota(groups.begin(), groups.end(), 1);
    std::vector< std::vector < std::vector< double > > > flux( nmoments );
    std::vector< std::vector< std::vector < std::vector< double > > > >
    matrix( nmoments );
    std::vector< std::vector< std::vector < double > > > probability; 
    double temp;
    if ( records.size() != 0 ) {
        temp = records.front().TEMP();
    }
    else {
        throw std::runtime_error("Vector of DataRecords is empty!");
    }
    for ( const auto& record : records) {
        if ( record.IG() == 0 ) {
            std::cout << "I have encountered a record with probabilities" << std::endl;
            probability.resize( nmoments );
            for ( unsigned int l = 0; l < nmoments; ++l ) {
                if (probability[l].size() == 0) {
                    probability[l].resize( ndilutions );
                } // endif

                for ( unsigned int z = 0; z < ndilutions; ++z ) {
                    if ( probability[l][z].size() == 0 ) {
                        probability[l][z] = std::vector< double > (ngroups, 0. );
                    } // endif
                    for ( unsigned int g = 0; g < ngroups; ++g ) {
                        probability[l][z][g] = record.list()[ g * ndilutions + z];
                    } 
                }
            }
        } // endif 

        else {
            auto g_i = record.IG() - 1; // g_i = incident_erg
            // std::cout << "\ngroup :" << g_i << std::endl;
            int block = 1;
            for ( unsigned int g_o = record.IG2LO() - 1; g_o <= g_i; ++g_o ) { // g_o = outgoing_erg
                for ( unsigned int l = 0; l < nmoments; ++l ) {
                    if ( flux[l].size() == 0 ) {
                        flux[l].resize( ndilutions );
                        matrix[l].resize( ndilutions );
                    } // endif
                    for ( unsigned int z = 0; z < ndilutions; ++z ) {
                        if ( flux[l][z].size() == 0 ) {
                            flux[l][z] = std::vector< double > (ngroups, 0. );
                            matrix[l][z] = std::vector< std::vector< double > >
                            (ngroups, std::vector< double >(ngroups, 0.));
                        } // endif
                        if ( g_i == g_o ) {
                            flux[l][z][g_i] = record.list()[ z * nmoments + l];
                        }
                        matrix[l][z][g_i][g_o] = record.list()[block  * ndilutions * nmoments + z * nmoments + l];
                        // std::cout << "( l, z, g_i, g_o ) :" << "( " << l << ", " << z << ", " << g_i << ", " << g_o << " )" << std::endl;
                        // std::cout << "Index: " << block * ndilutions * nmoments + z * nmoments + l << std::endl;
                        // std::cout << "Entry: " << block << std::endl;
                        // std::cout << record.list()[block * ndilutions * nmoments + z * nmoments + l ] << std::endl;
                        // } // endif
                    } // dilutions
                } // moments
                block += 1;
            } // outgoing erg
        } // endif
    } // records

    return std::make_tuple(temp, groups, flux, matrix, probability);
}