#include "gtest/gtest.h"
#include "statistical/estimator_mle.hpp"


#define MAX_VALUE 100000
#define MAX_VALUE_F 2.0

// The fixture for testing class Project1. From google test primer.
class EstimatorMLE_Test : public ::testing::Test {
protected:
	// You can remove any or all of the following functions if its body
	// is empty.

	EstimatorMLE_Test() 
	{
		// You can do set-up work for each test here.
	}

	virtual ~EstimatorMLE_Test() {
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:
	virtual void SetUp() {
		// Code here will be called immediately after the constructor (right
		// before each test).
	}

	virtual void TearDown() {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}


};

TEST_F(EstimatorMLE_Test, EVT_1_1_05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{0.191028, 2.23268, 0.125111, 0.23119, 1.47925, 0.308607, 3.4642, 3.45605, 2.50758, 0.45171, 2.10044, 1.46814, 11.083, 2.04172, 3.2378, 1.25003, 1.18423, 3.56445, 0.269165, 0.408548, 0.5109, 1.06371, 3.65408, 3.27426, 0.194038, 1.08725, 1.49846, 1.13791, 2.08502, 1.93213, 0.802566, 1.182, -0.020331, 14.7796, 0.495391, 0.335627, 1.01235, 0.571887, 1.36693, 0.924233, 7.98221, 5.94123, 0.165715, 2.62736, 0.745677, 1.15569, 1.57831, 7.23611, 1.14068, 14.2976, 0.8264, 2.35622, 2.13899, 1.54451, 2.33618, 2.14009, 0.522673, 0.394952, 64.937, 0.505256, 0.0809362, 1.6314, 4.64075, 2.15554, 0.553025, 1.00282, 1.27192, 13.6913, 0.468325, 4.06301, 2.01899, 1.02295, 0.55423, 1.17181, 1.3412, 0.37517, 1.75119, 0.640452, 1.04604, 1.72269, 0.703071, 0.798698, 1.87855, 0.736201, 3.551, 14.1235, 2.56705, 0.935762, 1.72738, 0.339971, 5.37655, 4.58522, 3.45894, 0.724986, 1.77276, 0.0268325, 1.16288, 0.854995, 0.481138, 0.524243, 1.15584, 0.301331, 1.79157, 1.30471, 2.32192, 2.34808, 1.98612, 0.0857522, 0.222501, 0.872608, 1.51329, 2.0716, 1.11121, 3.4893, 2.47741, 10.2062, 1.51505, 0.886892, 0.33398, 1.84923, 3.00001, 1.15752, 0.291307, 0.739138, 0.46136, 0.775145, 1.20757, 1.49945, 1.26145, 4.48188, 1.46617, 7.30248, 1.98184, 8.6195, 0.675901, 2.19691, 0.795253, 2.17108, 2.3166, 0.219795, 0.710392, 0.635213, 2.14768, 3.86305, 0.937306, 3.01775, 2.19214, -0.105874, 1.80824, 1.05204, 5.75165, -0.231171, 1.27741, 1.16018, 1.27252, 2.91362, 0.879995, 3.06219, 1.30611, 0.0958536, 0.517075, 2.5025, 1.31305, 0.458983, 0.928516, 1.83244, 0.556249, 2.63196, 0.68114, 5.81261, 0.745534, 2.86893, 0.548668, 0.791336, 0.292166, 1.69366, 2.24132, 1.57332, 1.16428, 2.01728, 2.03429, 2.2145, 1.97189, 7.42256, 0.598348, 2.41244, 0.664964, 0.371889, 1.83204, 1.23859, 1.26557, 2.11372, 2.91485, 0.952545, 2.11409, 1.13603, 3.8216, 3.67753, 0.714446, 1.86112};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 1., 1e-1);	
	ASSERT_NEAR(res.get_scale(), 1., 1e-1);	
	ASSERT_NEAR(res.get_shape(), 0.5, 1e-1);	

}

