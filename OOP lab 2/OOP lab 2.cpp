#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class SimCard
{
public:
    string phoneNumber;
    SimCard(const string& number) : phoneNumber(number) {}
};

class PhoneBookEntry
{
public:
    string name, number;
    PhoneBookEntry(const string& n, const string& num) : name(n), number(num) {}
};

class PhoneBook
{
    vector<PhoneBookEntry> contacts;
public:
    void addContact(const string& name, const string& number)
    {
        contacts.push_back(PhoneBookEntry(name, number));
    }

    void listContacts()
    {
        for (size_t i = 0; i < contacts.size(); ++i)
            cout << i + 1 << ". " << contacts[i].name << " (" << contacts[i].number << ")\n";
    }

    string findNumber(const string& name)
    {
        for (auto& contact : contacts)
            if (contact.name == name) return contact.number;
        return "";
    }

    string getContactName(int index)
    {
        if (index >= 0 && index < contacts.size())
            return contacts[index].name;
        return "";
    }
};

class Account
{
public:
    double balance;
    Account(double bal = 0) : balance(bal) {}
    void addFunds(double amount) { balance += amount; }
    bool chargeCall(double cost)
    {
        if (balance >= cost)
        {
            balance -= cost;
            return true;
        }
        return false;
    }
};

class MobilePhone
{
    SimCard simCard;
    PhoneBook phoneBook;
    Account account;
public:
    MobilePhone(const string& phoneNumber, double balance)
        : simCard(phoneNumber), account(balance) {}

    void addFunds(double amount) { account.addFunds(amount); }

    void addContact(const string& name, const string& number) { phoneBook.addContact(name, number); }

    void listContacts() { phoneBook.listContacts(); }

    void makeCall(const string& name)
    {
        string number = phoneBook.findNumber(name);
        if (!number.empty() && account.chargeCall(5))
            cout << "Дзвінок на " << number << " успішний.\n";
        else
            cout << "Неможливо здійснити дзвінок.\n";
    }

    double checkBalance() { return account.balance; }

    void simulateCallMenu()
    {
        int choice;
        while (true)
        {
            cout << "\n--- Меню ---\n";
            cout << "1. Показати контакти\n";
            cout << "2. Здійснити дзвінок\n";
            cout << "3. Поповнити рахунок\n";
            cout << "4. Перевірити баланс\n";
            cout << "5. Вийти\n";
            cout << "Виберіть дію: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                listContacts();
                break;
            case 2:
            {
                int contactIndex;
                listContacts();
                cout << "Виберіть номер контакту для дзвінка: ";
                cin >> contactIndex;
                string contactName = phoneBook.getContactName(contactIndex - 1);
                if (!contactName.empty())
                {
                    makeCall(contactName);
                }
                else
                {
                    cout << "Невірний вибір!\n";
                }
                break;
            }
            case 3:
            {
                double amount;
                cout << "Введіть суму поповнення: ";
                cin >> amount;
                if (amount > 0)
                {
                    addFunds(amount);
                    cout << "Баланс поповнено.\n";
                }
                else
                {
                    cout << "Сума поповнення має бути більша 0!\n";
                }
                break;
            }
            case 4:
                cout << "Баланс: " << checkBalance() << " грн.\n";
                break;
            case 5:
                return;
            default:
                cout << "Невірний вибір. Спробуйте ще раз.\n";
            }
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MobilePhone phone("0991234567", 10.00);
    phone.addContact("Олександр", "0991111111");
    phone.addContact("Марія", "0992222222");

    phone.simulateCallMenu();

    return 0;
}