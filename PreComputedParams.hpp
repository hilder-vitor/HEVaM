#ifndef __AGCD_BASED_HE_PARAMS_NOISY_X0__
#define __AGCD_BASED_HE_PARAMS_NOISY_X0___

#include <map>

class PreComputedParams {

	public:
	
	long lambda;
	long n;
	long eta;
	long rho;
	long rho_0;
	long gamma;
	long log_baseG;
	long log_delta;
	
	PreComputedParams(long lambda, long n, 
		long eta, long rho, long rho_0, long gamma, long log_baseG, long log_delta){
		this->lambda = lambda;
		this->lambda = n;
		this->eta = eta;
		this->rho = rho;
		this->rho_0 = rho_0;
		this->gamma = gamma;
		this->log_baseG = log_baseG;
		this->log_delta = log_delta;
	}
};

std::map<long , PreComputedParams> params_80_noisy_x0 {
//{n, PreComputedParams(lambda, n, eta, rho, rho_0, gamma, log_b, log_delta)},
{8, PreComputedParams(80, 8, 80, 52, 38, 1240, 7, 80-2)},
{10, PreComputedParams(80, 10, 80, 52, 38, 992, 7, 80-2)},
//{12, PreComputedParams(80, 12, 80, 52, 38, 827, 7, 80-2)},
{16, PreComputedParams(80, 16, 80, 52, 38, 620, 7, 80-2)},
//{20, PreComputedParams(80, 20, 80, 52, 38, 496, 7, 80-2)},
//{24, PreComputedParams(80, 24, 80, 52, 38, 414, 7, 80-2)},
//{28, PreComputedParams(80, 28, 80, 52, 38, 354, 7, 80-2)},
{32, PreComputedParams(80, 32, 80, 52, 38, 310, 7, 80-2)},
//{36, PreComputedParams(80, 36, 80, 60, 38, 275, 7, 80-2)},
//{40, PreComputedParams(80, 40, 80, 52, 38, 248, 7, 80-2)},
//{44, PreComputedParams(80, 44, 80, 52, 38, 226, 7, 80-2)},
//{48, PreComputedParams(80, 48, 80, 52, 38, 216, 7, 80-2)},
//{52, PreComputedParams(80, 52, 80, 52, 38, 191, 7, 80-2)},
//{56, PreComputedParams(80, 56, 80, 52, 38, 178, 7, 80-2)},
//{60, PreComputedParams(80, 60, 80, 52, 38, 165, 7, 80-2)},
{64, PreComputedParams(80, 64, 80, 60, 38, 160, 8, 80-2)},
	/* -- */
{72, PreComputedParams(80, 72, 80, 50, 40, 160, 8, 80-2)},
{80, PreComputedParams(80, 80, 80, 49, 40, 160, 9, 80-2)},
{88, PreComputedParams(80, 88, 80, 47, 40, 160, 9, 80-2)},
{96, PreComputedParams(80, 96, 80, 46, 40, 160, 10, 80-2)},
{104, PreComputedParams(80, 104, 80, 44, 40, 160, 11, 80-2)},
{112, PreComputedParams(80, 112, 80, 42, 40, 160, 12, 80-2)},
{128, PreComputedParams(80, 128, 80, 40, 40, 160, 13, 80-2)},
{144, PreComputedParams(80, 144, 80, 38, 40, 160, 13, 80-2)},
{160, PreComputedParams(80, 160, 80, 35, 40, 160, 13, 80-2)},
{176, PreComputedParams(80, 176, 80, 33, 40, 160, 13, 80-2)},
{192, PreComputedParams(80, 192, 80, 31, 40, 160, 13, 80-2)},
{208, PreComputedParams(80, 208, 80, 29, 40, 160, 13, 80-2)},
{224, PreComputedParams(80, 224, 80, 27, 40, 160, 13, 80-2)},
{240, PreComputedParams(80, 240, 80, 25, 40, 160, 13, 80-2)},
{256, PreComputedParams(80, 256, 80, 23, 40, 160, 14, 80-2)},
{320, PreComputedParams(80, 320, 80, 17, 40, 160, 14, 80-2)},
{384, PreComputedParams(80, 384, 80, 11, 40, 160, 14, 80-2)},
{448, PreComputedParams(80, 448, 80, 5, 40, 160, 14, 80-2)},
{512, PreComputedParams(80, 512, 80, 2, 40, 160, 14, 80-2)},
{640, PreComputedParams(80, 640, 80, 2, 40, 160, 14, 80-2)},
{768, PreComputedParams(80, 768, 80, 2, 40, 160, 15, 80-2)},
{896, PreComputedParams(80, 896, 80, 2, 40, 160, 15, 80-2)},
{1024, PreComputedParams(80, 1024, 80, 2, 40, 160, 15, 80-2)},
};
std::map<long , PreComputedParams> params_100_noisy_x0 {
//{n, PreComputedParams(lambda, n, eta, rho, rho_0, gamma, log_b, log_delta)},
{8, PreComputedParams(100, 8, 100, 73, 58, 1372, 7, 100-2)},
{10, PreComputedParams(100, 10, 100, 73, 58, 1098, 7, 100-2)},
//{12, PreComputedParams(100, 12, 100, 73, 58, 915, 7, 100-2)},
{16, PreComputedParams(100, 16, 100, 73, 58, 686, 7, 100-2)},
//{20, PreComputedParams(100, 20, 100, 73, 58, 549, 7, 100-2)},
//{24, PreComputedParams(100, 24, 100, 73, 58, 458, 7, 100-2)},
//{28, PreComputedParams(100, 28, 100, 73, 58, 392, 7, 100-2)},
{32, PreComputedParams(100, 32, 100, 73, 58, 343, 7, 100-2)},
//{36, PreComputedParams(100, 36, 100, 73, 58, 305, 7, 100-2)},
//{40, PreComputedParams(100, 40, 100, 73, 58, 275, 7, 100-2)},
//{44, PreComputedParams(100, 44, 100, 73, 58, 250, 7, 100-2)},
//{48, PreComputedParams(100, 48, 100, 73, 58, 229, 7, 100-2)},
{52, PreComputedParams(100, 52, 100, 73, 58, 212, 7, 100-2)},
	/* -- */
{56, PreComputedParams(100, 56, 100, 73, 59, 200, 9, 100-2)},
{60, PreComputedParams(100, 60, 100, 72, 59, 200, 10, 100-2)},
{64, PreComputedParams(100, 64, 100, 71, 59, 200, 11, 100-2)},
{72, PreComputedParams(100, 72, 100, 69, 59, 200, 11, 100-2)},
{80, PreComputedParams(100, 80, 100, 68, 59, 200, 11, 100-2)},
{88, PreComputedParams(100, 88, 100, 66, 59, 200, 12, 100-2)},
{96, PreComputedParams(100, 96, 100, 65, 59, 200, 12, 100-2)},
{104, PreComputedParams(100, 104, 100, 63, 59, 200, 13, 100-2)},
{112, PreComputedParams(100, 112, 100, 62, 59, 200, 14, 100-2)},
{128, PreComputedParams(100, 128, 100, 59, 59, 200, 17, 100-2)},
{144, PreComputedParams(100, 144, 100, 57, 59, 200, 16, 100-2)},
{160, PreComputedParams(100, 160, 100, 55, 59, 200, 16, 100-2)},
{176, PreComputedParams(100, 176, 100, 53, 59, 200, 16, 100-2)},
{192, PreComputedParams(100, 192, 100, 51, 59, 200, 16, 100-2)},
{208, PreComputedParams(100, 208, 100, 49, 59, 200, 17, 100-2)},
{224, PreComputedParams(100, 224, 100, 47, 59, 200, 17, 100-2)},
{240, PreComputedParams(100, 240, 100, 45, 59, 200, 17, 100-2)},
{256, PreComputedParams(100, 256, 100, 43, 59, 200, 17, 100-2)},
{320, PreComputedParams(100, 320, 100, 36, 59, 200, 17, 100-2)},
{384, PreComputedParams(100, 384, 100, 30, 59, 200, 17, 100-2)},
{448, PreComputedParams(100, 448, 100, 25, 59, 200, 17, 100-2)},
{512, PreComputedParams(100, 512, 100, 19, 59, 200, 17, 100-2)},
{576, PreComputedParams(100, 576, 100, 15, 59, 200, 17, 100-2)},
{640, PreComputedParams(100, 640, 100, 10, 59, 200, 16, 100-2)},
{704, PreComputedParams(100, 704, 100, 6, 59, 200, 16, 100-2)},
{768, PreComputedParams(100, 768, 100, 2, 59, 200, 16, 100-2)},
{832, PreComputedParams(100, 832, 100, 2, 59, 200, 16, 100-2)},
{896, PreComputedParams(100, 896, 100, 2, 59, 200, 16, 100-2)},
{960, PreComputedParams(100, 960, 100, 2, 59, 200, 16, 100-2)},
{1024, PreComputedParams(100, 1024, 100, 2, 59, 200, 16, 100-2)},
};

