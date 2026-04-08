#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct CallerIDEntry
{
    std::string phoneNumber;
    std::string name;

    // True if this entry had an element that was deleted, false otherwise
    bool hadElement;

    CallerIDEntry() : phoneNumber(""), name(""), hadElement(false)
    {
    }
};

class CallerIDFinder
{
private:
    std::vector<CallerIDEntry> hashTable;

    int hash(const std::string &phoneNumber);

public:
    CallerIDFinder(int initialSize);

    std::pair<std::string, bool> find(const std::string &phoneNumber);
    void insert(const std::string &phoneNumber, const std::string &name);
    void erase(const std::string &phoneNumber);

};

CallerIDFinder::CallerIDFinder(int initialSize)
{
    hashTable = std::vector<CallerIDEntry>(initialSize, CallerIDEntry());
}

std::pair<std::string, bool> CallerIDFinder::find(const std::string &phoneNumber)
{
    int index = hash(phoneNumber) % hashTable.size();

    while ((hashTable[index].phoneNumber != "" && hashTable[index].phoneNumber != phoneNumber) 
           || (hashTable[index].phoneNumber == "" && hashTable[index].hadElement))
    {
        index++;
        index %= hashTable.size();
    }

    if (hashTable[index].phoneNumber == phoneNumber)
    {
        return std::pair<std::string, bool>(hashTable[index].name, true);
    }
    else
    {
        return std::pair<std::string, bool>("", false);
    }
}

// Assumption: two people will never have the same phone number
void CallerIDFinder::insert(const std::string &phoneNumber, const std::string &name)
{
    int index = hash(phoneNumber) % hashTable.size();

    while ((hashTable[index].phoneNumber != ""))
    {
        index++;
        index %= hashTable.size();
    }

    hashTable[index].phoneNumber = phoneNumber;
    hashTable[index].name = name;
}

void CallerIDFinder::erase(const std::string &phoneNumber)
{
    int index = hash(phoneNumber) % hashTable.size();

    while ((hashTable[index].phoneNumber != "" && hashTable[index].phoneNumber != phoneNumber) 
           || (hashTable[index].phoneNumber == "" && hashTable[index].hadElement))
    {
        index++;
        index %= hashTable.size();
    }

    hashTable[index].name="";
    hashTable[index].phoneNumber="";
    hashTable[index].hadElement=true;
}

int CallerIDFinder::hash(const std::string &phoneNumber)
{
    // Convert the first 3 digits of the phone number to an int
    int areaCode = std::stoi(phoneNumber.substr(1, 3));
    return areaCode;
}


int main(){
    CallerIDFinder personFinder(7);
    
    personFinder.insert("(518) 555-7777", "Robert Walpole");
    personFinder.insert("(705) 323-5566","Jonathan Wild");

    personFinder.insert("(518) 522-9981", "Ishmael Whaleton");
    personFinder.erase("(518) 555-7777");

    std::pair<std::string, bool> person1 = personFinder.find("(518) 522-9981");
    std::pair<std::string, bool> person2 = personFinder.find("(518) 555-7777");


    std::cout<<"All done"<<std::endl;
    return 0;
}