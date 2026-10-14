#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;


int Level(string level) {
    if(level=="Low"){
        return 1;
    }

    if(level=="Medium"){
        return 2;
    }

    if(level=="High"){
        return 3;
    }

    if(level=="Critical"){
        return 4;
    }
    return -1;
}

class Location{
    private:
    string city, place;

    public:
    Location(string c="", string p=""){
        city=c;
        place=p;
    }

    string getcity(){
        return city;
    }

    string getplace(){
        return place;
    }

    bool operator==(const Location& other){
        return city==other.city;
    }

    friend ostream& operator<<(ostream& out, const Location& loc);
};

ostream& operator<<(ostream& out, const Location& loc){
    out<<loc.city<<", "<<loc.place;
    return out;
}


class Person{
    protected:
    string name, password;
    Location location;

    public:
    Person(string n="", string p="", Location loc= Location()){
        name=n;
        password= p;
        location= loc;
    }

    string getname(){
        return name;
    }

    string getpassword(){
        return password;
    }

    Location getlocation(){
        return location;
    }

    virtual void display(){
        cout<<"Name: "<<name<<"\nLocation: "<<location<<endl;
    }
};

class User: public Person{
    private:
    vector<string> notifications;

    public:
    User(string n = "", string p = "", Location loc = Location()) : Person(n, p, loc){
    }

    void addnotification(string msg){
        notifications.push_back(msg);
    }

    void shownotifications(){
        cout<<"\npush notification"<<endl;

        if(notifications.empty()){
            cout<<"No notification"<<endl;
            return;
        }

        for(int i=0; i<notifications.size(); i++){
            cout<<i+1<<notifications[i]<<endl;
        }
    }

    void display() override{
        cout<<"User name: "<<name<<"\nLocation: "<<location<<endl;
    }
};

class Comment{
    private:
    string commenterName, text;

    public:
    Comment(string n="", string t=""){
        commenterName=n;
        text=t;
    }

    void display(){
        cout<<commenterName<<" : "<<text<<endl;
    }
};

class DisasterReport{
    private:
    int reportId;
    string reporterName, disasterType, details, currentSituation, disasterLevel;
    Location location;
    vector<Comment> comments;

    public:
    DisasterReport(int id = 0, string r = "",string t = "",string det = "",string s = "",string l = "",Location loc = Location()) {
        reportId= id;
        reporterName= r;
        disasterType= t;
        details= det;
        currentSituation= s;
        disasterLevel= l;
        location= loc;
    }

    int getReportId(){
        return reportId;
    }

    string getDisasterLevel() const{
        return disasterLevel;
    }

    Location getlocation() const{
        return location;
    }

    string getDisasterType() const{
        return disasterType;
    }

    string getReporterName() const{
        return reporterName;
    }

    void addComment(Comment c){
        comments.push_back(c);
    }

    bool operator>(const DisasterReport& other) const{
        return Level(disasterLevel)>Level(other.disasterLevel);
    }

    void display(){
        cout <<"\nReport ID: " << reportId <<"\nReporter: " << reporterName <<"\nDisaster Type: " << disasterType <<"\nLocation: " << location <<"\nDisaster Level: " << disasterLevel <<"\nDetails: " << details <<"\nCurrent Situation: " << currentSituation << endl;

        cout<<"Comments:\n";
        if(comments.empty()){
            cout<<"no comments yet"<<endl;
        }

        else{
            for(int i=0; i<comments.size(); i++){
                comments[i].display();
            }
        }
        }
};


class EmergencyService{
    public:
    virtual void respond(Location loc, string disasterType)=0;
};


class Ambulance: public EmergencyService{
    public:
    void respond(Location loc, string disasterType) override{
        cout<<"\nAmbulance alerted for: "<<disasterType<<"at "<<loc<<endl;
    }
};

class FireBrigade: public EmergencyService{
    public:
    void respond(Location loc, string disasterType) override{
        cout<<"\nFire bridged alerted for "<<disasterType<<" at "<<loc<<endl;
    }
};

class RescueTeam: public EmergencyService{
    public:
    void respond(Location loc, string disasterType) override{
        cout<<"\nRescue Team alerted for "<<disasterType<<" at "<<loc<<endl;
    }
};

class DisasterSystem{
    private:
    vector<User> users;
    vector <DisasterReport> reports;
    int nextReportId;

    public:
    DisasterSystem(){
        nextReportId= 1;
    }

    string toLowerCase(string str){
        for(int i=0; i <str.length(); i++){
            if(str[i]>= 'A' && str[i]<= 'Z'){
                str[i]= str[i]+32;
            }
        }
        return str;
    }