std::map<long , PreComputedParams> params_80_private_x0 {
//{n, PreComputedParams(lambda, n, eta, rho, rho_0, gamma, log_b, log_delta)},
{8, PreComputedParams(80, 8, 80, 50, 38, 1424, 7, 80-2)},
{10, PreComputedParams(80, 10, 80, 50, 38, 1139, 7, 80-2)},
{12, PreComputedParams(80, 12, 80, 50, 38, 950, 7, 80-2)},
{16, PreComputedParams(80, 16, 80, 50, 38, 712, 7, 80-2)},
{20, PreComputedParams(80, 20, 80, 50, 38, 570, 7, 80-2)},
{24, PreComputedParams(80, 24, 80, 50, 38, 474, 7, 80-2)},
{28, PreComputedParams(80, 28, 80, 50, 38, 407, 7, 80-2)},
{32, PreComputedParams(80, 32, 80, 50, 38, 356, 7, 80-2)},
{36, PreComputedParams(80, 36, 80, 50, 38, 316, 7, 80-2)},
{40, PreComputedParams(80, 40, 80, 50, 38, 285, 7, 80-2)},
{44, PreComputedParams(80, 44, 80, 50, 38, 259, 7, 80-2)},
{48, PreComputedParams(80, 48, 80, 50, 38, 238, 7, 80-2)},
{52, PreComputedParams(80, 52, 80, 50, 38, 219, 7, 80-2)},
{56, PreComputedParams(80, 56, 80, 50, 38, 204, 7, 80-2)},
{60, PreComputedParams(80, 60, 80, 50, 38, 190, 7, 80-2)},
{64, PreComputedParams(80, 64, 80, 50, 38, 178, 7, 80-2)},
	/*  ---- */
{72, PreComputedParams(80, 72, 80, 50, 53, 160, 7, 80-2)},
{80, PreComputedParams(80, 80, 80, 48, 53, 160, 8, 80-2)},
{88, PreComputedParams(80, 88, 80, 46, 53, 160, 10, 80-2)},
{96, PreComputedParams(80, 96, 80, 45, 53, 160, 11, 80-2)},
{104, PreComputedParams(80, 104, 80, 43, 53, 160, 13, 80-2)},
{112, PreComputedParams(80, 112, 80, 42, 53, 160, 14, 80-2)},
{128, PreComputedParams(80, 128, 80, 39, 53, 160, 17, 80-2)},
{144, PreComputedParams(80, 144, 80, 37, 53, 160, 19, 80-2)},
{160, PreComputedParams(80, 160, 80, 34, 53, 160, 22, 80-2)},
{176, PreComputedParams(80, 176, 80, 32, 53, 160, 24, 80-2)},
{192, PreComputedParams(80, 192, 80, 30, 53, 160, 26, 80-2)},
{208, PreComputedParams(80, 208, 80, 28, 53, 160, 28, 80-2)},
{224, PreComputedParams(80, 224, 80, 26, 53, 160, 30, 80-2)},
{240, PreComputedParams(80, 240, 80, 24, 53, 160, 32, 80-2)},
{256, PreComputedParams(80, 256, 80, 22, 53, 160, 34, 80-2)},
{320, PreComputedParams(80, 320, 80, 15, 53, 160, 41, 80-2)},
{384, PreComputedParams(80, 384, 80, 9, 53, 160, 47, 80-2)},
{448, PreComputedParams(80, 448, 80, 3, 53, 160, 53, 80-2)},
{512, PreComputedParams(80, 512, 80, 2, 53, 160, 54, 80-2)},
{576, PreComputedParams(80, 576, 80, 2, 53, 160, 54, 80-2)},
{640, PreComputedParams(80, 640, 80, 2, 53, 160, 54, 80-2)},
{704, PreComputedParams(80, 704, 80, 2, 53, 160, 54, 80-2)},
{768, PreComputedParams(80, 768, 80, 2, 53, 160, 54, 80-2)},
{832, PreComputedParams(80, 832, 80, 2, 53, 160, 54, 80-2)},
{896, PreComputedParams(80, 896, 80, 2, 53, 160, 54, 80-2)},
{960, PreComputedParams(80, 960, 80, 2, 53, 160, 54, 80-2)},
{1024, PreComputedParams(80, 1024, 80, 2, 53, 160, 54, 80-2)},
};
std::map<long , PreComputedParams> params_100_private_x0 {
//{n, PreComputedParams(lambda, n, eta, rho, rho_0, gamma, log_b, log_delta)},
{8, PreComputedParams(100, 8, 100, 73, 0, 1372, 7, 100-2)},
{12, PreComputedParams(100, 12, 100, 73, 77, 915, 7, 100-2)},
{16, PreComputedParams(100, 16, 100, 73, 77, 686, 7, 100-2)},
{20, PreComputedParams(100, 20, 100, 73, 58, 549, 7, 100-2)},
{24, PreComputedParams(100, 24, 100, 73, 58, 458, 7, 100-2)},
{28, PreComputedParams(100, 28, 100, 73, 58, 392, 7, 100-2)},
{32, PreComputedParams(100, 32, 100, 73, 58, 343, 7, 100-2)},
{36, PreComputedParams(100, 36, 100, 73, 58, 305, 7, 100-2)},
{40, PreComputedParams(100, 40, 100, 73, 58, 275, 7, 100-2)},
{44, PreComputedParams(100, 44, 100, 73, 58, 250, 7, 100-2)},
{48, PreComputedParams(100, 48, 100, 73, 58, 229, 7, 100-2)},
{52, PreComputedParams(100, 52, 100, 73, 58, 212, 7, 100-2)},
	/* -- */
{60, PreComputedParams(100, 60, 100, 72, 0, 200, 7, 100-2)},
{64, PreComputedParams(100, 64, 100, 72, 0, 200, 11, 100-2)},
{72, PreComputedParams(100, 72, 100, 70, 0, 200, 11, 100-2)},
{80, PreComputedParams(100, 80, 100, 68, 0, 200, 11, 100-2)},
{88, PreComputedParams(100, 88, 100, 66, 0, 200, 12, 100-2)},
{96, PreComputedParams(100, 96, 100, 65, 0, 200, 13, 100-2)},
{104, PreComputedParams(100, 104, 100, 63, 0, 200, 15, 100-2)},
{112, PreComputedParams(100, 112, 100, 62, 0, 200, 17, 100-2)},
{128, PreComputedParams(100, 128, 100, 59, 0, 200, 19, 100-2)},
{144, PreComputedParams(100, 144, 100, 57, 0, 200, 20, 100-2)},
{160, PreComputedParams(100, 160, 100, 54, 0, 200, 22, 100-2)},
{176, PreComputedParams(100, 176, 100, 52, 0, 200, 24, 100-2)},
{192, PreComputedParams(100, 192, 100, 50, 0, 200, 26, 100-2)},
{208, PreComputedParams(100, 208, 100, 48, 0, 200, 28, 100-2)},
{224, PreComputedParams(100, 224, 100, 46, 0, 200, 30, 100-2)},
{240, PreComputedParams(100, 240, 100, 44, 0, 200, 32, 100-2)},
{256, PreComputedParams(100, 256, 100, 42, 0, 200, 36, 100-2)},
{320, PreComputedParams(100, 320, 100, 35, 0, 200, 41, 100-2)},
{384, PreComputedParams(100, 384, 100, 29, 0, 200, 47, 100-2)},
{448, PreComputedParams(100, 448, 100, 23, 0, 200, 53, 100-2)},
{512, PreComputedParams(100, 512, 100, 18, 0, 200, 60, 100-2)},
{576, PreComputedParams(100, 576, 100, 13, 0, 200, 64, 100-2)},
{640, PreComputedParams(100, 640, 100, 8, 0, 200, 68, 100-2)},
{704, PreComputedParams(100, 704, 100, 4, 0, 200, 72, 100-2)},
{768, PreComputedParams(100, 768, 100, 2, 0, 200, 75, 100-2)},
{832, PreComputedParams(100, 832, 100, 2, 0, 200, 75, 100-2)},
{896, PreComputedParams(100, 896, 100, 2, 0, 200, 75, 100-2)},
{960, PreComputedParams(100, 960, 100, 2, 0, 200, 75, 100-2)},
{1024, PreComputedParams(100, 1024, 100, 2, 0, 200, 76, 100-2)},
};


#endif
