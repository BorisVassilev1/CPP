#include <iostream>
#include <math.h>
#include <cstring>
#include <bitset>

/**
 * Домашно №0
 * компилира се с g++ -std=c++2a
 * */

namespace floats { 

	class floating {

		/*
		 * sign exp 6b     mantissa 17b
		 *    0|000000|0 00000000 0000000000
		 */
		uint8_t value[3];

		public:

		static floating zero;
		static floating inf;
		static floating minus_inf;
		static floating nan;
		
		// default constructor
		floating() : floating(0.f) {}

		floating(uint8_t a, uint8_t b, uint8_t c) : value{a, b, c} {}

		floating(uint8_t sign, uint8_t exp, uint32_t mantissa) {
			value[0] = 
				(sign     << 7 ) | 
				(exp      << 1 ) |
				(mantissa >> 16);
			value[1] = (mantissa >> 8);
			value[2] = (mantissa     );
		}

		// copy constructor
		floating(const floating& other) {
			memcpy(this, &other, sizeof(floating));
		}

		floating(float a) {
			uint32_t b = *(reinterpret_cast<uint32_t*>(&a));

			// separating the bits of the float
			//								        |       |       |       |
			uint8_t src_sign		= (b & 0b10000000000000000000000000000000) >> 31;
			uint8_t src_exp			= (b & 0b01111111100000000000000000000000) >> 23;
			uint32_t src_mantissa	= (b & 0b00000000011111111111111111111111);

			if(src_exp == 0 && src_mantissa == 0) { // if it is zero, do nothing
				//src_exp = 0; 
			} else if(src_exp == 255) { // if it is Infinity or NaN, fix the exponent
				src_exp = 63;
			} else {
				src_exp = (int16_t)src_exp - 127 + 31; // substract the bias and add the new one
			}
			src_mantissa >>= 6; // from 23-bit to 17-bit mantissa

			// compose the new number
			value[0] = 
				(src_sign     << 7 ) | 
				(src_exp      << 1 ) |
				(src_mantissa >> 16);
			value[1] = (src_mantissa >> 8);
			value[2] = (src_mantissa     );
		}

		// returns the mantissa
		uint32_t get_mantissa() const {
			return 
				((value[0] & 0b00000001) << 16) |
				((value[1] & 0b11111111) << 8 ) |
				((value[2] & 0b11111111)      );
		}

		// returns the sign: 0 for positive and 1 for negative.
		uint8_t get_sign() const {
			return (value[0] & 0b10000000) >> 7;
		}

		// returns the exponent
		int8_t get_exp() const {
			return ((value[0] & 0b01111110) >> 1);
		}

		// converts to float32
		float get_float() const {
			uint8_t exp = get_exp();
			uint32_t mantissa = get_mantissa();	
			uint8_t sign = get_sign();

			if(exp == 0 && mantissa == 0) {
				exp = 0;
			} else if(exp == 63) { // Infinity and NaN will be translated correctly
				exp = 255;
			} else {
				exp = (int16_t)exp - 31 + 127; // fix exponent bias
			}

			mantissa <<= 6; // shift left to convert to 23-bit mantissa

			// compose the new float
			uint32_t f = 
				(sign << 31) |
				(exp  << 23) |
				mantissa;

			return *(reinterpret_cast<float*> (&f));
		}

