#include<iostream>
#include <chrono>//for sleep func
#include <thread>//for sleep func
#include <vector>//for dynamic array
#include <iomanip> // for formatting output

using namespace std;

struct Menu_Item
{
    string item_name;
    int price;
};

struct Bill_Item 
{
    string item_name;
    int quantity;
    double price;
};

vector<Bill_Item> bill;//dynamic

Menu_Item menu[6];
Menu_Item drinks[3];

string customer_name;
int reservation;
double total;

//main .helper function declaration
void init_menu(void);
void Greet_user(void);
void Get_the_order(void);
void Display_bill(void);
void Payment_process(void);
void Make_resvation(void);

int main(void)
{
    //initilaze the menu
    init_menu();

    //Greet the user with ascii art
    Greet_user();
    
    //take the order
    Get_the_order();
    
    //Show the final bill
    Display_bill();
    
    //payment processing and recipt
    Payment_process();

    //make resvation
    Make_resvation();

    return 0;
}

                        //intialize menu items
void init_menu(void)
{
    menu[0]={"Beef burger" ,3250};
    menu[1]={"Chicken burger",2780};
    menu[2]={"Fish burger" ,2250};
    menu[3]={"Veggi burger",1080};
    menu[4]={"Grilled rice",1320};
    menu[5]={"Bk rice",450};

    drinks[0]={"Virgin mojito", 490};
    drinks[1]={"Iced millo", 720};
    drinks[2]={"Iced coffe", 720};
}

                        //Greet the user with ascii art
