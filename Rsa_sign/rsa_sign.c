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
	long long a = 1, b = x; //i=0��ʱ��b = x^(2^0) = x
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
���㷨�����ж�һ������ 3 ������ n �Ƿ����������� k ���ھ��� n �������ĸ��ʡ�
���㷨�ܹ��϶����ж� n �Ǻ���������ֻ��˵ n ������������
�� 01 �У��� n �C 1 �ֽ�Ϊ 2s��d  ����ʽ������ d ��������
�� 02 �У������²���(�� 03 �� 10 ��)ѭ�� k �Ρ�
�� 03 �У����� [2, n - 2] �ķ�Χ�ж����������ѡ��һ�������� a ��
�� 04 �У����������еĵ�һ��ֵ��x �� ad mod n ��
�� 05 �У�����������еĵ�һ������ 1 ���� n - 1����������������n ������������ת���� 03 �н���һ�´�ѭ����
�� 06 �У���ѭ��ִ�е� 07 �� 09 �У�˳�����������ʣ�µ� s �C 1 ��ֵ��
�� 07 �У�����������е���һ��ֵ��x �� x2 mod n ��
�� 08 �У����������ֵ�� 1 ������ǰ�ߵ�ֵ���� n - 1��������������������� n �϶��Ǻ������㷨������
�� 09 �У����������ֵ�� n - 1�������һ��ֵһ���� 1����������������n ������������ת���� 03 �н�����һ��ѭ����
�� 10 �У����ָ����в����� 1 ������������������������� n �϶��Ǻ������㷨������
�� 11 �У��Ѿ��� k �������������ѡ��� a ֵ�����˼��飬����ж� n �ǳ��п������������㷨������
��һ�μ����У����㷨����Ŀ��ܶ������ķ�֮һ��������Ƕ����غ������ѡ�� a �����ظ����飬һ�����㷨���� n �Ǻ�����
���ǾͿ���ȷ�� n �϶�������������������㷨�ظ����� 25 �α��涼����˵ n ������������
�����ǿ���˵ n �������϶�����������
��Ϊ����һ�� 25 �εļ�����̸���������������Ĵ�����Ϣ�ĸ���С�� (1/4)25��
���ֻ���С�� 1015 ��֮һ��
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