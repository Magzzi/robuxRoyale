#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <vector>


using namespace std;

// Global Variables
int robux = 0, tix = 0;
const int MAX_PURCHASES = 100;
string purchases[MAX_PURCHASES];
int purchasesPrice[MAX_PURCHASES];
string itemGame[MAX_PURCHASES];
int purchaseCount = 0;
int moneyOut = 0;


int displayReceipt();

// Login Function
string logIn (){	
	
	string user;

	bool loggedIn = false; // the user needs to login to become true
	
	
	// set max and min length of username
	const int maxLength = 20;
	const int minLength = 3;
	
	// Welcome Message
	cout << "----- Welcome to Roblox -----\n\n";
	
	// Ask the user their username
	cout << "Please enter your username (3-20 characters only): ";
	cin >> user;
	
	// check if username is 3 to 20 characters only
	
	// if length is less than min or greater than max allowable characters
	if (user.length() < minLength || user.length() > maxLength){ 
	
		cout << "Invalid. Try Again! ";
		Sleep(2000);
		system ("cls"); // clear screen
		
		
		// allow the user to login again (retry)
		return logIn();
		
	// if length is within allowable length
	} else {
		
		//return the user name
		
		system("cls");
		return user;
	}
	
}

// Set Robux and Tix based on username length
void checkRobuxAndTix (string username, int &r, int &t){
	
	// set the value of variable u to the username
	string u = username;
	
	// set max and min length of username
	const int maxLength = 20;
	const int minLength = 3;
	
	// If Username = 10 to 20 characters, then they will have 5000 robux and 10000 tix
	if (u.length() >= 10 && u.length() <= maxLength){
		r = 5000;
		t = 10000;
		cout << "Hello " << u << "! You currently have " << r << " ROBUX and "<< t << " TIX. Spend your money wisely. ";
		cout << endl;
		
	// If Username = 3 to 9 characters, then they have 20000 robux and 500 tix
	} else if (u.length() <= 9 && u.length() >= minLength){
		r = 20000;
		t = 500;
		cout << "Hello " << u << "! You currently have " << r << " ROBUX and "<< t << " TIX. Spend your money wisely. ";
		cout << endl;
	} 
	
	

}

// Displays a menu of Roblox games and their corresponding options.
int gameMenu(int tix, int robux){
	int option;
	// Array of Game Names
	string games[] = {
        "Bee Swarm Simulator",
        "Adopt Me!",
        "Welcome to Bloxburg",
        "Jailbreak",
        "Lumber Tycoon 2",
        "Resturant Tycoon",
        "Natural Disaster Survival",
        "The Mimic",
        "Arsenal",
        "Convert Tix to Robux",
        "Convert Robux to Tix",
        "Exit"
    };
    system("cls");
    cout << "Robux: " << robux << endl;
    cout << "Tix: " << tix << endl;
    
    cout << endl;
    // use for loop to list all games
    cout<<"--- ROBLOX MENU ---"<<endl;
    for (int i = 0; i < sizeof(games) / sizeof(games[0]); i++){
    	cout << "[ " << (i+1) << " ] " << games[i] << endl;
	}
	
	// lets the user select an option based on the meny
	cout << "\nSelect a Game: ";
	cin >> option;
	return option;
	
}

// Allows the user to go back to the menu option
int continueAgainOption ();

// Convert tix to robux
int convertTixToRobux(int &ti, int &rb) { // use of ampersand to change the value of the global variable tix
	int tixAmount;
    const int conversionRate = 10;
    cout << "Enter the amount of tix you want to convert to robux (Conversion Rate: 10 TIX = 1 ROBUX): ";
    cin >> tixAmount;
    
    // Check if the amount the user wants to convert within the current amount
    if (tixAmount <= ti && tixAmount >= 10) {
        
        int convertedTix = tixAmount / conversionRate;
        ti -= tixAmount;
        rb += convertedTix;
        cout << tixAmount << " has been deducted from your tix, while " << convertedTix << " has been added to your robux." << endl;
        return convertedTix;
    } else if (tixAmount < 10) {
        cout << "Please enter a valid amount. \n";
    } else {
        cout << "You do not have enough tix. \n";
		cout << "Current Tix: " << ti << endl;
    }
}

// convert robux to tix
int convertRobuxToTix(int &rb, int &ti) {
	int robuxAmount;
    const int conversionRate = 10;
    cout << "Enter the amount of robux you want to convert to tix (Conversion Rate: 1 RB = 10 TIX):  ";
    cin >> robuxAmount;
   
    
    if (robuxAmount <= rb && robuxAmount > 0)  {
        
        int convertedRobux = robuxAmount * conversionRate;
        rb -= robuxAmount;
        ti += convertedRobux;
        
        cout << robuxAmount << " has been deducted from your robux, while " << convertedRobux << " has been added to your tix." << endl;
        return convertedRobux;
    } else if (robuxAmount <= 0) {
        cout << "Please enter a valid amount. \n";
    } else {
        cout << "You do not have enough robux. \n";
		cout << "Current Robux: " << rb << endl;
    }

    return 0;
}

