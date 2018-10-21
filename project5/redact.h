#ifndef REDACT_H
#define REDACT_H

#include<string>
using std::string;
#include<vector>
using std::vector;
#include<algorithm>
using std::replace;

string redact_all_chars(const string & str);
string redact_alphabet_digits(const string & str);
string redact_words(const string & str, const vector<string> & words_to_redact);

#endif
