static auto
makeVectors( const DataRecord& record,
             int ntimes, int ngroups ) {
    
    std::vector< double > lambda;
    std::vector< std::vector< double > > chi;
    double temp;
    int ng2 = record.NG2();

    if ( record.list().size() != 0 ) {
        chi.resize( ntimes ); 
        bool has_lambda = ng2 == ngroups ? false : true;
        temp = record.TEMP();

        if ( has_lambda ) {
            lambda.resize( ntimes );
            for ( size_t t = 0; t < ntimes; ++t ) {
                lambda[t] = record.list()[ t ];

                for ( unsigned int g = 0; g < ( ng2 - 1 ); ++g ) {

                    if ( chi[t].size() == 0 ) {
                        chi[t] = std::vector< double > (ngroups, 0. );
                    } // endif
                    chi[t][g] = record.list()[ ntimes * ( g + 1 ) + t ];
                } // groups
            } // groups
        } // endif

        else {
            chi[0] = std::vector< double > ( ngroups, 0.0 );
            for ( unsigned int g = 0; g < ngroups; ++g) {
                chi[0][g] = record.list()[ g ]; 
            } // groups
        } // endif
    } // endif

    
    return std::make_tuple(temp, ng2, std::move( chi ), std::move( lambda ) );
}