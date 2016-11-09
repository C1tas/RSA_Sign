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

long long GCD(long long a, long long b) {
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

int check_prime_in_thounsand_prime(long long num) {
	if (DEBUG) {
		printf("Doing checking in thounsand prime...\n");
	}
	int i = 0;
	
	for (i; i < 168; i++) {
		long long remainder = num % thousand_prime[i];
		if (num == thousand_prime[i]) {
			return 1;
		}
		else if (remainder == 0) {
			if (DEBUG) {
				printf("%lld mod %d, and remainder is %lld.\n", num, thousand_prime[i], remainder);
				printf("Thounsand checking faild, the num is a composite.\n\n");
			}
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
该算法用于判断一个大于 3 的奇数 n 是否素数。参数 k 用于决定 n 是素数的概率。
该算法能够肯定地判断 n 是合数，但是只能说 n 可能是素数。
第 01 行，将 n – 1 分解为 2s·d  的形式，这里 d 是奇数。
第 02 行，将以下步骤(第 03 到 10 行)循环 k 次。
第 03 行，◇在 [2, n - 2] 的范围中独立和随机地选择一个正整数 a 。
第 04 行，◇计算该序列的第一个值：x ← ad mod n 。
第 05 行，◇如果该序列的第一个数是 1 或者 n - 1，符合上述条件，n 可能是素数，转到第 03 行进行一下次循环。
第 06 行，◇循环执行第 07 到 09 行，顺序遍历该序列剩下的 s – 1 个值。
第 07 行，◇◇计算该序列的下一个值：x ← x2 mod n 。
第 08 行，◇◇如果这个值是 1 ，但是前边的值不是 n - 1，不符合上述条件，因此 n 肯定是合数，算法结束。
第 09 行，◇◇如果这个值是 n - 1，因此下一个值一定是 1，符合上述条件，n 可能是素数，转到第 03 行进行下一次循环。
第 10 行，◇发现该序列不是以 1 结束，不符合上述条件，因此 n 肯定是合数，算法结束。
第 11 行，已经对 k 个独立和随机地选择的 a 值进行了检验，因此判断 n 非常有可能是素数，算法结束。
在一次检验中，该算法出错的可能顶多是四分之一。如果我们独立地和随机地选择 a 进行重复检验，一旦此算法报告 n 是合数，
我们就可以确信 n 肯定不是素数。但如果此算法重复检验 25 次报告都报告说 n 可能是素数，
则我们可以说 n “几乎肯定是素数”。
因为这样一个 25 次的检验过程给出关于它的输入的错误信息的概率小于 (1/4)25。
这种机会小于 1015 分之一。
*/
int check_miller_rabin(long long num) {
	printf("Doing Miller_Rabin checking...\nChecking Num is %lld\n", num);
	long long d, s, t;
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
		long long a = rand() % (num - 1 - 2 + 1) + 2;
		if (DEBUG) {
			printf("The random num a is %lld, the factor d is %lld, the factor s is %lld.\n", a, d, s);
		}
		
		k += 1;
		if (GCD(a, num) != 1) {
			continue;
		}
		long long x = multiply_calculation_method_square(a, d, num);
		if (DEBUG) {
			printf("The result of a**d mod N is %lld.\n", x);
		}
		if (x == 1 || x == num - 1) {
			continue;
		}
		else {
			long long r = 0;
			for (r; r <= s - 1; r++) {
				long long n_x = multiply_calculation_method_square(a, 2 ^ r*d, num);
				if (DEBUG) {
					printf("The result of %lld in (0, s-1) , (a**(d * 2**r)):%lld**(%lld * 2**%lld) mod N is %lld.\n", r, a, d, r, x);
				}
				if (n_x == (num - 1)) {
					continue;
				}
				else if (n_x == 1 && x != num - 1) {
					printf("Mailler_Rabin checking faild, the num is a composite.\n\n");
					return 0;
				}
			}
		}
	}
	return 1;
}

long long randPrime(long long min_border, long long border) {

}

int main(void) {
	int x = 5, y = 20, z = 3;
	srand((unsigned int)time(NULL));
	// printf("%lld", repeat_calculation_method_square(x, y, z));

	long long num = 8;
	struct my_binary demo_binary;
	demo_binary = trans_to_binary(num);

	// printf("%lld\n", multiply_calculation_method_square(7, 17, 9));

	long long prime = 9;
	// long long prime = 7368811;
	// printf("%d", check_prime_thounsand(prime));
	//srand((unsigned)time(NULL));
	check_prime_in_thounsand_prime(prime);
	check_miller_rabin(prime);

	getchar();
}