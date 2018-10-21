#include "bio.h"

#include<iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::swap;
using std::sort;

//https://stackoverflow.com/questions/27981349/sort-array-of-strings-by-length-words-c
//This source helped me to sort vecotr<string>.
struct compare_length {
    bool operator()(const string &l, const string &r) const {
        return l.size()<r.size();
    }
};

/*
This function should return true if and only if
every character in the input is one of ATCG.
*/
bool is_valid_DNA_sequence(const string & input) {
  for(long i=0; i < input.size();i++){
    if(input[i] == 'A' || input[i] == 'T' || input[i] == 'C' || input[i] == 'G'){
      return true;
    }
    else{
      break;
    }
  }
  return true;
}

/*
This function should calculate the reverse complement DNA sequence.

The first argument is the sequence, the second argument is a pointer to
an empty string, which you should modify to store the result.

This is obtained by reversing the input sequence and swaping each
nucleotide/letter with it's complement:
A <-> T
C <-> G

Example:
input = AAATTCGGGG
reverse = GGGGCTTAAA
reverse complement = CCCCGAATTT
*/
void get_reverse_complement_sequence(const string & input,  string * const output) {
  string reverse_str = input;
  string complement = "";
  long len = input.length();
  for (long i=0; i < len/2; i++){
    swap(reverse_str[i], reverse_str[len-i-1]);
  }
  for(long i=0; i < len; i++){
    if(reverse_str[i] == 'A'){
      reverse_str[i] = 'T';
    }
    else if(reverse_str[i] == 'G'){
      reverse_str[i] = 'C';
    }
    else if(reverse_str[i] == 'T'){
      reverse_str[i] = 'A';
    }
    else if(reverse_str[i] == 'C'){
      reverse_str[i] = 'G';
    }
    complement.push_back(reverse_str[i]);
    *output = complement;
  }
}

/*
This function should return the RNA transcript from a DNA sequence.

A RNA transcript is the reverse complement of the DNA sequence, but RNA
has U (uracil) instead of T (thiamine).

Make sure you don't have redundant code with the
get_reverse_complement_sequence function.
*/
string get_RNA_transcript(const string &input) {
    string reverse_str = input;
    string result;
    get_reverse_complement_sequence(reverse_str, &result);
    for(long i=0; i < reverse_str.size(); i++){
      if(result[i] == 'T'){
        result[i] = 'U';
      }
    }
    return result;
}

/*
This function should return a sub string with order like so:
1: Original (0 offset)
2: Original (1 offset)
3: Original (2 offset)
4: Antiparallel (0 offset)
5: Antiparallel (1 offset)
6: Antiparallel (2 offset)
*/
string find_offset(const string sequence){
  string input = sequence;
  string offset_str;
  input.erase(input.begin());
  offset_str += input;
  return offset_str;
}

/*
This function should return a vector that break each string into a vector o length 3 strings (called codons).
*/
vector<string> break_codons(const string sequence){
  string input = sequence;
  string sub_str;
  vector<string> codons;
  for(long i = 0; i < sequence.size(); i += 3){
    sub_str = input.substr(i,3);
    if(sub_str.size() == 3){
      codons.push_back(sub_str);
    }
  }
  return codons;
}

