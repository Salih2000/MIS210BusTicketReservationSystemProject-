#include <iostream> 

#include <string> 

  

  

using namespace std; 

  

#include <sstream> 

  

template<typename T> 

std::string to_string(const T & value) { 

    std::ostringstream oss; 

    oss << value; 

    return oss.str(); 

} 

  

  

// Passenger sınıfı, seyahat etmek isteyen birisini temsil eder. 

// Ad, soyad ve yaş özelliklerini içerir. 

class Passenger { 

    string name; 

    string surname; 

    int age; 

  

public: 

    // Passenger constructor'u 

    Passenger(const string &name, const string &surname, int age); 

  

    // Passenger'ın getter setter methodları 

    const string &getName() const; 

    void setName(const string &name); 

    const string &getSurname() const; 

    void setSurname(const string &surname); 

    int getAge() const; 

    void setAge(int age); 

  

    // İki passengerın birbiriyle aynı olup olmadığını kontrol edeceğimiz == operator fonksiyonu. 

    friend bool operator == (const Passenger& left, const Passenger& right); //Friend Func. 

}; 

  

Passenger::Passenger(const string &name, const string &surname, int age) : 

name(name), 

surname(surname), 

age(age) 

{ 

  

} 

  

const string &Passenger::getName() const { 

    return name; 

} 

  

void Passenger::setName(const string &name) { 

    Passenger::name = name; 

} 

  

const string &Passenger::getSurname() const { 

    return surname; 

} 

  

void Passenger::setSurname(const string &surname) { 

    Passenger::surname = surname; 

} 

  

int Passenger::getAge() const { 

    return age; 

} 

  

void Passenger::setAge(int age) { 

    Passenger::age = age; 

} 

  

// Passengerların adları, soyadları ve yaşları eşitse doğru dönmesini istediğimiz operator 

bool operator==(const Passenger &left, const Passenger &right) { 

    return (left.name == right.name && left.surname == right.surname && left.age == right.age); 

} 

  

  

// ----- BUS ------ 

  

#include <vector> 

  

class Bus { 

    string busName; 

    string destination; 

    string busCode; 

    vector<Passenger> passengers; 

  

public: 

    const int passengerSize = 40; 

    Bus(const string &busName, const string &destination, const string &busCode); 

    Bus(const string &busName, const string &destination, const string &busCode, const vector<Passenger>& passengers); 

    Bus(); 

  

    const string &getBusName() const; 

    void setBusName(const string &busName); 

    const string &getDestination() const; 

    void setDestination(const string &destination); 

    const string &getBusCode() const; 

    void setBusCode(const string &busCode); 

    const vector<Passenger> &getPassengers() const; 

    void updateRefillPassengers(const vector<Passenger> &passengers); 

  

    void addPassenger(const Passenger& passenger); 

    void removePassenger(int index); 

    vector<Passenger> dischargeBus(); 

  

  

    friend bool operator == (const Bus& left, const Bus& right); 

    Bus& operator = (const Bus& bus); 

}; 

  

ostream& operator << (ostream& ostream1, const Bus& bus); 

  

Bus::Bus(const string &busName, 

         const string &destination, 

         const string &busCode) : busName(busName), 

                                  destination(destination), 

                                  busCode(busCode) { 

  

    passengers = vector<Passenger>(); 

} 

  

const string &Bus::getBusName() const { 

    return busName; 

} 

  

void Bus::setBusName(const string &busName) { 

    Bus::busName = busName; 

} 

  

const string &Bus::getDestination() const { 

    return destination; 

} 

  

void Bus::setDestination(const string &destination) { 

    Bus::destination = destination; 

} 

  

const string &Bus::getBusCode() const { 

    return busCode; 

} 

  

void Bus::setBusCode(const string &busCode) { 

    Bus::busCode = busCode; 

} 

  

const vector<Passenger> &Bus::getPassengers() const { 

    return passengers; 

} 

  

void Bus::updateRefillPassengers(const vector<Passenger> &passengers) { 

    Bus::passengers = passengers; 

} 

  

void Bus::addPassenger(const Passenger &passenger) { 

  

    if(passengers.size() >= passengerSize){ 

        cout << "Bus is full. Cannot add any more passenger. " << endl; 

        return; 

    } 

  

    passengers.push_back(passenger); 

  

} 

  