    vector<string> getPlaceByCity(string city){
        city = toLowerCase(city);

        if(city=="karachi"){
          return {"Saddar", "Sea View", "Shahrah-e-Faisal", "Clifton Beach", "Mazar-e-Quaid", "Gulshan"};  
        }

        else if(city=="lahore"){
            return {"Badshahi Mosque", "Minar-e-Pakistan", "Anarkali", "Liberty Market", "Shalimar Garden"};
        }

        else if(city=="islamabad"){
            return {"Faisal Mosque", "Daman-e-Koh", "F-9 Park", "Blue Area"};  
        }

        else if(city=="hyderabad"){
            return {"Rani Bagh", "Latifabad", "Qasimabad", "Clock Tower"};
        }

        else if(city=="umerkot"){
            return {"Umerkot Fort", "Shiv Mandir", "Akbar Birthplace", "Local Bazaar"};
        }

        else if(city=="samaro"){
            return {"Samaro Town", "Samaro Bazaar", "Agricultural Fields"};
        }

        else if(city=="kunri"){
            return {"Kunri Bazaar", "Red Chili Market", "Chili Farms"};
        }

        else if(city=="mithi"){
            return {"Gadi Bhit", "Thar Culture Museum", "Local Handicraft Market"};
        }

        return {};
    }

    Location inputLocation(){
        string city, searchText;

        cout<<"Enter city: ";
        getline(cin, city);

        vector<string> places= getPlaceByCity(city);

        if(places.empty()){
            string customplace;

            cout<<"No saved place found"<<endl;
            cout<<"Enter place manually: ";
            getline(cin, customplace);

            return Location(city, customplace);
        }

        while(true){
            vector<string> matchedplaces;

            cout<<"Search place by starting letter: ";
            getline(cin, searchText);

            for(int i=0; i <places.size(); i++){
                string lowerplace= toLowerCase(places[i]);
                string lowersearch= toLowerCase(searchText);

                if(lowerplace.find(lowersearch)==0){
                    matchedplaces.push_back(places[i]);
                }
            }

            if(matchedplaces.empty()){
                cout<<"No places found"<<endl;
            }

            else{
                cout<<"\nsimilar places: "<<endl;
                for(int i=0; i<matchedplaces.size(); i++){
                    cout<<i+1<<"."<<matchedplaces[i]<<endl;
                }

                int choice;
                cout<<"Select place number: ";
                cin>>choice;
                
                if(choice>= 1 && choice<= matchedplaces.size()){
                    return Location(city, matchedplaces[choice-1]);
                }

                else{
                    cout<<"Invalid choice"<<endl;
                }
            }
            
        }
        }
    

        string selectDisasterType(){
            int choice;

            cout<<"\nSelect type of disaster: "<<endl;
            cout << "1. Earthquake\n"<< "2. Flood\n"<< "3. Fire\n"<< "4. Tsunami\n"<< "5. Storm\n"<<"6. Landslide\n"<< "7. Heavy Rain\n"<< "8. Building Collapse\n"<< "Enter choice: ";
            cin >> choice;

            if(choice==1){
                return "Earthquake";
            }

            else if(choice==2){
                return "Flood";
            }

            else if(choice==3){
                return "Fire";
            }

            else if(choice==4){
                return "Tsunami";
            }

            else if(choice==5){
                return "Storm";
            }

            else if(choice==6){
                return "Landslide";
            }

            else if(choice==7){
                return "Heavy Rain";
            }

            else if(choice==8){
                return "Building collapse";
            }

            else {
                return "Invalid";
            }
        }

        string selectDisasterLevel(){
            int choice;

            cout<<"\nSelect level of disaster: ";
            cout << "\n1. Low\n"<< "2. Medium\n"<< "3. High\n"<< "4. Critical\n"<< "Enter choice: ";
            cin>>choice;

            if(choice==1){
                return "Low";
            }

            else if(choice==2){
                return "Medium";
            }

            else if(choice==3){
                return "High";
            }

            else if(choice==4){
                return "Critical";
            }

            else {
                return "Invalid";
            }
        }

        string Sentiment(string text){
            int pos=0, neg=0;
            string positive[] = {"safe", "good", "helped", "better", "controlled"};
            string negative[] = {"danger", "panic", "bad", "urgent", "scared", "worse"};

            for(char& ch: text){
                if (ch>= 'A' && ch<= 'Z') {
                ch = ch + 32;
            }
            }

            for(int i=0; i<5; i++){
                if(text.find(positive[i])!= string::npos){
                    pos++;
                }
            }

            for(int i=0; i<6; i++){
                if(text.find(negative[i])!= string::npos){
                    neg++;
                }
            }

            if(pos>neg){
                return "Positive";
            }

            else if(neg>pos){
                return "Negative";
            }

            else{
                return "neutral";
            }
        }

