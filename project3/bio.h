/*
Add the appropiate function declarations, includes, and guards
to this header file.
*/
#ifndef BIO_H
#define BIO_H

#include <string>
using std::string;
#include <vector>
using std::vector;

bool is_valid_DNA_sequence(const string & input);

void get_reverse_complement_sequence(const string & input,  string * const output);

string get_RNA_transcript(const string &input);

string find_offset(const string sequence);

vector<string> break_codons(const string sequence);

vector<vector<string>> get_reading_frames_as_codons(const string &input);

string translate(const vector<string> &codon_sequence);

string get_longest_open_reading_frame(const string &DNA_sequence);
bool isInside(const string & str, char c);
vector<long> find_position(const string str, char c);

#endif
