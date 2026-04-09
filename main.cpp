/*
 * Project Title: Mini Banking System – Personal Savings Account
 * Assignment   : DA2 – C++ OOP Mini Project
 *
 * COMPILE COMMAND:
 *   em++ main.cpp -o index.html \
 *     -sASYNCIFY=1 \
 *     -sASYNCIFY_IMPORTS="['emscripten_sleep']" \
 *     -sFORCE_FILESYSTEM=1 \
 *     -sEXIT_RUNTIME=0 \
 *     -O2
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <stdexcept>

#ifdef __EMSCRIPTEN__
  #include <emscripten.h>
  #define WASM_YIELD() emscripten_sleep(50)
#else
  #define WASM_YIELD()
#endif

using namespace std;

// ──────────────────────────────────────────────
// SAFE INPUT HELPERS
// Using ONLY getline() — never cin >> — because
// in Emscripten/Asyncify, cin >> leaves a \n in
// the buffer that causes getline to return empty.
// Every read goes through readLine() which calls
// WASM_YIELD() first so the browser can deliver
// the queued keystroke to Module.stdin().
// ──────────────────────────────────────────────
string readLine() {
    WASM_YIELD();
    string s;
    getline(cin, s);
    // strip \r in case of Windows line endings
    if (!s.empty() && s.back() == '\r') s.pop_back();
    return s;
}

int readInt() {
    while (true) {
        string s = readLine();
        try {
            size_t pos;
            int v = stoi(s, &pos);
            // make sure entire string was a number
            while (pos < s.size() && isspace(s[pos])) pos++;
            if (pos == s.size()) return v;
        } catch (...) {}
        cout << "  [!] Enter a valid integer: "; cout.flush();
    }
}

double readDouble() {
    while (true) {
        string s = readLine();
        try {
            size_t pos;
            double v = stod(s, &pos);
            while (pos < s.size() && isspace(s[pos])) pos++;
            if (pos == s.size()) return v;
        } catch (...) {}
        cout << "  [!] Enter a valid number: "; cout.flush();
    }
}

// ──────────────────────────────────────────────
// CLASS: Transaction
// ──────────────────────────────────────────────
class Transaction {
public:
    int    txnId;
    int    accNo;
    string type;
    double amount;
    double balanceAfter;
    string dateTime;

    Transaction() {}
    Transaction(int id, int acc, string t, double amt, double bal, string dt)
        : txnId(id), accNo(acc), type(t), amount(amt), balanceAfter(bal), dateTime(dt) {}

    string toFileString() const {
        return to_string(txnId) + "," + to_string(accNo) + "," + type + "," +
               to_string(amount) + "," + to_string(balanceAfter) + "," + dateTime;
    }

    static Transaction fromFileString(const string& line) {
        Transaction t;
        stringstream ss(line);
        string tok;
        getline(ss, tok, ','); t.txnId       = stoi(tok);
        getline(ss, tok, ','); t.accNo        = stoi(tok);
        getline(ss, tok, ','); t.type         = tok;
        getline(ss, tok, ','); t.amount       = stod(tok);
        getline(ss, tok, ','); t.balanceAfter = stod(tok);
        getline(ss, tok);      t.dateTime     = tok;
        return t;
    }
};

// ──────────────────────────────────────────────
// CLASS: Account
// Private data members, public member functions
// ──────────────────────────────────────────────
class Account {
private:
    int    accNo;
    string name;
    double balance;

public:
    Account(int no, string n, double bal = 0.0)
        : accNo(no), name(n), balance(bal) {}

    int    getAccNo()   const { return accNo; }
    string getName()    const { return name;  }
    double getBalance() const { return balance; }

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }

    void display() const {
        cout << left
             << setw(8)  << accNo
             << setw(22) << name
             << "Rs. " << fixed << setprecision(2) << balance << "\n";
    }

    string toFileString() const {
        return to_string(accNo) + "," + name + "," + to_string(balance);
    }

    static Account fromFileString(const string& line) {
        stringstream ss(line);
        string tok;
        int    no;  getline(ss, tok, ','); no  = stoi(tok);
        string nm;  getline(ss, tok, ','); nm  = tok;
        double bal; getline(ss, tok, ','); bal = stod(tok);
        return Account(no, nm, bal);
    }
};

// ──────────────────────────────────────────────
// CLASS: BankSystem
// ──────────────────────────────────────────────
class BankSystem {
private:
    vector<Account>     accounts;
    vector<Transaction> transactions;
    int                 txnCounter;

    const string ACCOUNTS_FILE = "accounts.txt";
    const string TXN_FILE      = "transactions.txt";

    string currentDateTime() const {
        time_t now = time(nullptr);
        char buf[20];
        strftime(buf, sizeof(buf), "%d/%m/%Y %H:%M", localtime(&now));
        return string(buf);
    }

    Account* findAccount(int no) {
        for (auto& a : accounts)
            if (a.getAccNo() == no) return &a;
        return nullptr;
    }

    void printSep() const { cout << string(54, '-') << "\n"; }

public:
    BankSystem() : txnCounter(1) {
        loadAccounts();
        loadTransactions();
    }

    // ── File I/O ──────────────────────────────

    void loadAccounts() {
        ifstream f(ACCOUNTS_FILE);
        if (!f.is_open()) return;
        string line;
        while (getline(f, line))
            if (!line.empty()) accounts.push_back(Account::fromFileString(line));
        f.close();
    }

    void saveAccounts() const {
        ofstream f(ACCOUNTS_FILE);
        if (!f.is_open()) { cerr << "Error: cannot write accounts file.\n"; return; }
        for (const auto& a : accounts) f << a.toFileString() << "\n";
        f.close();
    }

    void loadTransactions() {
        ifstream f(TXN_FILE);
        if (!f.is_open()) return;
        string line;
        while (getline(f, line)) {
            if (!line.empty()) {
                Transaction t = Transaction::fromFileString(line);
                transactions.push_back(t);
                if (t.txnId >= txnCounter) txnCounter = t.txnId + 1;
            }
        }
        f.close();
    }

    void saveTransactions() const {
        ofstream f(TXN_FILE);
        if (!f.is_open()) { cerr << "Error: cannot write transactions file.\n"; return; }
        for (const auto& t : transactions) f << t.toFileString() << "\n";
        f.close();
    }

    // ── Operations ────────────────────────────

    void createAccount() {
        int    accNo;
        string name;
        double openBal;

        // --- Account Number ---
        cout << "Enter Account Number : "; cout.flush();
        accNo = readInt();
        if (accNo <= 0) { cout << "Invalid account number.\n"; return; }
        if (findAccount(accNo)) {
            cout << "Account #" << accNo << " already exists.\n"; return;
        }

        // --- Name ---
        cout << "Enter Member Name    : "; cout.flush();
        name = readLine();
        while (name.empty()) {
            cout << "  [!] Name cannot be empty. Try again: "; cout.flush();
            name = readLine();
        }

        // --- Opening Balance ---
        cout << "Opening Balance (Rs.): "; cout.flush();
        openBal = readDouble();
        if (openBal < 0) { cout << "Balance cannot be negative.\n"; return; }

        accounts.emplace_back(accNo, name, openBal);

        if (openBal > 0) {
            Transaction t(txnCounter++, accNo, "DEPOSIT", openBal, openBal, currentDateTime());
            transactions.push_back(t);
        }
        saveAccounts();
        saveTransactions();
        cout << "\nAccount #" << accNo << " created for " << name << ".\n";
    }

    void deposit() {
        cout << "Account Number : "; cout.flush();
        int accNo = readInt();
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << acc->getBalance() << "\n";

        cout << "Deposit Amount : "; cout.flush();
        double amount = readDouble();
        if (!acc->deposit(amount)) { cout << "Invalid amount (must be > 0).\n"; return; }

        Transaction t(txnCounter++, accNo, "DEPOSIT", amount, acc->getBalance(), currentDateTime());
        transactions.push_back(t);
        saveAccounts(); saveTransactions();
        cout << "Deposited Rs. " << fixed << setprecision(2) << amount
             << " | New Balance: Rs. " << acc->getBalance()
             << " | Ref: TXN" << setfill('0') << setw(4) << t.txnId << "\n";
    }

    void withdraw() {
        cout << "Account Number : "; cout.flush();
        int accNo = readInt();
        Account* acc = findAccount(accNo);
        if (!acc) { cout << "Account not found.\n"; return; }
        cout << "Current Balance: Rs. " << fixed << setprecision(2) << acc->getBalance() << "\n";

        cout << "Withdraw Amount: "; cout.flush();
        double amount = readDouble();
        if (!acc->withdraw(amount)) {
            cout << "Withdrawal failed. Insufficient funds or invalid amount.\n"; return;
        }

        Transaction t(txnCounter++, accNo, "WITHDRAW", amount, acc->getBalance(), currentDateTime());
        transactions.push_back(t);
        saveAccounts(); saveTransactions();
        cout << "Withdrawn Rs. " << fixed << setprecision(2) << amount
             << " | New Balance: Rs. " << acc->getBalance()
             << " | Ref: TXN" << setfill('0') << setw(4) << t.txnId << "\n";
    }

    void balanceEnquiry() const {
        cout << "Account Number: "; cout.flush();
        int accNo = readInt();
        for (const auto& a : accounts) {
            if (a.getAccNo() == accNo) {
                cout << "\nAccount  : #" << a.getAccNo() << "\n"
                     << "Name     : "    << a.getName()   << "\n"
                     << "Balance  : Rs. " << fixed << setprecision(2) << a.getBalance() << "\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    // ── History ───────────────────────────────

    void viewTransactionHistory() const {
        cout << "Account Number      : "; cout.flush();
        int accNo = readInt();

        bool found = false;
        for (const auto& a : accounts)
            if (a.getAccNo() == accNo) { found = true; break; }
        if (!found) { cout << "Account not found.\n"; return; }

        cout << "Show last N records : "; cout.flush();
        int limit = readInt();
        if (limit <= 0) limit = 5;

        vector<Transaction> fil;
        for (const auto& t : transactions)
            if (t.accNo == accNo) fil.push_back(t);

        if (fil.empty()) { cout << "No transactions on this account.\n"; return; }

        int start = max(0, (int)fil.size() - limit);
        printSep();
        cout << left << setw(10) << "REF" << setw(18) << "DATE/TIME"
             << setw(10) << "TYPE" << setw(12) << "AMOUNT" << "BALANCE\n";
        printSep();
        for (int i = (int)fil.size() - 1; i >= start; --i) {
            const auto& t = fil[i];
            ostringstream ref;
            ref << "TXN" << setfill('0') << setw(4) << t.txnId;
            cout << left << setw(10) << ref.str()
                 << setw(18) << t.dateTime
                 << setw(10) << t.type
                 << setw(12) << fixed << setprecision(2) << t.amount
                 << fixed << setprecision(2) << t.balanceAfter << "\n";
        }
        printSep();
    }

    // ── Reports ───────────────────────────────

    void reportTotalFunds() const {
        double total = 0;
        for (const auto& a : accounts) total += a.getBalance();
        cout << "\nTotal accounts : " << accounts.size() << "\n"
             << "Total funds    : Rs. " << fixed << setprecision(2) << total << "\n";
    }

    void reportLowBalance() const {
        cout << "Enter threshold (Rs.): "; cout.flush();
        double threshold = readDouble();
        cout << "\nAccounts below Rs. " << fixed << setprecision(2) << threshold << ":\n";
        printSep();
        bool any = false;
        for (const auto& a : accounts) {
            if (a.getBalance() < threshold) {
                cout << "#" << setw(6) << a.getAccNo() << "  "
                     << setw(22) << a.getName() << "  "
                     << "Rs. " << fixed << setprecision(2) << a.getBalance() << "\n";
                any = true;
            }
        }
        if (!any) cout << "None found.\n";
        printSep();
    }

    void listAllAccounts() const {
        if (accounts.empty()) { cout << "No accounts registered.\n"; return; }
        printSep();
        cout << left << setw(8) << "ACC NO" << setw(22) << "NAME" << "BALANCE\n";
        printSep();
        for (const auto& a : accounts) a.display();
        printSep();
    }

    // ── Menu ─────────────────────────────────

    void run() {
        while (true) {
            cout << "\n====== SAVINGS BANK SYSTEM ======\n"
                 << " 1. Create New Account\n"
                 << " 2. Deposit\n"
                 << " 3. Withdraw\n"
                 << " 4. Balance Enquiry\n"
                 << " 5. Transaction History\n"
                 << " 6. All Accounts\n"
                 << " 7. Total Funds Report\n"
                 << " 8. Low Balance Report\n"
                 << " 0. Exit\n"
                 << "=================================\n"
                 << "Choice: "; cout.flush();

            int choice = readInt();

            switch (choice) {
                case 1: createAccount();          break;
                case 2: deposit();                break;
                case 3: withdraw();               break;
                case 4: balanceEnquiry();         break;
                case 5: viewTransactionHistory(); break;
                case 6: listAllAccounts();        break;
                case 7: reportTotalFunds();       break;
                case 8: reportLowBalance();       break;
                case 0: cout << "Goodbye.\n"; return;
                default: cout << "Invalid choice. Enter 0-8.\n";
            }
        }
    }
};

int main() {
    BankSystem bank;
    bank.run();
    return 0;
}