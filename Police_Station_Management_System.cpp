#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <conio.h>
#include <vector>  

using namespace std;

class Person {
    friend class Officers;

private:
    int ID;
    string name;
    int phoneNo;
    string gender, citizenShip, joiningDate;
     vector<int> phoneNumbers;  // phoneNumbers is instance of vector type int, vector is dynamic arry

public:
    Person() : ID(0), name(""), phoneNo(0), gender(""), citizenShip(""), joiningDate("") {}
    Person(int id, string n, int pN, string G, string cZ, string jD)
        : ID(id), name(n), phoneNo(pN), gender(G), citizenShip(cZ), joiningDate(jD) {}

    void setDetails() {

        cout << "Enter Name: ";
        cin.ignore(); // Ignore the newline character from the previous input
        getline(cin, name);

       while (true) {
            int phoneNumberInput;
            cout << "Enter Phone Number : ";

            if (!(cin >> phoneNumberInput)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Invalid input for Phone Number. Please enter a valid phone number." << endl;
        } else {
            phoneNumbers.push_back(phoneNumberInput);       // push back enter each number to phoneNumber vector
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
        }
        }

        cout << "Enter Gender: ";
        cin >> gender;

        cout << "Enter Citizenship: ";
        cin >> citizenShip;

    }
    
    void displayPhoneNumbers() const {
    cout << "Phone Numbers: ";
    for (int number : phoneNumbers) {   // displayPhoneNumbers of paticular person by iterating through phoneNumber vector 
        cout << number << " ";
    }
    cout << endl;
}

    void displayDetails() const {
        cout << "ID: " << ID << "\nName: " << name << "\nPhone Number: " << phoneNo
                  << "\nGender: " << gender << "\nCitizenship: " << citizenShip
                  << "\nJoining Date: " << joiningDate << endl;
    }

