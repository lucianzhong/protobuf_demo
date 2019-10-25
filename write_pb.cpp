#include<iostream>
#include<fstream>
#include<string>
#include"addressbook.pb.h"

using namespace std;

void PromptForAddress(tutorial::Person* person){
    // set ID
    cout<<"Enter person ID number";
    int id;
    cin>>id;
    person->set_id(id);

    cout<<"Enter Name";
    // set name
    getline(cin,*person->mutable_name());
    
    // set name
    string name;
    getline(cin,name);
    person->set_name(name);

    // set email
    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin,email);
    if(!email.empty()){
        person->set_email(email);
    }

    // 
    while(true){
        cout<<"Enter a phone number (or leave blank)";
        string number;
        getline(cin,number);
        if(number.empty()){
            break;
        }

        tutorial::Person::PhoneNumber* phone_number=person->add_phone();
        phone_number->set_number(number);
         cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
        phone_number->set_type(tutorial::Person::MOBILE); // pb
        } else if (type == "home") {
        phone_number->set_type(tutorial::Person::HOME);   // pb
        } else if (type == "work") {
        phone_number->set_type(tutorial::Person::WORK);   // pb
        } else {
        cout << "Unknown phone type.  Using default." << endl;
        }
    }
}



// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.



int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.

  // GOOGLE_PROTOBUF_VERIFY_VERSION;   // pb

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }
  tutorial::AddressBook address_book;   // pb
  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!address_book.ParseFromIstream(&input)) {    // pb
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }
  // Add an address.
  PromptForAddress(address_book.add_person());  // pb
  {
    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book.SerializeToOstream(&output)) {    // pb
      cerr << "Failed to write address book." << endl;
      return -1;
    }
  }
  // Optional:  Delete all global objects allocated by libprotobuf.

  google::protobuf::ShutdownProtobufLibrary();  // pb
  return 0;
}