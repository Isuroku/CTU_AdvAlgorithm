// Assignement_5.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "IOSwitcher.h"
#include <vector>
#include <algorithm>
#include <climits>
#include <map>

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
	"Pd/pub11.in", //47 58
	"Pd/pub12.in", //152 209
};

struct SStringPart
{
public:
	string string_value;
	size_t length;

	SStringPart(const string& dst, const size_t dst_len)
	{
		string_value = dst;
		length = dst_len;
	}
};

struct StringPartCmp
{
	bool operator()(const SStringPart& lhs, const SStringPart& rhs) const
	{
		const int cmp_res = strcmpi(lhs.string_value.c_str(), rhs.string_value.c_str());
		if (cmp_res == 0)
			return lhs.length < rhs.length;
		return cmp_res < 0;
	}
};

map<SStringPart, int, StringPartCmp> _cache_dist;
vector<vector<size_t>> _matrix;
int levenshtein_distance(const string& src, const string& dst, const size_t dst_len)
{
	const SStringPart part(dst, dst_len);
	if (_cache_dist.find(part) != _cache_dist.end())
		return _cache_dist[part];

	const size_t m = src.size();
	const size_t n = min(dst_len, dst.size());
	if (m == 0)
		return n;
	if (n == 0)
		return m;

	//vector<vector<size_t>> matrix(m + 1);
	for (size_t i = 0; i < _matrix.size(); ++i)
		_matrix[i].clear();
	_matrix.clear();
	
	_matrix.resize(m + 1);
	for (size_t i = 0; i <= m; ++i) 
	{
		_matrix[i].resize(n + 1);
		_matrix[i][0] = i;
	}
	for (size_t i = 0; i <= n; ++i)
		_matrix[0][i] = i;

	for (size_t i = 1; i <= m; ++i) 
	{
		for (size_t j = 1; j <= n; ++j) 
		{
			const size_t cost = src[i - 1] == dst[j - 1] ? 0 : 1;
			const size_t above_cell = _matrix[i - 1][j];
			const size_t left_cell = _matrix[i][j - 1];
			const size_t diagonal_cell = _matrix[i - 1][j - 1];
			_matrix[i][j] = min(min(above_cell + 1, left_cell + 1), diagonal_cell + cost);
		}
	}

	const int res = _matrix[m][n];
	_cache_dist[part] = res;
	return res;
}

map<string, int> _cache;

int find_max_length_train2(const string& pattern, const int change_count, bool max_select, const string& formation)
{
	const size_t formation_len = formation.size();
	if (formation_len == 0)
		return 0;
	if (_cache.find(formation) != _cache.end())
		return _cache[formation];

	int max_value = max_select ? INT_MAX - 1: INT_MIN + 1;
	const size_t pattern_len = pattern.length();
	const size_t min_str_len = pattern_len - change_count;

	if (formation.size() < min_str_len)
		return max_value;

	size_t max_str_len = pattern_len + change_count;
	max_str_len = min(max_str_len, formation_len);

	for(size_t i = min_str_len; i <= max_str_len; ++i)
	{
		const int d = levenshtein_distance(pattern, formation, i);
		if (d <= change_count)
		{
			const string sunstring = formation.substr(i, formation.size() - i);
			const int child_res = find_max_length_train2(pattern, change_count, max_select, sunstring);
			if ((max_select && (child_res < max_value)) || (!max_select && (child_res > max_value)))
			{
				max_value = child_res;
				if (max_value == 1 && i < max_str_len - 1) //������ 1 ������ 0, � �� ������ ���� ��� ������ ��������
					i = max_str_len - 1;
			}
		}
	}

	const int res = max_value + 1;
	_cache[formation] = res;
	return res;
}

int find_min_length_train2(const string& pattern, const int change_count, const string& formation)
{
	if (formation.size() == 0)
		return 0;

	if (_cache.find(formation) != _cache.end())
		return _cache[formation];

	int max_value = INT_MIN + 1;
	
	for (size_t i = 1; i <= formation.size(); ++i)
	{
		const int d = levenshtein_distance(pattern, formation, i);
		if (d <= change_count)
		{
			const int child_res = find_min_length_train2(pattern, change_count, formation.substr(i, formation.size() - i));
			if (child_res > max_value)
				max_value = child_res;
		}
	}

	const int res = max_value + 1;
	_cache[formation] = res;
	return res;
}

//void test(const string& pattern)
//{
//	//lstnnt - pattern
//	//tnt lsdtnttntl sdlsdtnt
//	const string t = "lsdtnttntl";
//	int d = levenshtein_distance(pattern, t, t.size());
//}

int main()
{
	string fn = "";
	const int test_n = -1;
	const bool from_file = test_n >= 0 && test_n < static_cast<int>(arr_file_names->length());
	if (from_file)
		fn = arr_file_names[test_n];

	CIOSwitcher IOSwitcher(from_file, fn);

	string formation;
	IOSwitcher.getline(formation);

	string pattern;
	IOSwitcher.getline(pattern);

	string s_change_count;
	IOSwitcher.getline(s_change_count);
	int change_count;
	if (sscanf(s_change_count.c_str(), "%i", &change_count) != 1)
	{
		cerr << "read change_count was wrong";
		return 1;
	}

	//test(pattern);

	const int max_length_train = find_max_length_train2(pattern, change_count, true, formation);

	_cache.clear();
	const int min_length_train = find_max_length_train2(pattern, change_count, false, formation);

	cout << max_length_train << " " << min_length_train;

    return 0;
}