vector<Passenger> Bus::dischargeBus() { 

  

    vector<Passenger> allPassengersInBus; 

    for (int i = 0; i < passengers.size(); ++i) { 

        allPassengersInBus.push_back(passengers[passengers.size() - 1]); 

        passengers.pop_back(); 

    } 

    return allPassengersInBus; 

  

    /* 

    for (Passenger passenger : passengers) { 

        allPassengersInBus.push_back(passengers[passengers.size() - 1]); 

        passengers.pop_back(); 

    } 

  

    return allPassengersInBus;*/ 

} 

  

bool operator==(const Bus &left, const Bus &right) { 

    return (left.busName == right.busName && left.destination == right.destination); 

} 

  

Bus::Bus(const string &busName, 

         const string &destination, 

         const string &busCode, 

         const vector<Passenger> &passengers) : busName(busName), 

                                                destination(destination), 

                                                busCode(busCode) { 

  

    this->passengers = passengers; 

} 

  

Bus::Bus() { 

  

} 

  

Bus& Bus::operator=(const Bus &bus) { 

    this->passengers = bus.passengers; 

    this->busCode = bus.busCode; 

    this->destination = bus.destination; 

    this->busName = bus.busName; 

    return *this; 

} 

  

void Bus::removePassenger(int index) { 

    passengers.erase(passengers.begin() + index); 

} 

  

//Operator Overloading 

ostream & operator<<(ostream &ostream1, const Bus& bus) { 

    ostream1 << "Bus Name: " << bus.getBusName() << "\nDestination: " << bus.getDestination() << endl; 

    ostream1 << "Bus Code: " << bus.getBusCode() << "\nIncludes " << bus.getPassengers().size() << "/" << bus.passengerSize << " passengers." << endl << endl; 

    return ostream1; 

} 

  

  

  

// ----- TICKET ----- 

  

  

  

// Ticket sınıfı, bileti temsil eder. 

// 4 Tür bilet bulunur; bunlar, Çocuk Bileti, Öğrenci Bileti, Normal Bilet, Yaşlı Bileti'dir. 

// Biletlerin bir biletkodu, ve satın alan passenger'ı bulunur. 

// Bunun yanında bineceği otobüs ve bilet fiyatı da özelliklerdendir. 

// Base-Info adlı method, children sınıflarda kullanılacaktır. 

class Ticket { 

protected: 

    string ticketCode; 

    Passenger passenger; 

    Bus bus; 

    double cost; 

    void baseInfo(); 

  

public: 

  

    // Bilet constructor'u. 

    Ticket(const string &ticketCode, const Passenger &passenger, Bus &bus); 

     

  

   // Bilet sınıfının bir abstract sınıf olmasını istediğimiz için; setCost ve printInfo adlı iki virtual fonksiyon yazdım. 

   // Bu fonksiyonlar, kendisini inheritleyen children sınıflar tarafından (Çocuk, Öğrenci, Normal ve Yaşlı bilet) tanımlancaktır. 

    virtual void setCost() = 0; 

    virtual void printInfo() = 0; 

  

    // Biletlerin aynı olup olmadığını kontrol edicek operator fonksiyonu 

    friend bool operator == (const Ticket& left, const Ticket& right); 

  

  

    // Getter ve Setterlar. 

    const string &getTicketCode() const; 

    void setTicketCode(const string &ticketCode); 

    const Passenger &getPassenger() const; 

    void setPassenger(const Passenger &passenger); 

    const Bus &getBus() const; 

    void setBus(const Bus &bus); 

    double getCost() const; 

  

}; 

  

// Çocuk Bilet sınıfı, 

class ChildTicket: public Ticket{ 

public: 

    ChildTicket(const string &ticketCode, const Passenger &passenger, Bus &bus); 

    void setCost(); //override; 

  

    void printInfo();//  override; 

}; 

  

// Normal Bilet sınıfı, 

class NormalTicket: public Ticket{ 

public: 

    NormalTicket(const string &ticketCode, const Passenger &passenger, Bus &bus); 

    void setCost(); //override; 

  

    void printInfo();//  override; 

  

}; 

  

// Yaşlı Bilet sınıfı, 

class OldTicket: public Ticket{ 

public: 

    OldTicket(const string &ticketCode, const Passenger &passenger, Bus &bus); 

    void setCost(); //override; 

  

