// Assignement_4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "IOSwitcher.h"
#include "Automaton.h"
#include "StringGen.h"

const string arr_file_names[] =
{
	"Pd/pub01.in", //baabaa
	"Pd/pub02.in", //bbdc
	"Pd/pub03.in", //gc
	"Pd/pub04.in", //bhbbc
	"Pd/pub05.in", //baaabaaaabababbaa
	"Pd/pub06.in", //baabbba
	"Pd/pub07.in", //bdcda
	"Pd/pub08.in", //ada
	"Pd/pub09.in", //cad
	"Pd/pub10.in", //cad
};

struct ReadResult
{
	string Alphabet;
	CAutomaton* A1;
	CAutomaton* A2;
};

void split(const string& instr, const string& delimeter, vector<string>& out_strings)
{
	const size_t delim_size = delimeter.length();
	const size_t buf_size = instr.length() + 1;
	char* buffer = new char[buf_size];
	size_t prev_pos = 0;
	size_t pos = instr.find(delimeter, prev_pos);
	while (pos < instr.length())
	{
		const size_t length = instr.copy(buffer, pos - prev_pos, prev_pos);
		buffer[length] = '\0';

		out_strings.push_back(string(buffer));

		prev_pos = pos + delim_size;
		pos = instr.find(delimeter, prev_pos);
	}

	if (pos == string::npos)
	{
		const size_t length = instr.copy(buffer, instr.length() - prev_pos, prev_pos);
		buffer[length] = '\0';

		out_strings.push_back(string(buffer));
	}
}


CAutomaton* ReadAutomaton(CIOSwitcher& IOSwitcher)
{
	string line;
	IOSwitcher.getline(line);

	int state_count, transition_count;
	if (sscanf(line.c_str(), "%i %i", &state_count, &transition_count) != 2)
	{
		cerr << "read state_count and transition_count was wrong";
		return NULL;
	}

	CAutomaton* A = new CAutomaton(state_count);
	for (size_t l = 0; l < static_cast<size_t>(transition_count); l++)
	{
		IOSwitcher.getline(line);

		int st_from, st_to;
		char ch;
		if (sscanf(line.c_str(), "%i %c %i", &st_from, &ch, &st_to) != 3)
		{
			cerr << "read state_count and transition_count was wrong";
			return NULL;
		}

		A->AddTransition(st_from, ch, st_to);
	}

	IOSwitcher.getline(line);

	vector<string> strings;
	split(line, string(" "), strings);

	for_each(strings.begin(), strings.end(), [A](const string& s)
	{
		int val;
		if (sscanf(s.c_str(), "%d", &val) != 1)
			cerr << "read finish state was wrong! " << s;
		else
			A->AddFinalState(val);
	});

	return A;
}

bool ReadSources(const int test_n, ReadResult& outResult)
{
	string fn = "";
	const bool from_file = test_n >= 0 && test_n < static_cast<int>(arr_file_names->length());
	if (from_file)
		fn = arr_file_names[test_n];

	CIOSwitcher IOSwitcher(from_file, fn);

	string line;
	IOSwitcher.getline(line);

	outResult.Alphabet = line;
	outResult.A1 = ReadAutomaton(IOSwitcher);
	outResult.A2 = ReadAutomaton(IOSwitcher);

	return outResult.Alphabet.length() > 0 && outResult.A1 != NULL && outResult.A2 != NULL;
}

int main()
{
	ReadResult result;
	if (!ReadSources(-1, result))
		return 1;

	sort(result.Alphabet.begin(), result.Alphabet.end());

	SStringGen gen(result.Alphabet);

	/*for (int i = 0; i < 200; i++)
		cout << gen.GetNext() << endl;*/

	string word = gen.GetNext();

	while (!result.A1->CheckWord(word) || !result.A2->CheckWord(word))
	{
		word = gen.GetNext();
	}
	cout << word << endl;

	delete(result.A1);
	delete(result.A2);
    return 0;
}

