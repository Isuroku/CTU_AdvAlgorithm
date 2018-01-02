// Assignement_6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "IOSwitcher.h"
#include <vector>
#include <algorithm>
#include "uint128_t.h"
#include <set>

 

typedef uint128_t unint;
typedef unsigned __int64 unint64;

unsigned __int64 atoui64(const char *szUnsignedInt) {
	return _strtoui64(szUnsignedInt, NULL, 10);
}

const string arr_file_names[] =
{
	"Pd/pub01.in", //4 7
	"Pd/pub02.in", //2 3
	"Pd/pub03.in", //3 8
	"Pd/pub04.in", //5 13
	"Pd/pub05.in", //4 23
	"Pd/pub06.in", //6 9
	"Pd/pub07.in", //20 94
	"Pd/pub08.in", //11 15
	"Pd/pub09.in", //62 125
	"Pd/pub10.in", //13 13
};



unint Pow(unint64 in_Number, unint64 in_Power)
{
	unint tmp = in_Number;

	if (in_Power == 0)
		return 1;
		

	for (unint64 i = 1; i < in_Power; i++)
		tmp *= in_Number;
		

	return tmp;
}

//vector<unint64> FindAllPrimes(unint64 in_LowBound, unint64 in_HighBound)
//{
//	vector<unint64> primes;
//	unint64 tmp = 0;
//
//	while (in_LowBound <= in_HighBound)
//	{
//		tmp = 0;
//
//		for (unint64 i = 2; i <= in_LowBound / 2; ++i)
//		{
//			if (in_LowBound % i == 0)
//			{
//				tmp = 1;
//				break;
//			}
//		}
//
//		if (tmp == 0)
//			primes.push_back(in_LowBound);
//
//		++in_LowBound;
//	}
//
//	return primes;
//}


int* FindAllPrimes(unint64 in_L, unint64 in_H)
{
	set
	for (unint64 i = 2; i*i <= in_H; i++)
	{
		if (arr[i] > 0)
		{
			for (unint64 k = 0, j = i * i; j <= in_N; k++, j = i * i + k * i)
				arr[j] = 0;
		}
	}

	return arr;
}



vector<unint64> FindAllPrimeFactors(unint64 in_M)
{
	unint64 z = 2;
	vector<unint64> prime_factors;

	while (z * z <= in_M)
	{
		if (in_M % z == 0)
		{
			prime_factors.push_back(z);
			in_M /= z;
		}
		else
			z++;
	}

	if (in_M > 1)
		prime_factors.push_back(in_M);

	return prime_factors;
}


vector<int> FindAllDivisors(int in_Number)
{
	vector<int> Divisors;

	for (int i = 1; i <= sqrt(in_Number); i++)
	{
		if (in_Number % i == 0)
		{
			if (in_Number / i == i)
				Divisors.push_back(i);
			else
			{
				Divisors.push_back(i);
				Divisors.push_back(in_Number / i);
			}
		}
	}

	return Divisors;
}

size_t FindAllDivisorCount(unint64 in_Number)
{
	size_t count = 0;

	for (int i = 1; i <= sqrt(in_Number); i++)
	{
		if (in_Number % i == 0)
		{
			count++;
			if (in_Number / i != i)
				count++;
		}
	}

	return count;
}


bool CheckCongruenceWithOne(const unint& in_Num1, unint64 modulo)
{
	unint n = in_Num1 - 1;
	unint d = n % modulo;
	return d == 0;
}

unint64 FindMod(unint64 inR, unint64 inPower, unint64 inM)
{
	unint64 left_power = inPower;
	unint64 max_value = 0xFFFFFFFFFFFFFFFF / inR;
	unint64 reminders = 1;
	while (left_power > 0)
	{
		unint64 piece = 1;
		while (piece < max_value && left_power > 0)
		{
			piece *= inR;
			left_power--;
		}

		unint64 int_part = piece / inM;
		unint64 int_remainder = piece - int_part * inM;
		reminders *= int_remainder;
	}

	unint64 int_part = reminders / inM;
	unint64 int_remainder = reminders - int_part * inM;
	return int_remainder;
}

size_t FindAllPrimitiveRootsInInterval(unint64 in_LowBound, unint64 in_HighBound, unint64 in_M, size_t in_NumberOfDivisors)
{
	vector<unint64> PrimeFactorsOfM;

	size_t count_roots = 0;
	
	PrimeFactorsOfM = FindAllPrimeFactors(in_M - 1);

	for (unint64 R = in_LowBound; R <= in_HighBound; R++)
	{
		if (FindAllDivisorCount(R) >= in_NumberOfDivisors)
		{
			bool R_is_bad = false;
			for (size_t i = 0; i < PrimeFactorsOfM.size() && !R_is_bad; i++)
			{
				unint64 p = PrimeFactorsOfM[i];
				unint64 power = (in_M - 1) / p;
				//unint r = Pow(R, power);
				//R_is_bad = CheckCongruenceWithOne(r, in_M);
				unint64 reminder = FindMod(R, power, in_M);
				R_is_bad = reminder == 1;
			}

			if (!R_is_bad)
			{
				count_roots++;
				//cerr << in_M << " " << R << endl;
			}
		}
	}

	return count_roots;
}




vector<unint64> FindSetS(vector<unint64> in_Primes, unint64 in_C, unint64 in_D, size_t in_E, int in_F)
{
	vector<unint64> SetS;

	for (size_t i = 0; i < in_Primes.size(); i++)
	{
		size_t root_count = FindAllPrimitiveRootsInInterval(in_C, in_D, in_Primes[i], in_F);
		if (root_count >= in_E)
		{
			SetS.push_back(in_Primes[i]);
		}
	}

	return SetS;
}

int main()
{
	string fn = "";
	size_t ind = 0;
	size_t tmp = 0;
	const int test_n = 2;

	const bool from_file = test_n >= 0 && test_n < static_cast<int>(arr_file_names->length());
	if (from_file)
		fn = arr_file_names[test_n];

	CIOSwitcher IOSwitcher(from_file, fn);

	string input_data;
	IOSwitcher.getline(input_data);

	//printf_s(input_data.c_str());


	ind = input_data.find(' ', 0);
	unint64 a = atoui64(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	ind = input_data.find(' ', tmp + 1);
	unint64 b = atoui64(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	ind = input_data.find(' ', tmp + 1);
	unint64 c = atoui64(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	ind = input_data.find(' ', tmp + 1);
	unint64 d = atoui64(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	ind = input_data.find(' ', tmp + 1);
	int e = atoi(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	ind = input_data.find(' ', tmp + 1);
	int f = atoi(input_data.substr(tmp, ind).c_str());
	tmp = ind;

	vector<unint64> primes;
	vector<unint64> SetS;

	int* primes_arr = FindAllPrimes(b);

	for (unint64 i = a; i <= b; i++)
		if (primes_arr[i] > 0)
			primes.push_back(i);

	SetS = FindSetS(primes, c, d, e, f);

	printf_s("%d", SetS.size());
	

    return 0;
}