TEST_F(EstimatorMLE_Test, EVT_0_1_M05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{1.7796, -0.66039, -0.32861, 0.077164, -1.2272, 0.76767, 0.091768, 1.7368, 0.091235, 0.61876, -0.73379, 0.036279, -0.70224, 0.94753, 1.2571, -0.047052, 0.77109, -0.21239, 0.40791, 1.1435, 0.56471, -0.090642, -0.19687, 0.21926, 0.14396, -0.022618, 0.47314, 0.90881, 0.14826, 0.16101, -0.88476, -1.8532, -0.22462, -0.14216, 0.69597, 1.5804, 1.4845, 0.23236, -0.38757, 0.96208, 0.95058, 0.90414, 0.91164, -0.99671, 0.76166, 0.24562, -0.4903, -1.0447, 1.1189, -0.64039, -0.69111, 0.72488, 1.3318, 0.37449, 0.81202, -0.73749, 1.5634, 0.43213, 0.75734, -1.638, 1.0798, 0.92385, -0.91116, 0.39467, -0.11789, 0.44525, 0.082613, 0.12463, -0.61588, -0.33664, -1.9424, 1.4365, 0.696, 1.4717, -0.69137, 1.4266, 1.0412, 0.5178, 0.18793, -0.3292, 0.93212, -0.42938, -1.3142, 0.97075, 0.73717, 0.84211, 0.66873, 0.13477, 0.061282, 1.0985, -0.14243, 1.0942, 1.0266, 1.2004, 0.34841, 0.65376, 1.5512, 0.19777, -1.3545, 1.2437, 0.64331, -0.035122, 1.8904, -0.44569, 0.69307, 0.5822, 0.051979, -0.79329, -1.8385, 0.14005, -0.60175, 0.86772, 0.0067388, 1.1693, 0.88836, 0.50291, -0.63243, 1.5826, -0.30375, 1.4399, -0.44715, 0.015393, -1.1216, 0.66418, -0.61639, -1.5213, 0.86139, -0.056376, 0.71224, 0.043007, 0.63434, -1.9155, 1.3878, 1.0567, 0.91698, 1.0903, 0.04151, 0.61085, 0.51336, 0.40654, -0.27221, -0.35949, 0.21689, -0.43283, 1.0671, 1.7634, -1.7453, 0.41981, -1.1247, 1.0608, 1.7911, -1.2887, 1.4999, -2.0038, 0.76706, 1.0127, 0.4162, 1.3021, 1.3474, 0.63105, -0.81528, -0.46915, -0.60996, -1.5634, -0.9903, 0.6089, 1.5011, -0.036833, 0.11313, 1.7488, 1.5269, 0.75003, 1.7831, 0.96949, -0.086687, 0.71639, -0.37479, -0.20822, 0.75839, 0.40131, 0.11562, 0.57671, 0.92857, 0.53214, 0.45782, 0.53223, 0.3632, -1.1584, 0.85265, 1.8759, -0.036615, 1.6585, -0.059146, 1.306, 0.22447, 0.12035, -0.4694, -0.88043, -0.16766, 0.86852};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 0., 1e-1);	
	ASSERT_NEAR(res.get_scale(), 1., 1e-1);
	ASSERT_NEAR(res.get_shape(), -0.5, 1e-1);

}


