#include<iostream>
#include<fstream>
#include<string>
#include"addressbook.pb.h"

using namespace std;

void ListPeople(const tutorial::AddressBook& address_book){
    for(int i=0;i<address_book.person_size();i++){
        const tutorial::Person& person= address_book.person(i);
        cout<<" person.id() "<<person.id()<<endl;
        cout<<" person.name() "<<person.name()<<endl;
        if(person.has_email()){
            cout<<" person.email() "<<person.email()<<endl;
        }
        
        for(int j=0;j<person.phone_size();i++){
            const tutorial::Person::PhoneNumber& phone_number=person.phone(j);

            switch (phone_number.type()){
                case tutorial::Person::MOBILE:
                cout<<"mobile phone";
                break;

                case tutorial::Person::HOME:
                cout<<"Home phone";
                break;

                case tutorial::Person::WORK:
                cout<<"work phone";
                break;
            }
            cout<<phone_number.number()<<endl;
        }
    }
}


// Main function:  Reads the entire address book from a file and prints all
//   the information inside.



int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;   // pb
  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
    return -1;
  }
  tutorial::AddressBook address_book;   // pb
  {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!address_book.ParseFromIstream(&input)) {   // pb
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
  }
  ListPeople(address_book);
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();  // pb
  return 0;
}