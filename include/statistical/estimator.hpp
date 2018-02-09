#ifndef STATISTICAL_ESTIMATOR_HPP_
#define STATISTICAL_ESTIMATOR_HPP_

#include "statistical/ev_distribution.hpp"
#include "measures_pool.hpp"

template <typename T_INPUT, typename T_TIME>
class Estimator {

public:

	virtual ~Estimator() {}

	virtual bool run(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept = 0;

	virtual EV_Distribution get_result() const = 0;

	

};

#endif