TEST_F(EstimatorMLE_Test, EVT_0_1_P05) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{2.04238, 1.30775, -1.07003, 2.84309, 5.0338, 1.92137, -0.873931, 0.0282173, 1.37823, 1.56135, -0.364209, -0.254483, 1.17835, 0.326199, 0.910929, -0.334513, -0.479826, 2.62795, 1.88243, 5.68283, -0.659695, -0.467196, -0.684573, 0.367184, -0.440066, 4.03199, -0.684589, -0.867688, 0.615641, 1.93651, -0.146991, -0.475221, -0.0771772, -0.398695, 0.437854, 4.37856, 0.936908, -0.677601, 0.06348, -0.827059, 0.406698, 0.182211, 38.467, 2.37746, 0.353326, 3.98822, -0.580021, 0.0610936, 5.28272, 4.81561, 1.44281, 0.884586, -0.065791, 5.77847, -0.613666, 1.56967, 1.02816, 2.68114, 0.0844709, 1.7273, 2.71327, -0.120034, 0.595579, 11.7713, 0.583938, -0.0994395, 0.890099, -0.0195928, 1.78614, 0.129433, 0.375948, 1.314, 10.0288, -0.10636, 2.7542, 1.63721, 7.23428, -0.922368, -0.0297111, 1.11777, -0.22362, -0.349311, 1.42543, 0.915169, 0.756061, 1.10516, -0.854028, -0.0512599, 0.242337, -0.323615, 1.45336, 3.07555, -0.223605, 1.5733, -0.579458, 2.73696, -0.577278, 0.745471, -0.00467716, 2.31603, 0.415406, 0.36661, 3.52173, -0.0396731, 0.236424, 8.3763, -0.875449, 10.0794, -0.449992, 1.14353, 0.737709, 1.19082, -0.0185548, 0.894035, 2.37164, -0.993672, -0.729601, 10.5193, 1.05456, -0.347225, 0.099339, -0.621039, -0.256005, -0.282101, -0.0962127, -0.542256, -0.0533201, -0.622012, 3.69976, -0.698525, 5.42643, 0.0865691, -0.854635, -0.068199, 1.61214, 2.17198, 0.566757, 1.25925, 3.9639, -0.826412, -0.16802, -0.85946, -0.43459, 1.49069, 1.50246, 3.53981, 0.720292, -0.771301, 5.05333, 2.23829, -0.212539, 0.561945, 14.1475, 1.45793, 2.773, 0.186849, 0.303734, 0.629428, -0.254392, 1.72038, 0.41578, 1.02994, -0.157665, -0.576959, 0.319887, -0.0146799, 2.09863, 2.01543, 1.15166, -0.590579, -0.978995, 0.625896, -0.175206, 5.99977, 12.4034, -0.210857, 2.24363, 4.03873, 0.78705, 3.6962, 6.31074, 0.583348, 1.55266, 0.695986, -0.953891, 0.227389, 1.02722, 0.477617, 0.0120874, 5.84898, 2.6263, 2.94475, 0.0126935, 0.767521, 3.41665, 5.62423, 1.15138, -0.406927, 1.06831, -0.766835};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 0., 1e-1);	
	ASSERT_NEAR(res.get_scale(), 1., 1e-1);
	ASSERT_NEAR(res.get_shape(), 0.5, 1e-1);

}

TEST_F(EstimatorMLE_Test, EVT_0_1_0) {

	constexpr int n_elem = 200;
	double xs[n_elem] =
	{1.5852, 2.3132, -0.72449, 2.4012, 0.78024, -0.84479, -0.24557, 0.50497, 3.1368, 3.3314, -0.61389, 3.5116, 3.1286, 0.32458, 1.5015, -0.66923, 0.14697, 2.4301, 1.457, 3.1857, 0.86277, -1.2037, 1.8107, 2.684, 0.94798, 1.2822, 1.2144, 0.066231, 0.86182, -0.56815, 1.0553, -1.2376, -0.24999, -1.1234, -0.84659, 1.6386, 1.0104, -0.13849, 2.9748, -1.2144, 0.19378, 0.037192, 1.3197, 1.4733, -0.5172, 0.33711, 0.21274, 0.82903, 1.0689, 1.2678, -0.25252, 0.95166, 0.86045, -0.59685, -0.75549, 0.3618, 3.192, -0.074807, 0.62421, -0.40343, 1.2518, -0.31197, 0.38375, 1.0272, 2.1583, 3.1806, 0.50598, -0.68107, -0.64282, -0.30506, 1.7516, -0.31431, 1.5826, -0.34539, 2.6123, -0.048665, -0.4865, -0.32351, 0.72477, 0.29029, -0.044105, 1.6856, 0.6242, 0.5136, 2.4483, -0.225, 1.2797, 1.2633, 0.034166, 0.56925, -0.94738, -1.0715, 0.45669, 1.3882, 2.6843, -0.71341, 0.57237, 0.27929, -1.4886, -0.083705, -0.59831, 1.4683, -0.15467, 0.44997, -0.58661, 0.6782, -0.28946, 0.85678, 0.98832, 1.2374, 0.22652, -0.90788, -0.38807, 2.4007, -0.63201, 1.6535, 0.47923, 5.5538, -0.93562, 0.20468, -0.80566, 3.2481, -1.6816, 1.3665, 1.6008, 1.9607, -0.90493, 0.086829, -0.2983, 1.5003, 0.17354, 2.3687, -0.53332, -0.2871, -0.65613, -0.69044, 1.9656, 0.60654, 0.51401, -0.65821, 1.8391, 0.74502, -0.046029, 0.40498, 0.092356, -0.9468, -0.3559, -0.73859, -0.52669, -0.35579, 0.13464, -1.0995, 2.2794, 2.8683, 0.34026, 0.33565, -0.082077, 2.2509, 0.0037168, -0.78682, 1.3938, 0.059454, -0.35072, 0.0981, -0.84959, -0.70565, 2.8185, 3.1043, 0.59236, -1.0357, -0.37095, -0.040026, 1.6246, -1.4287, -1.1461, -0.57544, 0.83899, 1.1636, 0.83412, 0.22758, 0.50536, -0.19582, 1.2215, -0.51057, 0.97884, -0.52797, 0.001645, 0.75712, 1.3936, -0.92098, 2.6141, 1.3705, 0.32862, 0.1858, 0.21607, -0.16808, 0.39116, 0.39775, 1.6027, 1.4713};

	// 0.5, 1, 1

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 0., 1e-1);	
	ASSERT_NEAR(res.get_scale(), 1., 1e-1);
	ASSERT_NEAR(res.get_shape(), 0., 1e-1);

}


