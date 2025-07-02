private:

GType(int zaid, double awr, int nz,
    ListRecord&& list) :
    BaseWithoutMT(zaid, awr), nz_(nz),
    parameters_( std::move(list)) {}    

public:
/**
 *  @brief Constructor
 *  @param[in] zaid     the ZA value of the material
 *  @param[in] awr      the atomic weight ratio
 *  @param[in] nz       the number of sig_0 (dil. values)
 *  @param[in] temp     the temperature evaluated
 *  @param[in] ngn      number of neutron groups
 *  @param[in] ngg      number of photon groups
 *  @param[in] sigz     dilution values (size(nz))
 *  @param[in] egn      neutron group edges (size(ngn))
 *  @param[in] egg      photon group edges (size(ngg))
*/

GType( int zaid, double awr, int nz, double temp,
       int ngn, int ngg,
      std::vector<double> sigz, std::vector<double> egn, std::vector<double> egg ) :
    BaseWithoutMT(zaid, awr), nz_(nz),
    parameters_(makeParameters(temp, ngn, ngg, sigz, egn, egg)) {}

/**
 *  @brief Constructor (from buffer)
 * 
 *  @tparam Iterator        a buffer iterator
 * 
 *  @param[in] head         the head record of the section
 *  @param[in] begin        the current position in the buffer
 *  @param[in] end          the end of the buffer
 *  @param[in] lineNumber   the current line number
 *  @param[in] MAT          the expected MAT number
 */
template<typename Iterator>
GType(  HEAD& head,
        Iterator& begin,
        const Iterator& end,
        long& lineNumber,
        int MAT)
    try:
        BaseWithoutMT( head, MAT, 1), nz_(head.L2()),
        parameters_(readParameters(begin, end, lineNumber, MAT)) {
        readFEND(begin, end, lineNumber, MAT);
        }
    catch(std::exception& e) {
        Log::info("Trouble reading gsection 451 of File 1 of Material {}",
                    MAT);
        Log::info("lineNumber: {}", lineNumber);
        throw e;
    }
    
