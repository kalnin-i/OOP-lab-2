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
            cout << "������ �� " << number << " �������.\n";
        else
            cout << "��������� �������� ������.\n";
    }

    double checkBalance() { return account.balance; }

    void simulateCallMenu()
    {
        int choice;
        while (true)
        {
            cout << "\n--- ���� ---\n";
            cout << "1. �������� ��������\n";
            cout << "2. �������� ������\n";
            cout << "3. ��������� �������\n";
            cout << "4. ��������� ������\n";
            cout << "5. �����\n";
            cout << "������� ��: ";
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
                cout << "������� ����� �������� ��� ������: ";
                cin >> contactIndex;
                string contactName = phoneBook.getContactName(contactIndex - 1);
                if (!contactName.empty())
                {
                    makeCall(contactName);
                }
                else
                {
                    cout << "������� ����!\n";
                }
                break;
            }
            case 3:
            {
                double amount;
                cout << "������ ���� ����������: ";
                cin >> amount;
                if (amount > 0)
                {
                    addFunds(amount);
                    cout << "������ ���������.\n";
                }
                else
                {
                    cout << "���� ���������� �� ���� ����� 0!\n";
                }
                break;
            }
            case 4:
                cout << "������: " << checkBalance() << " ���.\n";
                break;
            case 5:
                return;
            default:
                cout << "������� ����. ��������� �� ���.\n";
            }
        }
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MobilePhone phone("0991234567", 10.00);
    phone.addContact("���������", "0991111111");
    phone.addContact("����", "0992222222");

    phone.simulateCallMenu();

    return 0;
}