bool isPurchasable(int price, int robux) {
    return price <= robux;
}

int showMenu();

void purchaseGamepass(const string& itemName, int price, int &r, string gameName) {
    char sure;
	cout << "Are you sure you want to purchase " << itemName << "? (Y/N) ";
	cin >> sure;
    if (purchaseCount < MAX_PURCHASES && (sure == 'Y' || sure == 'y')) {
    	cout << itemName << " has been successfully purchased for " << price << " Robux.\n";
    	r -= price;
        purchases[purchaseCount++] = itemName;
        purchasesPrice[purchaseCount] = price; 
        itemGame[purchaseCount] = gameName;
        moneyOut += price;
    } else if (purchaseCount < MAX_PURCHASES && (sure == 'N' || sure == 'n' )){
        
    } else {
        cout << "Purchase limit reached.\n";
    }
}

int listGamepass(string ar[], int price[], int &r, int size, string gameName) {
    r = robux;
    cout << endl;
    cout << "List of Gamepasses:" << endl << endl;
    for (int i = 0; i < size; i++) {
        cout << "[ " << (i + 1) << " ] " << setw(70) << left << ar[i] << "\t\t\t" << price[i] << endl;
    }

    int op;
    cout << "Select a gamepass: ";
    cin.ignore();
    cin >> op;

    if (op < 1 || op > size) {
        cout << "Invalid!" << endl;
    } else {
        cin.ignore();
        if (isPurchasable(price[op - 1], r)) {
            purchaseGamepass(ar[op - 1], price[op - 1], r, gameName);
        } else {
            cout << "Sorry. Insufficient Balance." << endl;
        }
    }
    continueAgainOption();
}


// show gamepass or the option he selected
void showGamepasses(int x, int &r) {
    int option = x;

	// list all gamepasses and their prices
    const int numberofGamepasses[] = {6, 11, 8, 7, 14, 5, 3, 3, 4};
    
    // bee swarm simulator
    string beeSwarm[] = {"x2 Honeymaking Speed", "x2 Bee Pollen", "Bear Bee", "Cub Buddy", "x2 Ticket", "Honey Starter Pack"};
    int bs[] = {250, 400, 800, 600, 700, 99};    
    
	// adopt me
    string adoptMe[] = {"VIP" , "Premium Plots", "Mermaid Mansion", "Celebrity Mansion", "Modern Mansion", "Hotdog Stand", "Lemonade Stand", "Cozy Home Lure", "Fly-A-Pet Potion", "Ride-A-Pet Potion", "Starter Pack"};
    int am[] = {750,449,400,800,350,95,95,1200,295,150,99};
	
	// blox burg
	string bloxburg[] = {"Excellent Employee", "Marvelous Mood", "Multiple Floors", "Advanced Placing", "Large Plot", "Basements", "Transform Plus", "Premium"};
    int bb[] = {300,180,300,200,250,100,600,400};
	
	// jailbreak
	string jailbreak[] = {"SWAT Team", "Cat Stereo", "Duffel Bag", "VIP", "Pro Garage", "Crime Boss", "VIP Trading"};
    int jb[] = {425,250,300,1000,450,425,400};
	
	// lumber Tycoon
	string lumberTycoon[] = {"Super Blueprints", "Super Bridge", "Super Hoove", "VIP", "Floral Bench", "Starter Pack", "Lighting Station", "PRO", "Firework Barrel", "Jukebox", "Obby Kit", "Banner Bench", "Instruments", "Shared Bank Account"};
    int lt[] = {720,220,390,399,149,199,149,1699,199,499,399,499,499,119};
    
	// restaurant tycoon
	string restaurantTycoon[] = {"x5 Diamond Rate", "Infinite Money", "Furniture Pack 1", "Extra Save Slots", "Car"};
    int rt[] = {200,750,35,50,143};
	
	// natural disaster
	string naturalDisaster[] = {"Green Balloon", "Red Apple", "Yellow Compass"};
    int nd[] = {80,80,80};
	
	// the mimic
	string theMimic[] = {"Lantern 2x", "VIP", "Ancient Fan"};
    int tm[] = {30,599,175};
	
	// arsenal
	string arsenal[] = {"VIP", "Primus the Knight Bundle", "Bugs & Beasts Bundle", "Nexus Bundle"};    
    int ar[] = {395,245,495,725};    
    
    switch (option) {
    	
        case 1:
    
        	listGamepass(beeSwarm, bs, r, sizeof(beeSwarm)/sizeof(beeSwarm[0]), "Bee Swarm");
            break;
        case 2:
        	listGamepass(adoptMe, am, r, sizeof(adoptMe)/sizeof(adoptMe[0]), "Adopt Me");
            break;
        case 3:
        	cout << endl;
          	listGamepass(bloxburg, bb, r, sizeof(bloxburg)/sizeof(bloxburg[0]), "Bloxburg");
            break;
        case 4:
        	listGamepass(jailbreak, jb, r, sizeof(jailbreak)/sizeof(jailbreak[0]), "Jailbreak");
            break;
        case 5:
        	listGamepass(lumberTycoon, lt, r, sizeof(lumberTycoon)/sizeof(lumberTycoon[0]), "Lumber Tycoon");
            break;
        case 6:
        	listGamepass(restaurantTycoon, rt, r, sizeof(restaurantTycoon)/sizeof(restaurantTycoon[0]), "Restaurant Tycoon");
            break;
        case 7:
        	listGamepass(naturalDisaster, nd, r, sizeof(naturalDisaster)/sizeof(naturalDisaster[0]), "Natural Disaster");
            break;
        case 8:
        	listGamepass(theMimic, tm, r, sizeof(theMimic)/sizeof(theMimic[0]), "The Mimic");
            break; 
        case 9:
        	listGamepass(arsenal, ar, r, sizeof(arsenal)/sizeof(arsenal[0]), "Arsenal");
            break;
        case 10:
			convertTixToRobux(tix, robux);
        	continueAgainOption();
            break;
		case 11:
			convertRobuxToTix(robux, tix);
			continueAgainOption();
			break;
		case 12:
			break;
        default:
            cout << "Invalid";
            showMenu();
    }
}