    void printInfo();//  override; 

  

}; 

  

// Öğrenci Bilet sınıfı, 

class StudentTicket: public Ticket{ 

public: 

    StudentTicket(const string &ticketCode, const Passenger &passenger, Bus &bus); 

    void setCost(); //override; 

  

    void printInfo();//  override; 

  

}; 

  

  

  

Ticket::Ticket(const string &ticketCode, 

               const Passenger &passenger, 

               Bus &bus) :ticketCode(ticketCode), 

                          passenger(passenger), 

                          bus(bus) { 

} 

  

bool operator==(const Ticket& left, const Ticket& right) { 

    return (left.cost == right.cost && left.passenger == right.passenger && 

            left.bus == right.bus && left.ticketCode == right.ticketCode); 

} 

  

// Base Info, Kullanıcının bilet bilgilerini yazdırır. 

void Ticket::baseInfo() { 

    cout << "Ticket Code: " << ticketCode << endl; 

    cout << "Passenger: " << passenger.getName() << " " << passenger.getSurname() << endl; 

    cout << "Bus: " << bus.getBusName() << "-" << bus.getBusCode() << "---" << bus.getDestination() << endl; 

    cout << "Cost: " << getCost() << endl; 

} 

  

const string &Ticket::getTicketCode() const { 

    return ticketCode; 

} 

  

void Ticket::setTicketCode(const string &ticketCode) { 

    Ticket::ticketCode = ticketCode; 

} 

  

const Passenger &Ticket::getPassenger() const { 

    return passenger; 

} 

  

void Ticket::setPassenger(const Passenger &passenger) { 

    Ticket::passenger = passenger; 

} 

  

const Bus &Ticket::getBus() const { 

    return bus; 

} 

  

void Ticket::setBus(const Bus &bus) { 

    Ticket::bus = bus; 

} 

  

double Ticket::getCost() const { 

    return cost; 

} 

  

  

// Çocuklar için cost setterı, bilet fiyatını otomatik olarak 5 lira olarak belirler. 

void ChildTicket::setCost() { 

    cost = 5; 

} 

  

// Constructorda, kendi sınıfımızda yazılmış olan setCost çağrılır, bu sayede SINIF TÜRÜNE GÖRE bilet fiyatımız belirlenir. 

ChildTicket::ChildTicket(const string &ticketCode, 

                         const Passenger &passenger, 

                         Bus &bus) : Ticket(ticketCode, passenger, bus) { 

    setCost(); 

} 

  

// Çocuklar için bilet bilgilerini yazdırırken; biletin çocuklar için olduğunu belirttiğimiz ve diğer bilgileri yazdırdığımız fonksiyon 

void ChildTicket::printInfo() { 

    cout << "Ticket - For Children" << endl; 

    baseInfo(); 

    cout << endl; 

} 

  

  

// Normal insanlar için cost setterı, bilet fiyatını otomatik olarak 80 lira olarak belirler. 

void NormalTicket::setCost() { 

    cost = 80; 

} 

  

// Constructorda, kendi sınıfımızda yazılmış olan setCost çağrılır, bu sayede SINIF TÜRÜNE GÖRE bilet fiyatımız belirlenir. 

NormalTicket::NormalTicket(const string &ticketCode, 

                           const Passenger &passenger, 

                           Bus &bus) : Ticket(ticketCode,passenger,bus) { 

    setCost(); 

} 

  

// Normal insanlar için bilet bilgilerini yazdırırken; biletin çocuklar, öğrenciler veya yaşlılar haricindeki insanlar için olduğunu belirttiğimiz ve diğer bilgileri yazdırdığımız fonksiyon 

void NormalTicket::printInfo() { 

    cout << "Ticket - Standard" << endl; 

    baseInfo(); 

    cout << endl; 

} 

  

// Yaşlı insanlar için cost setterı, bilet fiyatını otomatik olarak 20 lira olarak belirler. 

void OldTicket::setCost() { 

    cost = 20; 

} 

  

// Constructorda, kendi sınıfımızda yazılmış olan setCost çağrılır, bu sayede SINIF TÜRÜNE GÖRE bilet fiyatımız belirlenir. 

OldTicket::OldTicket(const string &ticketCode, 

                     const Passenger &passenger, 

                     Bus &bus) : Ticket(ticketCode,passenger,bus) { 

    setCost(); 

} 

  

