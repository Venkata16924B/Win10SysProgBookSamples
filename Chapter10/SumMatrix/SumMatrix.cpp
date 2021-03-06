// SumMatrix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Inc\Matrix.h"

long long SumMatrix1(const Matrix<int>& m) {
	long long sum = 0;
	for (int r = 0; r < m.Rows(); ++r)
		for (int c = 0; c < m.Columns(); ++c)
			sum += m[r][c];

	return sum;
}

long long SumMatrix2(const Matrix<int>& m) {
	long long sum = 0;
	for (int c = 0; c < m.Columns(); ++c)
		for (int r = 0; r < m.Rows(); ++r)
			sum += m[r][c];

	return sum;
}

using namespace std;

int main() {

	int size = 256;
	cout << "Type" << setw(20) << "Size" << setw(20) << "Sum" << setw(20) << "Time (nsec)" << endl;
	cout << string(65, '-').c_str() << endl;

	LARGE_INTEGER freq, start, end;
	::QueryPerformanceFrequency(&freq);

	while (size <= 1 << 14) {
		Matrix<int> m(size, size);
		stringstream ss;
		ss << size << " X " << size;
		auto sizes = ss.str();

		int x = 0;
		for (int c = 0; c < m.Columns(); ++c)
			for (int r = 0; r < m.Rows(); ++r)
				m[r][c] = ++x;

		::QueryPerformanceCounter(&start);
		auto sum = SumMatrix1(m);
		::QueryPerformanceCounter(&end);

		auto duration = 1000000 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
		cout << "Row major " << setw(15) << right << sizes.c_str() << setw(20) << right << sum << setw(12) << right << duration << " usec" << endl;

		::QueryPerformanceCounter(&start);
		sum = SumMatrix2(m);
		::QueryPerformanceCounter(&end);

		duration = 1000000 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
		cout << "Col Major " << setw(15) << right << sizes.c_str() << setw(20) << right << sum << setw(12) << right << duration << " usec" << endl << endl;

		size *= 2;
	}

	return 0;
}

