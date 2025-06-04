template<typename Iterator>
static auto
readParameters(Iterator& it, const Iterator& end, long& lineNumber, int MAT) {
    auto list = ListRecord( it, end, lineNumber, MAT, 1, 451);
    return list;
}