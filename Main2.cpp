#include <iostream>
#include <string> 
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cstdlib> <regex> <stdexcept>
#include <ctime> <memory> <iomanip> <sstream> <chrono>
#include <cstring> <vector> <cstdio> <limits>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <conio.h>

sql::Connection* globalCon = nullptr;

using namespace std;
bool isValidPhoneNumber(const string& phone);
void executeInstructionWithValidation(const string& query, const string& successMessage);
bool isValidUsername(const string& username);
void RunQueryAndDisplayResultWithAverage(const string& query, const string& totalMessage, const string& avgMessage);
void Add_guest();
void Add_staff();
bool isNumeric(const string& str);
string getPasswordInput();
bool isValidMonth1(const std::string& month);
bool isValidDay1(const std::string& day);
bool isValidYear1(const std::string& year);
string getCurrentYear();
string formatDateString(const std::string& year, const std::string& month, const std::string& day);
void applyVoucher(const std::string& username, const std::string& pass);
void generateReceipt(const std::string& username, const std::string& pass);
void cancelReservationForStaff(const string& username, const string& pass);
void RunQueryAndDisplayAllData(const string& query);
double RunSalesQuery(const string& query);
void DailyReport();
void MonthlyReport();
void QuarterlyReport();
void HalfYearlyReport();
void getMonthInput(int& year, int& month);
void YearlyReport();
string getDateInput();
bool isValidDate1(int year, int month, int day);
bool isValidDay(int year, int month, int day);
bool isValidMonth(int month);
bool isValidYear(int year);
void RunQueryAndDisplayResult(const string& query, const string& message);
void ViewRoomBookings();
void ViewSalesReport();
void AdminReportModule();
void Room_info(const string& username, const string& pass);
void Update_check_in(const string& username, const string& pass); // for the staff menu 
string generateUniqueRoomNumber();
void viewReservations(const string& username, const string& pass);
bool isValidDate(int year, int month, int day);
void payment(const string& paymentMethod, const string& id);
string calculateCheckOutDate(const string& checkInDate, int numberOfNights);
void bookRoom(const string& username, const string& pass);
void Update_guest_details(const string& username, const string& pass);
void Guest_account_manage(const string& username, const string& pass);
void Guest_account_update();
void Delete_guest();
void ShowAllGuestUsernames();
void ShowAllstaffUsernames();
void Delete_staff();
void Staff_account_update();
void Guest_managment();
void Staff_managment();
void Guest_account_info(const string& username, const string& pass);
void Admin_account_info();
void connectToDatabase();
void closeDatabaseConnection();
void executeInstruction(const string& instruction);
bool isColumnDataPresent(const string& tableName, const string& columnName);
bool doesValueExist(const string& keyColumn, const string& keyValue, const string& tableName);
void MainMenu();
void admin_main_menu();
void staff_main_menu(const string& username, const string& pass);
void Register();
void Login();
void guest_main_menu(const string& username, const string& pass);
void Staff_account_info(const string& username, const string& pass);




int main() {
    system("cls");
    string res1;
    do {
        cout << R"(
  _  _     _       _   __  __                                       _     ___         _             
 | || |___| |_ ___| | |  \/  |__ _ _ _  __ _ __ _ ___ _ __  ___ _ _| |_  / __|_  _ __| |_ ___ _ __  
 | __ / _ \  _/ -_) | | |\/| / _` | ' \/ _` / _` / -_) '  \/ -_) ' \  _| \__ \ || (_-<  _/ -_) '  \ 
 |_||_\___/\__\___|_| |_|  |_\__,_|_||_\__,_\__, \___|_|_|_\___|_||_\__| |___/\_, /__/\__\___|_|_|_|
                                            |___/                             |__/                  
)" << "\n\n";

        cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << "\n";
        cout << "     @@\t\t\t\t\t\t    @@" << "\n";
        cout << "     @@ Would you like to enter the program ? (Y/N) @@" << "\n";
        cout << "     @@\t\t\t\t\t\t    @@" << "\n";
        cout << "     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << "\n" << endl;
        cout << "     Enter your answer > ";
        getline(cin,res1);

        if (res1 == "Y" || res1 == "y" || res1 == "yes" || res1 == "Yes") {
            system("cls");
            MainMenu();
        }
        else if (res1 == "N" || res1 == "n" || res1 == "No") {
            cout << " \tThank you ..." << endl;
            exit(0);
        }
        else {
            string retry;
            do {
                cout << "\tWrong input ... try again (Y/N) : ";
                getline(cin,retry);
                if (retry == "Y" || retry == "y" || retry == "Yes") {
                    system("cls");
                    break;
                }
                else if (retry == "N" || retry == "n" || retry == "No") {
                    cout << " \tThank you ..." << endl;
                    exit(0);
                }
                else {
                    cout << "\tInvalid input. Please enter Y or N." << endl;
                }
            } while (true);
        }
    } while (true);
}

void connectToDatabase() {
    try {
        sql::Driver* driver = get_driver_instance();
        globalCon = driver->connect("tcp://127.0.0.1:3306", "root", "");
        globalCon->setSchema("hms"); // Replace with your database name
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void closeDatabaseConnection() {
    if (globalCon) {
        globalCon->close();
        delete globalCon;
        globalCon = nullptr;
    }
}

void executeInstruction(const string& instruction) {
    try {
        sql::Statement* stmt = globalCon->createStatement();
        stmt->execute(instruction);
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool isColumnDataPresent(const string& tableName, const string& columnName) {
    bool dataPresent = false;
    try {
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT COUNT(*) FROM " + tableName + " WHERE " + columnName + " IS NOT NULL AND " + columnName + " != ''";
        sql::ResultSet* res = stmt->executeQuery(query);

        if (res->next()) {
            dataPresent = res->getInt(1) > 0;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return dataPresent;
}

bool doesValueExist(const string& keyColumn, const string& keyValue, const string& tableName) {
    bool exists = false;
    try {
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT EXISTS(SELECT 1 FROM " + tableName + " WHERE " + keyColumn + " = '" + keyValue + "')";
        sql::ResultSet* res = stmt->executeQuery(query);

        if (res->next()) {
            exists = res->getInt(1) == 1;
        }
        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return exists;
}

void MainMenu() {
    int res1;
    string res2;

    do {
        system("cls");
        cout << R"(
 ____    ____          _             ____    ____                         
|_   \  /   _|        (_)           |_   \  /   _|                        
  |   \/   |   ,--.   __   _ .--.     |   \/   |  .---.  _ .--.  __   _   
  | |\  /| |  `'_\ : [  | [ `.-. |    | |\  /| | / /__\\[ `.-. |[  | | |  
 _| |_\/_| |_ // | |, | |  | | | |   _| |_\/_| |_| \__., | | | | | \_/ |, 
|_____||_____|\'-;__/[___][___||__] |_____||_____|'.__.'[___||__]'.__.'_/ 
                                                                          

)" << endl;

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Register " << "\t\t @" << endl;
        cout << "\t@\t" << " 2. Login " << "\t\t @" << endl;
        cout << "\t@\t" << " 3. Exit " << "\t\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> res1;

        // Check if the input is not an integer or not in the valid range
        if (cin.fail() || res1 < 1 || res1 > 3) {
            cin.clear(); // Clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            res1 = -1; // Set a sentinel value to indicate invalid input
        }

        switch (res1) {
        case 1:
            cout << "Debug: Register option selected." << endl;
            system("cls");
            Register();
            break;
        case 2:
            cout << "Debug: Login option selected." << endl;
            system("cls");
            Login();
            break;
        case 3:
            system("cls");
            exit(0); // Ensure we exit the loop and return to the calling function
        default:
            bool validInput = false;
            do {
                cout << "\tWrong input ... Please try again (Y/N) : ";
                getline(cin,res2);
                if (cin.fail()) {
                    cin.clear(); // Clear the error flags
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                }
                else if (res2 == "N" || res2 == "n" || res2 == "No") {
                    cout << " \tThank you ..." << endl;
                    exit(0);
                }
                else if (res2 == "Y" || res2 == "y" || res2 == "Yes") {
                    cout << "Debug: Re-displaying menu." << endl;
                    validInput = true; // Exit the loop and re-display the menu
                }
                else {
                    cout << "\tInvalid input. Please enter Y or N." << endl;
                }
            } while (!validInput);
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    } while (true);
}