int main(){
	
	// start the program by asking for username (3 to 20 char)
	
	string username = logIn(); // the function returns a value — the username
	
 	checkRobuxAndTix(username, robux, tix); // checks the robux and tix after login — depends on the length of the username
 	
 	Sleep(2000); // wait
 	
 	showMenu(); // show menu (list all games and other options)
 	
 	// if a user selects a product and done purchasing
 	
   	displayReceipt(); // display the receipt
    
	return 0;
	
}

// Call the Game Menu to display the menu and Ask what option
int showMenu(){
	switch (gameMenu(tix, robux)){
   		
   		case 1:
   			showGamepasses(1, robux);
   			break;
   		case 2:
   			showGamepasses(2, robux);
   			break;
   		case 3:
   			showGamepasses(3, robux);
   			break;
   		case 4:
   			showGamepasses(4, robux);
   			break;
   		case 5:
   			showGamepasses(5, robux);
   			break;
   		case 6:
   			showGamepasses(6, robux);
   			break;
   		case 7:
   			showGamepasses(7, robux);
   			break;
   		case 8:
   			showGamepasses(8, robux);
   			break;
   		case 9:
   			showGamepasses(9, robux);
   			break;
   		case 10:
   			showGamepasses(10, robux);
   			break;
   		case 11:
   			showGamepasses(11, robux);
   			break;
	   }    
}

int continueAgainOption (){
	
	char yn;
            cout << "Do you still want to continue? (Y/N) ";
            cin >> yn;
            
            if (yn == 'Y' || yn == 'y') {
            	system ("cls");
        		return showMenu();  // Prompt the user to select another game
        		
    		} else {
        		return 0;  // Exit the function and go back to the main menu
    		}
}

int displayReceipt(){
	
	
	if (purchaseCount == 0){
		system("cls");
		cout << "No Purchases has been made. " << endl;
		return 0;
	}
	system ("cls");
	cout << "\nReceipt:\n";
    cout << setw(70) << left << "Item" << setw(20) << left << "Game" << setw(10) << right << "Price" << endl;
    cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	
	for (int i = 0; i < purchaseCount; ++i){
		cout << setw(70) << left << purchases[i] << setw(20) << itemGame[i+1] << setw(10) << right << purchasesPrice[i+1] << endl;
	}
	cout << setfill('-') << setw(100) << "" << setfill(' ') << endl;
	

	
	
	cout << setw(70) << left << "Total" << setw(20) << left << " " <<setw(10) << right << moneyOut << endl;
	cout << setw(70) << left << "Remaining Robux" << setw(20) << left << " " <<setw(10) << right << robux << endl;
	cout << setw(70) << left << "Remaining Tix" << setw(20) << left << " " <<setw(10) << right << tix << endl;
}