// Yaşlı insanlar için bilet bilgilerini yazdırırken; biletin yaşlılar için olduğunu belirttiğimiz ve diğer bilgileri yazdırdığımız fonksiyon 

void OldTicket::printInfo() { 

    cout << "Ticket - For Elders" << endl; 

    baseInfo(); 

    cout << endl; 

} 

  

// Öğrenci insanlar için cost setterı, bilet fiyatını otomatik olarak 35 lira olarak belirler. 

void StudentTicket::setCost() { 

    cost = 35; 

} 

  

  

// Constructorda, kendi sınıfımızda yazılmış olan setCost çağrılır, bu sayede SINIF TÜRÜNE GÖRE bilet fiyatımız belirlenir. 

StudentTicket::StudentTicket(const string &ticketCode, 

                             const Passenger &passenger, 

                             Bus &bus) : Ticket(ticketCode,passenger,bus) { 

    setCost(); 

} 

  

// Constructorda, kendi sınıfımızda yazılmış olan setCost çağrılır, bu sayede SINIF TÜRÜNE GÖRE bilet fiyatımız belirlenir. 

void StudentTicket::printInfo() { 

    cout << "Ticket - For Students" << endl; 

    baseInfo(); 

    cout << endl; 

} 

  

  

  

// ---- BUS SYSTEM ---- 

  

  

// Bus System, kullanıcıların bilet alabilmesini sağlayan veya seyahat yapmasını sağlayan bir sistem. 

// Bilet listesi ve otobüs listesini sisteminde barındırır. 

class BusSystem { 

    vector<Ticket*> tickets; 

    vector<Bus> busList; 

  

public: 

    // Bus System constructorları ve fonksiyonlari 

    BusSystem(); 

  

  /* 

* Bilet listesine bilet ekler. Bu eklemeyi yapmadan önce şu koşullara dikkat eder: 

* - Bilet almak isteyen Passenger'ın binmek istediği otobüs sistemde var mı ? 

*/ 

    void addTicket(Ticket* ticket); 

  

    /* 

* Bilet listesinden bileti çıkartır. Bu aynı zamanda otobüste bulunan yolcu sayısını da azaltır. 

*/ 

    void removeTicket(int index); 

  

    /* 

* Biletlerin başka biletlerle değiştirilmesini sağlayan fonksiyon 

*/ 

    void updateTickets(vector<Ticket*> & tickets); 

  

   /* 

* Biletin bilgilerini bulmak için arama fonksiyonu 

*/ 

    void searchTicket(Ticket* ticket); 

  

    /* 

* Parametre olan otobüsün sistemde yer alıp almadığını kontrol eder. 

*/ 

    bool doesBusExist(const Bus& bus); 

  

/* 

* The function to check if any bus exists in the system

*/ 

    bool doesAnyBusExist(); 

  

  

  

/* 

* The function to add a bus to the system

*/ 

     

    void enterBus(); 

  

/* 

* The function to place a passenger on a bus in the system 

*/ 

    bool addPassengerToBus(const Passenger& passenger, Bus& bus); 

  

/* 

* Function that prints the destination of a bus in the system

*/ 

    void printDestinationsOfBus(const Bus& bus); 

  

/* 

* Ticket purchasing function through the system

*/ 

    void buyTicket(); 

  

   /* 

* Travel function based on the ticket entered through the system

*/ 

    void departure(); 

  

    // Printing function for the bus system

    friend ostream& operator << (ostream& ostream1, BusSystem& busSystem); 

  

  

}; 

  

  

BusSystem::BusSystem() { 

    tickets = vector<Ticket*>(); 

    busList = vector<Bus>(); 

} 

  

void BusSystem::addTicket(Ticket *ticket) { 

    if(busList.empty()){ 

        cout << "You have to enter a bus first. There is no ticket available " << endl; 

        return; 

    } 

  

    for (int i = 0; i < busList.size(); ++i) { 

        if(busList[i] == ticket->getBus()) 

        { 

            tickets.push_back(ticket); 

            return; 

        } 

    } 

  

    /* 

    for(Bus bus: busList){ 

        if(bus == ticket->getBus()) 

        { 

            tickets.push_back(ticket); 

            return; 

        } 

    }*/ 

} 

  