void Register() {
    int res;
    do {
        connectToDatabase();
        string usernames;
        string passe;
        string name;
        string address;
        string phone;
        int x = time(0);
        srand(x);
        int random = 10000 + (rand() % 20000);
        string id = to_string(random);

        system("cls");
        cout << R"(
  ___          _    _           
 | _ \___ __ _(_)__| |_ ___ _ _ 
 |   / -_) _` | (_-<  _/ -_) '_|
 |_|_\___\__, |_/__/\__\___|_|  
         |___/                  
)";
        while (true) {
            cout << "\n\tEnter Your Username (or 0 to go back): ";
            cin >> usernames;
            if (usernames == "0") {
                MainMenu();
                return;
            }
            if (usernames.empty() || usernames.size() < 5) {
                cout << "\n\tError: Username must be at least 5 characters long." << endl;
                continue;
            }
            break;
        }
        string type = usernames.substr(0, 1);
        if (type == "&") {
            if (doesValueExist("Admin_username", usernames, "admin")) {
                cout << "\n\tError: Username is already taken." << endl;
            }
            else if (isColumnDataPresent("admin", "Admin_username")) {
                cout << "\n\tError: Only one admin is allowed at a time." << endl;
            }
            else {
                while (true) {
                    passe = getPasswordInput();
                    if (passe.length() < 4 || passe.length() > 16) {
                        cout << "\n\tError: Password must be between 4 and 16 characters." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter your name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);

                while (true) {
                    cout << "\tEnter your phone number: ";
                    cin >> phone;
                    if (!isValidPhoneNumber(phone)) {
                        cout << "\n\tError: Phone number must be numeric, start with 0, and have 11 digits." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter your address: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, address);

                if (name.empty() || phone.empty() || address.empty()) {
                    cout << "\n\tError: All fields must be filled." << endl;
                    continue;
                }

                cout << "\n\tRegistration Completed ... !!";

                executeInstruction("INSERT INTO `admin`(`Admin_ID`, `Admin_name`, `Admin_username`, `Admin_password`, `Admin_address`, `Admin_phonenumber`) VALUES('" + id + "', '" + name + "', '" + usernames + "','" + passe + "', '" + address + "', '" + phone + "')");
            }
        }
        else if (type == "$") {
            if (doesValueExist("Staff_username", usernames, "staff")) {
                cout << "\n\tError: Username is already taken." << endl;
            }
            else {
                while (true) {
                    passe = getPasswordInput();
                    if (passe.length() < 4 || passe.length() > 16) {
                        cout << "\n\tError: Password must be between 4 and 16 characters." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter Staff name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);

                while (true) {
                    cout << "\tEnter Staff phone number: ";
                    cin >> phone;
                    if (!isValidPhoneNumber(phone)) {
                        cout << "\n\tError: Phone number must be numeric, start with 0, and have 11 digits." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter Staff address: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, address);

                if (name.empty() || phone.empty() || address.empty()) {
                    cout << "\n\tError: All fields must be filled." << endl;
                    continue;
                }

                cout << "\n\tRegistration Completed ... !!" << endl;

                executeInstruction("INSERT INTO `staff`(`Sfaff_ID`, `Staff_username`, `Staff_password`, `Staff_name`, `Staff_phonenumber`, `Staff_address`) VALUES('" + id + "', '" + usernames + "', '" + passe + "', '" + name + "', '" + phone + "', '" + address + "')");
            }
        }
        else {
            if (doesValueExist("Guest_username", usernames, "guest")) {
                cout << "\n\tError: Username is already taken." << endl;
            }
            else {
                while (true) {
                    passe = getPasswordInput();
                    if (passe.length() < 4 || passe.length() > 16) {
                        cout << "\n\tError: Password must be between 4 and 16 characters." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter your name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);

                while (true) {
                    cout << "\tEnter your phone number: ";
                    cin >> phone;
                    if (!isValidPhoneNumber(phone)) {
                        cout << "\n\tError: Phone number must be numeric, start with 0, and have 11 digits." << endl;
                        continue;
                    }
                    break;
                }

                cout << "\tEnter your address: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, address);

                if (name.empty() || phone.empty() || address.empty()) {
                    cout << "\n\tError: All fields must be filled." << endl;
                    continue;
                }

                cout << "\n\tRegistration Completed ... !!" << endl;

                executeInstruction("INSERT INTO `guest`(`Guest_ID`, `Guest_name`, `Guest_username`, `Guest_password`, `Guest_address`, `Guest_phonenumber`) VALUES ('" + id + "','" + name + "','" + usernames + "','" + passe + "','" + address + "','" + phone + "')");
            }
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any service ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit program) \t\t     @";
        cout << "\n\n\t@ 3.Main Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            MainMenu(); // Uncomment and implement MainMenu if needed
        }

    } while (res == 1);

    closeDatabaseConnection();
}

void Login() {
    connectToDatabase();
    string username;
    string pass;
    int res;
    do {
        cout << system("cls");
        cout << R"(
  _              _      
 | |   ___  __ _(_)_ _  
 | |__/ _ \/ _` | | ' \ 
 |____\___/\__, |_|_||_|
           |___/        
)";
        cout << "\tEnter your username or press (0) to go back: ";
        cin >> username;
        if (username == "0") {
            MainMenu();
            return;
        }
        pass = getPasswordInput();
        string type = username.substr(0, 1);

        bool validLogin = false;
        if (type == "&") {
            string query = "SELECT `Admin_username`,`Admin_password` FROM `admin` WHERE `Admin_username` = '" + username + "' AND `Admin_password` = '" + pass + "'";
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* resultSet = stmt->executeQuery(query);
            if (resultSet->next()) {
                cout << system("cls");
                admin_main_menu();
                validLogin = true;
            }
        }
        else if (type == "$") {
            string query = "SELECT `Staff_username` FROM `staff` WHERE `Staff_username` = '" + username + "' AND `Staff_password` = '" + pass + "'";
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* resultSet = stmt->executeQuery(query);
            if (resultSet->next()) {
                cout << system("cls");
                staff_main_menu(username, pass);
                validLogin = true;
            }
        }
        else {
            string query = "SELECT `Guest_username` FROM `guest` WHERE `Guest_username` = '" + username + "' AND `Guest_password` = '" + pass + "'";
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* resultSet = stmt->executeQuery(query);
            if (resultSet->next()) {
                cout << system("cls");
                guest_main_menu(username, pass);
                validLogin = true;
            }
        }

        if (!validLogin) {
            cout << "\n\tError: Wrong username or password" << endl;
            cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
            cout << "\n        @  Would you like to try again ?     @";
            cout << "\n\n\t@ 1. Yes \t\t\t     @";
            cout << "\n\n\t@ 2. No (Exit Program) \t             @";
            cout << "\n\n\t@ 3. Main Menu \t\t\t     @";
            cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
            cout << "\n\tEnter your choice > ";

            while (true) {
                cin >> res;
                if (cin.fail()) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                    cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                    cout << "\n\tEnter your choice > ";
                    continue; // Prompt again for valid input
                }

                if (res == 1 || res == 2 || res == 3) {
                    break; // Exit the loop if input is valid
                }
                else {
                    cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                    cout << "\n\tEnter your choice > ";
                }
            }

            if (res == 2) {
                exit(0);
            }
            else if (res == 3) {
                system("cls");
                MainMenu();
            }
        }
        else {
            res = 0; // Exit the loop if login is successful
        }
    } while (res == 1);

    closeDatabaseConnection();
}

void admin_main_menu() {
    system("cls");
    int respond, res;
    do {
        system("cls");
        cout << R"(
    _      _       _        __  __              
   /_\  __| |_ __ (_)_ _   |  \/  |___ _ _ _  _ 
  / _ \/ _` | '  \| | ' \  | |\/| / -_) ' \ || |
 /_/ \_\__,_|_|_|_|_|_||_| |_|  |_\___|_||_\_,_|
                                                

)";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Account Details " << "\t @" << endl;
        cout << "\t@\t" << " 2. Staff Management " << "    @" << endl;
        cout << "\t@\t" << " 3. Guest management " << "\t @" << endl;
        cout << "\t@\t" << " 4. Report module " << "\t @" << endl;
        cout << "\t@\t" << " 5. Go back to Main Menu " << "@" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> respond;
        if (respond == 1) {

            Admin_account_info();

        }
        else if (respond == 2) {
            Staff_managment();
        }
        else if (respond == 3) {
            Guest_managment();

        }
        else if (respond == 4) {
            AdminReportModule();
        }
        else if (respond == 5) {

            MainMenu();
        }
        cout << "\n\tError : Wrong input ... " << endl;
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like to try again ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit program) \t\t     @";
        cout << "\n\n\t@ 3.Main Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            MainMenu();
        }
    } while (res == 1);
}

void staff_main_menu(const string& username, const string& pass) {
    int respond, res;
    do {
        system("cls");
        cout << R"(
  ___ _         __  __   __  __              
 / __| |_ __ _ / _|/ _| |  \/  |___ _ _ _  _ 
 \__ \  _/ _` |  _|  _| | |\/| / -_) ' \ || |
 |___/\__\__,_|_| |_|   |_|  |_\___|_||_\_,_|
                                             
                                                                               
)";

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Account Details " << "\t @" << endl;
        cout << "\t@\t" << " 2. Cancel Reservation" << "\t @" << endl;
        cout << "\t@\t" << " 3. Generate receipt " << "\t @" << endl;
        cout << "\t@\t" << " 4. Voucher Application  " << "@" << endl;
        cout << "\t@\t" << " 5. Go back " << "\t\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\tEnter your Choice > ";
        cin >> respond;
        if (respond == 1) {

            Staff_account_info(username, pass);
        }
        else if (respond == 2) {
            cancelReservationForStaff(username, pass);
            cout << endl;
        }
        else if (respond == 3) {
            generateReceipt(username, pass);
        }
        else if (respond == 4) {
            applyVoucher(username, pass);
        }
        else if (respond == 5) {
            MainMenu();
        }
        else {
            cout << "\n\tError : Wrong input ... ";
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit program) \t\t     @";
        cout << "\n\n\t@ 3.Main Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            MainMenu();
        }

    } while (res == 1);
}

void guest_main_menu(const string& username, const string& pass) {
    int respond;

    int res1;
    do {
        connectToDatabase();
        system("cls");

        cout << R"(
   ___             _     __  __              
  / __|_  _ ___ __| |_  |  \/  |___ _ _ _  _ 
 | (_ | || / -_|_-<  _| | |\/| / -_) ' \ || |
  \___|\_,_\___/__/\__| |_|  |_\___|_||_\_,_|
                                             
                                        
)";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Account Management " << "\t @" << endl;
        cout << "\t@\t" << " 2. Book a room" << " \t @" << endl;
        cout << "\t@\t" << " 3. View reservations " << "\t @" << endl;
        cout << "\t@\t" << " 4. Room description" << "\t @" << endl;
        cout << "\t@\t" << " 5. Go back" << "\t         @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> respond;
        if (respond == 1) {
            system("cls");
            Guest_account_manage(username, pass);

        }
        else if (respond == 2) {
            system("cls");
            bookRoom(username, pass);

        }
        else if (respond == 3) {
            system("cls");
            viewReservations(username, pass);

        }
        else if (respond == 4) {
            system("cls");
            Room_info(username, pass);

        }
        else if (respond == 5) {
            system("cls");
            MainMenu();
        }
        else {
            cout << "\n\tError : Wrong input ... ";
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit program) \t\t     @";
        cout << "\n\n\t@ 3.Main Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            MainMenu();
        }
        closeDatabaseConnection();
    } while (res1 == 1);

}

void Admin_account_info() {
    connectToDatabase();
    int res, res1;
    do {
        system("cls");
        do {
            cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
            cout << "\n\t@       Admin Account Info       @";
            cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
            cout << "\n\t@ 1. View Account Info           @";
            cout << "\n\t@ 2. Update Account Info         @";
            cout << "\n\t@ 3. Go Back to Admin Menu       @";
            cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue;
            }

            if (res == 1 || res == 2 || res == 3) {
                break;
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        } while (true);

        if (res == 1) {
            // View Account Info
            try {
                sql::Statement* stmt = globalCon->createStatement();
                sql::ResultSet* res_id = stmt->executeQuery("SELECT Admin_ID FROM admin LIMIT 1");

                int admin_id = -1;
                if (res_id->next()) {
                    admin_id = res_id->getInt("Admin_ID");
                }

                delete res_id;
                delete stmt;

                if (admin_id != -1) {
                    stmt = globalCon->createStatement();
                    sql::ResultSet* res = stmt->executeQuery("SELECT * FROM admin WHERE Admin_ID = " + to_string(admin_id));

                    if (res->next()) {
                        system("cls");
                        cout << "\n";
                        cout << "\tAdmin ID: " << res->getString("Admin_ID") << endl;
                        cout << "\tAdmin Name: " << res->getString("Admin_name") << endl;
                        cout << "\tAdmin Username: " << res->getString("Admin_username") << endl;
                        cout << "\tAdmin Password: " << res->getString("Admin_password") << endl;
                        cout << "\tAdmin Address: " << res->getString("Admin_address") << endl;
                        cout << "\tAdmin Phone Number: " << res->getString("Admin_phonenumber") << endl;
                    }
                    else {
                        cout << "Error: No data found for Admin ID " << admin_id << endl;
                    }

                    delete res;
                    delete stmt;
                }
                else {
                    cout << "Error: No Admin ID found in the database" << endl;
                }
            }
            catch (sql::SQLException& e) {
                cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                    << ", SQLState: " << e.getSQLState() << " )" << endl;
            }
        }
        else if (res == 2) {
            // Update Account Info
            try {
                sql::Statement* stmt = globalCon->createStatement();
                sql::ResultSet* res_id = stmt->executeQuery("SELECT Admin_ID FROM admin LIMIT 1");

                int admin_id = -1;
                if (res_id->next()) {
                    admin_id = res_id->getInt("Admin_ID");
                }

                delete res_id;
                delete stmt;

                if (admin_id != -1) {
                    string name, username, password, address, phone;

                    cout << "\tEnter new Admin Name: ";
                    cin.ignore();
                    getline(cin, name);

                    do {
                        cout << "\tEnter new Admin Username (must start with '&'): ";
                        cin >> username;
                        if (username[0] != '&') {
                            cout << "\tError: Username must start with '&'. Please try again." << endl;
                        }
                    } while (username[0] != '&');

                    password = getPasswordInput();

                    cout << "\tEnter new Admin Address: ";
                    cin.ignore();
                    getline(cin, address);

                    cout << "\tEnter new Admin Phone Number: ";
                    cin >> phone;
                    while (cin.fail() || phone.find_first_not_of("0123456789") != string::npos) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\tError: Phone number must be numeric. Please enter again: ";
                        cin >> phone;
                    }

                    string query = "UPDATE admin SET Admin_name = '" + name + "', Admin_username = '" + username + "', Admin_password = '" + password + "', Admin_address = '" + address + "', Admin_phonenumber = '" + phone + "' WHERE Admin_ID = " + to_string(admin_id);
                    stmt = globalCon->createStatement();
                    stmt->executeUpdate(query);

                    cout << "\n\tAdmin info updated successfully!" << endl;

                    delete stmt;
                }
                else {
                    cout << "Error: No Admin ID found in the database" << endl;
                }
            }
            catch (sql::SQLException& e) {
                cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                    << ", SQLState: " << e.getSQLState() << " )" << endl;
            }
        }
        else if (res == 3) {
            // Go Back
            system("cls");
            admin_main_menu();
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Admin Menu \t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            admin_main_menu();
        }
    } while (res1 == 1);
    closeDatabaseConnection();
}

