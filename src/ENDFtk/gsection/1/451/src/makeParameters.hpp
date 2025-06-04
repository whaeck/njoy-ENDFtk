static auto
makeParameters(double temp, double zero2, int ngn, int ngg, int zero3,
               std::vector<double> sigz, std::vector<double> egn, std::vector<double> egg) {
    std::vector<double> data;
    // The additional 0 is temporary for now until I can figure out if it has any real meaning
    data.reserve(sigz.size() + egn.size() + egg.size() + 1);
    data.insert(data.end(), 0.0);
    data.insert(data.end(), sigz.begin(), sigz.end());
    data.insert(data.end(), egn.begin(), egn.end());
    data.insert(data.end(), egg.begin(), egg.end());
    return ListRecord(temp, zero2, ngn, ngg, zero3, std::move(data));
}