#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>
#include <assert.h>

using namespace std;

template <typename Fn>
struct less_to_greater_st {
	less_to_greater_st(Fn&& less_fn) : _less(forward<Fn>(less_fn)) {}
	template <typename T1, typename T2>
	bool operator()(T1&& a, T2&& b) {
		return _less(forward<T2>(b), forward<T1>(a));
	}
private:
	Fn&& _less;
};

template <typename Fn>
less_to_greater_st<Fn> less_to_greater(Fn&& f) {
	return less_to_greater_st<Fn>(forward<Fn>(f));
}

struct Point {
	Point(int x, int y) : x(x), y(y) {}
	int x, y;
};

void sort_points_test() {
	vector<Point> pt_vec;
	pt_vec.emplace_back(1,2);
	pt_vec.emplace_back(4,2);
	pt_vec.emplace_back(2,3);
	pt_vec.emplace_back(5,3);

	auto point_less = [] (Point& a, Point& b) {
		return a.x < b.x || a.x == b.x && a.y < b.y;
	};
	auto point_greater = less_to_greater(point_less);

	sort(begin(pt_vec), end(pt_vec), point_less);
	assert(pt_vec[0].x == 1 && pt_vec[0].y == 2);
	sort(begin(pt_vec), end(pt_vec), point_greater);
	assert(pt_vec[0].x == 5 && pt_vec[0].y == 3);
}

void sort_int_test() {
	vector<int> int_vec;
	int_vec.emplace_back(1);
	int_vec.emplace_back(2);
	int_vec.emplace_back(6);
	int_vec.emplace_back(9);

	auto int_less = less<int>();
	auto int_greater = less_to_greater(int_less);
	sort(begin(int_vec), end(int_vec), int_less);
	assert(int_vec[0] == 1);
	sort(begin(int_vec), end(int_vec), int_greater);
	assert(int_vec[0] == 9);
}

void wrong_code() {
	vector<int> int_vec;
	int_vec.emplace_back(1);
	int_vec.emplace_back(2);
	int_vec.emplace_back(6);
	int_vec.emplace_back(9);
	auto int_greater = less_to_greater(less<int>());
	assert(int_greater(4, 3));
#if WRONG_CODE
	sort(begin(int_vec), end(int_vec), int_greater);
	sort(begin(int_vec), end(int_vec), less_to_greater(less<int>()))
#endif
}

int main() {
	sort_points_test();
	sort_int_test();
	wrong_code();
	return 0;
}