void Staff_account_info(const string& username, const string& pass) {
    connectToDatabase();
    system("cls");
    try {
        // Fetch guest information based on the provided username and password
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT * FROM staff WHERE Staff_username = '" + username + "' AND Staff_password = '" + pass + "'";
        sql::ResultSet* res = stmt->executeQuery(query);

        // Check if there are any results
        if (res->next()) {
            cout << "\tStaff ID: " << res->getString("Sfaff_ID") << endl;
            cout << "\tStaff Name: " << res->getString("Staff_name") << endl;
            cout << "\tStaff Username: " << res->getString("Staff_username") << endl;
            cout << "\tStaff Password: " << res->getString("Staff_password") << endl;
            cout << "\tStaff Address: " << res->getString("Staff_address") << endl;
            cout << "\tStaff Phone Number: " << res->getString("Staff_phonenumber") << endl;
        }
        else {
            cout << "No data found for the provided credentials" << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    closeDatabaseConnection();
}

void Guest_account_info(const string& username, const string& pass) {
    system("cls");
    int res1;
    connectToDatabase();
    system("cls");
    try {
        // Fetch guest information based on the provided username and password
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT * FROM guest WHERE Guest_username = '" + username + "' AND Guest_password = '" + pass + "'";
        sql::ResultSet* res = stmt->executeQuery(query);

        // Check if there are any results
        if (res->next()) {
            cout << "\n\tGuest ID: " << res->getString("Guest_ID") << endl;
            cout << "\tGuest Name: " << res->getString("Guest_name") << endl;
            cout << "\tGuest Username: " << res->getString("Guest_username") << endl;
            cout << "\tGuest Password: " << res->getString("Guest_password") << endl;
            cout << "\tGuest Address: " << res->getString("Guest_address") << endl;
            cout << "\tGuest Phone Number: " << res->getString("Guest_phonenumber") << endl;
        }
        else {
            cout << "\n\tError : No data found for the provided credentials\n" << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    closeDatabaseConnection();
}

void Staff_managment() {
    connectToDatabase();
    int respond, res1, res;
    do {
        system("cls");

        cout << R"(
  ___ _         __  __   __  __                                       _   
 / __| |_ __ _ / _|/ _| |  \/  |__ _ _ _  __ _ __ _ ___ _ __  ___ _ _| |_ 
 \__ \  _/ _` |  _|  _| | |\/| / _` | ' \/ _` / _` / -_) '  \/ -_) ' \  _|
 |___/\__\__,_|_| |_|   |_|  |_\__,_|_||_\__,_\__, \___|_|_|_\___|_||_\__|
                                              |___/                       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
)";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Expel Staff " << "\t @" << endl;
        cout << "\t@\t" << " 2. Staff account update " << "@" << endl;
        cout << "\t@\t" << " 3. Hire new Staff " << "      @" << endl;
        cout << "\t@\t" << " 4. Go back to Admin Menu" << "@" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> respond;
        if (respond == 1) {
            system("cls");
            Delete_staff();
        }
        else if (respond == 2) {
            system("cls");
            Staff_account_update();
        }
        else if (respond == 3) {
            system("cls");
            Add_staff();
        }
        else if (respond == 4) {
            system("cls");
            admin_main_menu();
        }
        else {
            cout << "\n\tError :  Wrong input ...  \n ";
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services  ?    @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Admin Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            admin_main_menu();
        }

    } while (res == 1);
    closeDatabaseConnection();
}

void Delete_staff() {
    connectToDatabase();
    int res;
    string respond;
    do {
        system("cls");
        cout << R"(
  ___ _         __  __   ___      _     _   _           
 / __| |_ __ _ / _|/ _| |   \ ___| |___| |_(_)___ _ _   
 \__ \  _/ _` |  _|  _| | |) / -_) / -_)  _| / _ \ ' \  
 |___/\__\__,_|_| |_|   |___/\___|_\___|\__|_\___/_||_| 
                                                        
)";

        ShowAllstaffUsernames();

        cout << "\n\n\tType the Username you would like to expel or type '0' to go back: ";
        cin >> respond;

        if (respond == "0") {
            Staff_managment();
            return;
        }

        if (doesValueExist("Staff_username", respond, "staff")) {
            executeInstruction("DELETE FROM staff WHERE Staff_username='" + respond + "'");
            cout << "\n\tExpel Completed !!\n";
        }
        else {
            cout << "\n\tError : The username you chose does not exist.";
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue;
            }

            if (res == 1 || res == 2 || res == 3) {
                break;
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            Staff_managment();
        }

    } while (res == 1);
    closeDatabaseConnection();
}

void ShowAllstaffUsernames() {

    try {
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT Sfaff_ID, Staff_name, Staff_username FROM staff");

        cout << left << setw(15) << "Username"
            << left << setw(30) << "Name"
            << left << setw(10) << "ID"
            << endl;
        cout << "-----------------------------------------------------------" << endl;

        // Iterate over the result set and display each staff's details
        while (res->next()) {
            cout << left << setw(15) << res->getString("Staff_username")
                << left << setw(30) << res->getString("Staff_name")
                << left << setw(10) << res->getString("Sfaff_ID")
                << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

}

void Staff_account_update() {
    connectToDatabase();
    int res, res1;
    string respond, newValue;

    do {
        system("cls");

        cout << R"(
  ___ _         __  __     _                      _     _   _          _      _       
 / __| |_ __ _ / _|/ _|   /_\  __ __ ___ _  _ _ _| |_  | | | |_ __  __| |__ _| |_ ___ 
 \__ \  _/ _` |  _|  _|  / _ \/ _/ _/ _ \ || | ' \  _| | |_| | '_ \/ _` / _` |  _/ -_)
 |___/\__\__,_|_| |_|   /_/ \_\__\__\___/\_,_|_||_\__|  \___/| .__/\__,_\__,_|\__\___|
                                                             |_|                      
)";

        ShowAllstaffUsernames();

        cout << "\n\n\tType the Username you would like to update or type '0' to go back: ";
        getline(cin,respond);

        if (respond == "0") {
            Staff_managment();
            return;
        }

        if (doesValueExist("Staff_username", respond, "staff")) {
            cout << "\n\tUsername Found!! \n" << endl;

            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@\t" << " Choose your option" << "\t @" << endl;
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@\t" << " 1. Username " << "\t         @" << endl;
            cout << "\t@\t" << " 2. Password " << "            @" << endl;
            cout << "\t@\t" << " 3. Phone number" << "\t @" << endl;
            cout << "\t@\t" << " 4. Name" << "\t\t @" << endl;
            cout << "\t@\t" << " 5. Address" << "\t\t @" << endl;
            cout << "\t@\t" << " 6. Go back" << "\t\t @" << endl;
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            switch (res) {
            case 1:
                do {
                    cout << "\n\tEnter the new username (must start with $): ";
                    cin >> newValue;
                    if (newValue[0] != '$') {
                        cout << "\tError: The username must start with the '$' character.\n";
                    }
                } while (newValue[0] != '$');
                executeInstruction("UPDATE staff SET Staff_username='" + newValue + "' WHERE Staff_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 2:
                cout << "\n\tEnter the new password: ";
                cin >> newValue;
                executeInstruction("UPDATE staff SET Staff_password='" + newValue + "' WHERE Staff_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 3:
                cout << "\n\tEnter the new phone number: ";
                cin >> newValue;
                executeInstruction("UPDATE staff SET Staff_phone='" + newValue + "' WHERE Staff_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 4:
                cout << "\n\tEnter the new name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, newValue);
                executeInstruction("UPDATE staff SET Staff_name='" + newValue + "' WHERE Staff_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 5:
                cout << "\n\tEnter the new address: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, newValue);
                executeInstruction("UPDATE staff SET Staff_address='" + newValue + "' WHERE Staff_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 6:
                Staff_managment();
                return;
            default:
                cout << "\n\tInvalid option selected.";
                break;
            }
        }
        else {
            cout << "\n\tError: The username you chose is not in the database.";
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like anymore services ? @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue;
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break;
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            Staff_managment();
        }

    } while (res1 == 1);
    closeDatabaseConnection();
}

void ShowAllGuestUsernames() {
    connectToDatabase();
    try {
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* res = stmt->executeQuery("SELECT Guest_ID, Guest_name, Guest_username FROM guest");

        cout << left << setw(15) << "Username"
            << left << setw(30) << "Name"
            << left << setw(10) << "ID"
            << endl;
        cout << "-----------------------------------------------------------" << endl;

        // Iterate over the result set and display each staff's details
        while (res->next()) {
            cout << left << setw(15) << res->getString("Guest_username")
                << left << setw(30) << res->getString("Guest_name")
                << left << setw(10) << res->getString("Guest_ID")
                << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    closeDatabaseConnection();
}

void Guest_managment() {
    connectToDatabase();
    int respond, res1, res;
    do {
        system("cls");

        cout << R"(
   ___             _     __  __                                       _   
  / __|_  _ ___ __| |_  |  \/  |__ _ _ _  __ _ __ _ ___ _ __  ___ _ _| |_ 
 | (_ | || / -_|_-<  _| | |\/| / _` | ' \/ _` / _` / -_) '  \/ -_) ' \  _|
  \___|\_,_\___/__/\__| |_|  |_\__,_|_||_\__,_\__, \___|_|_|_\___|_||_\__|
                                              |___/                       
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
)";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. Delete Guest " << "\t @" << endl;
        cout << "\t@\t" << " 2. Guest account update " << "@" << endl;
        cout << "\t@\t" << " 3. Add new Guest" << "        @" << endl;
        cout << "\t@\t" << " 4. Go back to Admin Menu" << "@" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> respond;
        if (respond == 1) {
            system("cls");
            Delete_guest();
        }
        else if (respond == 2) {
            system("cls");
            Guest_account_update();
        }
        else if (respond == 3) {
            system("cls");
            Add_guest();
        }
        else if (respond == 4) {
            system("cls");
            admin_main_menu();
        }
        else {
            cout << "\n\tError :  Wrong input ... \n ";
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like anymore services ? @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            admin_main_menu();
        }



    } while (res1 == 1);
    closeDatabaseConnection();
}

void Guest_account_update() {

    connectToDatabase();

    if (globalCon == nullptr) {
        cout << "Failed to connect to the database." << endl;
        return;
    }
    int res, res1;
    string user, newValue, respond;

    do {
        system("cls");



        cout << R"(
   ___             _       _                      _     _   _          _      _       
  / __|_  _ ___ __| |_    /_\  __ __ ___ _  _ _ _| |_  | | | |_ __  __| |__ _| |_ ___ 
 | (_ | || / -_|_-<  _|  / _ \/ _/ _/ _ \ || | ' \  _| | |_| | '_ \/ _` / _` |  _/ -_)
  \___|\_,_\___/__/\__| /_/ \_\__\__\___/\_,_|_||_\__|  \___/| .__/\__,_\__,_|\__\___|
                                                             |_|                      

)";

        ShowAllGuestUsernames();

        connectToDatabase();
        cout << "\n\n\tType the Username you would like to Update or press (0) to go back: ";
        cin >> respond;
        if (respond == "0") {
            Guest_managment();
            return;
        }

        if (doesValueExist("Guest_username", respond, "guest")) {

            cout << "\n\tUsername Found!! \n" << endl;

            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@\t" << " Choose your option" << "\t @" << endl;
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@ " << " 1. Username " << "\t                 @" << endl;
            cout << "\t@ " << " 2. Password " << "                  @" << endl;
            cout << "\t@ " << " 3. Phone number" << "\t         @" << endl;
            cout << "\t@ " << " 4. Name" << "\t\t         @" << endl;
            cout << "\t@ " << " 5. Address" << "\t\t         @" << endl;
            cout << "\t@ " << " 6. Go back to Guest Management" << "@" << endl;
            cout << "\t@\t\t\t\t @" << endl;
            cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
            cout << "\n\tEnter your choice > ";
            cin >> res;

            switch (res) {
            case 1:

                cout << "\n\tEnter the new username : ";
                cin >> newValue;
                executeInstruction("UPDATE guest SET Guest_username='" + newValue + "' WHERE Guest_username='" + respond + "'");
                executeInstruction("UPDATE booking SET Guest_username='" + newValue + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 2:
                cout << "\n\tEnter the new password: ";
                cin >> newValue;
                executeInstruction("UPDATE guest SET Guest_password='" + newValue + "' WHERE Guest_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 3:
                cout << "\n\tEnter the new phone number: ";
                cin >> newValue;
                executeInstruction("UPDATE guest SET Guest_phone='" + newValue + "' WHERE Guest_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 4:
                cout << "\n\tEnter the new name: ";
                cin >> newValue;
                executeInstruction("UPDATE guest SET Guest_name='" + newValue + "' WHERE Guest_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 5:
                cout << "\n\tEnter the new address: ";
                cin >> newValue;
                executeInstruction("UPDATE guest SET Guest_address='" + newValue + "' WHERE Guest_username='" + respond + "'");
                cout << "\n\t Update completed !! \n";
                break;
            case 6:

                Guest_managment();

                break;
            default:
                cout << "\n\tInvalid option selected.";
                break;
            }
        }
        else {
            cout << "\n\tError: The username you chose is not in the database.";
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like anymore services ? @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Guest Management \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            Guest_managment();
        }

    } while (res1 == 1);
    closeDatabaseConnection();


}

void Delete_guest(){
    connectToDatabase();
    int res;
    string respond;
    do {
        system("cls");
        cout << R"(
   ___             _     ___      _     _   _          
  / __|_  _ ___ __| |_  |   \ ___| |___| |_(_)___ _ _  
 | (_ | || / -_|_-<  _| | |) / -_) / -_)  _| / _ \ ' \ 
  \___|\_,_\___/__/\__| |___/\___|_\___|\__|_\___/_||_|
                                                       

)";

        ShowAllGuestUsernames();


        connectToDatabase();
        cout << "\n\tWARNING : deleteing any account will result to cancel booking for that account";
        cout << "\n\n\tType the Username you would like to delete or press (0) to go back : ";
        cin >> respond;

        if (respond == "0") {
            Guest_managment();
            return;
        }

        if (doesValueExist("Guest_username", respond, "guest")) {

            cout << "\n\tDeletion Completed !! \n" << endl;

            executeInstruction("DELETE FROM guest WHERE Guest_username='" + respond + "'");
            executeInstruction("DELETE FROM booking WHERE Guest_username='" + respond + "'");

        }
        else {
            cout << "\n\tError : The username you choose is not in the database ";
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Guest Management      @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            Guest_managment();
        }

    } while (res == 1);
    closeDatabaseConnection();
}

void Guest_account_manage(const string& username, const string& pass) {

    int res, res1;
    do {
        system("cls");
        cout << R"(
    _                      _     __  __                         
   /_\  __ __ ___ _  _ _ _| |_  |  \/  |__ _ _ _  __ _ __ _ ___ 
  / _ \/ _/ _/ _ \ || | ' \  _| | |\/| / _` | ' \/ _` / _` / -_)
 /_/ \_\__\__\___/\_,_|_||_\__| |_|  |_\__,_|_||_\__,_\__, \___|
                                                      |___/     

)";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. View Information    " << " @" << endl;
        cout << "\t@\t" << " 2. Update account  " << "     @" << endl;
        cout << "\t@\t" << " 3. Go back to Guest Menu" << "@" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> res;
        if (res == 1) {
            system("cls");
            Guest_account_info(username, pass);
        }
        else if (res == 2) {
            system("cls");

            Update_guest_details(username, pass);
        }
        else if (res == 3) {
            system("cls");
            guest_main_menu(username, pass);

        }
        else {
            cout << "\n\tError : wrong input ... " << endl;
        }


        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Guest Menu \t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            guest_main_menu(username, pass);
        }
    } while (res1 == 1);
}

void Update_guest_details(const string& username, const string& pass) {
    connectToDatabase();

    int res, res1;
    string newValue;

    do {
        system("cls");

        cout << R"(
    _                      _     _   _          _      _       
   /_\  __ __ ___ _  _ _ _| |_  | | | |_ __  __| |__ _| |_ ___ 
  / _ \/ _/ _/ _ \ || | ' \  _| | |_| | '_ \/ _` / _` |  _/ -_)
 /_/ \_\__\__\___/\_,_|_||_\__|  \___/| .__/\__,_\__,_|\__\___|
                                      |_|                      

)";

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@ " << " 1. Username " << "\t                 @" << endl;
        cout << "\t@ " << " 2. Password " << "                  @" << endl;
        cout << "\t@ " << " 3. Phone number" << "\t         @" << endl;
        cout << "\t@ " << " 4. Name" << "\t\t         @" << endl;
        cout << "\t@ " << " 5. Address" << "\t\t         @" << endl;
        cout << "\t@ " << " 6. Go back to Guest Manage" << "    @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> res;

        switch (res) {
        case 1:
            cout << "\n\tEnter the new username: ";
            cin >> newValue;
            if (!isValidUsername(newValue)) {
                cout << "\n\tError: Username cannot start with '&' or '$'. Please try again." << endl;
            }
            else {
                executeInstructionWithValidation("UPDATE guest SET Guest_username='" + newValue + "' WHERE Guest_username='" + username + "'", "Update");
            }
            break;
        case 2:
            cout << "\n\tEnter the new password: ";
            cin >> newValue;
            executeInstructionWithValidation("UPDATE guest SET Guest_password='" + newValue + "' WHERE Guest_username='" + username + "'", "Update");
            break;
        case 3:
            cout << "\n\tEnter the new phone number: ";
            cin >> newValue;
            executeInstructionWithValidation("UPDATE guest SET Guest_phone='" + newValue + "' WHERE Guest_username='" + username + "'", "Update");
            break;
        case 4:
            cout << "\n\tEnter the new name: ";
            cin >> newValue;
            executeInstructionWithValidation("UPDATE guest SET Guest_name='" + newValue + "' WHERE Guest_username='" + username + "'", "Update");
            break;
        case 5:
            cout << "\n\tEnter the new address: ";
            cin >> newValue;
            executeInstructionWithValidation("UPDATE guest SET Guest_address='" + newValue + "' WHERE Guest_username='" + username + "'", "Update");
            break;
        case 6:
            Guest_account_manage(username, pass);
            break;
        default:
            cout << "\n\tError: Invalid option selected." << endl;
            break;
        }

        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like anymore services ? @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Guest Manage \t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            MainMenu();
        }

    } while (res1 == 1);

    closeDatabaseConnection();
}

bool isValidDate(int year, int month, int day) {
    if (year < 2024) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if (month == 2) { // February
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeap)) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) { // April, June, September, November
        if (day > 30) return false;
    }

    return true;
}

void bookRoom(const string& username, const string& pass) {

    const int numRoomTypes = 7;
    string roomTypes[numRoomTypes] = { "Single Room", "Double Room", "Suite", "Deluxe Room", "Family Room", "Executive Suite", "Presidental Suite" };
    int roomPrices[numRoomTypes] = { 100, 150, 250, 200, 180, 300, 500 };
    int roomChoice;
    int res1;
    int numberOfNights;
    string checkInDate, checkOutDate;
    string paymentMethod;
    int paymentMethodChoice;
    do {
        {connectToDatabase();
        int y = time(0);
        srand(y);
        int random1 = 10000 + (rand() % 20000);
        string id1 = to_string(random1);

        int x = time(0);
        srand(x);
        int random = 10000 + (rand() % 20000);
        string id = to_string(random);
        srand(time(0));
        string roomNumber = generateUniqueRoomNumber();
        system("cls");
        cout << R"(

  ___           _   _           
 | _ ) ___  ___| |_(_)_ _  __ _ 
 | _ \/ _ \/ _ \ / / | ' \/ _` |
 |___/\___/\___/_\_\_|_||_\__, |
                          |___/ 
)" << endl << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << "\t@\t\t\t\t           @" << endl;
        cout << "\t@\t      Available Room Types         @" << endl << "\t@\t\t\t\t           @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << "\t@\t\t\t\t           @" << endl;

        cout << "\t@\t" << "1. " << roomTypes[0] << " - $" << roomPrices[0] << " per night " << "   @" << endl;
        cout << "\t@\t" << "2. " << roomTypes[1] << " - $" << roomPrices[1] << " per night " << "   @" << endl;
        cout << "\t@\t" << "3. " << roomTypes[2] << " - $" << roomPrices[2] << " per night " << "         @" << endl;
        cout << "\t@\t" << "4. " << roomTypes[3] << " - $" << roomPrices[3] << " per night " << "   @" << endl;
        cout << "\t@\t" << "5. " << roomTypes[4] << " - $" << roomPrices[4] << " per night " << "   @" << endl;
        cout << "\t@\t" << "6. " << roomTypes[5] << "- $" << roomPrices[5] << " per night " << "@" << endl;
        cout << "\t@\t" << "7. " << roomTypes[6] << "-$" << roomPrices[6] << "per night " << "@" << endl;
        cout << "\t@\t\t\t\t           @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

        cout << "\n\tPromotion : Book more than 4 days and get upto 20% off \n";

        cout << endl << "Enter the number of the room type you want to book (or 0 to go back): ";
        while (!( cin >> roomChoice) || roomChoice <= 0 || roomChoice > numRoomTypes) {
            if (roomChoice == 0) {
                cout << "Going back to previous menu.\n";
                guest_main_menu(username, pass);
            }
            cout << "\n\tError: Invalid choice. Please enter a number between 0 and " << numRoomTypes << ".\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        if (roomChoice == 0) {
            cout << "Going back to previous menu.\n";
            guest_main_menu(username, pass);
        }

        if (roomChoice < 1 || roomChoice > numRoomTypes) {
            cout << "\n\tError : Invalid choice. Please try again.\n";
            break;
        }

        cout << "Enter the number of nights you want to stay: ";
        while (!(cin >> numberOfNights) || numberOfNights < 0) {
            cout << "\n\tError: Invalid input. Please enter a positive number for the number of nights.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }
        bool validDate = false;
        while (!validDate) {
            cout << "Enter check-in date (YYYY-MM-DD): ";
            cin >> checkInDate;
            cout << endl;

            int year, month, day;
            if (sscanf_s(checkInDate.c_str(), "%d-%d-%d", &year, &month, &day) == 3 && isValidDate(year, month, day)) {
                if (doesValueExist("Checkin_date", checkInDate, "booking") && doesValueExist("Room_number", roomNumber, "room")) {
                    cout << "Sorry, the selected Room date is already booked. Please choose another date.\n";
                }
                else {
                    validDate = true;
                }
            }
            else {
                cout << "Invalid date. Please enter a valid check-in date.\n";
            }
        }

        // Calculate check-out date
        checkOutDate = calculateCheckOutDate(checkInDate, numberOfNights);

        double totalCost = roomPrices[roomChoice - 1] * numberOfNights;

        cout << "You have selected: " << roomTypes[roomChoice - 1] << " costing $" << roomPrices[roomChoice - 1] << " per night for " << numberOfNights << " nights.\n" << endl;
        cout << "\tCheck-in date: " << checkInDate << "\t";
        cout << "Check-out date: " << checkOutDate << "\n" << endl;
        cout << "Total cost: $" << totalCost << endl << endl;
        string totalCostStr = to_string(totalCost);

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << "\t@\t\t\t\t           @" << endl;
        cout << "\t@\t      Select a payment method      @" << endl << "\t@\t\t\t\t           @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << "\t@\t\t\t\t           @" << endl;

        cout << "\t@\t" << "1. Credit Card" << "\t\t\t   @" << endl;
        cout << "\t@\t" << "2. Debit Card" << "\t\t\t   @" << endl;
        cout << "\t@\t" << "3. PayPal" << "\t\t\t   @" << endl;
        cout << "\t@\t" << "4. Cash" << "\t\t\t\t   @" << endl;
        cout << "\t@\t\t\t\t           @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl << endl;


        bool validPaymentMethod = false;

        while (!validPaymentMethod) {
            cout << "\tEnter the number of your payment method choice: ";
            cin >> paymentMethodChoice;
            cout << endl;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (paymentMethodChoice) {
            case 1:
                paymentMethod = "Credit Card";
                validPaymentMethod = true;
                break;
            case 2:
                paymentMethod = "Debit Card";
                validPaymentMethod = true;
                break;
            case 3:
                paymentMethod = "PayPal";
                validPaymentMethod = true;
                break;
            case 4:
                paymentMethod = "Cash";
                validPaymentMethod = true;
                break;
            default:
                cout << "Invalid payment method choice. Please try again.\n";
                break;
            }
        }


        cout << "You have selected: " << paymentMethod << " as your payment method.\n";
        cout << "Do you want to confirm the booking? (yes/no): ";
        string confirm;
        cin >> confirm;

        if (confirm == "yes" || confirm == "y" || confirm == "Y") {
            cout << "Booking confirmed for " << roomTypes[roomChoice - 1] << " using " << paymentMethod << " as payment method.\n";
            string chosenRoomType = roomTypes[roomChoice - 1];
            executeInstruction("INSERT INTO room (Room_ID, Room_type, Room_number) VALUES ('" + id1 + "','" + chosenRoomType + "','" + roomNumber + "')");
            executeInstruction("INSERT INTO booking (Booking_ID, Guest_username, Checkin_date, Checkout_date,Room_ID, Total_cost) VALUES ('" + id + "','" + username + "','" + checkInDate + "','" + checkOutDate + "','" + id1 + "', '" + totalCostStr + "')");
            payment(paymentMethod, id);


        }
        else {
            cout << "Booking cancelled. Do you want to try again? (yes/no): ";
            string retry;
            cin >> retry;
            if (retry != "yes" && retry != "y" && retry != "Y") {
                guest_main_menu(username,pass);
            }
        }
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Guest Menu \t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            guest_main_menu(username, pass);
        }

    } while (res1 == 1);
    closeDatabaseConnection();
}