void BusSystem::removeTicket(int index) { 

    for (int i = 0; i < busList.size(); i++) { 

        if(busList[i] == tickets.at(index)->getBus()){ 

            tickets.erase(tickets.begin() + index); 

            return; 

        } 

    } 

    cout << "Ticket is not found." << endl; 

} 

  

  

bool BusSystem::doesBusExist(const Bus &bus) { 

    for (int i = 0; i < busList.size(); i++) { 

        if(busList[i] == bus){ 

            return true; 

        } 

    } 

    return false; 

} 

  

void BusSystem::updateTickets(vector<Ticket *> &tickets) { 

    vector<Ticket*> newTickets = vector<Ticket*>(); 

    for (int i = 0; i < tickets.size(); i++) { 

        if(doesBusExist(tickets[i]->getBus())){ 

            newTickets.push_back(tickets[i]); 

        } 

    } 

  

    this->tickets = newTickets; 

} 

  
void BusSystem::searchTicket(Ticket* ticket) { 

    for (int i = 0; i < tickets.size(); i++) { 

        if(ticket == tickets[i]){ 

            cout << "Ticket Information: " << endl << endl; 

            cout << i << endl; 

            return; 

        } 

    } 

    cout << "Ticket is not found." << endl; 

}   

// The bus can be added to the system by first entering the name of the bus and then entering the name of the destination city to be traveled to.

// During this process, if the bus to be entered is already in the system, this operation will be invalid.

void BusSystem::enterBus() { 

  

    string busName; 

    cout << "Enter bus name: "; 

    cin >> busName; 

    string destination; 

    cout << "Enter destination city: "; 

    cin >> destination; 

  

    Bus bus = Bus(busName, destination, to_string(busList.size())); 

    if(doesBusExist(bus)) 

    { 

        cout << "This bus already exists. Returning to main menu..." << endl; 

        return; 

    } 

  

    busList.push_back(bus); 

    cout << endl; 

  

} 

  

bool BusSystem::addPassengerToBus(const Passenger &passenger, Bus& bus) { 

    if(!doesBusExist(bus)) 

    { 

        cout << "There's no bus exists called, " << bus.getBusName() << " with code: " << bus.getBusCode() << endl; 

        return false; 

    } 

  

    bus.addPassenger(passenger); 

    return true; 

} 


void BusSystem::printDestinationsOfBus(const Bus& bus) { 

  

    cout << "Destination "; 

    for (int i = 0; i < busList.size(); i++) { 

        if(busList[i] == bus){ 

            cout << bus.getDestination() << endl; 

            return; 

        } 

    } 

} 

// The ticket purchasing function first obtains the name of the bus from the user

// If such a bus exists, the user inputs their first name, last name,
// and age for that bus. An object of the ticket class corresponding to their age is created and the ticket is saved to the system.

void BusSystem::buyTicket() { 

  

    string busName; 

    cout << "Enter bus name: "; 

    cin >> busName; 

    Bus* bus = NULL; 

    for (int i = 0; i < busList.size(); ++i) { 

        if(busList[i].getBusName() == busName) 

        { 

            bus = &busList[i]; 

        } 

    } 

  

    if(bus == NULL) 

    { 

        cout << "There's no bus called " << busName << " in the system"; 

        return; 

    } 

  

    string name; 

    cout << "Enter name: "; 

    cin >> name; 

    string surName; 

    cout << "Enter surname: "; 

    cin >> surName; 

    int age; 

    cout << "Enter age: "; 

    cin >> age; 

    Passenger passenger = Passenger(name, surName, age); 

    Ticket* ticket; 

    if(age < 12) 

    { 

        ticket = new ChildTicket(to_string(tickets.size()),passenger, *bus); 

    } else if(age < 23) 

    { 

        ticket = new StudentTicket(to_string(tickets.size()),passenger, *bus); 

    } else if(age < 65) 

    { 

        ticket = new NormalTicket(to_string(tickets.size()),passenger, *bus); 

    } else { 

        ticket = new OldTicket(to_string(tickets.size()),passenger, *bus); 

    } 
  
    addTicket(ticket); 

    if(addPassengerToBus(passenger, *bus)){ 

        cout << "Your ticket bought at HH:MM; " << endl << endl; 

        ticket->printInfo(); 

        return; 

    } 

  

  

} 

