/* Name: Jia-Shu(Joseph) Chen ID: 11204321
   CIS22B Assignment 7 MW
   Compiler: GNU GCC Compiler on Codeblocks*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;

class linked_list;

class node
{
    string item;
    int inventory;
    node* next;
    int itemasint;
public:
    node(string, int, node*);
    friend class linked_list;

};

class linked_list
{
    node* addon;
public:
    linked_list();
    ~linked_list();
    void add_item(string);   //creates new item and inserts into correct position according to inventory number
    void print_inventory() const;
    void execute(string, string);
    node* finditem(string);
    void validate_command(string, int);
    string check_empty_items();
    void remove_node(string);

};


int main()
{
    linked_list inventorylist;

    ifstream infile;
    infile.open("Assignment 7 datafile.txt");

    if(!infile)
    {
        cout << "File Open Error." << endl;
        return 1;
    }

    string line;
    int linenumber = 1;
    while(getline(infile, line))
    {
        string command;
        string whichitem;
        if(line.length() == 0)
        {
            linenumber++;
            continue;
        }

        size_t alert = line.find("inventory");
        if(alert != std::string::npos)
        {
            command = line.substr(0, line.length()-10);
            whichitem = line.substr(line.length()-9, line.length());
        }
        else
        {
            command = line.substr(0, line.length()-5);
            whichitem = line.substr(line.length()-4, line.length());
        }
        inventorylist.validate_command(command, linenumber);
        if(command == "print")
        {
            for(int counter = 0; counter < 7; counter++)
            {
                string temp = inventorylist.check_empty_items();
                if(temp != "false")
                {
                    inventorylist.remove_node(temp);
                }
            }
            inventorylist.print_inventory();
        }

        if(inventorylist.finditem(whichitem) == 0 && whichitem != "inventory")
        {
            inventorylist.add_item(whichitem);
        }

        inventorylist.execute(command, whichitem);

        linenumber++;
    }

    infile.close();
}


string linked_list::check_empty_items()
{
    node* temp = addon;
    while(temp != 0)
    {
        if(temp->inventory == 0)
        {
            return temp->item;
        }
        temp = temp->next;
    }
    return "false";

}

void linked_list::remove_node(string emptyitem)
{
    node* temp = addon;
    node* temp2;
    if(addon->item == emptyitem)
    {
        addon = addon->next;
        delete temp;
    }
    while(temp->next->item != emptyitem)
    {
        temp = temp->next;
    }
    temp2 = temp->next;
    temp->next = temp2-> next;
    delete temp2;
}

void linked_list::validate_command(string variable, int line)
{
    if(variable != "add" && variable != "subtract" && variable != "print")
    {
        cout << "Bad Transaction: " << variable << " in line # " << line << endl;
    }
}

node* linked_list::finditem(string itemcode)
{
    node* temp = addon;
    while(temp != 0)
    {
        if(temp -> item == itemcode)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return 0;
}

void linked_list::execute(string command, string itemcode)
{
    node* temp = addon;
    while(temp != 0)
    {
        if(temp -> item == itemcode)
        {
            if(command == "add")
            {
                temp->inventory++;
            }
            else if(command == "subtract")
            {
                temp->inventory--;
            }

        }
        temp = temp->next;
    }
}

void linked_list::print_inventory() const
{
    cout << "Item" << setw(10) << "Quantity" << endl;
    node* temp = addon;
    while(temp != 0)
    {
        cout << temp -> item << setw(5) << temp -> inventory << endl;
        temp = temp -> next;
    }

}

void linked_list::add_item(string item)
{
    node* temp = new node(item, 0, addon);
    if(!temp)
    {
        cout << "Could not create item." << endl;
        exit(-1);
    }
    else
    {
        node* current = addon;
        if(addon == NULL || current->itemasint > temp->itemasint)
        {
            temp->next = addon;
            addon = temp;
        }
        else
        {
            while(current->next != NULL && current->next->itemasint < temp->itemasint)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }
}

node::node(string number, int amount, node* variable)
{
    item = number;
    inventory = amount;
    next = variable;
    itemasint = atoi(number.c_str());
}

linked_list::linked_list()
{
    addon = 0;
}

linked_list::~linked_list()
{
    node* temp = addon;
    while(temp != 0)
    {
        addon = addon->next;
        delete temp;
        temp = addon;
    }
}
