static auto
makeVectors( const DataRecord& record, int ngroups ) {
    
    double temp;
    std::vector< double > chi( ngroups );

    if ( record.list().size() != 0 ) {
        temp = record.TEMP();

        for ( unsigned int g = 0; g < ngroups; ++g) {
            chi[g] = record.list()[ g ]; 
        } // groups
    } // endif
    
    return std::make_tuple(temp, std::move( chi ) );
}