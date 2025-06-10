template<typename Iterator>
static auto readRecords(Iterator& it, const Iterator& end, 
                        int MAT, int MF, int MT, int NGN) {
    std::vector<DataRecord> records;
    do {
        long lineNumber = 0;
        auto record = DataRecord(it, end, lineNumber, MAT, MF, MT);
        records.emplace_back(record);
    }
    while (records.size() < NGN); //TODO: fix this
    
    return records;
}