string generateUniqueRoomNumber() {
    string roomNumber;
    bool isUnique = false;

    do {
        srand(time(0));
        int randomRoomNumber = 100 + (rand() % 900);
        roomNumber = to_string(randomRoomNumber);

        string query = "SELECT Room_number FROM Room WHERE Room_number = '" + roomNumber + "'";
        try {
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* res = stmt->executeQuery(query);
            if (!res->next()) {
                isUnique = true;
            }
            delete res;
            delete stmt;
        }
        catch (sql::SQLException& e) {
            cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )" << endl;
            // Handle the exception, such as retrying the operation or logging the error
        }
    } while (!isUnique);

    return roomNumber;
}

string calculateCheckOutDate(const string& checkInDate, int numberOfNights) {
    // Extract the year, month, and day from the check-in date
    int year, month, day;
    sscanf_s(checkInDate.c_str(), "%d-%d-%d", &year, &month, &day);

    // Create a tm structure with the extracted date
    struct tm checkInTm = {};
    checkInTm.tm_year = year - 1900;  // tm_year is years since 1900
    checkInTm.tm_mon = month - 1;     // tm_mon is 0-based
    checkInTm.tm_mday = day;

    // Add the number of nights to the tm structure
    checkInTm.tm_mday += numberOfNights;

    // Normalize the tm structure
    mktime(&checkInTm);

    // Format the new date as a string
    char buffer[11];
    strftime(buffer, 11, "%Y-%m-%d", &checkInTm);
    return string(buffer);
}