        void registerUser(){
            string name, password, city, place;

            cout<<"Enter name: ";
            getline(cin, name);

            cout<<"Enter password: ";
            getline(cin, password);

            Location userLocation = inputLocation();

            users.push_back(User(name, password, userLocation));
            cout<<"\nUser registered successfully"<<endl;
        }

        int LoginUser(){
            string name, password;

            cout<<"Enter name: ";
            getline(cin, name);

            cout<<"Enter password: ";
            getline(cin, password);

            for(int i=0; i<users.size(); i++){
                if(users[i].getname()==name && users[i].getpassword()==password){
                    cout<<"\nLogin successfully"<<endl;

                    return i;
                }
            }
            cout<<"\nInvalid name or password\n";
            return -1;
        }

        void sendNotification(const DisasterReport& report){
            string msg= "ALert "+ report.getDisasterLevel()+ " reported near you city \nlevel: "+report.getDisasterLevel();

            for(int i=0; i<users.size(); i++){
                if(users[i].getlocation()==report.getlocation() && users[i].getname()!= report.getReporterName()){
                    users[i].addnotification(msg);
                }
            }
        }

        void sendManualNotification(){
            string msg;

            cout<<"Enter notification message: ";
            cin.ignore();
            getline(cin, msg);

            for(int i=0; i<users.size(); i++){
                users[i].addnotification(msg);
            }

            cout<<"\nmessage sent to all users";
        }
        
        void addDisasterReport(int userIndex){
            string type, details, situation, level;

            type= selectDisasterType();

            if(type=="Invalid"){
                cout<<"\nInvalid disaster type selected"<<endl;
                return;
            }

            cout<<"Descirbe what happened: ";
            cin.ignore(); 
            getline(cin, details);

            cout<<"Enter current situation: ";
            getline(cin, situation);

            level= selectDisasterLevel();

            if(level=="Invalid"){
                cout<<"\nInvalid disaster level selected";
                return;
            }

            DisasterReport report(nextReportId,users[userIndex].getname(),type,details,situation,level,users[userIndex].getlocation());

            reports.push_back(report);
            sendNotification(report);

            cout<<"\nDisaster report added successfully \n Nearby users have been notified"<<endl;

            nextReportId++;
        }

        void viewAllReports(){
            if(reports.empty()){
                cout<<"\nNo disaster reports available";
                return ;
            }

            cout<<"\nAll disaster reports"<<endl;
            for(int i=0; i<reports.size(); i++){
                reports[i].display();
            }
        }

        void addComment(int userIndex){
            if(reports.empty()){
                cout<<"\nNo reports available"<<endl;
                return;
            }

            viewAllReports();

            int id;
            cout<<"Enter report id to comment: ";
            cin>>id;

            for(int i=0; i<reports.size(); i++){
                if(reports[i].getReportId()==id){
                    string text;

                    cout<<"Enter comment: ";
                    cin.ignore();
                    getline(cin, text);

                    string sentiment= Sentiment(text);
                    string finalText = text + " | Sentiment: " + sentiment;

                    reports[i].addComment(Comment(users[userIndex].getname(), finalText));

                    cout<<"\nComments added successfully"<<"\nDetected sentiment: "<<sentiment<<endl;

                    return;
                }
            }

            cout<<"\nInvalid report id"<<endl;
        }

        void callEmergencyService(){
            if(reports.empty()){
                cout<<"\nNo disaster report available"<<endl;
                return;
            }

            viewAllReports();

            int id;
            cout<<"Enter report id for emergency alert: ";
            cin>>id;

            DisasterReport* selectedReport= nullptr;

            for(int i=0; i<reports.size(); i++){
                if(reports[i].getReportId()==id){
                    selectedReport= &reports[i];
                    break;
                }
            }

            if(selectedReport== nullptr){
                cout<<"Invalid report id";
                return;
            }

            int choice;
            cout<<"\nEmergency alert system"<<endl;
            cout << "1. Ambulance"<< "\n2. Fire Brigade"<< "\n3. Rescue Team"<< "\nEnter choice: ";
            cin >> choice;

            EmergencyService* service= nullptr;

            Ambulance ambulance;
            FireBrigade fire;
            RescueTeam rescue;

            if (choice == 1){
            service = &ambulance;
            }

            else if (choice == 2){
            service = &fire;
            }

            else if (choice == 3){
            service = &rescue;
            }

            else {
            cout << "Invalid choice"<<endl;
            return;
            }

            service->respond(selectedReport->getlocation(),selectedReport->getDisasterType());
            }

            void searchByLocation() {
                string city;

                cout<<"Enter city to search for disaster: ";
                getline(cin, city);

                bool found= false;

                for(int i=0; i<reports.size(); i++){
                    if(reports[i].getlocation().getcity()==city){
                        reports[i].display();
                        found= true;
                    }
                }

                if(!found){
                    cout<<"\nNo disaster found in this city";
                }
            
            }