		floating operator + (const floating &b) const {
			// get the mantissas and add the prefix bit.
			uint32_t significand_a = get_mantissa() | (1 << 17);
			uint32_t significand_b = b.get_mantissa() | (1 << 17);

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			int8_t exp_diff = exp_a - exp_b;
			
			// nan checks
			if(
				(exp_a == 63 && exp_b == 63 && significand_a == 0 && significand_b == 0 && sign_a != sign_b) ||
				(exp_a == 63 && significand_a != (1 << 17)) ||
				(exp_b == 63 && significand_b != (1 << 17))
			  ) { // if +inf + -inf or -inf + +inf or either operand is nan
				return floating::nan;
			}
			
			// make the significand zero if it must be zero
			significand_a *= (exp_a != 0 || significand_a != (1 << 17));
			significand_b *= (exp_b != 0 || significand_b != (1 << 17));

			// align exponents
			if(exp_diff > 0) {
				significand_b >>= exp_diff;
				exp_b = exp_a;
			} else {
				significand_a >>= -exp_diff;
				exp_a = exp_b;
			}
			
			// signed integer multiplication
			int32_t significand_c = 
				(int32_t)significand_a * (sign_a ? -1 : 1) + 
				(int32_t)significand_b * (sign_b ? -1 : 1);

			// separate the sign
			uint8_t sign_c = significand_c > 0;
			significand_c = abs(significand_c);

			// those are either equal or at least one of them is zero, so a bitwise OR does the job
			uint8_t exp_c = exp_a | exp_b;

			int8_t offset = 32 - __builtin_clz(significand_c) - 18; // calculate how much the resulting significand must be shifted to normalize it.


			// shift the significand right to normalize it
			if(offset > 0) {
				significand_c >>= offset;
			} else {
				significand_c <<= -offset;
			}
			exp_c += offset; // change the exponent accordingly

			if(significand_c == 0) { // if it is zero, then the result is zero
				exp_c = 0;
				sign_c = 1;
			}

			if(exp_c == 63) significand_c = 0; // never return nan

			uint32_t mantissa_c = significand_c & ((1 << 17) - 1); // remove the additional 1 on 18th place

			return floating(!sign_c, exp_c, mantissa_c);
		}

		floating operator - () const { // just xor the sign bit
			floating n(*this);
			n.value[0] ^= (1 << 7);
			return n;
		}

		floating operator - (const floating& other) const { // add the negative equivalent
			return *this + (-other);
		}

		floating& operator += (const floating& other) {
			*this = *this + other;
			return *this;
		}

		floating& operator -= (const floating& other) {
			*this = *this - other;
			return *this;
		}

		floating& operator ++ () {
			*this += 1;
			return *this;
		}

		floating& operator -- () {
			*this -= 1;
			return *this;
		}

		floating operator ++ (int) {
			floating t = *this;
			++ *this;
			return t;
		}

		floating operator -- (int) {
			floating t = *this;
			-- *this;
			return t;
		}

		floating operator * (const floating& b) {
			// get the mantissas and add the prefix bit.
			uint32_t significand_a = get_mantissa() | (1 << 17);
			uint32_t significand_b = b.get_mantissa() | (1 << 17);

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			significand_a *= (exp_a != 0 || significand_a != (1 << 17)); // if either is zero, make the significand zero
			significand_b *= (exp_b != 0 || significand_b != (1 << 17));
			
			// nan checks
			if(
				(exp_a == 0  && exp_b == 63 && significand_a == 0         && significand_b == (1 << 17)) ||
				(exp_a == 63 && exp_b == 0  && significand_a == (1 << 17) && significand_b == 0        ) ||
				(exp_a == 63 && significand_a != (1 << 17)) ||
				(exp_b == 63 && significand_b != (1 << 17))
			  ) { // if inf/0 or 0/inf or either operand is nan
				return floating::nan;
			}

			// multiply the significands with more bits to prevent overflow
			uint64_t significand_c = 
				((uint64_t)significand_a) * 
				((uint64_t)significand_b);
			
			// != works too
			uint8_t sign_c = sign_a ^ sign_b; // xor the signs to get the result sign

			int16_t exp_new = (int16_t)exp_a - 31 + (int16_t)exp_b; // add the exponents noting the bias, but use more bits in case it overflows

			uint8_t offset = std::max(64 - __builtin_clzll(significand_c) - 18, 0); // calculate how much the resulting significand must be shifted to normalize it, making sure that the offset never gets negative (if one operand's significand is zero, there will be a 64 leading zeros)
			significand_c >>= offset; // shift the significand right to normalize it
			exp_new += offset - 17; // since both significands have 18 digits, the significand will always need to be shifted 17 bits right, even when both signifiacands are 1.0

			if(significand_c == 0) { // if we got sero, make it a real zero
				exp_new = 0;
			}

			uint8_t exp_c = exp_new; // this may be incorrect because of overflow
			if(exp_new > 63) { // so fix it
				exp_c = 63;
				significand_c = 0;
			} else if(exp_new < 0) {
				exp_c = 0;
				significand_c = 0;
			}

			if(exp_c == 63) significand_c = 0; // never return nan

			uint32_t mantissa_c = significand_c & ((1 << 17) - 1); // remove the additional 1 on the 18th place if it is there

			return floating(sign_c, exp_c, mantissa_c);
		}

