#include "limiter.hpp"

limiter::Bucket::Bucket(const uint16_t rate, const uint16_t per)
	: rate(rate),
	  per(per),
	  allowance(rate) { }

bool limiter::Bucket::can_spend(const uint16_t count) {
	const auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> passed = now - last_check;
	last_check = now;
	allowance += passed.count() * ((float)rate / per);
	if(allowance > rate){
		allowance = rate;
	}
	if(allowance < count){
		return false;
	}
	allowance -= count;
	return true;
}


limiter::Simple::Simple(const float rate)
	: rate(rate) { }

bool limiter::Simple::can_spend() {
	const auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> passed = now - last_check;
	if(passed.count() < rate){
		return false;
	}
	last_check = now;
	return true;
}