void payment(const string& paymentMethod, const string& id) {
    connectToDatabase();

    int x = time(0);
    srand(x);
    int random = 10000 + (rand() % 20000);
    string id2 = to_string(random);

    executeInstruction("INSERT INTO `payment`(`Payment_ID`, `Payment_method`, `Booking_ID`) VALUES ('" + id2 + "','" + paymentMethod + "','" + id + "')");

    closeDatabaseConnection();
}

void viewReservations(const string& username, const string& pass) {
    connectToDatabase();
    int res1;
    try {
        sql::Statement* stmt = globalCon->createStatement();
        string query = "SELECT Checkin_date, Checkout_date FROM booking WHERE Guest_username = '" + username + "'";
        sql::ResultSet* res = stmt->executeQuery(query);

        if (!res->rowsCount()) {
            cout << "\t  Error : No reservations found " << endl;
        }
        else {
            cout << "\t\t     Reservations" << endl;
            cout << "\t---------------------------------------" << endl;
            cout << "\tCheck-in Date       Check-out Date" << endl;
            cout << "\t---------------------------------------" << endl;

            int maxCheckinLength = 0;
            int maxCheckoutLength = 0;

            while (res->next()) {
                string checkinDate = res->getString("Checkin_date");
                string checkoutDate = res->getString("Checkout_date");
                maxCheckinLength = max(maxCheckinLength, static_cast<int>(checkinDate.length()));
                maxCheckoutLength = max(maxCheckoutLength, static_cast<int>(checkoutDate.length()));
            }

            res->beforeFirst(); // Reset cursor to the beginning

            while (res->next()) {
                string checkinDate = res->getString("Checkin_date");
                string checkoutDate = res->getString("Checkout_date");

                cout << "\t " << checkinDate;
                for (int i = 0; i < maxCheckinLength - checkinDate.length() + 5; ++i) {
                    cout << " ";
                }
                cout << "     " << checkoutDate << endl;
            }
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }


    closeDatabaseConnection();
}

void cancelReservationForStaff(const std::string& username, const std::string& pass) {
    connectToDatabase();
    int res1;
    do {
        try {
            sql::Statement* stmt = globalCon->createStatement();
            std::string query = "SELECT Booking_ID, Guest_username, Checkin_date, Checkout_date FROM booking";
            sql::ResultSet* res = stmt->executeQuery(query);

            if (!res->rowsCount()) {
                std::cout << "No reservations found." << std::endl;
            }
            else {
                system("cls");
                std::cout << "\n\t\tSelect the reservation to cancel" << std::endl;
                std::cout << "\t---------------------------------------------------------------------" << std::endl;
                std::cout << "\tReservation ID   Guest Username   Check-in Date   Check-out Date" << std::endl;
                std::cout << "\t---------------------------------------------------------------------" << std::endl;

                while (res->next()) {
                    std::string bookingID = res->getString("Booking_ID");
                    std::string guestUsername = res->getString("Guest_username");
                    std::string checkinDate = res->getString("Checkin_date");
                    std::string checkoutDate = res->getString("Checkout_date");

                    std::cout << "\t " << std::setw(15) << std::left << bookingID;
                    std::cout << std::setw(18) << std::left << guestUsername;
                    std::cout << std::setw(15) << std::left << checkinDate;
                    std::cout << std::setw(15) << std::left << checkoutDate << std::endl;
                }

                std::cout << "\t---------------------------------------------------------------------" << std::endl;
                std::cout << "\tEnter the Reservation ID to cancel or press (0) to go back : ";
                std::string bookingID;
                std::cin >> bookingID;
                if (bookingID == "0") {
                    staff_main_menu(username, pass);
                    return;
                }

                if (doesValueExist("Booking_ID", bookingID, "booking")) {
                    std::string cancelQuery = "DELETE FROM booking WHERE Booking_ID = '" + bookingID + "'";
                    executeInstruction(cancelQuery);
                    std::cout << "\n\tReservation canceled successfully." << std::endl;
                }
                else {
                    std::cout << "\n\tError: Reservation ID does not exist." << std::endl;
                }
            }

            delete res;
            delete stmt;
        }
        catch (sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        std::cout << "\n        @  Would you like any services ?     @";
        std::cout << "\n\n\t@ 1.Yes \t\t\t     @";
        std::cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        std::cout << "\n\n\t@ 3.Go back to Staff Menu \t   @";
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        while (true) {
            std::cout << "\n\tEnter your Choice > ";
            std::cin >> res1;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            staff_main_menu(username, pass);
        }
    } while (res1 == 1);

    closeDatabaseConnection();
}

void Update_check_in(const string& username, const string& pass) {
    connectToDatabase();
    int res1;
    int numberOfNights;
    do {
        try {
            sql::Statement* stmt = globalCon->createStatement();
            string query = "SELECT Booking_ID, Checkin_date, Checkout_date FROM booking WHERE Guest_username = '" + username + "'";
            sql::ResultSet* res = stmt->executeQuery(query);

            if (!res->rowsCount()) {
                cout << "No reservations found." << endl;
            }
            else {
                system("cls");
                cout << "\n\t\tSelect the reservation to update" << endl;
                cout << "\t-------------------------------------------------------" << endl;
                cout << "\tReservation ID       Check-in Date       Check-out Date" << endl;
                cout << "\t-------------------------------------------------------" << endl;

                while (res->next()) {
                    string bookingID = res->getString("Booking_ID");
                    string checkinDate = res->getString("Checkin_date");
                    string checkoutDate = res->getString("Checkout_date");

                    cout << "\t " << bookingID;
                    cout << "                 " << checkinDate << "          " << checkoutDate << endl << endl;
                }

                cout << "\tEnter the Reservation ID to update : ";
                string bookingID;
                cin >> bookingID;

                if (doesValueExist("Booking_ID", bookingID, "booking")) {
                    cout << "\nEnter the new Check-in Date (YYYY-MM-DD): ";
                    string newCheckinDate;
                    cin >> newCheckinDate;

                    cout << endl << "Enter the number of nights you want to stay: ";
                    cin >> numberOfNights;

                    string checkout = calculateCheckOutDate(newCheckinDate, numberOfNights);

                    if (doesValueExist("Checkin_date", newCheckinDate, "booking")) {
                        cout << "\nError: Check-in date already exists for another reservation. Please choose another date." << endl;
                    }
                    else {
                        string updateQuery = "UPDATE booking SET Checkin_date = '" + newCheckinDate + "' WHERE Booking_ID = '" + bookingID + "'";
                        executeInstruction("UPDATE booking SET Checkout_date = '" + checkout + "' WHERE Booking_ID = '" + bookingID + "'");
                        executeInstruction(updateQuery);
                        cout << "\n\tReservation updated successfully." << endl;
                    }
                }
                else {
                    cout << "\n\tError: Reservation ID does not exist." << endl;
                }
            }

            delete res;
            delete stmt;
        }
        catch (sql::SQLException& e) {
            cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode() << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        cin >> res1;
        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
        }
        else {
            cout << "\n\tError: Wrong input. Please try again.\n" << endl;
        }
    } while (res1 == 1);

    closeDatabaseConnection();
}

string calculateCheckOutDate1(const string& checkInDate) {
    // Extract the year, month, and day from the check-in date
    int year, month, day;
    sscanf_s(checkInDate.c_str(), "%d-%d-%d", &year, &month, &day);

    // Create a tm structure with the extracted date
    struct tm checkInTm = {};
    checkInTm.tm_year = year - 1900;  // tm_year is years since 1900
    checkInTm.tm_mon = month - 1;     // tm_mon is 0-based
    checkInTm.tm_mday = day;


    // Normalize the tm structure
    mktime(&checkInTm);

    // Format the new date as a string
    char buffer[11];
    strftime(buffer, 11, "%Y-%m-%d", &checkInTm);
    return string(buffer);
}

void Room_info(const string& username, const string& pass) {
    int res, res1;
    do {
        system("cls");
        cout << "\n     !!! Here you can have a breif description about the rooms in the hotel and if it is suits your needs !!!\n\n";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1.Single Room " << "\t         @" << endl;
        cout << "\t@\t" << " 2.Double Room" << " \t         @" << endl;
        cout << "\t@\t" << " 3.Suite" << "\t         @" << endl;
        cout << "\t@\t" << " 4.Deluxe Room" << "\t         @" << endl;
        cout << "\t@\t" << " 5.Family Room" << "\t         @" << endl;
        cout << "\t@\t" << " 6.Presidental Suite" << "\t @" << endl;
        cout << "\t@\t" << " 7.Executive Suite" << "\t @" << endl;
        cout << "\t@\t" << " 8.Go back to Guest Menu" << " @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\n\tEnter your Choice > ";
        cin >> res;
        if (res == 1) {
            cout << "\n\tSingle Room : A cozy room designed for one person, featuring a single bed and essential amenities.\n";
        }
        else if (res == 2) {
            cout << "\n\tDouble Room: A comfortable room for two, equipped with a double bed or two single beds, perfect for couples or friends.\n";
        }
        else if (res == 3) {
            cout << "\n\tSuite: A spacious room with separate living and sleeping areas, offering extra comfort and luxury.\n";
        }
        else if (res == 4) {
            cout << "\n\tDeluxe Room: An upgraded room with more space and enhanced amenities, providing a more luxurious stay.\n";
        }
        else if (res == 5) {
            cout << "\n\tFamily Room: A larger room designed to accommodate families, featuring multiple beds and additional space for a comfortable family stay.";
        }
        else if (res == 6) {
            cout << "\n\tPresidential Suite: The most luxurious accommodation, featuring expansive space, top-notch amenities, and exclusive services for a lavish stay.\n";
        }
        else if (res == 7) {
            cout << "\n\tExecutive Suite: A high-end suite with premium furnishings, offering a separate living area and exclusive amenities for business travelers.\n";
        }
        else if (res == 8) {
            system("cls");
            guest_main_menu(username, pass);
        }
        else {
            cout << "\n\tError : Wrong input ... ";
        }


        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any service ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            guest_main_menu(username, pass);
        }


    } while (res1 == 1);
}

void AdminReportModule() {
    system("cls");
    int choice, res;
    do {
        system("cls");
        cout << R"(
    _   _  _   _   _ __   _____ ___ ___ 
   /_\ | \| | /_\ | |\ \ / / __|_ _/ __|
  / _ \| .` |/ _ \| |_\ V /\__ \| |\__ \
 /_/ \_\_|\_/_/ \_\____|_| |___/___|___/
                                        
)" << endl;

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " Choose your option" << "\t @" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@\t" << " 1. View Sales Report " << "\t @" << endl;
        cout << "\t@\t" << " 2. View Room Bookings " << "  @" << endl;
        cout << "\t@\t" << " 3. Go back to Admin Menu" << "@" << endl;
        cout << "\t@\t\t\t\t @" << endl;
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n" << endl;
        cout << "\t";
        cin >> choice;

        if (choice == 1) {
            ViewSalesReport();
            system("cls");
        }
        else if (choice == 2) {
            ViewRoomBookings();
            system("cls");
        }
        else if (choice == 3) {
            admin_main_menu();
            system("cls");
        }
        else {
            cout << "\n\tError : Wrong input ... please try again ";
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any services  ?    @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Admin Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res == 1 || res == 2 || res == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res == 2) {
            exit(0);
        }
        else if (res == 3) {
            system("cls");
            admin_main_menu();
        }
    } while (res == 1);
}

void ViewSalesReport() {
    int choice, res1;
    do {
        system("cls");
        cout << R"(
  ___   _   _    ___ ___ 
 / __| /_\ | |  | __/ __|
 \__ \/ _ \| |__| _|\__ \
 |___/_/ \_\____|___|___/
                         
)" << endl;

        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t   @\n";
        cout << "\t@\tChoose your option\t   @\n";
        cout << "\t@\t\t\t\t   @\n";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\t@\t\t\t\t   @\n";
        cout << "\t@\t1. Daily Report\t\t   @\n";
        cout << "\t@\t2. Monthly Report\t   @\n";
        cout << "\t@\t3. Quarterly Report\t   @\n";
        cout << "\t@\t4. Half-Yearly Report\t   @\n";
        cout << "\t@\t5. Yearly Report\t   @\n";
        cout << "\t@\t6. Go back to Report Menu@\n";
        cout << "\t@\t\t\t\t   @\n";
        cout << "\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
        cout << "\n\t Enter your choice > ";
        cin >> choice;

        switch (choice) {
        case 1:
            DailyReport();
            break;
        case 2:
            MonthlyReport();
            break;
        case 3:
            QuarterlyReport();
            break;
        case 4:
            HalfYearlyReport();
            break;
        case 5:
            YearlyReport();
            break;
        case 6:
            AdminReportModule();
            break;
        default:
            cout << "\tInvalid input. Please try again.\n";
            break;
        }
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        cout << "\n        @  Would you like any service ?     @";
        cout << "\n\n\t@ 1.Yes \t\t\t     @";
        cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        cout << "\n\n\t@ 3.Go back to Report Menu \t\t\t     @";
        cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
        while (true) {
            cout << "\n\tEnter your Choice > ";
            cin >> res1;

            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            AdminReportModule();
        }

    } while (res1 == 1);
}

void ViewRoomBookings() {
    int res1;
    do {
        system("cls");
        std::string startYear, startMonth, startDay, endYear, endMonth, endDay;

        while (true) {
            std::cout << "Enter start year (YYYY): ";
            std::cin >> startYear;
            if (isValidYear1(startYear)) break;
            std::cout << "Invalid year. Please enter a year from 2024 onwards." << std::endl;
        }

        while (true) {
            std::cout << "Enter start month (MM): ";
            std::cin >> startMonth;
            if (isValidMonth1(startMonth)) break;
            std::cout << "Invalid month. Please enter a month between 01 and 12." << std::endl;
        }

        while (true) {
            std::cout << "Enter start day (DD): ";
            std::cin >> startDay;
            if (isValidDay1(startDay)) break;
            std::cout << "Invalid day. Please enter a day between 01 and 31." << std::endl;
        }

        while (true) {
            std::cout << "Enter end year (YYYY): ";
            std::cin >> endYear;
            if (isValidYear1(endYear) && std::stoi(endYear) >= std::stoi(startYear)) break;
            std::cout << "Invalid year. End year should be the same or after the start year." << std::endl;
        }

        while (true) {
            std::cout << "Enter end month (MM): ";
            std::cin >> endMonth;
            if (isValidMonth1(endMonth)) break;
            std::cout << "Invalid month. Please enter a month between 01 and 12." << std::endl;
        }

        while (true) {
            std::cout << "Enter end day (DD): ";
            std::cin >> endDay;
            if (isValidDay1(endDay)) break;
            std::cout << "Invalid day. Please enter a day between 01 and 31." << std::endl;
        }

        std::string startDate = formatDateString(startYear, startMonth, startDay);
        std::string endDate = formatDateString(endYear, endMonth, endDay);

        try {
            connectToDatabase();

            // Query room type bookings
            std::string roomTypeQuery = "SELECT r.Room_type, COUNT(*) AS Bookings FROM booking b JOIN room r ON b.Room_ID = r.Room_ID WHERE b.Checkin_date >= '" + startDate + "' AND b.Checkout_date <= '" + endDate + "' GROUP BY r.Room_type";

            // Query total room bookings
            std::string totalBookingsQuery = "SELECT COUNT(*) AS TotalBookings FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";

            sql::Statement* stmt = globalCon->createStatement();

            // Execute total bookings query
            sql::ResultSet* totalBookingsResultSet = stmt->executeQuery(totalBookingsQuery);
            int totalBookings = 0;
            if (totalBookingsResultSet->next()) {
                totalBookings = totalBookingsResultSet->getInt("TotalBookings");
                std::cout << "Total Rooms Booked from " << startDate << " to " << endDate << ": " << totalBookings << std::endl;
            }
            else {
                std::cout << "No booking data found for the given period." << std::endl;
            }
            delete totalBookingsResultSet;

            // Execute room type query
            sql::ResultSet* roomTypeResultSet = stmt->executeQuery(roomTypeQuery);
            std::cout << "\nRoom Type Occupancy Rates (Out of 200 rooms):" << std::endl;

            // Variables for bar chart
            const int totalRooms = 200;

            // Find the maximum bookings to scale the graph
            int maxBookings = 0;
            while (roomTypeResultSet->next()) {
                int bookings = roomTypeResultSet->getInt("Bookings");
                if (bookings > maxBookings) {
                    maxBookings = bookings;
                }
            }

            // Reset result set
            roomTypeResultSet->beforeFirst();

            // Display occupancy rates using a bar chart
            while (roomTypeResultSet->next()) {
                std::string roomType = roomTypeResultSet->getString("Room_type");
                int bookings = roomTypeResultSet->getInt("Bookings");

                // Calculate percentage occupancy
                double occupancyRate = (static_cast<double>(bookings) / totalRooms) * 100;

                // Calculate the length of the bar for the chart
                int barLength = static_cast<int>((bookings / static_cast<double>(maxBookings)) * 50);

                // Print room type, number of rooms booked, and bar chart
                std::cout << std::setw(15) << std::left << roomType << " | " << std::setw(3) << bookings << " rooms | ";
                for (int i = 0; i < barLength; ++i) {
                    std::cout << "=";
                }
                std::cout << " " << std::fixed << std::setprecision(2) << occupancyRate << "%" << std::endl;
            }
            delete roomTypeResultSet;
            delete stmt;

            closeDatabaseConnection();
        }
        catch (sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Invalid input: " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        std::cout << "\n        @  Would you like any service ?      @";
        std::cout << "\n\n\t@ 1.Yes \t\t\t     @";
        std::cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        std::cout << "\n\n\t@ 3.Go back to Report Menu \t     @";
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        while (true) {
            std::cout << "\n\tEnter your Choice > ";
            std::cin >> res1;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            AdminReportModule();
        }
    } while (res1 == 1);
}

bool isValidYear(int year) {
    return year >= 2024;
}

bool isValidMonth(int month) {
    return month >= 1 && month <= 12;
}

bool isValidDay(int year, int month, int day) {
    // Days in each month (index 0 is ignored for convenience)
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Check for leap year
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        daysInMonth[2] = 29;
    }

    return day >= 1 && day <= daysInMonth[month];
}

bool isValidDate1(int year, int month, int day) {
    return isValidYear(year) && isValidMonth(month) && isValidDay(year, month, day);
}

string getDateInput() {
    int year, month, day;
    string date;
    do {
        cout << "\n\tEnter date (YYYY-MM-DD): ";
        cin >> date;
        if (sscanf_s(date.c_str(), "%d-%d-%d", &year, &month, &day) == 3 && isValidDate1(year, month, day)) {
            break;
        }
        else {
            cout << "Invalid date. Please try again." << endl;
        }
    } while (true);

    return date;
}

void getMonthInput(int& year, int& month) {
    do {
        cout << "Enter year (YYYY): ";
        cin >> year;
        if (!isValidYear(year)) {
            cout << "Invalid year. Please enter a year from 2024 onwards." << endl;
            continue;
        }
        cout << "Enter month (MM): ";
        cin >> month;
        if (!isValidMonth(month)) {
            cout << "Invalid month. Please enter a valid month (1-12)." << endl;
            continue;
        }
        break;
    } while (true);
}

void YearlyReport() {
    system("cls");
    int year;
    cout << "Enter year (YYYY): ";
    cin >> year;

    if (!isValidYear(year)) {
        cout << "Invalid year. Please enter a year from 2024 onwards." << endl;
        return;
    }

    string startDate = to_string(year) + "-01-01";
    string endDate = to_string(year) + "-12-31";

    string query = "SELECT * FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayAllData(query);

    string query1 = "SELECT SUM(Total_cost) AS TotalSales, COUNT(*) AS TotalBookings FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayResultWithAverage(query1, "\n\tTotalSales for " + to_string(year), "\n\tAverage Sales for " + to_string(year));
}

void RunQueryAndDisplayResult(const string& query1, const string& message) {
    try {
        connectToDatabase();
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* resultSet = stmt->executeQuery(query1);
        if (resultSet->next()) {
            cout << message << ": $" << resultSet->getDouble("TotalSales") << endl;
        }
        else {
            cout << "No sales data found for the given period." << endl;
        }
        delete resultSet;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void HalfYearlyReport() {
    system("cls");
    int year, half;
    cout << "Enter year (YYYY): ";
    cin >> year;
    cout << "Enter half (1 or 2): ";
    cin >> half;

    string startDate, endDate;
    if (half == 1) {
        startDate = to_string(year) + "-01-01";
        endDate = to_string(year) + "-06-30";
    }
    else if (half == 2) {
        startDate = to_string(year) + "-07-01";
        endDate = to_string(year) + "-12-31";
    }
    else {
        cout << "Invalid half. Please enter 1 or 2." << endl;
        return;
    }

    string query = "SELECT * FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayAllData(query);

    string query1 = "SELECT SUM(Total_cost) AS TotalSales, COUNT(*) AS TotalBookings FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayResultWithAverage(query1, "\n\tTotalSales for H" + to_string(half) + " " + to_string(year), "\n\tAverage Sales for H" + to_string(half) + " " + to_string(year));
}


void DailyReport() {
    system("cls");
    string date = getDateInput();
    string query = "SELECT * FROM booking WHERE Checkin_date <= '" + date + "' AND Checkout_date >= '" + date + "'";
    RunQueryAndDisplayAllData(query);
    string query1 = "SELECT SUM(Total_cost) AS TotalSales FROM booking WHERE Checkin_date <= '" + date + "' AND Checkout_date >= '" + date + "'";
    RunQueryAndDisplayResult(query1, "\n\tTotalSales for " + date);
}

void MonthlyReport() {
    system("cls");
    int year, month;
    getMonthInput(year, month);
    string startDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-01";
    string endDate = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month) + "-31";

    string query = "SELECT * FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayAllData(query);

    string query1 = "SELECT SUM(Total_cost) AS TotalSales, COUNT(*) AS TotalBookings FROM booking WHERE YEAR(Checkin_date) = " + to_string(year) + " AND MONTH(Checkin_date) = " + to_string(month);
    RunQueryAndDisplayResultWithAverage(query1, "\n\tTotalSales for " + to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month), "\n\tAverage Sales for " + to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month));
}

void RunQueryAndDisplayResultWithAverage(const string& query, const string& totalMessage, const string& avgMessage) {
    try {
        connectToDatabase();
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* resultSet = stmt->executeQuery(query);
        if (resultSet->next()) {
            double totalSales = resultSet->getDouble("TotalSales");
            int totalBookings = resultSet->getInt("TotalBookings");
            double avgSales = (totalBookings != 0) ? (totalSales / totalBookings) : 0.0;
            cout << totalMessage << ": $" << fixed << setprecision(2) << totalSales << endl;
            cout << avgMessage << ": $" << fixed << setprecision(2) << avgSales << endl;
        }
        else {
            cout << "No sales data found for the given period." << endl;
        }
        delete resultSet;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

double RunSalesQuery(const string& query) {
    double totalSales = 0.0;
    try {
        connectToDatabase();
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* resultSet = stmt->executeQuery(query);
        if (resultSet->next()) {
            totalSales = resultSet->getDouble("TotalSales");
        }
        delete resultSet;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
    return totalSales;
}

void RunQueryAndDisplayAllData(const string& query) {
    try {
        connectToDatabase();
        sql::Statement* stmt = globalCon->createStatement();
        sql::ResultSet* resultSet = stmt->executeQuery(query);

        // Display all data
        cout << "\n\tAll data for the specified month:\n";
        cout << "\n\t-------------------------------------------------------------------------------------------------------\n";
        while (resultSet->next()) {
            // Display each row of data
            // Modify this part according to your needs
            cout << "\tBooking ID: " << resultSet->getInt("Booking_ID") << ", ";
            cout << "\tCheckin_date: " << resultSet->getString("Checkin_date") << ", ";
            cout << "\tCheckout_date: " << resultSet->getString("Checkout_date") << ", ";
            cout << "\tTotal_cost: " << resultSet->getDouble("Total_cost") << endl;
        }
        cout << "\n\t-------------------------------------------------------------------------------------------------------\n";

        delete resultSet;
        delete stmt;
        closeDatabaseConnection();
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void QuarterlyReport() {
    system("cls");
    int year, quarter;
    cout << "Enter year (YYYY): ";
    cin >> year;
    cout << "Enter quarter (1-4): ";
    cin >> quarter;

    string startDate, endDate;
    switch (quarter) {
    case 1:
        startDate = to_string(year) + "-01-01";
        endDate = to_string(year) + "-03-31";
        break;
    case 2:
        startDate = to_string(year) + "-04-01";
        endDate = to_string(year) + "-06-30";
        break;
    case 3:
        startDate = to_string(year) + "-07-01";
        endDate = to_string(year) + "-09-30";
        break;
    case 4:
        startDate = to_string(year) + "-10-01";
        endDate = to_string(year) + "-12-31";
        break;
    default:
        cout << "Invalid quarter. Please enter a number between 1 and 4." << endl;
        return;
    }

    string query = "SELECT * FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayAllData(query);

    string query1 = "SELECT SUM(Total_cost) AS TotalSales, COUNT(*) AS TotalBookings FROM booking WHERE Checkin_date >= '" + startDate + "' AND Checkout_date <= '" + endDate + "'";
    RunQueryAndDisplayResultWithAverage(query1, "\n\tTotalSales for Q" + to_string(quarter) + " " + to_string(year), "\n\tAverage Sales for Q" + to_string(quarter) + " " + to_string(year));
}

void generateReceipt(const std::string& username, const std::string& pass) {
    connectToDatabase();
    int res1;
    system("cls");
    do {
        try {
            // Fetch all bookings
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* res = stmt->executeQuery("SELECT Booking_ID, Guest_username, Checkin_date FROM booking");

            std::cout << "\n\t\tAvailable Bookings:" << std::endl << std::endl;
            std::cout << "\t-------------------------------------------------" << std::endl;
            std::cout << "\tID            Name                   Date" << std::endl;
            std::cout << "\t-------------------------------------------------" << std::endl;

            while (res->next()) {
                std::string booking_id = res->getString("Booking_ID");
                std::string customer_name = res->getString("Guest_username");
                std::string booking_date = res->getString("Checkin_date");

                std::cout << "\t" << std::setw(14) << std::left << booking_id
                    << std::setw(22) << std::left << customer_name
                    << booking_date << std::endl;
            }
            delete res;
            delete stmt;

            // Ask staff to choose a booking ID
            std::string chosen_booking_id;
            std::cout << "\n\tEnter the booking ID to generate receipt or press (0) to go back : ";
            std::cin >> chosen_booking_id;
            if (chosen_booking_id == "0") {
                staff_main_menu(username, pass);
                return;
            }

            sql::PreparedStatement* pstmt = globalCon->prepareStatement(
                "SELECT b.Guest_username, b.Checkin_date, b.Total_cost, r.Room_type, p.Payment_method "
                "FROM booking b "
                "JOIN room r ON b.Room_id = r.Room_id "
                "JOIN payment p ON b.Booking_ID = p.Booking_ID "
                "WHERE b.Booking_ID = ?;");
            pstmt->setString(1, chosen_booking_id);
            res = pstmt->executeQuery();

            if (res->next()) {
                std::string customer_name = res->getString("Guest_username");
                std::string booking_date = res->getString("Checkin_date");
                std::string room_type = res->getString("Room_type");
                std::string amount = res->getString("Total_cost");
                std::string payment_method = res->getString("Payment_method");

                std::cout << "\nReceipt:" << std::endl;
                std::cout << "\tCustomer Name: " << customer_name << std::endl;
                std::cout << "\tBooking Date: " << booking_date << std::endl;
                std::cout << "\tRoom Type: " << room_type << std::endl;
                std::cout << "\tAmount: $" << amount << std::endl;
                std::cout << "\tPayment Method: " << payment_method << std::endl << std::endl;

                // Write receipt to a file
                std::ofstream receipt_file("receipt_" + chosen_booking_id + ".txt");
                if (receipt_file.is_open()) {
                    receipt_file << "\tReceipt:" << std::endl;
                    receipt_file << "\tCustomer Name: " << customer_name << std::endl;
                    receipt_file << "\tBooking Date: " << booking_date << std::endl;
                    receipt_file << "\tRoom Type: " << room_type << std::endl;
                    receipt_file << "\tAmount: $" << amount << std::endl;
                    receipt_file << "\tPayment Method: " << payment_method << std::endl;
                    receipt_file.close();
                    std::cout << "\n\tReceipt saved to receipt_" << chosen_booking_id << ".txt" << std::endl;
                }
                else {
                    std::cerr << "Unable to open file for writing." << std::endl;
                }
            }
            else {
                std::cerr << "\n\tError : No booking found with the given ID." << std::endl;
            }

            delete res;
            delete pstmt;
        }
        catch (sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        std::cout << "\n        @  Would you like any service ?      @";
        std::cout << "\n\n\t@ 1.Yes \t\t\t     @";
        std::cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        std::cout << "\n\n\t@ 3.Go back to Staff Menu \t     @";
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        while (true) {
            std::cout << "\n\tEnter your Choice > ";
            std::cin >> res1;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            staff_main_menu(username, pass);
        }
    } while (res1 == 1);
    closeDatabaseConnection();
}

void applyVoucher(const std::string& username, const std::string& pass) {
    connectToDatabase();
    int res1;
    do {
        system("cls");
        try {
            // Fetch all bookings with more than 3 booking days
            sql::Statement* stmt = globalCon->createStatement();
            sql::ResultSet* res = stmt->executeQuery(
                "SELECT Booking_ID, Guest_username, Checkin_date, Checkout_date, DATEDIFF(Checkout_date, Checkin_date) as days, Total_cost "
                "FROM booking "
                "HAVING days > 3");

            std::cout << "\n\t\tEligible Bookings for Voucher Application:" << std::endl << std::endl;
            std::cout << "\t----------------------------------------------------------------------------------------" << std::endl;
            std::cout << "\tID            Name                 Check-in Date   Check-out Date Days  Total Cost" << std::endl;
            std::cout << "\t----------------------------------------------------------------------------------------" << std::endl;

            while (res->next()) {
                std::string booking_id = res->getString("Booking_ID");
                std::string customer_name = res->getString("Guest_username");
                std::string checkin_date = res->getString("Checkin_date");
                std::string checkout_date = res->getString("Checkout_date");
                int days = res->getInt("days");
                double total_cost = res->getDouble("Total_cost");

                std::cout << "\t" << std::setw(14) << std::left << booking_id
                    << std::setw(22) << std::left << customer_name
                    << std::setw(15) << std::left << checkin_date
                    << std::setw(16) << std::left << checkout_date
                    << std::setw(7) << std::left << days
                    << "$" << total_cost << std::endl;
            }
            delete res;
            delete stmt;

            std::string chosen_booking_id;
            int booking_days = 0;
            bool valid_booking_id = false;

            while (!valid_booking_id) {
                // Ask staff to choose a booking ID and voucher
                std::cout << "\n\tEnter the booking ID to apply voucher (Enter '0' to go back): ";
                std::cin >> chosen_booking_id;

                if (chosen_booking_id == "0") {
                    staff_main_menu(username, pass);
                    return;
                }

                // Fetch the number of days for the chosen booking ID
                sql::PreparedStatement* pstmt = globalCon->prepareStatement(
                    "SELECT DATEDIFF(Checkout_date, Checkin_date) as days FROM booking WHERE Booking_ID = ?");
                pstmt->setString(1, chosen_booking_id);
                res = pstmt->executeQuery();

                if (res->next()) {
                    booking_days = res->getInt("days");
                    valid_booking_id = true;
                }
                else {
                    std::cerr << "\n\tError : Invalid booking ID. Please try again..." << std::endl;
                }

                delete res;
                delete pstmt;
            }

            if (res1 != 3 && valid_booking_id) {
                // Display available vouchers
                std::cout << "\n\tAvailable Vouchers:" << std::endl;
                std::cout << "\t1. Voucher A - 10% discount (Valid for 4 to 5 days bookings)" << std::endl;
                std::cout << "\t2. Voucher B - 15% discount (Valid for 6 to 8 days bookings)" << std::endl;
                std::cout << "\t3. Voucher C - 20% discount (Valid for bookings above 8 days)" << std::endl;

                int voucher_choice;
                std::cout << "\n\tEnter the voucher number: ";
                std::cin >> voucher_choice;

                double discount = 0.0;
                bool valid_voucher = false;

                if (voucher_choice == 1 && booking_days >= 4 && booking_days <= 5) {
                    discount = 0.10;
                    valid_voucher = true;
                }
                else if (voucher_choice == 2 && booking_days >= 6 && booking_days <= 8) {
                    discount = 0.15;
                    valid_voucher = true;
                }
                else if (voucher_choice == 3 && booking_days > 8) {
                    discount = 0.20;
                    valid_voucher = true;
                }
                else {
                    std::cerr << "\n\tError : Invalid voucher choice for the selected booking duration." << std::endl;
                }

                if (valid_voucher) {
                    // Apply the discount and update the booking total cost
                    sql::PreparedStatement* pstmt = globalCon->prepareStatement(
                        "UPDATE booking SET Total_cost = Total_cost * ? WHERE Booking_ID = ?");
                    pstmt->setDouble(1, 1.0 - discount);
                    pstmt->setString(2, chosen_booking_id);
                    int updateCount = pstmt->executeUpdate();

                    if (updateCount > 0) {
                        std::cout << "\n\tVoucher applied successfully!" << std::endl;
                    }
                    else {
                        std::cerr << "\n\tFailed to apply voucher. Please check the booking ID." << std::endl;
                    }

                    delete pstmt;
                }
            }
        }
        catch (sql::SQLException& e) {
            std::cout << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
                << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        }
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
        std::cout << "\n        @  Would you like any service ?     @";
        std::cout << "\n\n\t@ 1.Yes \t\t\t     @";
        std::cout << "\n\n\t@ 2.No (Exit Program) \t\t     @";
        std::cout << "\n\n\t@ 3.Go back to Staff Menu\t   @";
        std::cout << "\n\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        while (true) {
            std::cout << "\n\tEnter your Choice > ";
            std::cin >> res1;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
                continue; // Prompt again for valid input
            }

            if (res1 == 1 || res1 == 2 || res1 == 3) {
                break; // Exit the loop if input is valid
            }
            else {
                std::cout << "\n\tError: Wrong input, please enter a number (1, 2, or 3)." << std::endl;
            }
        }

        if (res1 == 2) {
            exit(0);
        }
        else if (res1 == 3) {
            system("cls");
            staff_main_menu(username, pass);
        }
    } while (res1 == 1);

    closeDatabaseConnection();
}

std::string getCurrentYear() {
    time_t t = time(0);   // Get current time
    struct tm now;
    localtime_s(&now, &t); // Use localtime_s for safer conversion
    int year = now.tm_year + 1900;  // tm_year is years since 1900
    return std::to_string(year);
}

std::string formatDateString(const std::string& year, const std::string& month, const std::string& day) {
    return year + "-" + (month.length() == 1 ? "0" + month : month) + "-" + (day.length() == 1 ? "0" + day : day);
}

bool isValidMonth1(const std::string& month) {
    try {
        int m = std::stoi(month);
        return m >= 1 && m <= 12;
    }
    catch (...) {
        return false;
    }
}

bool isValidDay1(const std::string& day) {
    try {
        int d = std::stoi(day);
        return d >= 1 && d <= 31;
    }
    catch (...) {
        return false;
    }
}

bool isValidYear1(const std::string& year) {
    try {
        int y = std::stoi(year);
        return y >= 2024;
    }
    catch (...) {
        return false;
    }
}

string getPasswordInput() {
    string password;
    char ch;
    cout << "\tEnter your password: ";
    while ((ch = _getch()) != '\r') { // '\r' is the Enter key
        if (ch == '\b' && !password.empty()) { // Handle backspace
            cout << "\b \b";
            password.pop_back();
        }
        else if (ch != '\b') {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void Add_staff() {
    connectToDatabase();
    int x = time(0);
    srand(x);
    int random = 10000 + (rand() % 20000);
    string id = to_string(random);
    string username, password, phone, name, address;

    cout << "\n\tEnter the new staff details below:\n";

    do {
        cout << "\n\tUsername (must start with $ or enter '0' to go back): ";
        cin >> username;
        if (username == "0") {
            system("cls");
            Staff_managment();
            return;
        }
        if (username[0] != '$') {
            cout << "\tError: The username must start with the '$' character.\n";
        }
    } while (username[0] != '$');

    password = getPasswordInput();

    cout << "\n\tPhone number: ";
    cin >> phone;

    cout << "\n\tName: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "\n\tAddress: ";
    cin >> address;

    string query = "INSERT INTO staff (Sfaff_ID, Staff_name, Staff_username, Staff_password, Staff_address, Staff_phonenumber) VALUES ('" +
        id + "', '" + name + "', '" + username + "', '" + password + "', '" + address + "','" + phone + "')";

    executeInstruction(query);

    cout << "\n\tNew staff member added successfully!\n";
    closeDatabaseConnection();
}

void Add_guest() {
    connectToDatabase();
    int x = time(0);
    srand(x);
    int random = 10000 + (rand() % 20000);
    string id = to_string(random);
    string username, password, phone, name, address;

    cout << "\n\tEnter the new Guest details below:\n";

    do {
        cout << "\n\tEnter Username or '0' to go back): ";
        cin >> username;
        if (username == "0") {
            system("cls");
            Guest_managment();
            return;
        }
        if (username[0] == '$') {
            cout << "\tError: The username must not start with the '$' character.\n";
        }
        else if (username[0] == '&') {
            cout << "\tError: The username must not start with the '&' character.\n";
        }
    } while (username[0] == '$' || username[0] == '&');

    password = getPasswordInput();

    cout << "\n\tPhone number: ";
    cin >> phone;

    cout << "\n\tName: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "\n\tAddress: ";
    cin >> address;

    string query = "INSERT INTO guest (Guest_ID, Guest_name, Guest_username, Guest_password, Guest_address, Guest_phonenumber) VALUES ('" +
        id + "', '" + name + "', '" + username + "', '" + password + "', '" + address + "','" + phone + "')";

    executeInstruction(query);

    cout << "\n\tNew Guest member added successfully!\n";
    closeDatabaseConnection();
}

bool isNumeric(const string& str) {
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidUsername(const string& username) {
    return !username.empty() && username[0] != '&' && username[0] != '$';
}

void executeInstructionWithValidation(const string& query, const string& successMessage) {
    try {
        executeInstruction(query);
        system("cls");
        cout << "\n\t" << successMessage << " completed!! \n";
    }
    catch (const sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << " (MySQL error code: " << e.getErrorCode()
            << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

bool isValidPhoneNumber(const string& phone) {
    if ((phone.length() != 10 && phone.length() != 11) || phone[0] != '0') {
        return false;
    }
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}
