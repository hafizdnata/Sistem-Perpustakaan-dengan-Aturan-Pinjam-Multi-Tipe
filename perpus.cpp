#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;


class Item {
protected:
    string id, title;
    bool available;
public:
    Item(string i, string t) : id(i), title(t), available(true) {}
    virtual ~Item() = default;


    string getId() const { return id; }
    string getTitle() const { return title; }
    bool isAvailable() const { return available; }
    void setAvailable(bool a) { available = a; }


    virtual int maxLoanDays() const = 0;
    virtual double computeFine(int daysLate) const = 0;
    virtual unique_ptr<Item> clone() const = 0;


    bool operator<(const Item &other) const { return id < other.id; }


    virtual void info() const {
        cout << "[" << id << "] " << title
             << " | " << (available ? "Available" : "Borrowed") << endl;
    }
};


class Book : public Item {
    string author;
    bool isRare;
public:
    Book(string i, string t, string a, bool r)
        : Item(i, t), author(a), isRare(r) {}
    int maxLoanDays() const override {
        return isRare ? 3 : 14;
    }
    double computeFine(int daysLate) const override {
        return 1000 * daysLate;
    }
    unique_ptr<Item> clone() const override {
        return make_unique<Book>(*this);
    }
    void info() const override {
        cout << "Book - " << title << " by " << author
             << (isRare ? " [Rare]" : "")
             << " | " << (available ? "Available" : "Borrowed") << endl;
    }
};


class Magazine : public Item {
public:
    Magazine(string i, string t) : Item(i, t) {}
    int maxLoanDays() const override { return 7; }
    double computeFine(int daysLate) const override {
        return 500 * daysLate;
    }
    unique_ptr<Item> clone() const override {
        return make_unique<Magazine>(*this);
    }
    void info() const override {
        cout << "Magazine - " << title
             << " | " << (available ? "Available" : "Borrowed") << endl;
    }
};


class DVD : public Item {
public:
    DVD(string i, string t) : Item(i, t) {}
    int maxLoanDays() const override { return 3; }
    double computeFine(int daysLate) const override {
        return 2000 * daysLate;
    }
    double computeFine(int daysLate, bool isDamaged) const {
        double fine = computeFine(daysLate);
        if (isDamaged) fine += 50000;
        return fine;
    }
    unique_ptr<Item> clone() const override {
        return make_unique<DVD>(*this);
    }
    void info() const override {
        cout << "DVD - " << title
             << " | " << (available ? "Available" : "Borrowed") << endl;
    }
};


class Member {
    string id, name;
    int level, freeLoanCredits, totalLoans;
public:
    Member(string i, string n)
        : id(i), name(n), level(0), freeLoanCredits(0), totalLoans(0) {}


    string getId() const { return id; }
    string getName() const { return name; }
    int getLevel() const { return level; }
    int getCredits() const { return freeLoanCredits; }


    void borrow(Item &it, int daysRequested, bool useCredit = false,
                int *totalFreeCreditsUsed = nullptr) {
        if (daysRequested <= 0) {
            cout << "Pinjam harus lebih dari 0 hari.\n";
            return;
        }
        if (!it.isAvailable()) {
            cout << "Item tidak ada.\n";
            return;
        }
        if (daysRequested > it.maxLoanDays()) {
            cout << "Melebihi batas maksimum pinjam ("
                 << it.maxLoanDays() << " hari).\n";
            return;
        }


        if (useCredit && freeLoanCredits > 0) {
            freeLoanCredits--;
            if (totalFreeCreditsUsed) (*totalFreeCreditsUsed)++;
            cout << name << " menggunakan free credit untuk pinjam.\n";
        }


        it.setAvailable(false);
        totalLoans++;
        updateLevel();
        cout << name << " meminjam " << it.getTitle()
             << " selama " << daysRequested << " hari.\n";
    }


    double returnItem(Item &it, int actualDays) {
        it.setAvailable(true);
        int late = max(0, actualDays - it.maxLoanDays());
        double fine = it.computeFine(late);
        cout << name << " mengembalikan " << it.getTitle()
             << " | Telat " << late << " hari | Denda Rp " << fine << endl;
        return fine;
    }