		floating operator / (const floating& b) {
			// get the mantissas and add the prefix bit.
			uint32_t significand_a = get_mantissa() | (1 << 17);
			uint32_t significand_b = b.get_mantissa() | (1 << 17);

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			significand_a *= (exp_a != 0 || significand_a != (1 << 17)); // if either is zero, make the significand zero
			significand_b *= (exp_b != 0 || significand_b != (1 << 17));
			
			// nan checks
			if(
				(exp_a == 0  && exp_b == 0  && significand_a == 0         && significand_b == 0        ) ||
				(exp_a == 63 && exp_b == 63 && significand_a == (1 << 17) && significand_b == (1 << 17)) ||
				(exp_a == 63 && significand_a != (1 << 17)) ||
				(exp_b == 63 && significand_b != (1 << 17))
			  ) { // if 0/0 or inf/inf or either operand is nan
				return floating::nan;
			} else if(exp_b == 63 && significand_b == (1 << 17)) {
				return floating::zero;
			} else if(exp_a == 63 && significand_a == (1 << 17)) {
				return *this;
			}

			// != works too
			uint8_t sign_c = sign_a ^ sign_b;

			// shift the left operand's significand 17 bits so that the division can be done with integers, then divide
			uint64_t significand_c = (
				((uint64_t)significand_a << 17) /
				((uint64_t)significand_b      ));

			int16_t exp_new = (int16_t)exp_a - (int16_t)exp_b + 31; // subtract the exponents, accounting for the biases, using more bits in case it overflows

			uint8_t offset = -(64 - __builtin_clzll(significand_c) - 18); // look at the comment on the * operator..., but this time we will always get something with at most 17 bits, so will instead get its negative and shift left.
			significand_c <<= offset;
			exp_new -= offset;

			if(significand_c == 0) { // if we got sero, make it a real zero
				exp_new = 0;
			}

			uint8_t exp_c = exp_new; // this may be incorrect because of overflow
			if(exp_new > 63) { // so fix it
				exp_c = 63;
				significand_c = 0;
			} else if(exp_new < 0) {
				exp_c = 0;
				significand_c = 0;
			}

			if(exp_c == 63) significand_c = 0; // never return nan

			uint32_t mantissa_c = significand_c & ((1 << 17) - 1); // remove the additional 1 on the 18th place if it is there

			return floating(sign_c, exp_c, mantissa_c);
		}
		

		// comparison operators...

		bool operator > (const floating &b) const {
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return false;
			}


			if(sign_a     != sign_b    ) return sign_a     > sign_b    ;
			if(exp_a      != exp_b     ) return exp_a      > exp_b     ;
			if(mantissa_a != mantissa_b) return mantissa_a > mantissa_b;
			return false;
		}

		bool operator >= (const floating &b) const {
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return false;
			}

