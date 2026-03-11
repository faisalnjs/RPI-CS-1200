// phonebook.cpp
// A simple "caller ID" program

#include <iostream>
#include <map>
#include <string>
using namespace std;

std::map<int, std::string> phonebook;

// add a number, name pair to the phonebook
void add(int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(int number) {
  if (phonebook[number] == "")
    cout << "unknown caller!" << endl;
  else
    cout << phonebook[number] << " is calling!" << endl;
}

int main() {
  // add several names to the phonebook
  add(1111111, "fred");
  add(2222222, "sally");
  add(3333333, "george");

  // test the phonebook
  identify(2222222);
  identify(4444444);
  identify(3333333);
  identify(5555555);
  identify(7777777);
  identify(1111111);
  identify(6666666);
}