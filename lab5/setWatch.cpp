#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstring>

struct User {
    char name[8];
    int access_level; // should always be 1
};

// Keep original names safe
std::vector<std::string> original_names;

// Bad function: this function would change some users' access level from 1 to something else.
void buggy(std::vector<User>& users) {
    std::srand(std::time(nullptr));

    bool flag = false;
    for (size_t i = 0; i < users.size(); ++i) {
        User* u = &users[i];

        // Random chance to overflow the name buffer
        int chance = std::rand() % 10; // 0–9
        int overwrite_limit = (chance == 0) ? 10 : 6;

        // THIS LOOP triggers overflow if overwrite_limit > 7
        for (int j = 0; j <= overwrite_limit; ++j) {
            u->name[j] = 'A'; // may corrupt access_level naturally
            if(flag == true){
                 return;
            }
        }
    }
}

int main() {
    std::srand(std::time(nullptr));

    std::vector<User> users = {
    {"James",1}, {"Mary",1}, {"John",1}, {"Pat",1}, {"Robert",1},
    {"Jenny",1}, {"Michael",1}, {"Beth",1}, {"William",1},
    {"Linda",1}, {"David",1}, {"Barbara",1}, {"Richard",1}, {"Susan",1},
    {"Joseph",1}, {"Jessica",1}, {"Thomas",1}, {"Sarah",1}, {"Charles",1},
    {"Karen",1}, {"Chris",1}, {"Nancy",1}, {"Daniel",1}, {"Lisa",1},
    {"Matthew",1}, {"Marggie",1}, {"Anthony",1}, {"Betty",1}, {"Mark",1},
    {"Sandra",1}, {"Donald",1}, {"Ashley",1}, {"Steven",1}, {"Kim",1},
    {"Paul",1}, {"Emily",1}, {"Andrew",1}, {"Donna",1}, {"Joshua",1},
    {"Michel",1}, {"Kenneth",1}, {"Dorothy",1}, {"Kevin",1}, {"Carol",1},
    {"Brian",1}, {"Amanda",1}, {"George",1}, {"Melissa",1}, {"Edward",1},
    {"Deborah",1}, {"Ronald",1}, {"Steph",1}, {"Timothy",1}, {"Rebecca",1},
    {"Jason",1}, {"Sharon",1}, {"Jeffrey",1}, {"Laura",1}, {"Ryan",1},
    {"Cynthia",1}, {"Jacob",1}, {"Kate",1}, {"Gary",1}, {"Amy",1},
    {"Nicole",1}, {"Shirley",1}, {"Eric",1}, {"Angela",1}, {"Jonas",1},
    {"Helen",1}, {"Stephen",1}, {"Anna",1}, {"Larry",1}, {"Brenda",1},
    {"Justin",1}, {"Pamela",1}, {"Scott",1}, {"Nicole",1}, {"Brandon",1},
    {"Emma",1}, {"Ben",1}, {"Sam",1}, {"Samuel",1}, {"Kathie",1},
    {"Gregory",1}, {"Kris",1}, {"Frank",1}, {"Debra",1}, {"Alex",1},
    {"Rachel",1}, {"Raymond",1}, {"Cathie",1}, {"Patrick",1}, {"Carolyn",1},
    {"Jack",1}, {"Janet",1}, {"Dennis",1}, {"Ruth",1}, {"Jerry",1}, {"Maria",1},
    {"Tyler",1}, {"Heather",1}
    };

    for (const User& u : users) {
        original_names.push_back(u.name);
    }

    // Print before corruption
    std::cout << "Before corruption:\n";
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << original_names[i] << ": " << users[i].access_level << '\n';
    }

    buggy(users);

    // Print after corruption — always show **original names**
    std::cout << "\nAfter corruption:\n";
    for (size_t i = 0; i < users.size(); ++i) {
        std::cout << original_names[i] << ": " << users[i].access_level << '\n';
    }

    // Identify the corrupted user by checking access_level
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].access_level != 1) {
            std::cout << "\nThe corrupted user is: " << original_names[i] << '\n';
        }
    }

    return 0;
}