            void showHighestLevelDisaster(){
                if(reports.empty()){
                    cout<<"\nNo disaster reports available"<<endl;
                    return;
                }

                DisasterReport highest= reports[0];

                for (int i = 1; i < reports.size(); i++) {
                    if (reports[i] > highest) {
                    highest = reports[i];
            }
            }

            cout<<"\nHighest level disaster"<<endl;
            highest.display();
        }

        void sortReportByPriority(){
            if(reports.empty()){
                cout<<"No reports available"<<endl;
                return;
            }

            for(int i=0; i<reports.size()-1; i++){
                for(int j=0; j<reports.size()-i-1; j++){
                    if(Level(reports[j].getDisasterLevel())<Level(reports[j+1].getDisasterLevel())){
                        DisasterReport temp= reports[j];
                        reports[j]= reports[j+1];
                        reports[j+1]= temp;
                    }
                }
            }
            cout<<"\nReports are sorted by level of disaster"<<endl;
            viewAllReports();
        
        }

        void saveReportsToFile() {
        ofstream file("disaster_reports.txt");

        if (!file) {
            cout << "\nFile could not be created.\n";
            return;
        }

        file<<"\nDisaster reports\n"<<endl;

        for (int i = 0; i < reports.size(); i++) {
            file << "Report ID: " << reports[i].getReportId() << endl;
            file << "Reporter: " << reports[i].getReporterName() << endl;
            file << "Disaster Type: " << reports[i].getDisasterType() << endl;
            file << "Disaster Level: " << reports[i].getDisasterLevel() << endl;
            file << "Location: " << reports[i].getlocation() << endl;
        }

        file.close();
        }
        
        void showDashBoard(){
            cout << "Total Registered Users: " << users.size() << "\nTotal Disaster Reports: " << reports.size() << endl;

            if(!reports.empty()){
                showHighestLevelDisaster();
            }
        
        }

        void userMenu(int userIndex) {
        int choice;

        do {
            cout << "\n========User Menu=========\n";
            cout << "1. Add Disaster Report\n";
            cout << "2. View All Disaster Reports\n";
            cout << "3. Comment on Disaster Report\n";
            cout << "4. Call Emergency Service\n";
            cout << "5. View Push Notifications\n";
            cout << "6. Search Disaster by Location\n";
            cout << "7. Show Highest Level Disaster\n";
            cout << "8. Sort Reports by Priority\n";
            cout << "9. Save Reports to File\n";
            cout << "10. System Dashboard\n";
            cout << "11. Send Manual Notification\n";
            cout << "12. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1){
                addDisasterReport(userIndex);
            }
            else if (choice == 2){
                viewAllReports();
            }

            else if (choice == 3){
                addComment(userIndex);
            }

            else if (choice == 4){
                callEmergencyService();
            }

            else if (choice == 5){
                users[userIndex].shownotifications();
            }

            else if (choice == 6){
                searchByLocation();
            }

            else if (choice == 7){
                showHighestLevelDisaster();
            }

            else if (choice == 8){
                sortReportByPriority();
            }

            else if (choice == 9){
                saveReportsToFile();
            }

            else if (choice == 10){
                showDashBoard();
            }

            else if (choice == 11){
                sendManualNotification();
            }

            else if (choice == 12){
                cout << "\nLogged out successfully.\n";
            }

            else{
                cout << "\nInvalid choice!\n";
            }

        } 
        while (choice != 12);
    }

    void mainMenu() {
        int choice;

        do {
            cout << "\n-----Disaster response system------\n";
            cout << "1. Register User\n"<<"2. Login User\n"<< "3. View All Disaster Reports\n"<< "4. Search Disaster by Location\n"<< "5. System Dashboard\n"<< "6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1)
                registerUser();
            else if (choice == 2) {
                int index = LoginUser();
                if (index != -1)
                    userMenu(index);
            }
            else if (choice == 3){
                viewAllReports();
            }

            else if (choice == 4){
                searchByLocation();
            }

            else if (choice == 5){
                showDashBoard();
            }

            else if (choice == 6){
                cout << "\nSystem closed.\n";
            }

            else{
                cout << "\nInvalid choice!\n";
            }

        } 
        while (choice != 6);
    }


    friend void emergencyAdminAccess(DisasterSystem& system);
};

    void emergencyAdminAccess(DisasterSystem& system) {
        cout << "Total Registered Users: " << system.users.size() << "\nTotal Disaster Reports: " << system.reports.size() << endl;

        system.viewAllReports();
    }

int main() {
    DisasterSystem system;
    system.mainMenu();

    return 0;
}