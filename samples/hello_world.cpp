#include "hello_world.hpp"

#include "evt/evtapproach_bm.hpp"
#include "statistical/estimator_mle.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ljung_box.hpp"

#include <iostream>

using namespace chronovise;

using exit_code_t = AbstractExecutionContext<unsigned int, unsigned long>::exit_code_t;

static int my_testing_function(int x) {
	volatile int i, a;
	for (i=0; i < x * 10; i++) {
		a = i;
	}
	return a;
}


exit_code_t HelloWorld::onSetup() noexcept {

	/* ********** PRE-RUN SECTION  ********** */
	this->set_input_source(std::move(uniform_input_dist));
//	this->add_input_transformer();		// TODO
//	this->add_representativity_test();	// TODO

	/* ********** POST-RUN SECTION ********** */
	std::shared_ptr<StatisticalTest<unsigned int>> stat_test(
		new TestLjungBox<unsigned int>(0.05, 10)
	);
	this->add_sample_test(stat_test);


	this->set_merging_technique(merger_type_e::ENVELOPE);

	std::unique_ptr<EVTApproach<unsigned int>> evt_app(
		new EVTApproach_BM<unsigned int>(10)
	);
	this->set_evt_approach(std::move(evt_app), 0.25);
	


	std::unique_ptr<Estimator<unsigned int>> evt_est(
		new Estimator_MLE<unsigned int>()
	);
	this->set_evt_estimator(std::move(evt_est));


	std::shared_ptr<StatisticalTest_AfterEVT<unsigned int>> aft_test(
		new TestKS<unsigned int>(0.05, distribution_t::EVT_GEV)
	);
	this->add_post_evt_test(aft_test);

	this->print_configuration_info();

	return AEC_OK;
}

exit_code_t HelloWorld::onConfigure() noexcept
{
	if (get_input_iteration() > 10)
		return AEC_OK;
	return AEC_CONTINUE;
}

exit_code_t HelloWorld::onRun() noexcept {

	// Clear the system state

	// Measure
	timing.start_timing();
//	my_testing_function(this->get_current_input_value());
	my_testing_function(10);
	timing.stop_timing();

	// Publish data
	this->add_sample(timing.get_ns());
	return AEC_OK;
}

exit_code_t HelloWorld::onMonitor() noexcept {

//	if (get_iteration() > 10000)
//		return AEC_OK;
	return AEC_SLOTH;
}

exit_code_t HelloWorld::onRelease() noexcept {

	this->print_distributions_summary();

	std::cout << "pWCET with 0.99 of probability is: " << this->get_pwcet_wcet(0.99);
	//this->print_pwcet_probability(1000);

	return AEC_OK;
}