void Greet_user(void)
{
    cout<< " ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡤⠶⠶⠚⠛⠛⠻⠿⢷⣶⡶⢾⣿⢿⣿⣷⣶⣶⣤⣤⣀⡀⠀⠀⠀⠀" << endl
    << " ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⠶⠛⠉⠀⡀⠴⣏⡧⠐⠚⢛⡛⠓⠺⣿⣮⡿⠦⢤⡀⠀⠈⣭⠉⠛⠻⠷⣦⣄⡀⠀⠀" << endl
    << " ⠀⠀⠀⠀⠀⠀⠀⣠⣶⠟⠉⣤⡄⠀⣠⡛⠃⢠⣦⡄⠀⠀⡛⠛⠀⠰⠿⠟⢧⡀⠀⠻⠦⠀⠀⠀⠶⠀⢠⣦⡙⢿⣶⡄⠀" << endl
    << " ⠀⠀⠀⠀⠀⣠⡾⠋⠑⠀⠀⠉⠀⠐⠟⠁⢀⣤⡉⠀⠀⠸⢿⠂⠀⣶⡦⠀⠘⠇⠀⠀⠰⠆⠀⣠⣤⡀⠀⠉⠀⠀⠙⣿⣆⠀" << endl
    << "      ⢠⠇⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠘⠛⠃⠀⠀⠀⢰⡆⠀⠀⠀⠀⠀⠀⠠⣤⠄⠀⢀⠀⠀⠀⠀⠀⠀⠈⣧" << endl
    << " ⠀⠀⣿⣇⠈⣧⡟⣆⢘⢦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⢹⡄⠀ " << endl
    << " ⠀⠀⠘⣿⣦⣌⣁⠈⠚⠷⢽⣮⣦⣄⠀⢀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⠃⠀ " << endl
    << " ⠀⢀⣤⠾⢋⠈⠉⠛⠳⠦⣤⣀⡉⠉⠉⠒⠛⠷⢶⡤⠤⠤⠤⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⡀⠤⠴⠶⢾⣿⣅⠀⠀" << endl
    << " ⣴⣿⠿⢿⣿⠃⡀⠀⠀⠀⣀⠈⠉⠛⠒⠲⣦⣤⡤⠤⠤⠤⠤⠤⠤⠤⠤⠴⠶⠖⠲⠶⣶⣒⠛⠛⠋⠉⠉⠀⠀⠀⠀⠀⢀⣀⣈⣻⣿⣦" << endl
    << " ⠀⠀⠀⠚⠛⣻⡇⠀⣴⣏⣙⣷⠦⠶⠶⣟⠉⠀⠀⠀⠀⢠⡤⠤⣤⣀⠀⠀⠀⣤⢶⣄⣠⡭⠿⢶⣄⠀⢀⣤⠶⠶⢦⡤⠼⣿⡏⠉⠙⠻ "<< endl
    << " ⠀⠀⠀⢠⣴⣿⣷⣶⣿⣤⣉⡙⠛⠒⠒⠛⠛⣿⡄⢀⣤⠾⠤⠤⠖⠛⢷⣤⣼⣿⠶⣭⣄⣀⣀⢀⣸⣾⣋⣀⣀⣤⡤⣶⣿⣿⣅⠀" << endl
    << " ⠀⠀⠀⢿⣿⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⠀⠀⠀⠀⠀⢀⣠⠴⢚⣽⣿⣿⣿⣿⣿⣿⡿⠻⠙⠋⠉⠘⣿⡄" << endl
    << " ⠀⠀⠀⣸⣿⣿⣿⣿⣿⣟⣿⣿⣿⡟⢻⣏⣹⢻⣿⢻⣻⣿⣿⣦⠀⣀⣀⡴⠞⣋⣤⣶⡿⣿⠋⠳⣞⢁⡠⠁⠀⠀⠀⠀⠀⢀⣿⡇" <<endl
    << " ⠀⠀⠀⣿⡆⣆⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⢷⡄⠀⠉⠉⣉⡽⠛⠋⠙⠛⠿⣤⣤⠴⠟⠋⠁⠀⠀⠀⠀⠀⠈⠉⠛⠒⠛⠀⠀⢹⡇⠀⠀ "<< endl
    << " ⠀⠀⠀⢿⣷⢻⣿⣆⢠⡀⠀⡀⠀⠀⠀⠀⠀⠙⠳⠶⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⡇⠀⠀ "<< endl
    << " ⠀⠀⠀⠘⢿⣦⣍⡛⠦⣷⣀⠳⣀⠈⠳⣄⠀⠀⣀⢀⣀⣀⣀⣀⣀⣀⣀⠀⠀⢀⣀⣀⣀⣀⡠⠤⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⠟⠀⠀⠀ "<< endl
    << " ⠀⠀⠀⠀⠀⠉⠙⠛⠻⠷⣶⣶⣾⣽⣷⣦⣤⣀⣈⣉⣉⣁⣀⣀⣀⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣶⡶⠶⠶⠶⠒⠚⠋⠉⠁⠀⠀"<< endl;
    
    cout<<"                Welcome to Grill & Gather                    "<<endl;
}


                             //Order taking function

//order taking supportive function declaration
void Display_menu(void);
string Corret_the_text(string arg);
void Get_the_drinks_order(void);

