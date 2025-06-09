static auto mapRecords(std::vector<DataRecord>&& records) {
    std::map<unsigned int, DataRecord> mapped_records;
    for (auto& record: records) {
        mapped_records.emplace(record.IG(), std::move(record));
    }
    return mapped_records;
}