    void updateLevel() {
        if (totalLoans >= 10) { level = 2; freeLoanCredits += 3; }
        else if (totalLoans >= 5) { level = 1; freeLoanCredits += 1; }
    }


    void info() const {
        cout << "[" << id << "] " << name
             << " | Level " << level
             << " | Credits: " << freeLoanCredits
             << " | Loans: " << totalLoans << endl;
    }
};


bool idExists(const vector<unique_ptr<Item>> &catalogue, const string &id) {
    return any_of(catalogue.begin(), catalogue.end(),
                  [&](const unique_ptr<Item> &it){ return it->getId() == id; });
}


bool memberExists(const vector<Member> &members, const string &id) {
    return any_of(members.begin(), members.end(),
                  [&](const Member &m){ return m.getId() == id; });
}


void initializeCatalogue(vector<unique_ptr<Item>> &catalogue) {
    catalogue.push_back(make_unique<Book>("B001", "The Great Gatsby", "F. Scott Fitzgerald", false));
    catalogue.push_back(make_unique<Book>("B002", "To Kill a Mockingbird", "Harper Lee", true));
    catalogue.push_back(make_unique<Magazine>("M001", "National Geographic - July Edition"));
    catalogue.push_back(make_unique<Magazine>("M002", "TIME Magazine - August"));
    catalogue.push_back(make_unique<DVD>("D001", "Inception"));
    catalogue.push_back(make_unique<DVD>("D002", "Interstellar"));


    sort(catalogue.begin(), catalogue.end(),
         [](const auto &a, const auto &b){ return *a < *b; });


    cout << "Data awal katalog berhasil dimuat.\n";
}