//order taking
void Get_the_order(void)
{
    //Ask ready to order
    char inpt;
    do{
        cout<<"Are you ready to order now? (Y/n) ";
        cin>> inpt;
        if(inpt == 'n' || inpt == 'N')
        {
            cout<<"Okay, Waiting for 5 seconds!"<<endl;
            //sleep function call
            this_thread::sleep_for(5000ms);
        }
    }while (inpt != 'Y' &&  inpt !='y');

    //Take the order type
    char inptc;
    cout<<"To take out press 't', To make reservation press 'r': ";
    cin>>inptc;
    if(inptc== 't' || inptc== 'T')
    {
        reservation = 0;
        cout<<"Okay Let's order...\n";
        this_thread::sleep_for(5000ms);

    }
    else
    {
        cout<<"For how many people? ";
        cin>> reservation;
        cout<<"Okay let's order\n";
        this_thread::sleep_for(5000ms);

    }
    Display_menu();

    //                  Taking order!
    //continue var
    char contin;
    do{
        //take order 2 inputs
        string first_word,second_word,arg;
        int quan = 0;
        cout<<"Enter the item name that you want to order: ";
        cin>>first_word>>second_word;

        //combine
        arg = first_word + " " + second_word;
        
        //make case correct
        string order = Corret_the_text(arg);

        //check map exits if not continue
        bool item_found = false;
        int item_index = 0;
        for (int i = 0; i < 6; i++) 
        {
            
            //comparison
            if (menu[i].item_name.compare(order) == 0) 
            { 
                item_found = true;
                item_index = i;
                break;
            }
        }

        if(!item_found)
        {
            cout<<"invalid item! Try again...\n";
            continue;
        }

        //ask quan 
        if(item_found)
        {
            cout<<"Enter the quantity: ";
            cin>>quan;
            bill.push_back({menu[item_index].item_name, quan, (menu[item_index].price * quan)});
        }

        //ask order again
        cout<<"Do you want to order more stuff? (Y/n)";
        cin>>contin;

    }while (contin != 'n' &&  contin !='N'); 
    
    double total;
    for (const auto& item : bill) 
    {
        total += item.price;
    }

    cout << "--------------------\n";
    cout << "Total: LKR " << total << endl;

    cout<<"Wait a second... \n";
    
    this_thread::sleep_for(1000ms);
    
    cout<<"We have special offer just for you........\n";

    //sleep function call
    this_thread::sleep_for(5000ms);

    cout<<"**********************************"<<endl 
        <<"* Do you wanto drink with 10% off*"<<endl
        <<"                                 *"<<endl
        <<"*                     LKR        *"<<endl                                     
        <<"*     Virgin Mojito - 490/=      *"<<endl                               
        <<"*     Iced Milo     - 720/=      *"<<endl                   
        <<"*     Iced Coffe    - 720/=      *"<<endl                          
        <<"**********************************"<<endl;
    
    char drink_var; 

    cout<<"Would do like to order drink(Y/n): ";
    cin>>drink_var;
    if(drink_var == 'Y' ||  drink_var == 'y')
    {
        Get_the_drinks_order();
    }
}

//Show menu to customer
void Display_menu(void)
{   
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl        
        <<"+            BURGER                        ||              RICE                 +"<<endl        
        <<"+                          LKR             ||                          LKR      +"<< endl                 
        <<"+         Beef Burger    - 3250/=          ||          Grilled Rice - 1320/=    +"<< endl                               
        <<"+         Chicken Burger - 2780/=          ||          BK Rice      -  450/=    +"<< endl                           
        <<"+         Fish Burger    - 2250/=          ||                                   +"<< endl           
        <<"+         Veggi Burger   - 1080/=          ||                                   +"<< endl
        <<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ "<<endl;           
}

//case correction
string Corret_the_text(string arg)
{
    int length = arg.length();
    for(int i = 0; i < length; i++)
    {

        char letter = arg[i];
        if(letter == ' ')
        {
            continue;
        }
        
        else if(i ==0)
        {
            if(letter >= 'a' && letter<='z')
            {
                letter = letter - 32;
                arg[i] = letter;
                continue;
            }
        }
        else if (i > 0)
        {
            if(letter >= 'A' && letter<='Z')
            {
                letter = letter + 32;
                arg[i] = letter;
            }
        }
    }  
    return arg;  
}


void Get_the_drinks_order(void)
{
    char contin;
    do{
        //take order 2 inputs
        string first_word,second_word,arg;
        int quan = 0;
        cout<<"Enter the item name that you want to order: ";
        cin>>first_word>>second_word;

        //combine
        arg = first_word + " " + second_word;
        
        //make case correct
        string order = Corret_the_text(arg);

        //check map exits if not continue
        bool item_found = false;
        int item_index = 0;
        for (int i = 0; i < 3; i++) 
        {
            
            //comparison
            if (drinks[i].item_name.compare(order) == 0) 
            { 
                item_found = true;
                item_index = i;
                break;
            }
        }

        if(!item_found)
        {
            cout<<"invalid item! Try again...\n";
            continue;
        }

        //ask quan 
        if(item_found)
        {
            cout<<"Enter the quantity: ";
            cin>>quan;
            bill.push_back({drinks[item_index].item_name, quan, ((drinks[item_index].price - drinks[item_index].price * 0.10) * quan)});
        }

        //ask order again
        cout<<"Do you want to order more stuff? (Y/n)";
        cin>>contin;

    }while (contin != 'n' &&  contin !='N');
}