			if(sign_a     != sign_b    ) return sign_a     > sign_b    ;
			if(exp_a      != exp_b     ) return exp_a      > exp_b     ;
			if(mantissa_a != mantissa_b) return mantissa_a > mantissa_b;
			return true;
		}

		bool operator < (const floating &b) const {
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return false;
			}

			if(sign_a     != sign_b    ) return sign_a     < sign_b    ;
			if(exp_a      != exp_b     ) return exp_a      < exp_b     ;
			if(mantissa_a != mantissa_b) return mantissa_a < mantissa_b;
			return false;
		}

		bool operator <= (const floating &b) const {
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return false;
			}

			if(sign_a     != sign_b    ) return sign_a     < sign_b    ;
			if(exp_a      != exp_b     ) return exp_a      < exp_b     ;
			if(mantissa_a != mantissa_b) return mantissa_a < mantissa_b;
			return true;
		}

		bool operator == (const floating &b) const { // the automatically generated operator could have worked, but nans would have sometimes beed equal when they should never be
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return false;
			}

			if(
				sign_a     == sign_b    && 
				exp_a      == exp_b     &&
				mantissa_a == mantissa_b) {
				return true;
			}
			return false;
		}

		bool operator != (const floating &b) const { // the automatically generated operator could have worked, but nans would have sometimes beed equal when they should never be
			uint32_t mantissa_a = get_mantissa();
			uint32_t mantissa_b = b.get_mantissa();

			uint8_t exp_a = get_exp();
			uint8_t exp_b = b.get_exp();

			uint8_t sign_a = get_sign();
			uint8_t sign_b = b.get_sign();

			if(
				(exp_a == 63 && mantissa_a != 0) ||
				(exp_b == 63 && mantissa_b != 0)) { // if either operand is nan
				return true;
			}

			if(
				sign_a     != sign_b    || 
				exp_a      != exp_b     ||
				mantissa_a != mantissa_b) {
				return true;
			}
			return false;
		}
		
		// assignment operator
		floating& operator = (const floating& b) {
			std::memcpy(this, &b, sizeof(floating));

			return *this;
		}
		
		// debugging utility function
		void print_info() const {
			std::cout << "sign:     " << (int) get_sign() << std::endl;
			std::cout << "exponent: " << (int )get_exp() << std::endl;
			std::cout << "mantissa: " << std::bitset<18>(get_mantissa() | (1 << 17)) << std::endl;

			std::cout << "float:    " << get_float() << std::endl;
		}
		
		friend std::istream& operator >> (std::istream& in, floating& a) {
			float b;
			in >> b; 
			a = floating(b);
			return in;
		}

		friend std::ostream& operator << (std::ostream& out, floating& a) {
			return out << a.get_float();
		}
	};

	// useful constantants
	floating floating::zero			((uint8_t)0, (uint8_t)0 , (uint32_t)0);
	floating floating::inf			((uint8_t)0, (uint8_t)63, (uint32_t)0);
	floating floating::minus_inf	((uint8_t)1, (uint8_t)63, (uint32_t)0);
	floating floating::nan			((uint8_t)0, (uint8_t)63, (uint32_t)1);

}

using namespace floats;

int main() {
	floating start, end;
	int n;

	std::cin >> start >> end >> n; // input start, end and N

	floating sum_interval(0), error_interval(0), sum(0), error(0);
	int count = 0;
	for(int i = 0; i < n; i ++) {
		floating time, val;
		std::cin >> time >> val; // input a line

		// kahan summation
		floating y = val - error;
		floating t = sum + y;
		error = (t - sum) - y;
		sum = t;

		if(time > start && time < end) { // kahan summation
			count ++;

			floating y1 = val - error_interval;
			floating t1 = sum_interval + y1;
			error_interval = (t1 - sum_interval) - y1;
			sum_interval = t1;
		}
	}

	floating mean_interval = sum_interval / count;
	floating mean = sum / n;
	
	std::cout << mean << std::endl << mean_interval << std::endl << (mean == mean_interval) << std::endl;
}
