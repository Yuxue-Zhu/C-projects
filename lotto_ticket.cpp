/* Name: Yuxue ZHu
*  ID: 260737363
*/
#include<iostream>
#include <algorithm>
#include<sstream>

using namespace std;

struct ticket {
    unsigned int numbers[6];
    ticket* next;
};

class SuperDraw {
public:
    SuperDraw();
    SuperDraw(int num);
    SuperDraw(SuperDraw& sd2);
    ~SuperDraw();
    void newTicket(int verbose);
    void newTicket();
    void printAllTicketNumbers();
    void verifySequence(int* num);
    void deleteSequence(int* num);
    //helper methods
    string numbersOfTicket(ticket* t);
    ticket* getHead();
private:
    ticket* ticketListHead;
    ticket* ticketListTail;
};

// constructor without any input, initialize head and tail with Null
SuperDraw::SuperDraw(){
    this->ticketListHead = NULL;
    this->ticketListTail = NULL;
    
}

//constructor with an input, create num of tickets in list
SuperDraw::SuperDraw(int num){
    this->ticketListHead = NULL;
    this->ticketListTail = NULL;
    for(int i=0;i<num;i++){
        this->newTicket(0);
    }
    cout<<num<<" new ticket were successfully generated."<<endl;
    cout<<"The numbers are: ";
    ticket* t = this->ticketListHead;
    for(int i=0;i<num;i++){
        cout<<numbersOfTicket(t);
        if(i!=num-1){
            cout<<" and ";
        }
        
        t= t->next;
    }

    cout<<"."<<endl;

}

//copy constructor. deep copy of a superDraw object
SuperDraw::SuperDraw(SuperDraw& sd2){
    this->ticketListHead=NULL;
    this->ticketListTail=NULL;
    ticket* list = sd2.getHead();
    while(list){
        
        ticket* t = new ticket;
        t->next=NULL;
       
        //copy numbers
        for(int i=0;i<6;i++){
            t->numbers[i]=list->numbers[i];
        }

        //put new ticket in list
        if(!(this->ticketListHead)){
            this->ticketListHead = t;
            this->ticketListTail = t;
        }else{
            this->ticketListTail->next=t;
            this->ticketListTail = t;
        }
        
        list=list->next;

    }

    
}

//helper method. get the ticketListHead
ticket* SuperDraw::getHead(){
    return this->ticketListHead;
}

//destructor, delete every ticket in list
SuperDraw::~SuperDraw(){
    
    while(this->ticketListHead){
        ticket* temp = this->ticketListHead;
        this->ticketListHead=this->ticketListHead->next;
        delete temp;
    }

}


//Generate a new ticket without inputs
void SuperDraw::newTicket(){
    newTicket(0);
}

//Generate a new ticket with a message
void SuperDraw::newTicket(int verbose){
    //create a new ticket
    ticket* t= new ticket;
    
    //create 6 random numbers
    for(int i=0;i<6;i++){
        t->numbers[i]=rand()%49+1;

        //get different lotto numbers
        for(int j=0;j<i;j++){
                    
            while(t->numbers[i] == t->numbers[j]){
                t->numbers[i]=rand()%49+1;
            }
        }
                
    }
    t->next=NULL;

    //sort in acsending order
    sort(t->numbers,t->numbers+6);

    //print message
    if(verbose == 1){
        cout<<"A new ticket was successfully generated. The numbers are: ";
        cout<<numbersOfTicket(t);
        cout<<endl;
    }

    //append new ticket to the end and update ticketlisthead and ticketlisttail
    if(!(ticketListHead)){
        ticketListHead=t;
        ticketListTail=t;
    }else{
        ticketListTail->next=t;
        ticketListTail=t;
    }
}

//Helper method. To get the numbers of a ticket in string type
string SuperDraw::numbersOfTicket(ticket* t){
    stringstream numbers;
    for(int i=0;i<6;i++){
        numbers<<(t->numbers[i]);
        if(i!=5){
            numbers<<", ";
        }
    }
    return numbers.str();
}

//Print the tickets in the list
void SuperDraw::printAllTicketNumbers(){
    ticket* temp = this->ticketListHead;
    int counter = 0; // keep track of the number of tickets
    string result=""; // store the numbers of each ticket
    //get the numbers of each ticket
    while(temp){
        result = result+numbersOfTicket(temp);
        result = result+"\n";
        counter++;
        temp=temp->next;
    }

    cout<<"We found "<<counter<<" generated tickets:"<<endl;
    cout<<result;
    
}

//Verify if a certain sequence of numbers is already generated.
void SuperDraw::verifySequence(int* num){
    //sort input numbers in ascending order
    sort(num,num+6);

    ticket* temp = this->ticketListHead;
    bool same=false;

    //stop loop when finding a ticket in list
    while(temp && !same){

        for(int i=0;i<6;i++){

            if(temp->numbers[i]!=num[i]){
                same = false;
                temp=temp->next;
                break; //get to the next ticket if numbers doesn't match
            }else{
                same=true;
            }
        }
    
    }

    //print message
    if(same){
        cout<<"The provided sequence of numbers was already generated."<<endl;
    }else{
        cout<<"The provided sequence of numbers was never generated before."<<endl;
    }

}

//deletes a ticket.
void SuperDraw::deleteSequence(int* num){
    //sort input numbers in ascending order
    sort(num,num+6);
    ticket* deleted = this->ticketListHead;//store the ticket that will be deleted
    ticket* previous=NULL;// store the ticket before the deleted ticket in list
    bool have = false;

    //check if there is the ticket in list
    while(deleted && !have){
        for(int i=0;i<6;i++){

            if(deleted->numbers[i]!=num[i]){
                have = false;
                previous=deleted;
                deleted=deleted->next;
                break;
            }else{
                have=true;
            }
        }
    
    }

    if(have){
        //If previous is NULL, the deleted ticket is the first ticket in list
        if(previous){
            previous->next=deleted->next;
            //if the deleted ticket is the last ticket in list, update tail
            if(deleted == ticketListTail){
                ticketListTail=previous;
            }
            
            delete deleted;
            
        }else{
            ticketListHead = deleted->next;
            delete deleted;
        }
        cout<<"The provided sequence of numbers was successfully deleted."<<endl;
    }else{

        cout<<"The provided sequence of numbers was never generated before."<<endl;
    }

}
int main()
{
    SuperDraw sd;
    sd.newTicket();
   sd.newTicket();
   sd.newTicket();
   sd.newTicket();
   SuperDraw sd2(sd);

    sd.printAllTicketNumbers();
    int my[6]={1, 21, 31, 37, 42, 49};
    sd.verifySequence(my);
    sd.deleteSequence(my);
   
    sd.printAllTicketNumbers();
    sd2.printAllTicketNumbers();
}