TEST_F(EstimatorMLE_Test, EVT_1_10_0) {

	constexpr int n_elem = 500;
	double xs[n_elem] =
	{5.3368428939, -0.160130636605, 17.9221021595, 16.5894843893, 6.35813297119, -1.8948395561, 10.5495314116, -2.74261670302, 3.42925317728, 1.45376593429, 5.80006406752, 48.8778562284, 13.7030618118, 40.251749685, -2.70939310737, 5.50043091816, -9.87691513872, 13.7813421545, 7.78196609244, 19.7002038757, 45.403241703, 27.1558254939, 2.13412950934, -19.7722327315, 5.86847189481, -3.52038929233, -3.1699140021, -0.146245955781, -7.5183077265, 13.3451468772, 13.3900565751, 5.94141138953, 0.190487902806, 17.9542136545, 6.22272194572, 32.3765239518, 22.7722754517, 0.690723360865, 6.03518210974, 0.423463157798, 8.47549812974, 15.811695059, 13.2690922734, -6.30038676471, 17.3201245171, -12.0369436108, 2.26863504351, 12.6224062319, 14.9957670146, 0.983866282503, 13.2231177157, 22.7164759893, -2.48067129777, -6.14578789131, -2.99683911772, 0.514171366342, -1.21524871838, 26.8660169352, -9.88493397833, 7.47938656748, -4.95879118422, 18.3583434143, -4.80207029352, 4.72868777957, 74.0712021999, 0.660902480288, -10.170923581, -3.33966117367, 1.81527279044, 0.0686650405314, -2.86218125479, 28.1792758253, 10.6499776174, 33.5391911756, 2.91647780623, 28.8843643921, -15.3783035989, 8.05638634006, 16.0598029333, -2.76239561545, 27.6040755888, 14.0876714905, 17.5749216043, 6.86877576653, 15.5903826323, -0.0577551819718, -3.04473956141, -0.514452361277, 7.21834784676, 17.7968320308, -1.12107540269, 1.94393039244, 20.0761796956, 8.2040205019, 48.2719445961, -3.64433443074, 17.623230388, 10.370881834, -2.29667231202, 3.9734475208, 1.84898692062, 7.69894992517, 16.0287174026, -7.12324878131, 17.2610753056, 18.541113037, 0.636397987364, 2.69829655648, 6.83041252365, 11.3423720096, 13.11423356, 13.829267638, 1.57793344129, 2.6771651324, 32.0919417243, 6.85334513808, 19.1495044508, -1.51617531787, 8.45925703782, 7.34098557061, 33.9102938812, -7.97939402423, 4.67952735829, 5.29439110856, -7.78008359387, 24.006975362, 21.9672331569, 2.9445964113, 15.0138641012, -5.45744143099, 8.37448687112, -1.96154395882, 3.12936507659, 18.7429272559, -3.8771808652, -0.7497444919, 4.18651457973, 0.181752306259, 15.9148574505, 44.7474406724, -5.08978324418, -2.6478373586, 11.3991465684, 1.20639255504, 37.2507885847, 36.7251373464, 9.1978687799, 19.9241159837, 1.92561345456, 8.78758691924, 43.0817930943, 6.43431231828, 27.7777528876, 12.1465781575, 4.20769065982, 9.03403734621, 22.2701498909, -3.798142188, 1.74785328385, 49.4654503649, 1.93839467797, 9.74070792315, 23.6467560518, 54.754316081, 9.53484648014, -6.98223694139, -11.0028817174, 8.31640229964, 6.67146621621, 33.4991336349, 13.2796394109, 9.87435036239, 5.34520793087, -1.98236433958, 33.50694006, 5.84819461994, -11.5207494821, 11.162384083, 5.23925762372, -9.4017072601, 22.4992318719, -0.0260167407598, -2.8592609503, -6.756518279, -0.554734395793, -2.89684781601, 9.49298048507, -8.99041404768, -1.54189989256, -1.3624603111, 21.5761680962, 3.09256743299, 13.7358191587, 7.82510548985, 15.0942788329, -6.75724572469, 39.3186313201, 19.0684510413, -9.92891019491, 3.70318208807, -0.150433192945, 8.72818469619, -2.84157098451, 7.07106159642, 7.82051213181, 7.71332557085, 3.20637428973, -11.0608485653, 5.06627300873, 2.08532550598, -6.99845845472, 3.52573394549, 3.27467959411, 6.17907626506, 16.3057649991, 11.3433892169, 20.8999712656, -9.82761706625, -3.15796466931, 3.51919470946, 32.6177112303, 15.4534430799, 3.30230414841, 0.0621118619094, -9.39783186849, 13.0436468704, 4.86177855455, -3.76116728804, 2.61909600839, -4.76439706415, 13.5377539735, 1.01281399648, 29.143537208, -13.0227686513, 17.7414879567, 8.6043870637, 5.80441747799, 9.43964853125, 12.4150356172, -7.58354990896, 21.3566145697, -13.4530813955, -1.01426798849, -4.3957134048, 26.6963729103, -8.87903275011, 7.10933155986, 8.9684629137, 9.46689799969, 20.2783457011, -9.58918697851, 16.9803583529, 5.51121544181, 11.084654649, -3.37778002836, 5.94082349441, 11.4105772705, 32.1130225317, 3.09844410823, -8.00337992403, -9.50385951421, 8.70226766182, 15.7871162314, 10.9604143825, 0.386049403503, 30.0680976391, 5.25320113932, 31.5150681266, -8.59031991046, -3.54180449865, 14.6705518169, 25.110700966, 15.0569480603, -0.980068352552, -5.33869600826, 19.0193002505, 15.1775690628, -1.67166878629, -2.91528602522, -0.27726177122, 17.7740810644, 17.3069596953, 6.78174041214, 6.81759358356, -1.24502292084, 11.2746398928, 15.7914634114, 3.01656599915, 3.1448984104, 3.6880228527, -1.44046005612, 10.3525258857, 23.8969762807, 24.4411687801, 13.3296751139, -1.96474489889, 10.8996771212, -6.06180386764, -6.37885042138, -4.04399380877, -5.55437669414, 7.23492621476, -8.60251505908, 17.3159099661, 12.2553055821, 26.63503687, 4.45340225591, 9.59676871069, 22.5076495595, 5.79778784438, -1.35167721305, 38.1578949195, -10.9769889664, -0.134250688597, 36.9877571528, 0.922614747777, -0.603570226278, -6.47961586323, 25.3047836811, -5.92619288889, 0.0263259480043, 23.2410148117, 4.65499665083, 8.22237357664, 7.17409029417, 11.2395264191, -11.6103282831, 5.48036753821, -11.353974898, 17.6189765825, 0.241041265416, 18.9338541816, -2.38000346976, 7.12195316407, 28.4342039746, -10.1218493698, -9.71304480439, -12.5624464284, 10.5844028542, 7.67257179537, -6.75323028989, 15.7907692929, 8.30831147306, -8.76901927574, -8.81933834603, -5.90667141119, 15.3916063077, -7.67791421039, -2.61886575754, -2.45029147942, -7.13367056575, 19.7901735384, 11.2373670057, 12.72481795, 9.4404704115, 5.1381341044, -0.130322193863, 9.84724597285, -6.61160805607, -5.48033413922, -12.6707576019, 34.1424735912, 36.0406612784, -6.36493644627, 3.7371552056, 9.66222533817, -1.12878788998, 13.6708499962, 6.39251200477, 2.63558539479, -1.77465115375, 13.63323007, 23.3337411446, 12.4934422496, 2.06072390948, 28.540626747, -2.11020238947, 5.6373907795, 31.7259924275, -1.75895966374, -2.26390108079, 26.8925060825, -8.85712343936, -0.872871377645, 7.44447722859, -3.65667216968, 8.92436425831, 15.9084273157, 4.71424833704, 9.45053782715, 15.7747742878, -2.75084217752, 7.74466025691, -6.8167831064, 5.12334482625, 18.3201634867, 25.9467624365, 4.61403797368, -1.48057786453, 9.5117374745, 25.4967066693, 4.95030637263, 37.4400554343, -3.84360451364, -6.86892474821, -0.929572502264, 1.77653785721, 2.44213456587, -0.539521337327, 11.0646349397, -7.70188483751, 1.93121530425, -0.989879111309, -0.676714600493, -7.10247785914, 7.51686229096, -1.33704931313, -5.22135149133, -18.9133295922, -1.312757109, 6.16904448522, 20.7886812489, -10.5185912789, 24.0131005342, -6.09392404143, 18.045899804, 16.0256639587, 25.57036469, -5.85901151851, 4.80196484152, 2.00958291504, -4.60279481607, 6.92278002245, 7.92116246446, -3.31586638202, 5.24561150508, 46.2146446665, 4.37540549946, 11.1053031495, 2.1863011667, -11.1158570362, -1.05515265765, 16.0804173966, 0.418568397839, -8.10319070413, 4.98721574737, 0.971565828023, 12.9796186613, 5.38734345498, 16.2551798305, 16.9837480488, -4.08933890492, -6.37139614088, 17.2335197448, 8.99447073482, -13.1772200632, 23.0849833322, 5.11190903548, 5.9783199674, 7.92855538202, 13.9512715334, 19.5630954744, 1.40755511581, -8.03910312006, 12.7305931254, 0.0228141252898, 18.4496212154, 1.10448903032, 17.6875186317, -4.50620515309, -6.14870042701, 21.5599323096, -10.3839979179, 10.7862205848, 12.72617261, 2.89433706099, 1.3251490764, 39.8478146841, 1.846755469, 2.97773318219, -5.16662315356, -0.140005464301, -0.468369315506, 22.9382366257, -2.35235082653, -0.561444078554, 2.11646125948, 11.6335384289, -5.62926013091, 20.8236126374, -8.11092508008, 3.57789347483, -11.5095384718, 13.6081206344, 11.3110134458, -3.31385227537, 10.524292864, 6.36716727657, 19.2188549903, 6.40626279071};

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 1., 1e-0);	
	ASSERT_NEAR(res.get_scale(), 10., 1e-0);
	ASSERT_NEAR(res.get_shape(), 0., 1e-0);

}

