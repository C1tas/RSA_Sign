#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


#define MAXLENGTH 100
#define DEBUG 1

int thousand_prime[] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,
									109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,
									227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,
									347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,
									461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,
									599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,
									727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,
									859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

struct my_binary {
	int binary[MAXLENGTH];
	int length;
};

long long gcd(long long a, long long b) {
	long long temp;
	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}


struct my_binary trans_to_binary(long long num) {
	int i = 0;
	struct my_binary tmp_struct;

	while (num) {
		tmp_struct.binary[i] = num % 2;
		num /= 2;
		i++;
	}
	tmp_struct.length = i - 1;
	return tmp_struct;
}

int check_prime_thounsand(long long num) {
	int i = 0;
	
	for (i; i < 168; i++) {
		long long remainder = num % thousand_prime[i];
		if (num == thousand_prime[i]) {
			return 1;
		}
		else if (remainder == 0) {
			return 0;
		}
		else {
			if (DEBUG) {
				printf("%lld mod %d, and remainder is %lld.\n", num, thousand_prime[i], remainder);
			}
			continue;
		}
	}
	return 1;
}

long long repeat_calculation_method_square(long long x, long long n, long long m) {
	long long a = 1, b = x; //i=0的时候b = x^(2^0) = x
	while (n)
	{
		if (n % 2 == 1)
			a = a * b % m;
		b = b * b % m;
		n /= 2;
	}
	return a;
}

long long multiply_calculation_method_square(long long x, long long n, long long m) {
	struct my_binary tmp_binary;
	long long remainder = 1;
	tmp_binary = trans_to_binary(n);
	int i = tmp_binary.length;
	for (i; i >= 0; i--) {
		if (tmp_binary.binary[i]) {
			remainder = remainder*remainder * x % m;
		}
		else {
			remainder = remainder*remainder % m;
		}
	}
	return remainder;
	
}


/*
要测试 {\displaystyle N} N是否为素数，首先将 {\displaystyle N-1} N-1分解为 
{\displaystyle 2^{s}d} 2^{s}d。
在每次测试开始时，先随机选一个介于 {\displaystyle [1,N-1]} [1,N-1]的整数 {\displaystyle a} a，
之后如果对所有的 {\displaystyle r\in [0,s-1]} r\in [0,s-1]，
若 {\displaystyle a^{d}\mod N\neq 1} a^{d}\mod N\neq 1
且 {\displaystyle a^{2^{r}d}\mod N\neq -1} a^{{2^{{r}}d}}\mod N\neq -1，则N是合数。
否则， {\displaystyle N} N有 {\displaystyle 3/4} 3/4的概率为素数。
*/
int check_miller_rabin(long long num) {
	long long d, a, r, s, t;
	d = num - 1;
	s = 0;
	t = 5;
	while (d % 2 == 0) {
		d /= 2;
		s += 1;
	}
	int k = 0;
	
	while (k < t) {
		//srand((unsigned)time(NULL));
		long long a = rand() % (d - 1 + 1) + 1;
		k += 1;
		if (gcd(a, num) != 1) {
			continue;
		}
		long long x = multiply_calculation_method_square(a, d, num);
		if (x != 1) {
			long long r = 0;
			for (r; r <= s - 1; r++) {
				x = multiply_calculation_method_square(a, 2 ^ r*d, num);
				if (x = (num - 1)) {
					return 1;
				}
			}
		}
		else if (x = 1) {
			break;
		}
	}
	return 0;
}


int main(void) {
	int x = 5, y = 20, z = 3;
	srand(time(NULL));
	// printf("%lld", repeat_calculation_method_square(x, y, z));

	long long num = 8;
	struct my_binary demo_binary;
	demo_binary = trans_to_binary(num);

	// printf("%lld\n", multiply_calculation_method_square(7, 17, 9));

	long long prime = 7368811;
	// printf("%d", check_prime_thounsand(prime));
	//srand((unsigned)time(NULL));
	printf("%d.\n", check_miller_rabin(prime));
	getchar();
}