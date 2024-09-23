#include <iostream>
#include <cctype>
#include <string>
#include <limits>
using namespace std;

// Base class for BankAccount
class BankAccount {
protected:
	double balance; // Protected so dervied classes can access it directly (encapsulation)

public:
	BankAccount() : balance(0) {} // Constructor initializes balance to 0
	
	// Pure virtual functions force derived classes to implement their versions of deposit, withdraw, and balance (abstraction)
	virtual void updateDeposit() = 0; // Abstract functions control the "balance" internally  (encapsulation)
	virtual void updateWithdraw() = 0;
	virtual void checkBalance() const = 0;
	
	void displaySubMenu() {
		cout << "Sub Menu" << endl;
		cout << "\t1 - Deposit" << endl;
		cout << "\t2 - Withdraw" << endl;
		cout << "\t3 - Check Balance" << endl;
		cout << "\t4 - Back" << endl;
	}
};

bool getValidDouble(double& amount) { 
    string input;
    bool validInput;

    do {
        validInput = true;
        cout << "\tAmount: Php ";
        cin >> input;

        for (char c : input) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            amount = stod(input); // Convert string to double
            if (amount <= 0) {
                validInput = false;
                cout << "\tPlease enter a positive amount." << endl;
            }
        } else {
            cout << "\tInvalid input!\n\tPlease enter a numeric value." << endl;
        }

    } while (!validInput);

    return true;
}

// Derived class for SavingsAccount
class SavingsAccount : public BankAccount {
public:
	// Constructor that accepts an initial balance
    SavingsAccount(double initialBalance) {
        balance = initialBalance;  // Access protected member of base class
    }
	
	// All interaction with balance is controlled using these methods (encapsulation)
	void updateDeposit() override {
		double amount;
		cout << "Deposit Money" << endl;
		if (getValidDouble(amount)) {
			balance += amount; 
			cout << "\tDeposit of Php " << amount << " was successful!" << endl << endl;
		}
	}
	
	void updateWithdraw() override {
		double amount;
		if (balance <= 1000) {
	        checkBalance();
	        return;
	    }
		do {
			checkBalance();
			cout << "Withdraw Money" << endl;
			getValidDouble(amount);
			
			if (amount <= 0) {
				cout << "\tInvalid amount!\n\tPlease enter a positive value." << endl << endl; 
			} else if (amount > balance) {
				cout << "\tWithdrawal denied!\n\tAmount exceeds current balance." << endl << endl;
			} else if (balance - amount < 1000) {
				cout << "\tWithdrawal denied!\n\tBalance is insufficient for withdrawal." << endl;
				cout << "\tMinimum balance of Php 1000 required.\n\tInput a new amount." << endl << endl;
			}
		} while (amount <= 0 || amount > balance || balance - amount < 1000);
		
		// If all conditions are met, perform the withdrawal
		balance -= amount;
		cout << "\tWithdrawal of Php " << amount << " was successful!" << endl << endl;
	}
	
	// Balance is only accessible using this method (encapsulation)
	void checkBalance() const override {
		cout << "Balance Inquiry" << endl;
		cout << "\tBalance: Php " << balance << endl; // Print balance
		if (balance <= 1000) {
			cout << "\tWithdrawals not allowed." << endl;
			cout << "\tMinimum balance of Php 1000 required." << endl << endl;
		} else {
			cout << "\tWithdrawals allowed." << endl << endl;
		}
	}
};

// Derived class for CurrentAccount
class CurrentAccount : public BankAccount {
public:
	CurrentAccount(double initialBalance) {
        balance = initialBalance; // Access protected member of base class
    }
	
	void updateDeposit() override {
		double amount;
		cout << "Deposit Money" << endl;
		if (getValidDouble(amount)) {
			balance += amount; // Add deposit amount to balance
			cout << "\tDeposit of Php " << amount << " was successful!" << endl << endl;
		}
	}
	
