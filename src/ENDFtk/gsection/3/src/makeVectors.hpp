static auto
makeVectors(const std::vector <DataRecord> records, int nmoments,
            int ndilutions, int ngroups) { 

    std::vector< unsigned int > groups(ngroups);
    std::iota(groups.begin(), groups.end(), 1);
    std::vector< std::vector< std::vector< double > > > flux( nmoments );
    std::vector< std::vector< std::vector< double > > > sigma( nmoments );
    std::vector< std::vector< std::vector< double > > > ratio;
    int nentries;
    double temp;
    if (records.size() != 0) {
        nentries = records.front().NG2();
        temp = records.front().TEMP();
    }
    else {
        throw std::runtime_error("Vector of Data Records is empty!");
    }
    if (nentries == 3) {
        ratio.resize( nmoments );
        int blockSigma = nentries * nmoments * ndilutions * 2 / 3;
        int blockRatio = nentries * 1 / 3;
        for ( const auto& record : records ) {
            auto g = record.IG() - 1;
            for ( unsigned int l = 0; l < nmoments; ++l ) {

                if ( flux[l].size() == 0) {
                    flux[l].resize( ndilutions );
                    sigma[l].resize( ndilutions );
                    ratio[l].resize( ndilutions );
                }

                for ( unsigned int z = 0; z < ndilutions; ++z ) {

                    if (flux[l][z].size() == 0 ) {

                        flux[l][z] = std::vector< double >( ngroups, 0. );
                        sigma[l][z] = std::vector< double >( ngroups, 0. );
                        ratio[l][z] = std::vector< double >( ngroups, 0.); 
                    }
                    flux[l][z][g] = record.list()[z * nmoments + l];
                    sigma[l][z][g] = record.list()[blockSigma + z * nmoments + l];
                    ratio[l][z][g] = record.list()[blockRatio + z * nmoments + l];
                }
            }
        }
    }

    else {
        int blockSigma = nentries * nmoments * ndilutions / 2;
        for ( const auto& record : records ) {
            auto g = record.IG() - 1;
            for ( unsigned int l = 0; l < nmoments; ++l ) {

                if ( flux[l].size() == 0) {
                    flux[l].resize( ndilutions );
                    sigma[l].resize( ndilutions );
                }

                for ( unsigned int z = 0; z < ndilutions; ++z ) {

                    if ( flux[l][z].size() == 0 ) {

                    flux[l][z] = std::vector< double >( ngroups, 0. );
                    sigma[l][z] = std::vector< double >( ngroups, 0. );
                    
                    }

                    flux[l][z][g] = record.list()[z * nmoments + l];
                    sigma[l][z][g] = record.list()[blockSigma + z * nmoments + l];
                }
            }
        }
    }

    return std::make_tuple( temp, groups, flux, sigma, ratio);

}