/*
This function should return a vector of vector of strings with each possible RNA reading frame from the given DNA sequence.
There are three possible reading frames (because the genetic code has three nucleotides per amino acid) in each direction (you can also transcribe DNA in the reverse complement direction, called the antiparallel strand).

Order the sequences like so:
1: Original (0 offset)
2: Original (1 offset)
3: Original (2 offset)
4: Antiparallel (0 offset)
5: Antiparallel (1 offset)
6: Antiparallel (2 offset)

With in the input sequence of: AATTCCCGAAA
Original RNA transcript = UUUCGGGAAUU
Antiparallel RNA transcript = AAUUCCCGAAA

The offsets (starting at pos 0, 1, and 2) of the two RNA transcripts
UUUCGGGAAUU
UUCGGGAAUU
UCGGGAAUU
AAUUCCCGAAA
AUUCCCGAAA
UUCCCGAAA

Instead of returning a vector of 6 strings, break each string into a vector of length 3 strings (called codons) These codons will be useful for the next translation step.
UUUCGGGAAUU -> {"UUU", "CGG", "GAA"}
// drop any remaining letters that don't fill a codon
UUCGGGAAUU -> {"UUC", "GGG", "AAU"}
UCGGGAAUU -> {"UCG", "GGA", "AUU"}
AAUUCCCGAAA -> {"AAU", "UCC", "CGA"}
AUUCCCGAAA -> {"AUU", "CCC", "GAA"}
UUCCCGAAA -> {"UUC", "CCG", "AAA"}

*/
vector<vector<string>> get_reading_frames_as_codons(const string &input) {
  vector<vector<string>> result;
  string DNA = input;
  string complement, anti_complement;
  vector<string> RNA, RNA_one, RNA_two, anti_RNA, anti_one, anti_two;
  get_reverse_complement_sequence(DNA,&complement);
  get_reverse_complement_sequence(complement,&anti_complement);
  anti_RNA = break_codons(get_RNA_transcript(anti_complement));
  result.push_back(anti_RNA);
  anti_one = break_codons(find_offset(get_RNA_transcript(anti_complement)));
  result.push_back(anti_one);
  anti_two = break_codons(find_offset(find_offset(get_RNA_transcript(anti_complement))));
  result.push_back(anti_two);
  RNA = break_codons(get_RNA_transcript(complement));
  result.push_back(RNA);
  RNA_one = break_codons(find_offset(get_RNA_transcript(complement)));
  result.push_back(RNA_one);
  RNA_two = break_codons(find_offset(find_offset(get_RNA_transcript(complement))));
  result.push_back(RNA_two);
  return result;
}

/*
This function translates/converts a vector<string> (vector of codons) into a
string of amino acids using the genetic code
(see https://en.wikipedia.org/wiki/Genetic_code).

For example, the codons:
{"UUU", "GCC", "CAA"}
translates to:
F (Phenylalanine), A (Alanine), Q (Glutamine)
abreviated:
FAQ

To make your lives easier, here's a list of the possible codons:
"GCU", "GCC", "GCA", "GCG", "CGU", "CGC", "CGA", "CGG", "AGA", "AGG",
"AAU", "AAC", "GAU", "GAC", "UGU", "UGC", "CAA", "CAG", "GAA", "GAG",
"GGU", "GGC", "GGA", "GGG", "CAU", "CAC", "AUU", "AUC", "AUA", "UUA",
"UUG", "CUU", "CUC", "CUA", "CUG", "AAA", "AAG", "AUG", "UUU", "UUC",
"CCU", "CCC", "CCA", "CCG", "UCU", "UCC", "UCA", "UCG", "AGU", "AGC",
"ACU", "ACC", "ACA", "ACG", "UGG", "UAU", "UAC", "GUU", "GUC", "GUA",
"GUG", "UAG", "UGA", "UAA"

And there corresponding amino acids ("*" represents STOP codons,
more on them later):

"A", "A", "A", "A", "R", "R", "R", "R", "R", "R", "N", "N", "D", "D",
"C", "C", "Q", "Q", "E", "E", "G", "G", "G", "G", "H", "H", "I", "I",
"I", "L", "L", "L", "L", "L", "L", "K", "K", "M", "F", "F", "P", "P",
"P", "P", "S", "S", "S", "S", "S", "S", "T", "T", "T", "T", "W", "Y",
"Y", "V", "V", "V", "V", "*", "*", "*"
*/
string translate(const vector<string> &codon_sequence) {
  string result;
  vector <string> input = codon_sequence;
  for(long i=0; i< input.size(); i++){
    if(input[i] == "UUU" || input[i] == "UUC"){
      input[i] = "F";
    }
    else if(input[i] == "GCC" || input[i] == "GCU" || input[i] == "GCA" || input[i] == "GCG"){
      input[i] = "A";
    }
    else if(input[i] == "CAA" || input[i] == "CAG"){
      input[i] = "Q";
    }
    else if(input[i] == "UUA" || input[i] == "UUG" || input[i] == "CUU" || input[i] == "CUC" || input[i] == "CUA" || input[i] == "CUG"){
      input[i] = "L";
    }
    else if(input[i] == "AUU" || input[i] == "AUC" || input[i] == "AUA"){
      input[i] = "I";
    }
    else if(input[i] == "AUG"){
      input[i] = "M";
    }
    else if(input[i] == "GUU" || input[i] == "GUC" || input[i] == "GUA" || input[i] == "GUG"){
      input[i] = "V";
    }
    else if(input[i] == "UCU" || input[i] == "UCC" || input[i] == "UCA" || input[i] == "UCG" || input[i] == "AGU" || input[i] == "AGC"){
      input[i] = "S";
    }
    else if(input[i] == "CCU" || input[i] == "CCC" || input[i] == "CCA" || input[i] == "CCG"){
      input[i] = "P";
    }
    else if(input[i] == "ACU" || input[i] == "ACC" || input[i] == "ACA" || input[i] == "ACG"){
      input[i] = "T";
    }
    else if(input[i] == "UAU" || input[i] == "UAC"){
      input[i] = "Y";
    }
    else if(input[i] == "UAA" || input[i] == "UAG" || input[i] == "UGA"){
      input[i] = "*";
    }
    else if(input[i] == "CAU" || input[i] == "CAC"){
      input[i] = "H";
    }
    else if(input[i] == "AAU" || input[i] == "AAC"){
      input[i] = "N";
    }
    else if(input[i] == "AAA" || input[i] == "AAG"){
      input[i] = "K";
    }
    else if(input[i] == "GAU" || input[i] == "GAC"){
      input[i] = "D";
    }
    else if(input[i] == "GAA" || input[i] == "GAG"){
      input[i] = "E";
    }
    else if(input[i] == "UGU" || input[i] == "UGC"){
      input[i] = "C";
    }
    else if(input[i] == "UGG"){
      input[i] = "W";
    }
    else if(input[i] == "CGU" || input[i] == "CGC" || input[i] == "CGA" || input[i] == "CGG" || input[i] == "AGA" || input[i] == "AGG"){
      input[i] = "R";
    }
    else{
      input[i] = "G";
    }
  result += input[i];
}
  return result;
}