    string getName() const {
	 return name;
	  }
    string getGender() const {
	 return gender; 
	 }
    string getCitizenShip() const {
	 return citizenShip; 
	 }
    int getPhoneNo() const {
	 return phoneNo; 
	 }
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Officers {
public:
 static int officerIDCounter; // Declare the counter as static

    static int allocateOfficerID() { // Make the allocation function static
        return ++officerIDCounter;
    }
	int ID;
	Officers():ID(0){}
Officers operator ++() {
    Officers temp;
    temp.ID = ++ID;
    return temp;
}
	void menu();
void viewOfficersRecords();
};
int Officers::officerIDCounter = 0;

void Officers::viewOfficersRecords() {
    int searchID;
    while (true) {
        try {
            cout << "Enter Officers you want to view: ";
            cin >> searchID;

            if (cin.fail()) {
                throw runtime_error("Invalid input! Please enter a valid integer ID.");
            }

            break; // Break out of the loop if the ID is valid
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        

    ifstream filein("officers.txt");
    if (filein.is_open()) {
        string line;
        bool found = false;

        while (getline(filein, line)) {
            size_t foundID = line.find("ID: " + to_string(searchID));
            if (foundID != string::npos) {
                found = true;
                for (int i = 0; i < 6; ++i) {
                    getline(filein, line);
                    cout << line << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "No Officers found with ID: " << searchID << endl;
        }

        filein.close();
    } else {
        cout << "Unable to open file for reading!" << endl;
    }
}   
void Officers::menu() {
 int choice;
	while (true) {
	system("cls");
	cout << "\t\t\t\t\t\t\t *******************************************\n";
	cout << "\t\t\t\t\t\t\t\t    Officers Information \n";
    cout << "\t\t\t\t\t\t\t *******************************************\n" << endl;
	
	cout << "\t\t\t\t\t\t\t 1. Add New Officer\n";
    cout << "\t\t\t\t\t\t\t 2. View Officers' Data\n";
    cout << "\t\t\t\t\t\t\t 3. Delete Officer Data\n";
	cout << "\t\t\t\t\t\t\t 4. Go back to the main menu\n\n";
	cout << "\t\t\t\t\t\t\t  Enter your choice: ";
	cin >> choice;
	system("cls");
	if (choice == 1) {
        cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Add Officers Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
	    Person newOfficer;// newOfficer is object of the person 
	     try{
	     	cout << "Enter Officer Name: ";
	    cin >> newOfficer.name;
	
	    while (true) {
            cout << "Enter Officer Phone Number: ";
            cin >> newOfficer.phoneNo;

            if (cin.fail()) {                                    // checks if the most recent input operation (cin) has failed
                cerr << "Invalid input for Phone Number." << endl;    // cerr is standard error stream 
                cin.clear();                                //cin.clear() is used to clear the error state of the input stream
                cin.ignore(numeric_limits<streamsize>::max(), '\n');   //discards characters from the input buffer,fetches the maximum number of characters the input buffer can hold
            } else {
                break;
            }
        }
	
	    cout << "Enter Officer Joining Date: ";
	    cin >> newOfficer.joiningDate;
	
	    cout << "Enter Officer Gender: ";
	    cin >> newOfficer.gender;
	
	    cout << "Enter Officer Citizenship: ";
	    cin >> newOfficer.citizenShip;
	
	    ofstream fileout("officers.txt", ios::app);
	        if (fileout.is_open()) {
	        fileout << "ID: " << allocateOfficerID() << "\nName: " << newOfficer.name << "\nPhone Number: " << newOfficer.phoneNo
	        << "\nJoining Date: " << newOfficer.joiningDate << "\nGender: " << newOfficer.gender<< "\nCitizenship: " << newOfficer.citizenShip << "\n\n";
	            fileout.close();
	            cout << "Officer added successfully." << endl;
	        } else {
	            cout << "Unable to open file for writing!";
	        }
	     } 
		    
  	catch (const exception &e) {
        cerr << "Error: " << e.what() << endl; // standard error stream
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
    }	
		
	} else if (choice == 2) {
	    system("cls");
	    cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            View Officers Record   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
           viewOfficersRecords();
           system("pause");
    } else if (choice == 3) {
	    system("cls");
	    cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Delete Officers Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;


    int deleteID;
    cout << "\t\t\t\t\t\t Enter Officer ID to delete: ";
    cin >> deleteID;

    ifstream inFile("officers.txt");
    ofstream outFile("temp_officers.txt");

    bool found = false;
    string line;
    while (getline(inFile, line)) {
        size_t foundID = line.find("ID: " + to_string(deleteID));
        if (foundID != string::npos) {
            // Skip lines related to the officer's data
            for (int i = 0; i < 6; ++i) {
                getline(inFile, line);
            }
            found = true;
        } else {
            outFile << line << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("officers.txt");
        rename("temp_officers.txt", "officers.txt");
        cout << "Officer with ID " << deleteID << " and associated data deleted successfully." << endl;
    } else {
        cout << "Invalid ID! No officer found with ID " << deleteID << endl;
    }

    system("pause");
     } else if (choice == 4) {
	    break;
    } else {
	    cout << "Invalid choice. Please enter a valid option." << endl;
	    system("pause");
	    }
	 }
}


class Crime : public Person {
private:
    string crimeType;
    string description;

public:
    Crime() : Person(), crimeType(""), description("") {}
    Crime(int id, string n, int pN, string G, string cZ, string jD, string cT, string d)
        : Person(id, n, pN, G, cZ, jD), crimeType(cT), description(d) {}

    void setCrimeType(string ct) { crimeType = ct; }
    void setDescription(string desc) { description = desc; }

    string getCrimeType() const { return crimeType; }
    string getDescription() const { return description; }

    void setCrimeDetails() {
        setDetails(); // Assume setDetails is a member function of the Person class

        cout << "Enter Crime Type: ";
        cin >> crimeType;

        cout << "Enter Description of Crime: ";
        cin.ignore(); // Ignore the newline character from the previous input
        getline(cin, description);
    }

    void displayDetails() const {
        Person::displayDetails();
        cout << "\nCrime Name: " << getName() << "\nCitizenship: " << getCitizenShip() << "\nCrime Type: " << crimeType
             << "\nDescription of Crime: " << description << endl;
    }
    
     string CrimeDetails(){
        cout<<"Enter Name: "<<Person:: getName();
        cout<<"Enter Gender:"<<Person:: getGender();
        cout<<"Enter CitizenShip: "<<Person:: getCitizenShip();
        cout<<"Enter Crime Palce: "<<getCrimeType();
        cout<<"Enter Description: "<<getDescription();
        return 0;
		}  
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FIR : public Crime {
private:
    string FIRTime;
    string offense;
    string sign;

public:
	 static int FIRIDCounter; // Declare the counter as static

    static int allocateFIRID() { // Make the allocation function static
        return ++FIRIDCounter;
    }
	int ID;
    FIR operator ++() {
        FIR temp;
        temp.ID = ++ID;
        return temp;
}
	
    FIR() : Crime(), FIRTime(""), offense(""), sign("") {}

    FIR(int id, string n, int pN, string G, string cZ, string cT, string jD, string t, string o, string s)
        : Crime(id, n, pN, G, cZ, jD, cT, ""), FIRTime(t), offense(o), sign(s) {}


    void setFIRDetails() {
        setCrimeDetails();
        cout << "Enter FIR Time: ";
        getline(cin, FIRTime);

        cout << "Enter Offense: ";
        getline(cin, offense);
        
               ofstream fileout("FIR.txt", ios::app);
		        if (fileout.is_open()) {
		            fileout << "ID: " <<allocateFIRID()<< "\n";
		            fileout << "Name: " << getName() << "\n";
		            fileout << "Phone Number: " << getPhoneNo() << "\n";
		            fileout << "Gender: " << getGender() << "\n";
		            fileout << "Citizenship: " << getCitizenShip() << "\n";
		            fileout << "Crime Type: " << getCrimeType() << "\n";
		            fileout << "Description: " << getDescription() << "\n";
		            fileout << "FIR Time: " << FIRTime << "\n";
		            fileout << "Offense: " << offense << "\n";
		            fileout << "--------------------------\n";
		            fileout.close();
		            cout << "FIR added successfully!" << endl;
		        } else {
		            cout << "Unable to open file for writing!" << endl;
		        }
    }

    void displayDetails() const {
        Crime::displayDetails();
        cout << "\nFIR Time: " << FIRTime << "\nOffense: " << offense << "\nSign: " << sign << endl;
    }

    void viewFIRRecord() {
    int searchID;
    while (true) {
        try {
            cout << "Enter the ID of the FIR you want to view: ";
            cin >> searchID;

            if (cin.fail()) {
                throw runtime_error("Invalid input! Please enter a valid integer ID.");
            }

            break; // Break out of the loop if the ID is valid
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        

    ifstream filein("FIR.txt");
    if (filein.is_open()) {
        string line;
        bool found = false;

        while (getline(filein, line)) {
            size_t foundID = line.find("ID: " + to_string(searchID));
            if (foundID != string::npos) {
                found = true;
                for (int i = 0; i < 9; ++i) {
                    getline(filein, line);
                    cout << line << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "No FIR found with ID: " << searchID << endl;
        }

        filein.close();
    } else {
        cout << "Unable to open file for reading!" << endl;
    }
}


    void menu() {
        int choice;
        while (true) {
            system("cls");
           cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t               FIR Information\n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;

            cout << "\t\t\t\t\t Enter 1 to add new FIR\n";
            cout << "\t\t\t\t\t Enter 2 to view FIR\n";
            cout << "\t\t\t\t\t Enter 3 to go back to the main menu\n";
            cout << "\n\t\t\t\t\t Enter your choice: ";
            cin >> choice;

            system("cls");
            if (choice == 1) {
        cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t               Add FIR Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
                setFIRDetails();
            } else if (choice == 2) {
        cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            View FIR Record   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
                viewFIRRecord();
                system("pause");
            }
         else if (choice == 3) {
	    break;
    } else {
	    cout << "Invalid choice. Please enter a valid option." << endl;
	    system("pause");
	    }
        }
    }
};

int FIR::FIRIDCounter = 0; // Initialize static member

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Investigation : public Crime {

private:
    string evidence, suspect, crimePlace;
     Person person;
     Crime crime; 
public:
static int InvestigationIDCounter; // Declare the counter as static

    static int allocateInvestigationID() { // Make the allocation function static
        return ++InvestigationIDCounter;
    }
	int ID;
    Investigation operator ++() {
        Investigation temp;
        temp.ID = ++ID;
        return temp;
}

   Investigation() : Crime(), evidence(" "), suspect(" "), crimePlace(" ") {}
   
       Investigation(int id, string n, int pN, string G, string cZ, string jD, string cT, string d, string e, string sus, string cP)
           : Crime(id, n, pN, G, cZ, jD, cT, d),evidence(e), suspect(sus),crimePlace(cP) {}
		     
    void setInvestigationData()
      {
        setCrimeDetails();
       cout << "Enter Evidence: ";
    cin >> evidence;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer


        cout << "Enter Suspect : ";
    cin.ignore(); // Ignore the newline character from previous input
    getline(cin, suspect);

    cout << "Enter Crime Place: ";
    getline(cin, crimePlace);
    }
     void displayDetails() {
	        Crime::displayDetails();
	        cout << "\nEvidence:  " << evidence<< "\nSuspect: " <<suspect  <<  "\nCrime Place: " << crimePlace << endl;
	    }
	 string getEvidence() const {
	 return evidence;
	  }
    string getSuspect() const {
	 return suspect; 
	 }
    string getCrimePlace() const {
	 return crimePlace; 
	 }
    
	    void Menu();
	    void viewInvestigationData();
   };
int Investigation::InvestigationIDCounter = 0; // Initialize static member
   
void Investigation::Menu()
 {
	 int choice;
	    while (true) {
	        system("cls");
	       cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Investigation Information   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
	        cout << endl;
	        cout << "\t\t\t\t Enter 1 to add new Investigation\n";
	        cout << "\t\t\t\t Enter 2 to view Investigation\n";
	        cout << "\t\t\t\t Enter 3 to go back to the main menu" << endl;
	        cout << "\n\t\t       \t\t Enter your choice: ";
	        cin >> choice;
	        system("cls");
	
	        if (choice == 1) {
	    cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Add Investigation Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
	          	  Investigation* newInvestigation = new Investigation();
               newInvestigation->setInvestigationData(); 
	            system("pause");
	         ofstream fileout("Investigation.txt", ios::app);
                if (fileout.is_open()) {
                    fileout <<"\nID: "<<newInvestigation->allocateInvestigationID() << "\nName: " << newInvestigation-> getName() <<" \nGender:  "<<newInvestigation-> getGender()<< "\nCitizenShip: "<<newInvestigation->getCitizenShip()<<"\nCrime Type: "<<newInvestigation->getCrimeType()<<"\nDescription: "<<newInvestigation->getDescription()<<"\nEvidence: "<< newInvestigation->getEvidence() << "\nSuspect: " << newInvestigation->getSuspect() << "\nCrime Place: " << newInvestigation->getCrimePlace() << endl;
                    fileout.close();
                } else {
                    cout << "Unable to open file for writing!";
                }
	            system("cls");
	            delete newInvestigation;// Deallocate memory
	        }
			 else if (choice == 2) {
	            viewInvestigationData();
	            system("pause");
	        } else if (choice == 3) {
	            break;
	        }
	    }	
	}

void Investigation::viewInvestigationData() {
	cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	cout << "\t\t\t\t\t\t\t\t            View Investigation Data   \n ";
    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
     int searchID;
    while (true) {
        try {
            cout << "Enter Investigation ID you want to view: ";
            cin >> searchID;

            if (cin.fail()) {
                throw runtime_error("Invalid input! Please enter a valid integer ID.");
            }

            break; // Break out of the loop if the ID is valid
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        

    ifstream filein("Investigation.txt");
    if (filein.is_open()) {
        string line;
        bool found = false;

        while (getline(filein, line)) {
            size_t foundID = line.find("ID: " + to_string(searchID));
            if (foundID != string::npos) {
                found = true;
                for (int i = 0; i < 9; ++i) {
                    getline(filein, line);
                    cout << line << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "No Investigation found with ID: " << searchID << endl;
        }

        filein.close();
    } else {
        cout << "Unable to open file for reading!" << endl;
    }
}

class Criminal {
private:
    int entryDate;
    string identityMark,punishment,  criminalRecord, crimetype;
    Person person;

public:
     int CriminalIDCounter=0;
     int allocateCriminalID() {
        return ++CriminalIDCounter;
    }

    int ID;
    Criminal operator++() {
        Criminal temp;
        temp.ID = ++ID;
        return temp;
    }

    Criminal() : entryDate(0), identityMark(""),punishment(""),  criminalRecord(""), crimetype(""), ID(0) {}

    void displayDetails() {
        person.displayDetails();
        cout << "\nEntry Date: " << entryDate <<  "\nIdentity Mark: " << identityMark<<"\nPunishment: " << punishment << "\nCriminal Record: " << criminalRecord << "\nCrime Type: " << crimetype << endl;
    }

    void setDetails() {
        person.setDetails();
         while (true) {
        try {
            cout << "Enter Criminal Entry Date: ";
            cin >> entryDate;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw runtime_error("Invalid input! Please enter a valid entry date.");
            }

            break; // Break out of the loop if the input is valid
        } catch (const exception &e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
 cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer,cin.ignore()Ignore the newline character from previous input
    cout << "Enter Criminal Identity Mark: ";
    getline(cin, identityMark);

    cout << "Enter Criminal Punishment: ";
    getline(cin, punishment);

    cout << "Enter Criminal Record: ";
    getline(cin, criminalRecord);

    cout << "Enter Criminal Crime Type: ";
    getline(cin, crimetype);
    }

    void crimeMenu();
};

//int Criminal::CriminalIDCounter = 0;

void Criminal::crimeMenu() {
    int choice;
    while (true) {
        system("cls");
       cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Criminals Information    \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
        cout << endl;
        cout << "\t\t\t\t\t    Enter 1 to add new criminal data\n";
        cout << "\t\t\t\t\t    Enter 2 to view criminal data\n";
        cout << "\t\t\t\t\t    Enter 3 to go back to the main menu\n";
        cout << "\t\t\t\t\t    Enter your choice: ";
        cin >> choice;
        system("cls");

        if (choice == 1) {
            cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Add Criminals Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
            setDetails();
            system("pause");
            ofstream fileout("criminal.txt", ios::app);
            if (fileout.is_open()) {
                fileout << "ID: " << Criminal::allocateCriminalID() << "\nName: " << person.getName()
                        << "\nEntry Date:" << entryDate << "\nIdentity Mark: " << identityMark<<"\nPunishment:" << punishment << "\nCriminal Record:" << criminalRecord << "\nCrime type:" << crimetype << "\n\n";
                fileout.close();
            } else {
                cout << "Unable to open file for writing!";
            }
        } else if (choice == 2) {
        cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            View Criminal Data   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;
           int searchID;
    while (true) {
        try {
            cout << "Enter Criminal ID you want to view: ";
            cin >> searchID;

            if (cin.fail()) {
                throw runtime_error("Invalid input! Please enter a valid integer ID.");
            }

            break; // Break out of the loop if the ID is valid
        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
        

    ifstream filein("criminal.txt");
    if (filein.is_open()) {
        string line;
        bool found = false;

        while (getline(filein, line)) {
            size_t foundID = line.find("ID: " + to_string(searchID));
            if (foundID != string::npos) {
                found = true;
                for (int i = 0; i < 9; ++i) {
                    getline(filein, line);
                    cout << line << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "No Criminal found with ID: " << searchID << endl;
        }

        filein.close();
    } else {
        cout << "Unable to open file for reading!" << endl;
    }
            
    }
   else if (choice == 3) {
	    break;
    } else {
	    cout << "Invalid choice. Please enter a valid option." << endl;
	    system("pause");
	    }
	 system("pause");
}  
}     
int main() {
     Officers officerMenu;
    FIR fir;
    Investigation investigationObj;
    Criminal criminal;
    system("color 8e");
    cout << "\t\t\t\t\t\t   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    cout << "\t\t\t\t\t\t          :::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;
    cout << "\t\t\t\t\t\t                    *******Semester Project*******\n"; 
    cout << "\t\t\t\t\t\t              *******Police Station Managment System*******\n" << endl;
    cout << "\t\t\t\t\t\t          :::::::::::::::::::::::::::::::::::::::::::::::::::\n";
    cout << "\t\t\t\t\t\t   :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n\n";
    cout << endl << endl << endl << endl;

    cout << "  ::::::::::::::::::::::::::::::::::::::::::::" << setw(110) << "\t\t::::::::::::::::::::::::::::::::::::::::::::\n";
    cout << "       :::GC University Chiniot Campus:::" << setw(110) << "\t     :::BSCS spring semester 2023:::\n\n";
    cout << "       :::Department : Computer Science:::" << setw(110) << "\t\t     :::Faculty : Physical Sciences:::\n";
    cout << "  :::::::::::::::::::::::::::::::::::::::::::" << setw(110) << "\t\t::::::::::::::::::::::::::::::::::::::::::::\n";
    cout << endl << endl << endl << endl << endl << endl;

    cout << "\t\t\t\t\t\t    """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""\n";
    cout << "\t\t\t\t\t\t\t\t\t   *****:::Developed By:::*****" << endl;
    cout << "\t\t\t\t\t\t    """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\t         1. Pakeeza Ghulam Muhammad" << endl;
    cout << "\t\t\t\t\t\t\t\t\t         2. Zainab Javed" << endl;
    cout << endl;


    cout << "\n\t\t\t\t\tPress Enter to Continue....... " << endl;
    cin.get();
 // Infinite loop to keep the program running until the user decides to terminate it
    while (true) {
        system("cls");
        cout << "\t\t\t\t\t ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t\t\t  ***************  Welcome ****************\n";
        cout << "\t\t\t\t\t ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;

        cout << "\t\t\t\t\t :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
        cout << "\t\t\t\t\t\t\t         *************  Main Menu *****************\n";
        cout << "\t\t\t\t\t :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n" << endl;
        cout << "\t\t\t\t\t 1- Officers Information\n";
        cout << "\t\t\t\t\t 2- Case Information\n";
        cout << "\t\t\t\t\t 3- Criminals Information\n";
        cout << "\t\t\t\t\t 4- Terminate\n\n";
        int choice;
        cout << "\t\t\t\t\t Enter your Choice(1, 2, 3, 4): ";
        cin >> choice;
        system("cls");
        if (choice == 1) {
           Officers newOfficer;
            ++newOfficer; 
            officerMenu.menu();
            system("cls");
        } else if (choice == 2) {
        cout << "\t\t\t  \t\t\t\t\t *******************************************\n";
	    cout << "\t\t\t\t\t\t\t\t            Case Information   \n ";
	    cout << "\t\t\t\t\t\t\t\t *******************************************\n"<<endl;

            cout << "\t\t\t\t 1. Information of FIRs\n";
            cout << "\t\t\t         2. Information of Case Investigation\n";
            cout << "\t\t\t\t 3. Go back to the main menu\n";
            int caseChoice;
            cout << "\t\t\t\t    Enter your choice: ";
            cin >> caseChoice;
            system("cls");
            if (caseChoice == 1) {
            	FIR newFIR;
                ++newFIR; 
                fir.menu();
            } else if (caseChoice == 2) {
              investigationObj.Menu();
            }      else if (caseChoice == 3) {
                break;
            }
        }
        else if(choice == 3){
            	Criminal newCriminal;
                ++newCriminal; 
                criminal.crimeMenu();   
		}
	else if(choice==4){
		break;
	}
  }

    return 0;
}