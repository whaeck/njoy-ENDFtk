protected:

    // GType(int mt, int zaid, double awr, int nl, int nz, int lrflag, int ngn,
    //     std::vector< DataRecord >&& records)
    //     :
    //     Base(zaid, awr, mt), nl_(nl), nz_(nz), lrflag_(lrflag), ngn_(ngn),
    //     records_(records) {
    //         // verifyRecords();
    // }

public:

    /**
     *  @brief Constructor from parameters
     * 
     *  @param[in] mt       the section number
     *  @param[in] zaid     the ZAID identifier
     *  @param[in] awr      the atomic weight ratio
     *  @param[in] nl       the number of Legendre moments
     *  @param[in] nz       the number of dilution values
     *  @param[in] lrflag   the break-up identifier flag
     *  @param[in] ngn      the number of neutron energy bins
     *  @param[in] records  the data records 
     */
    GType(int mt, int zaid, double awr, int nl, int nz, int lrflag, int ngn,
        std::vector<DataRecord>&& records)
        :
        Base(zaid, awr, mt), nl_(nl), nz_(nz), lrflag_(lrflag), ngn_(ngn),
        records_(std::move(records)) {}

    /**
     *  @brief Constructor from buffer/string
     * 
     *  @tparam Iterator        buffer iterator
     * 
     *  @param[in] head         the head record of the section
     *  @param[in] begin        the start for the iterator
     *  @param[in] end          the end for the iterator
     *  @param[in] lineNumber   the current line number
     *  @param[in] MAT          the expected MAT number
     */
    template<typename Iterator>
    GType(const HEAD& head,
          Iterator& begin,
          const Iterator& end,
          long& lineNumber,
          int MAT)
        try:
            GType(head.MT(), head.ZA(), head.AWR(), head.L1(),
             head.L2(), head.N1(), head.N2(),
            readRecords(begin, end, MAT, head.MF(),
                        head.MT(), head.N2())) {
            this->readSEND(begin, end, lineNumber, head.MAT(), head.MF());
        }
        catch(std::exception& e) {
            Log::info("Encountered error while reading section {} of file {} fo material {}"
                      " in GENDF file.", head.MT(), head.MF(), head.MAT());
            throw e;
        }
    