/*TEST_F(EstimatorMLE_Test, EVT_1_10_0) {

	constexpr int n_elem = 500;
	double xs[n_elem] =
	{12.7498838, 0.296007561, 37.8992011, 5.88408093, -0.455709707, 148.886179, 65.4976386, 6.73492336, 11.0947467, 8.77390254, -3.63647853, -1.66546494, 3.27915544, -3.18594897, 49.0887394, -3.88740062, -3.27761119, -4.34325313, -3.24270957, 2.03652798, -1.43566899, 115.447194, 1.85553488, -4.07720767, 90.0481529, 478.770568, 2.14252264, -5.44865264, -2.617447, 1.17661439, 9.25414991, -2.52952465, 9.75900601, 19.3444962, -3.36086091, -5.33150523, -1.77032675, -1.25307867, 1.66005891, 4.75899656, -5.93339579, -2.52376626, 35.0702039, -7.16945807, 125.494818, 21.8210273, 3.96272155, 8.27240237, -3.0483109, 2.83640242, 255.887225, 6.56556933, 5.34343456, -3.16364484, 3.97424974, 11.20852, 15.8441639, 0.780903762, -0.0120291136, 817.075349, -6.94848876, 71.982123, 100.247155, 33.8740577, -5.68136402, -2.53677074, -0.847185601, 15.9025328, -4.97750287, 20.5996935, -5.53003607, 13.5283586, 4.18705899, 30.0516124, 19.8132901, 88.7799873, 76.5817123, -0.876963084, 17.8964758, -3.82887158, -7.13359209, 23.8278472, 4.42788438, 3.62153979, 89.8728602, 10.2218354, 10.7552077, 56.0189844, 36.2309725, 8.16874425, -4.11312067, -2.99425374, 73.0146314, -7.18449379, 4.01441216, -4.39532586, 454.039487, 19.5244385, 4.44660036, 3.28533659, -6.45362805, 16.1255666, -6.83531566, -6.21042861, 5.36667854, -5.71886913, 39.8227921, 39.6409044, 20.7577348, -4.73134451, 14.0318918, 5.22922671, 354.998825, 13.1301756, 34.8973253, 2.65656558, 1.92714173, 42.0856102, -5.973052, -5.03998074, -4.29295371, 0.64728231, 44.1510525, 35.6731788, -6.4356853, 0.891489916, 5.60572756, 1.42661173, 13.7934044, 11.4934724, -1.87689268, 1.90281362, -7.60062165, 612.4858, -4.40951488, -5.54024825, 0.123910806, -3.82292971, 4.00584617, -0.743318324, 191.700388, 110.451799, -6.60277205, 22.8943305, -2.38153303, 1.61748106, 6.61914694, 159.583649, 1.45624678, 575.042119, -1.66065329, 18.1605641, 14.6331537, 6.18633432, 17.8253117, 14.65038, -4.20366427, -5.13526996, 10859.2305, -4.33550995, -7.07894259, 7.31067274, 69.5452592, 14.8936287, -3.97028599, 0.0282312465, 2.90402654, 529.586086, -4.61005583, 54.0850935, 12.7857862, 0.230781529, -3.96092027, 1.79188058, 3.70303395, -5.27226931, 8.92262654, -3.27229141, 0.465705893, 8.53253975, -2.74887235, -1.9117146, 10.7151291, -2.46401176, 41.7790722, 561.799787, 21.8096519, -0.632066043, 8.59650047, -5.51119638, 91.6509035, 67.9867296, 39.705322, -2.56106011, 9.22055311, -7.36403734, 1.69513864, -1.39748403, -4.5155732, -4.19170806, 1.61907952, -5.76634221, 9.48219414, 3.27918943, 17.5878472, 18.0241434, 12.2922977, -7.05285561, -6.26372551, -1.23334473, 5.79157939, 13.5867609, 1.14303118, 40.3844743, 20.2310334, 303.945908, 5.81366119, -1.0991004, -5.551246, 10.295256, 30.0002997, 1.63720399, -5.83131773, -2.43849482, -4.66106939, -2.12214916, 2.18342775, 5.61807168, 2.78537388, 65.1276426, 5.2049757, 162.327763, 12.2284927, 221.336734, -2.97838955, 15.5505311, -1.94266519, 15.1393697, 17.499627, -6.28025168, -2.68639627, -3.31519762, 14.7697929, 49.1232314, -0.617115199, 30.3558808, 15.4744125, -8.00134495, 9.71551802, 0.527180244, 103.962097, -8.52225656, 2.96649134, 1.66590316, 2.9109112, 28.2910922, -1.16404489, 31.2534915, 3.29541155, -6.99776234, -4.24621069, 20.6687006, 3.37554748, -4.67842023, -0.702063493, 10.0567411, -3.94521967, 22.9779141, -2.93442493, 106.029251, -2.38278039, 27.4215025, -4.00407129, -1.97778664, -5.82576701, 8.13946496, 16.2654203, 6.55490444, 1.71025105, 12.7599001, 13.0173524, 15.8324856, 12.0803129, 167.348604, -3.61321279, 19.111869, -3.06973819, -5.29479853, 10.0510947, 2.52816096, 2.83197439, 14.2381241, 28.315052, -0.468923465, 14.2438804, 1.40655527, 48.11946, 44.6981622, -2.65168767, 10.4650052, 8.48918217, 6.26497775, 61.77213, -2.47475089, -1.26996654, -5.29816796, 151.142605, 12.8493241, 3.6038119, 12.3536157, 6.46116228, 12.9923284, 6.41993702, 20.5762258, 5.40501448, 1573.46224, -3.42175029, -5.54807847, -5.47517255, -6.3706015, 1.05087406, 2.46680713, -0.0559286476, 27.0595368, 11.4878106, 28.6404532, 133.870328, 351.826319, -3.93980627, -4.93462313, 17.6225526, -5.77413056, 5.53791436, 5.76717522, 56.8903457, 3.81389405, 0.72058272, 15.1039419, 23.399396, 5.29459905, -0.533698685, -4.72890298, 8.71683411, -2.53093843, -6.78797238, 25.5712485, -2.93574544, 2.26188041, 16.7191878, -0.232442558, 22.6729894, 0.75719512, 16.2707337, 18.4973718, 2.25858772, -7.45764954, -0.958951149, 1.66463505, -2.35668159, -3.84342033, 40.9283908, 1.84619578, 74.0043152, 0.65439497, 28.0929783, 0.818479858, 37.0461674, 25.5953696, 0.262078597, -3.47424314, 32.5157414, 182.210525, -1.03996802, 15.0882967, 2.13496672, 44.9085913, 28.043954, -4.40792315, 57.3297955, 972.368264, 5.04418838, 71.3137919, 8.83295846, -4.64073982, -3.78929834, 1.12281398, 24.5531431, 42.1745063, 32.4143734, -1.25917435, 5.94287709, -5.84802746, -5.43772132, -4.9823167, 15.7967086, 4.22798999, -3.98408145, 4.22099355, -4.77313761, -6.55278476, 51.8502475, 7.27653294, 127.002526, 17.6665386, 8.52103233, 39.000414, 67.5466939, 886.835384, -8.67674531, 59.1951215, 10.4040899, 980.036826, 5.64296232, 3.60613422, 35.1547871, -3.23912626, 4.34790466, 85.7728227, 8.05136927, 49.4502738, 23.0093764, 8.71055769, -2.85429639, 14.6402005, -5.97279947, 11.3461228, 14.1496125, 21.7409203, 76.4385679, 550.059763, 28.0768904, 8.44214293, 124.433444, 8.36306549, -7.54634107, -5.26767447, 57.7158798, 3.79200136, 49.3156872, -3.6040308, 6.84410303, 11.6346923, -7.09496572, 10.5507982, -0.147541323, -6.67235103, 4.0011343, -3.93058454, -5.22648031, -3.68023617, -4.79336988, -3.99625292, -6.83009782, 12.0352337, -2.10310478, 6.16061671, 17.5020792, 4.39021358, 6.02583746, 2.35682343, -5.21077387, 4.03270495, 52.8939148, 64.2071157, -2.35616477, -3.62245542, 7.51418673, 12.4315839, 1.43380313, -3.67087796, 177.01612, -6.00026883, -5.54974294, -4.87610071, -4.42274766, 10.9867643, 7.99753498, -6.61592218, 130.292368, 21.5910111, 22.8919195, -6.37447396, 56.5288463, 137.394387, 625.943192, 55.7645585, 31.4319329, 4.9982603, -4.21365811, 0.871654206, -5.02593642, -7.12423648, 149.26382, -1.66408743, -1.79636578, -0.907472052, 3.13577097, 13.064941, -7.28245627, 48.2309738};

	MeasuresPool<int, double> mp;
	for (int i=0; i<n_elem; i++) {
		mp.push(0, xs[i]);
	}

	Estimator_MLE<int, double> mle;
	mle.run(mp);
	auto res = mle.get_result();

	ASSERT_NEAR(res.get_location(), 1., 1e-0);	
	ASSERT_NEAR(res.get_scale(), 10., 1e-0);
	ASSERT_NEAR(res.get_shape(), 0., 1e-0);

}

*/


