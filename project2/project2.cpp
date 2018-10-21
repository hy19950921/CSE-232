#include<iostream>
using std::cin; using std::cout; using std::endl;  //using declaration.
#include<string>         //string library.
using std::string;

//build the function to calculate single character shift.
char single_shift(char letter, long integer){
  long result = long(letter) + integer;
  (isupper(letter) && ( long(result) < 65)) ? result += 26 : 0;
  (isupper(letter) && (long(result) > 90)) ? result -= 26 : 0;
  (islower(letter) && (long(result) < 97)) ? result += 26 : 0;
  (islower(letter) && (long(result) > 122)) ? result -= 26 : 0;
  (isalpha(letter) == false) ? result = letter : 0;
  return char(result);
}

//This source helped me determine how to build the create_key, encryption and decryption function.
//www.geeksforgeeks.org/vigenere-cipher/

//build the function to create the repeated key.
string create_key(string input, string key){
  long length = input.size();
  bool check = false;
  for(long i=0; i < length && (check == false);i++){
    check = false;
    (length == i) ? i = 0 : 0;
    (key.size() == input.size()) ? check = true : 0;
    key.push_back(key[i]);
  }
  key.pop_back();
  return key;
}

//build the function to encrypt.
string encryption(string input, string key){
  string encrypt;
  for (long i=0; i< input.size(); i++){
    long result = (input[i] + key[i]) % 26;       //convert to 0-25;
    (isupper(input[i])) ? result += 'A' : 0;      //when input character is uppercase
    (islower(input[i])) ? (result = (toupper(input[i]) + key[i]) % 26, result += 'A', result = tolower(result)) : 0; //when input character is lowercase
    (isalpha(input[i]) == false) ? result = input[i] : 0;
    encrypt.push_back(result);
  }
  return encrypt;
}

//build the function to decrypt.
string decryption(string input, string key){
  string decrypt;
  for (long i = 0; i < input[i]; i++){
    long result = (input[i] - key[i] + 26) % 26;
    (isupper(input[i])) ? result += 'A' : 0;       //when input character is uppercase.
    (islower(input[i])) ? (result = (toupper(input[i]) - key[i] + 26) % 26, result += 'A', result = tolower(result)) : 0;  //when input character is lowercase
    (isalpha(input[i]) == false) ? result = input[i] : 0;
    decrypt.push_back(result);
  }
  return decrypt;
}

//main function to prompt user to choose option and call the function.
int main(){
  for(;;){
    long option;
    cout << "Select the mode:" << endl;
    cout << "0: Quit" << endl;
    cout << "1: Single Character Shift" << endl;
    cout << "2: Encrypt" << endl;
    cout << "3: Decrypt" << endl;
    cout << "Selection?" << endl;
    cin >> option;
    switch(option){
      case 0:         //quit the program.
      {
        cout << "Quitting." << endl;
        return 0;
      }
      case 1:            //call the single_shift function.
      {
        char letter_input;
        cout << "What character should be shifted?" << endl;
        cin >> letter_input;
        long shifted_integer;
        cout << "Shifted by what integer (-26 to 26)?" << endl;
        cin >> shifted_integer;
        char result = single_shift(letter_input, shifted_integer);
        cout << "The shifted character is: " << result << endl;
        cout << endl;
        break;
      }
      case 2:        //call the encyption function
      {
        string encrypt_input;
        cout << "Encrypting Please provide input (no whitespace) that ends with a period:" << endl;
        cin >> encrypt_input;
        string key_input = "CSE";
        string key = create_key(encrypt_input,key_input);
        string Encrypt = encryption(encrypt_input,key);
        cout << Encrypt << endl;
        cout << "Done Encrypting." << endl;
        cout << endl;
        break;
      }
      case 3:        //call the decryption function
      {
        string decrypt_input;
        cout << "Decrypting Please provide input (no whitespace) that ends with a period:" << endl;
        cin >> decrypt_input;
        string key_input = "CSE";
        string key = create_key(decrypt_input,key_input);
        string Decrypt = decryption(decrypt_input,key);
        cout << Decrypt << endl;
        cout << "Done Decrypting." << endl;
        cout << endl;
        break;
      }
    }
  }
}
