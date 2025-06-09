template<typename Iterator>
static auto readRecords(Iterator& it, const Iterator& end, 
                        int MAT, int MF, int MT, int NGN) {
    std::map<unsigned int, DataRecord> mapped_record;
    do {
        long lineNumber = 0;
        auto record = DataRecord(it, end, lineNumber, MAT, MF, MT);
        mapped_record.emplace(record.IG(), record);
    }
    while (mapped_record.rbegin()->first < NGN);
    
    return mapped_record;
}