/*
This function is to check if there is a character inside the string.
*/
bool isInside(const string & str, char c)
{
    return str.find(c) != std::string::npos;
}

/*
This function returns a vector<long> of the position of the finding character.
*/
vector<long> find_position(const string str, char c){
  vector<long> position;
  string input = str;
  for(long i=0; i<input.length(); i++){
    if(input[i] == c){
      position.push_back(i);
    }
  }
  return position;
}

/*
This function takes a DNA sequence and returns the longest possible
amino acid sequence / protein that is encoded by that sequence
(open reading frame). A valid open reading frame begins with the
codon AUG (the amino acid, Methionine (M)) and runs until a stop codon (*)
is encountered. There may be multiple open reading frames in a sequence, and
you need to check all six reading frames in order given by
get_reading_frames_as_codons. If there are ties for longest, favor the first
one found.

Return the longest open reading frame as an amino acid sequence. It must start
with an 'M' and end with a '*' with no other '*''s within.
*/
string get_longest_open_reading_frame(const string &DNA_sequence) {
  string longest;
  string amino;
  string input = DNA_sequence;
  vector<string> result;
  for (vector<string> frame : get_reading_frames_as_codons(input)){
    amino = translate(frame);
    if(isInside(amino,'M')==true && isInside(amino,'*')==true){
      vector<long> position_M = find_position(amino,'M');
      vector<long> position_stop = find_position(amino,'*');

      string sub;
      for(int i = 0; i<position_M.size(); i++){
        for(int j = 0; j<position_stop.size(); j++){
          if(position_stop[j]>position_M[i]){
            sub = amino.substr(position_M[i], position_stop[j]-position_M[i]+1);
            result.push_back(sub);
            break;
          }
        }
      }

    }
    else{
      longest = "";
    }
  }
  sort(result.begin(),result.end(),compare_length());
  if(result.empty() ==false){

    longest = result[result.size()-1];
  }
  return longest;
}
