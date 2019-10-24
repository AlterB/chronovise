#include "statistical/test_kpss.hpp"
#include "global.hpp"

#include <array>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>
#include <iostream>



namespace chronovise {

template <typename T_INPUT, typename T_TIME>
double TestKPSS<T_INPUT, T_TIME>::compute_statistics(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

    typedef std::pair<T_INPUT, T_TIME> P;

    size_t nobs = measures.size();
    T_TIME avg  = measures.avg();

    // Getting rid of input values
    std::vector<T_TIME> observ;
    observ.reserve(nobs);

    std::transform(measures.cbegin(), measures.cend(), std::back_inserter(observ), 
                   [avg](const P& p) { return p.second - avg; });

    double factor = 1. / nobs;

    std::vector<T_TIME> cumsum(nobs);
    std::partial_sum (observ.cbegin(), observ.cend(), cumsum.begin());

    double dot_product_cumsum = std::inner_product(cumsum.cbegin(), cumsum.cend(), cumsum.cbegin(), 0.);
    double dot_product_observ = std::inner_product(observ.cbegin(), observ.cend(), observ.cbegin(), 0.);
    double eta        = factor * factor * dot_product_cumsum;
    double obs_square = factor * dot_product_observ;

    double sum = 0.;
    
    for (unsigned int i=1; i <= n_lags; i++) {
        auto begin_v1 = std::next(observ.cbegin(), i-1);
        auto end_v1   = observ.cend();
        auto begin_v2 = observ.cbegin();
        auto end_v2   = std::prev(observ.cend(), i-1);

        assert(std::distance(begin_v1, end_v1) == std::distance(begin_v2, end_v2));

        double dot_product_partial = std::inner_product(begin_v1, end_v1, begin_v2, 0);
        double bartlett_weight = ((double)i) / (n_lags + 1);
        sum += (1. - bartlett_weight) * dot_product_partial;
    }

//    std::cout << "ETA= " << eta << " Factor=" << factor << " SUM=" << sum << " OBS_SQUARE=" << obs_square << " DPC=" << dot_product_cumsum << std::endl;

    return eta / (obs_square + 2 * factor * sum);

} 

template <typename T_INPUT, typename T_TIME>
double TestKPSS<T_INPUT, T_TIME>::compute_cv_value(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept {

    size_t size = measures.size();
    auto cv_values = this->coeff_kpss.at(this->trend_class).at(1. - this->significance_level);

    int n = size - n_lags - 1;

    double critical_value = 0.;

    for (size_t i=0; i < cv_values.at(0).size(); i++) {
        critical_value += cv_values.at(0).at(i) / std::pow(n, i);
    }
    for (size_t i=0; i < cv_values.at(1).size(); i++) {
        critical_value += cv_values.at(1).at(i) * std::pow(((double)n_lags) / n, i+1);
    }
    return critical_value;

}

template <typename T_INPUT, typename T_TIME>
void TestKPSS<T_INPUT, T_TIME>::run(const MeasuresPool<T_INPUT, T_TIME> &measures) {

    size_t size = measures.size();

    if(size < get_minimal_sample_size()) {
        throw std::invalid_argument("The number of samples is too low for this test");
    }

    if(this->trend_class == test_kpss_trend_t::TREND) {
        throw std::invalid_argument("Trend KPSS is not yet implemented.");
    }

    double statistics = compute_statistics(measures);
    double critical_value = compute_cv_value(measures);

    std::cout << statistics << " > " << critical_value << "?" << std::endl;


    if ( statistics > critical_value) {
        this->reject = true;
    } else {
        this->reject = false;
    }

}


/*
 * These numbers have been computed by Olivier Mallet and distributed with MIT License here:
 * https://github.com/olmallet81/URT
 */
template <typename T_INPUT, typename T_TIME>
const std::map<test_kpss_trend_t,std::map<float,std::map<int,std::vector<double>>>> TestKPSS<T_INPUT, T_TIME>::coeff_kpss = 
{
    {test_kpss_trend_t::LEVEL,{
        {0.001,{
            {0, {0.0167565, 0.1628078, -0.01441111}},
            {1, {0.2036426, 0.1065976, -0.5134231}}}},
        {0.005,{
            {0, {0.02160067, 0.1649124, -0.005748196}},
            {1, {0.1939746, 0.180736, -0.6535936}}}},
        {0.01,{
            {0, {0.02466286, 0.1635288, 0.04500264}},
            {1, {0.1893402, 0.2089429, -0.6943796}}}},
        {0.025,{
            {0, {0.03026605, 0.1623029, 0.09417188}},
            {1, {0.1847549, 0.2238625, -0.6818411}}}},
        {0.05,{
            {0, {0.03650665, 0.1643194, 0.118059}},
            {1, {0.1819509, 0.2103519, -0.5991279}}}},
        {0.1,{
            {0, {0.04597858, 0.1695003, 0.1046518}},
            {1, {0.1809212, 0.1596069, -0.4150671}}}},
        {0.2,{
            {0, {0.06222337, 0.1785042, 0.06728867}},
            {1, {0.1794514, 0.1031811, -0.2438007}}}},
        {0.5,{
            {0, {0.1188952, 0.2136505, -0.1988974}},
            {1, {0.1738762, -0.04517147, 0.1061083}}}},
        {0.8,{
            {0, {0.2413558, 0.2427114, -0.4925517}},
            {1, {0.07161341, 0.3635483, -0.8456676}}}},
        {0.9,{
            {0, {0.347477, 0.1815891, -0.8897294}},
            {1, {-0.1026364, 0.4255538, -0.6916551}}}},
        {0.95,{
            {0, {0.461564, -0.03241585, -0.4093091}},
            {1, {-0.4579306, 1.037593, -0.9517771}}}},
        {0.975,{
            {0, {0.5808698, -0.4198131, 1.286591}},
            {1, {-1.021283, 2.743161, -2.926945}}}},
        {0.99,{
            {0, {0.7434379, -1.282285, 7.296387}},
            {1, {-2.025517, 6.584114, -8.361188}}}},
        {0.995,{
            {0, {0.8686703, -2.108955, 13.70689}},
            {1, {-3.003148, 11.11568, -15.74966}}}},
        {0.999,{
            {0, {1.162377, -4.578843, 34.27324}},
            {1, {-5.808165, 25.97152, -41.79132}}}}
        }},
    {test_kpss_trend_t::TREND,{
        {0.001,{
            {0, {0.01234275, 0.1655343, 0.01672944, -1.675843}},
            {1, {0.2106948, 0.03970888, -0.3368414}}}},
        {0.005,{
            {0, {0.01526251, 0.1588324, 0.2212439, -3.176791}},
            {1, {0.2015772, 0.1179992, -0.5024903}}}},
        {0.01,{
            {0, {0.01699618, 0.1544975, 0.3604586, -4.262545}},
            {1, {0.1969925, 0.1538411, -0.5702144}}}},
        {0.025,{
            {0, {0.02005522, 0.1485785, 0.5907839, -6.211238}},
            {1, {0.1880815, 0.2169062, -0.6777426}}}},
        {0.05,{
            {0, {0.02326679, 0.1414555, 0.8224264, -7.893967}},
            {1, {0.1804144, 0.2639471, -0.7486399}}}},
        {0.1,{
            {0, {0.02781531, 0.1377224, 0.917243, -8.218599}},
            {1, {0.170477, 0.3089857, -0.7857759}}}},
        {0.2,{
            {0, {0.03489574, 0.1345627, 0.9657117, -7.923499}},
            {1, {0.1579158, 0.3369968, -0.7515043}}}},
        {0.5,{
            {0, {0.0556109, 0.1397416, 0.4620311, -1.559948}},
            {1, {0.1300005, 0.2833583, -0.4283284}}}},
        {0.8,{
            {0, {0.09159799, 0.1345566, -0.619965, 9.817577}},
            {1, {0.05585951, 0.2773908, -0.1216728}}}},
        {0.9,{
            {0, {0.1193112, 0.09514355, -1.079983, 16.87997}},
            {1, {-0.03271029, 0.4379497, -0.2279858}}}},
        {0.95,{
            {0, {0.1478756, 0.03863841, -1.89105, 30.13683}},
            {1, {-0.149998, 0.6506317, -0.2305911}}}},
        {0.975,{
            {0, {0.1773233, -0.03755152, -3.125617, 51.66143}},
            {1, {-0.3091562, 1.057115, -0.4266199}}}},
        {0.99,{
            {0, {0.2172606, -0.2049983, -4.308647, 82.65278}},
            {1, {-0.5765132, 1.915267, -1.057833}}}},
        {0.995,{
            {0, {0.2480191, -0.3967449, -4.07506, 101.2076}},
            {1, {-0.8216993, 2.85189, -1.957697}}}},
        {0.999,{
            {0, {0.3203646, -1.046171, -0.8434172, 144.566}},
            {1, {-1.515429, 6.124994, -6.22971}}}}
        }}
};

TEMPLATE_CLASS_IMPLEMENTATION(TestKPSS);

} // namespace chronovise