// display the bill with array
void Display_bill(void)
{
    total = 0;
    cout << "\nBill:   \n";
    for (const auto& item : bill) 
    {
        double item_total = item.price;
        cout << item.item_name << " x " << item.quantity << " - LKR " << item_total << endl;
        total += item_total;
    }

    cout << "--------------------\n";
    cout << "Total: LKR " << total << endl;
}


//                      Payment process function

//supportive functions declartion
bool Luhn_algo(const string& card_number);
void Display_recipt(string pay_meth);

//paymen process
void Payment_process(void)
{
    string pay_meth;
    
    cout<<"Do you want to pay with cash or card: ";
    cin>>pay_meth;
    
    if(pay_meth[2] == 'r')
    {
        bool card_val = false;
        do{
            //get input
            string card_num;

            cout<<"Enter a card number: ";
            cin>>card_num;
            
            //check validation
            card_val = Luhn_algo(card_num);
        
        }while (card_val == false);
        
        //display the recipt
        string card = "Debit Card";
        Display_recipt(card);
    }
    else
    {
        cout<<"Wait until we recive your payment!\n";
        
        //wait for 5scends
        this_thread::sleep_for(5000ms);
        
        //display the ricipt
        string cash= "Cash";
        Display_recipt(cash);
    }
    
}

//validate the card number according to luhn's algoritham
bool Luhn_algo(const string& card_number) 
{
    int sum = 0;
    bool alternate = false;
    
    for (int i = card_number.length() - 1; i >= 0; i--) 
    { 
        int digit = card_number[i] - '0'; // Convert character to integer

        if (alternate) 
        {
            digit *= 2;
            if (digit > 9) 
            {
                digit = (digit % 10) + 1; // Sum of digits if doubled value is > 9
            }
        }
        sum += digit;
        alternate = !alternate;
    }
    return (sum % 10 == 0);
}

//Display recipt
void Display_recipt(string pay_meth)
{
    cout << "\n\n--- Payment Successful Receipt ---\n";
    cout << "Date: " << __DATE__ << "  Time: " << __TIME__ << endl; // Current date and time
    cout << "-----------------------------------\n";

    for (const auto& item : bill) 
    {
        double item_total = item.price;
        cout << left << setw(20) << item.item_name // Left-align item names
             << "x" << setw(5) << item.quantity 
             << "LKR " << setw(8) << fixed << setprecision(2) << item_total << endl;
    }
    cout << "-----------------------------------\n";
    cout << setw(26) << right << "Total: LKR " << total << endl; // Right-align total
    cout << "Payment Method: " << pay_meth << endl;
    cout << "-----------------------------------\n";
    cout << "Thank you for your purchase!" << endl;
}

//book a table 
void Make_resvation(void)
{
    switch (reservation) 
    {
        case 1:
          cout << "We have B1 table waiting for you! \n";
          break;
        case 2:
          cout << "We have B2 table waiting for you! \n";
          break;
        case 3:
          cout << "We have B3 table waiting for you! \n";
          break;
        case 4:
          cout << "We have B4 table waiting for you! \n";
          break;
        case 5:
          cout << "We have B5 table waiting for you! \n";
          break;
        case 6:
          cout << "We have B7 table waiting for you! \n";
          break;
        case 7:
          cout << "We have B7 table waiting for you! \n";
          break;
        case 8:
          cout << "We have B8 table waiting for you! \n";
          break;
        default:
        if (reservation > 8)
        {
            cout << "We have B9 big dine table waiting for you \n";
        }
        else
        {
          cout << "Thank you for coming! Welcome again!";
        }
        break;
    }      
}