// After the user enters the ticket code in the travel function, they can travel if such a ticket exists.
// Once the ticket code information is correct, the user inputs their first and last name. 
//If the name and surname do not match those on the ticket, it means that someone else is trying to board the bus instead of the rightful owner of the ticket.


void BusSystem::departure() { 

  

    string ticketCode; 

    cout << "Enter ticket code: "; 

    cin >> ticketCode; 

    Ticket* ticket; 

    int ticketIndex = 0; 

    bool found = false; 

    for (int i = 0; i < tickets.size(); ++i) { 

        if(tickets[i]->getTicketCode() == ticketCode) 

        { 

            found = true; 

            ticket = tickets[i]; 

            ticketIndex = i; 

        } 

    } 

    if(!found) 

    { 

        cout << "You dont have any ticket to departure from this station." << endl; 

        return; 

    } 

  

    string name; 

    cout << "Enter name: "; 

    cin >> name; 

    string surName; 

    cout << "Enter surname: "; 

    cin >> surName; 

  

    if(!(name == ticket->getPassenger().getName() && 

         surName == ticket->getPassenger().getSurname())){ 

        cout << "You cant use anyone else's ticket. " << endl; 

        return; 

    } 

  

    cout << "Bus will go to " << ticket->getBus().getDestination() << ", departuring..." << endl; 

    removeTicket(ticketIndex); 

  

    Bus* bus = NULL; 

    int removeIndex = 0; 

    for (int i = 0; i < busList.size(); ++i) { 

        if(busList[i].getBusName() == ticket->getBus().getBusName()) 

        { 

            bus = &busList[i]; 

            removeIndex = i; 

            break; 

        } 

    } 

  

    bus->removePassenger(removeIndex); 

  

    cout << "Your ticket has been accomplished. " << endl; 

    cout << "You have arrived. Thanks for using BusSystem.com " << endl; 

  

  

  

  

} 

  

// To print the contents in the bus system; buses are printed." 

ostream & operator<<(ostream &ostream1, BusSystem& busSystem) { 

    for (int i = 0; i < busSystem.busList.size(); i++) { 

        cout << busSystem.busList[i] << endl; 

    } 

    return ostream1; 

} 

  

bool BusSystem::doesAnyBusExist(){ 

    return !busList.empty(); 

} 

// ---- MAIN ----- 


#define ADD_BUS_INPUT 1 

#define BUY_TICKET_INPUT 2 

#define DEPARTURE 3 

  

void printMenu(){ 

    cout << "WELCOME TO BUS SYSTEM ---- " << endl << endl; 

    cout << "1- Add bus to system" << endl; 

    cout << "2- Buy ticket from the system" << endl; 

    cout << "3- Departure" << endl; 

    cout << "4- Exit" << endl; 

    cout << "Enter menu input: "; 

  

  

} 

bool checkForBusContainment(BusSystem& busSystem) 

{ 

    return busSystem.doesAnyBusExist(); 

} 

int main() { 

  

    BusSystem busSystem = BusSystem(); 

    printMenu(); 

    int input; 

    cin >> input; 

    while(input < 1 || input > 4) 

    { 

        cout << "Enter a valid menu input again (1-3): "; 

        cin >> input; 

    } 

    while(input != 4) 

    { 

        if(input == ADD_BUS_INPUT) 

        { 

            cout << endl << endl << "How many busses do you want to add: "; 

            int busCount; 

            cin >> busCount; 

            while(busCount <= 0) 

            { 

                cout << "How many busses do you want to add, enter count more than 0: "; 

                cin >> busCount; 

            } 

            for (int i = 0; i < busCount; ++i) { 

                busSystem.enterBus(); 

            } 

            cout << busSystem; 

        } else if(input == BUY_TICKET_INPUT){ 

            busSystem.buyTicket(); 

            cout << busSystem; 

        } else if(input == DEPARTURE){ 

            busSystem.departure(); 

            cout << busSystem; 

        } else { 

            cout << "Thank you for using Bus System. Goodbye !! " << endl; 

            break; 

        } 

        printMenu(); 

        cin >> input; 

        while(input < 1 || input > 4) 

        { 

            cout << "Enter a valid menu input again (1-3): "; 

            cin >> input; 

        } 

        if(input == 4) 

        { 

            cout << "Thank you for using Bus System. Goodbye !! " << endl; 

            break; 

        } 

  

    } 
  
    return 0; 

} 