	void updateWithdraw() override {
		double amount;
		if (balance <= 0){
			checkBalance();
			return;
		} 		
		do {
			checkBalance();
			cout << "Withdraw Money" << endl;
			getValidDouble(amount);
			
			if (amount <= 0) {
				cout << "\tInvalid amount!\n\tPlease enter a positive value." << endl << endl;
			} else if (amount > balance) {
				cout << "\tWithdrawal denied!\n\tAmount exceeds current balance.\n\tInput a new amount." << endl << endl;
			}
		} while (amount <= 0 || amount > balance);
		balance -= amount; // Subtract withdrawal amount from balance
		cout << "\tWithdrawal of Php " << amount << " was successful!" << endl << endl;
	}
	
	void checkBalance() const override {
		cout << "Balance Inquiry" << endl;
		cout << "\tBalance: Php " << balance << endl; // Print balance
		if (balance <= 0) {
			cout << "\tYour account balance is Php 0.\n\tWithdrawals not allowed." << endl << endl;
		} else {
			cout << "\tWithdrawals allowed." << endl << endl;
		}
	}
};

bool getValidMenuChoice(int& choice, int min, int max) {
    string input;
    bool validInput;

    do {
        validInput = true;
        cout << "Select Action: ";
        cin >> input;

        // Check if the input is a valid integer
        for (char c : input) {
            if (!isdigit(c)) {
                validInput = false;
                break;
            }
        }

        if (validInput) {
            choice = stoi(input);
            if (choice < min || choice > max) {
                validInput = false;
                cout << "\tInvalid input!\n\tPlease select a number between " << min << " and " << max << "." << endl;
            }
        } else {
            cout << "\tInvalid input!\n\tPlease enter a numeric value." << endl;
        }

    } while (!validInput);

    return true;
}

void displaySubMenu(BankAccount* account){
	int choice;
	do {
		account->displaySubMenu(); // Call the method to show options
		getValidMenuChoice(choice, 1, 4);
		cout << endl;
		
		switch (choice) {
			case 1:
				account->updateDeposit(); // Call the method to update deposit
				break;
			case 2:
				account->updateWithdraw(); // Call the method to update withdraw
				break;
			case 3:
				account->checkBalance(); // Call the method to check balance
				break;
			case 4:
				cout << "Returning to Main Menu..." << endl << endl;
				break;
			default:
				cout << "Invalid action! Please try again." << endl;
		}
	} while (choice != 4);
}

// Function to display main menu and handle account selection
void displayMainMenu() {
	BankAccount* currentAccount = nullptr; // Pointer to current account
    BankAccount* savingsAccount = nullptr; // Pointer to savings account
	int choice;
	do {
		cout << "------------------ My Bank ------------------" << endl << endl;
		cout << "Main Menu" << endl;
		cout << "\t1 - Savings Account" << endl;
		cout << "\t2 - Current Account" << endl;
		cout << "\t3 - Exit" << endl;
		getValidMenuChoice(choice, 1, 3);
		cout << endl;
		
		switch (choice) {
		case 1:
			cout << "-------------- Savings Account --------------\n\n";
			// Only initialize the savings account if it doesn't exist yet
			if (!savingsAccount) {
				savingsAccount = new SavingsAccount(1000.00);
			}
			displaySubMenu(savingsAccount); // Use the same savings account
			break;
		case 2:
			cout << "-------------- Current Account --------------\n\n";
			// Only initialize the current account if it doesn't exist yet
			if (!currentAccount) {
				currentAccount = new CurrentAccount(0);
			}
			displaySubMenu(currentAccount); // Use the same current account
			break;
		case 3:
			cout << "Thank you for using My Bank!" << endl;
			break;
		default:
			cout << "Invalid action! Please try again." << endl << endl;
		}		
	} while (choice !=3);
	// Free the memory before exiting
	delete savingsAccount;
    delete currentAccount;
};

int main() {
	displayMainMenu();
	return 0;
}