int main() {
    vector<unique_ptr<Item>> catalogue;
    vector<Member> members;


    int totalLoansBook = 0, totalLoansMag = 0, totalLoansDVD = 0;
    double totalFine = 0;
    int totalFreeCreditsUsed = 0;


    initializeCatalogue(catalogue);


    int choice;
    do {
        cout << "\n====================================\n";
        cout << "     PERPUSTAKAAN KELOMPOK 8   \n";
        cout << "====================================\n";
        cout << "1. Add Item to Catalogue\n";
        cout << "2. Register New Member\n";
        cout << "3. Borrow Item\n";
        cout << "4. Return Item\n";
        cout << "5. Show All Items\n";
        cout << "6. Show All Members\n";
        cout << "7. Monthly Report\n";
        cout << "0. Exit\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;


          if (choice == 1) {
            cout << "\nAdd New Item\n";
            cout << "Select Item Type:\n";
            cout << "1. Book\n";
            cout << "2. Magazine\n";
            cout << "3. DVD\n";
            cout << "Enter Choice: ";
            int type; cin >> type;


            string id, title;
            cout << "Enter Item ID: "; cin >> id;
            if (idExists(catalogue, id)) {
                cout << "ID sudah ada.\n";
                continue;
            }
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin, title);


            if (type == 1) {
                string author;
                cout << "Enter Author: ";
                getline(cin, author);
               
                char choiceRare;
                cout << "Is this book rare? (y/n): ";
                cin >> choiceRare;
                bool rare = (choiceRare == 'y' || choiceRare == 'Y');
               
                catalogue.push_back(make_unique<Book>(id, title, author, rare));
            }
            else if (type == 2) {
                catalogue.push_back(make_unique<Magazine>(id, title));
            }
            else if (type == 3) {
                catalogue.push_back(make_unique<DVD>(id, title));
            }
            else {
                cout << "Invalid type!\n";
                continue;
            }


            sort(catalogue.begin(), catalogue.end(),
                [](const auto &a, const auto &b){ return *a < *b; });
            cout << "Item successfully added.\n";
        }


        else if (choice == 2) {
            cout << "\nRegister New Member\n";
            string id, name;
            cout << "Enter Member ID: "; cin >> id;
            if (memberExists(members, id)) {
                cout << "ID member sudah ada!\n";
                continue;
            }
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            members.emplace_back(id, name);
            cout << "Member registered.\n";
        }


        else if (choice == 3) {
            if (members.empty() || catalogue.empty()) {
                cout << "Tidak ada data member atau item!\n";
                continue;
            }
            cout << "\nBorrow Item\n";
            string mid, iid; int days;
            cout << "Enter Member ID: "; cin >> mid;
            cout << "Enter Item ID: "; cin >> iid;
            cout << "Enter Days to Borrow: "; cin >> days;
           
            char creditChoice;
            cout << "Use credit? (y/n): ";
            cin >> creditChoice;
            bool useCredit = (creditChoice == 'y' || creditChoice == 'Y');


            auto memIt = find_if(members.begin(), members.end(),
                                 [&](const Member &m){ return m.getId() == mid; });
            auto itemIt = find_if(catalogue.begin(), catalogue.end(),
                                  [&](const unique_ptr<Item> &it){ return it->getId() == iid; });


            if (memIt == members.end() || itemIt == catalogue.end()) {
                cout << "Member atau Item tidak ditemukan!\n";
            } else {
                memIt->borrow(*itemIt->get(), days, useCredit, &totalFreeCreditsUsed);
                if (dynamic_cast<Book*>(itemIt->get())) totalLoansBook++;
                else if (dynamic_cast<Magazine*>(itemIt->get())) totalLoansMag++;
                else if (dynamic_cast<DVD*>(itemIt->get())) totalLoansDVD++;
            }
        }


        else if (choice == 4) {
    if (members.empty() || catalogue.empty()) {
        cout << "Tidak ada data member atau item.\n";
        continue;
    }
    cout << "\nReturn Item\n";
    string mid, iid; int days;
    cout << "Enter Member ID: "; cin >> mid;
    cout << "Enter Item ID: "; cin >> iid;
    cout << "Enter Actual Borrowed Days: "; cin >> days;


    auto memIt = find_if(members.begin(), members.end(),
                         [&](const Member &m){ return m.getId() == mid; });
    auto itemIt = find_if(catalogue.begin(), catalogue.end(),
                          [&](const unique_ptr<Item> &it){ return it->getId() == iid; });


    if (memIt == members.end() || itemIt == catalogue.end()) {
        cout << "Member atau Item tidak ditemukan.\n";
    } else {
            if (dynamic_cast<DVD*>(itemIt->get())) {
            char damagedChoice;
            cout << "Is the DVD damaged? (y/n): ";
            cin >> damagedChoice;
            bool damaged = (damagedChoice == 'y' || damagedChoice == 'Y');


            DVD* dvdPtr = dynamic_cast<DVD*>(itemIt->get());
            int late = max(0, days - dvdPtr->maxLoanDays());
            double fine = dvdPtr->computeFine(late, damaged);
            dvdPtr->setAvailable(true);


            cout << memIt->getName() << " mengembalikan " << dvdPtr->getTitle()
                 << " | Telat " << late << " hari | "
                 << (damaged ? "Rusak" : "Baik")
                 << " | Denda Rp " << fine << endl;
            totalFine += fine;
        }
        else {
            totalFine += memIt->returnItem(*itemIt->get(), days);
        }
    }
}


        else if (choice == 5) {
            cout << "\nCatalogue\n";
            for (auto &it : catalogue) it->info();
        }


        else if (choice == 6) {
            cout << "\nMembers\n";
            for (auto &m : members) m.info();
        }


        else if (choice == 7) {
            cout << "\nMonthly Report\n";
            cout << "Books borrowed: " << totalLoansBook << endl;
            cout << "Magazines borrowed: " << totalLoansMag << endl;
            cout << "DVDs borrowed: " << totalLoansDVD << endl;
            cout << "Total Fine Collected: Rp " << totalFine << endl;
            cout << "Total Free Credits Used: " << totalFreeCreditsUsed << endl;
        }


        else if (choice != 0) {
            cout << "Invalid choice.\n";
        }


    } while (choice != 0);


    return 0;
}
