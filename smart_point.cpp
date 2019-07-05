/* Name: Yuxue ZHu
*  ID: 260737363
*/


#include<iostream>

using namespace std;
/*Q1
* 1.auto_ptr
* A std::unique_ptr owns of the object it points to and no other smart pointers can point to it.
* 
* 2.shared_ptr
* A std::shared_ptr owns the object it points to but, unlike std::unique_ptr, it allows for multiple references. A special internal counter is decreased each time a std::shared_ptr pointing to the same resource goes out of scope. This technique is called reference counting. When the very last one is destroyed the counter goes to zero and the data will be deallocated.
* 
* 3.unique_ptr
* A std::weak_ptr is basically a std::shared_ptr that doesn't increase the reference count. It is defined as a smart pointer that holds a non-owning reference, or a weak reference, to an object that is managed by another std::shared_ptr.
* 
* 4.weak_ptr
* It is created as a copy of a shared_ptr. The existence or destruction of weak_ptr copies of a shared_ptr have no effect on the shared_ptr or its other copies. After all copies of a shared_ptr have been destroyed, all weak_ptr copies become empty.
*/

//Exception for negtive number
class NegtiveInt: public exception{
public:
    virtual const char* what() const throw(){
        return "Warning: You can't assign negative numbers.";
    }
};

//Exception for lack of memory
class RunOutMemory: public exception{
public:
    virtual const char* what() const throw(){
        return "Warning: The variable was not being allocated.";
    }
};

//Exception fot the unequal length of two arrays
class notEqual: public exception{
public:
    virtual const char* what() const throw(){
        return "Warning: The variables are not with the same length.";
    }
};

NegtiveInt negtiveException;
RunOutMemory notAllocatedException;
notEqual notEqualException;

template <typename T>
class SmartPointer {
public:
    SmartPointer();//create a pointer initialized with 0 for one  element
    SmartPointer(T i);//create a pointer initialized with one type of i
    SmartPointer(T* array,int size);//create a pointer initialized with an array 
    ~SmartPointer();//destructor
    T getValue();//get the value of first entry
    T getValue(int index);//get the value of array at index
    int getSize();//get the size of array
    void setValue(T i,int index);//reset the value of array at index
    void setValue(T i);//reset the value 

    //overwrite the operator +
    friend SmartPointer<T> operator+( const SmartPointer<T>& pointer1,const SmartPointer<T>& pointer2){
       //check the length if not equal, thow an exception
        if( pointer1.size == pointer2.size){
            T array[pointer1.size];
            //calculate the result of each entry
            for(int i =0;i<pointer1.size;i++){
                array[i]=pointer1.ptr[i] + pointer2.ptr[i];
            }
            //create a result pointer
            SmartPointer<T> result(array,pointer1.size);
            return result;
 
        }else{
            throw notEqualException;
        }

   };
    //overwrite the operator -
    friend SmartPointer<T> operator-( const SmartPointer<T>& pointer1,const SmartPointer<T>& pointer2){
        //check the length if not equal, thow an exception
        if( pointer1.size == pointer2.size){
            T array[pointer1.size];
            //calculate the result of each entry
            for(int i =0;i<pointer1.size;i++){
                array[i]=pointer1.ptr[i] - pointer2.ptr[i];
            }
            //create a result pointer
            SmartPointer<T> result(array,pointer1.size);
            return result;
 
        }else{
            throw notEqualException;
        }

   };
    //overwrite the operator *
     friend SmartPointer<T> operator*( const SmartPointer<T>& pointer1,const SmartPointer<T>& pointer2){
       //check the length if not equal, thow an exception
        if( pointer1.size == pointer2.size){
            T array[pointer1.size];
            //calculate the result of each entry
            for(int i =0;i<pointer1.size;i++){
                array[i]=pointer1.ptr[i] * pointer2.ptr[i];
            }
            //create a result pointer
            SmartPointer<T> result(array,pointer1.size);
            return result;
 
        }else{
            throw notEqualException;
        }

   };
  
private:
    T* ptr;
    int size;//the number of entries fo type T
};

template <typename T>
//create a pointer initialized with 0 for one  element
SmartPointer<T>::SmartPointer(){
    try{
        //one element is equivalent to an array with one entry
        this->ptr=new T[1];
        this->ptr[0]=0;
        this->size=1;
    }catch(exception& e){
        throw notAllocatedException;
    }
}
template <typename T>
//create a pointer initialized with one type of i
SmartPointer<T>::SmartPointer(T i){
    //check for negtive input
    if(i<0){
        throw negtiveException;
    }else{
        try{
            this->ptr=new T[1];
            this->ptr[0]=i;
            this->size=1;
        }catch(exception& e){
            throw notAllocatedException;
        }
        
        
    }
    
}

template <typename T>
//create a pointer initialized with an array
SmartPointer<T>::SmartPointer(T* array,int size){
    //check for negtive elements
    for(int i=0;i<size;i++){
        if(array[i]<0){
            throw negtiveException;
        }
    }


    try{
        //allocate the array
        this->ptr=new T[size]; 

        this->size=size;
        for(int i=0;i<size;i++){
            this->ptr[i]=array[i];
            
        }  

    }catch(exception& e){
        throw notAllocatedException;

    }
    
    
}

template <typename T>
//destructor
SmartPointer<T>::~SmartPointer(){
    delete[] this->ptr;
}

template <typename T>
//get the value for pointer with one element
T SmartPointer<T>::getValue (){
    return this->ptr[0];
}

template <typename T>
//get the value of array at index
T SmartPointer<T>::getValue (int index){
    return this->ptr[index];
}
template <typename T>
//get the array size
int SmartPointer<T>::getSize(){
    return this->size;
}


template <typename T>
//reset the new value 
void SmartPointer<T>::setValue(T i){
    if(i<0){
        throw negtiveException;
    }else{
        this->ptr[0]=i;
        
    }
   
}

template <typename T>
//reset the new value of array at index
void SmartPointer<T>::setValue(T i,int index){
    if(i<0){
        throw negtiveException;
    }else{
        this->ptr[index]=i;
    }
   
}




int main(){
    try{
        // For SmartPointer class
        cout << "Testing SmartPointer class" << endl;

        // Testing Constructors
        cout << "Creating a SmartPointer of type int with value 11" << endl;
        SmartPointer<int> SmartIntPointer1(11);
        cout << "SmartIntPointer1 = " << SmartIntPointer1.getValue() << endl;

        // Testing negetive input exception
        try{
            cout << "Creating a SmartPointer of type int with value -1" << endl;
            SmartPointer<int> SmartIntPointer(-1);
            
        }
        catch( NegtiveInt& e){
            //print error messege.
            cout<< e.what()<<endl;
        
        }

        cout << "Creating a SmartPointer of type int with no value provided" << endl;
        SmartPointer<int> SmartIntPointer2;
        cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

        // Testing Setter & Getter
        cout << "Setting value of SmartIntPointer2 to 5" << endl;
        SmartIntPointer2.setValue(5);
        cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

        //test constructor for float type
        cout << "Creating a SmartPointer of type float with no value provided" << endl;
        SmartPointer<float> SmartFloatPointer1;
        cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

        cout << "Setting value of SmartFloatPointer1 to 1.5" << endl;
        SmartFloatPointer1.setValue(1.5);
        cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

        cout << "Creating a SmartPointer of type float with no value provided" << endl;
        SmartPointer<float> SmartFloatPointer2;
        cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

        cout << "Setting value of SmartFloatPointer2 to 2.5" << endl;
        SmartFloatPointer2.setValue(2.5);
        cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

        //test operators
        SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
        cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

        SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
        cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

        SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
        cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;

        // For handling arrays
        cout << "Testing arrays" << endl;

        //test contructor for array
        cout << "Creating a SmartArrayPointer of int array with value 11,23,4" << endl;
        int array1[3]={11,23,4};
        SmartPointer<int> SmartIntArrayPointer1(array1,3);
        cout << "SmartIntArrayPointer1 = ";
        for(int i=0;i<SmartIntArrayPointer1.getSize();i++){
            cout<<SmartIntArrayPointer1.getValue(i)<<" ";
        }
        cout<< endl;

        //test for exception catching
        try{
            cout << "Creating a SmartArrayPointer of int Array with value 1,-1,1" << endl;
            int array2[3]={1,-1,1};
            SmartPointer<int> SmartIntArrayPointer2(array2,3);
            cout << "SmartIntArrayPointer2 = ";
            for(int i=0;i<SmartIntArrayPointer1.getSize();i++){
                cout<<SmartIntArrayPointer1.getValue(i)<<" ";
            }
            cout<< endl;
            
        }
        catch( NegtiveInt& e){
            //print error messege.
            cout<< e.what()<<endl;
        
        }

         // Testing Setter & Getter
        cout << "Creating a SmartArrayPointer of int array with value 1,1,1" << endl;
        int array2[3]={1,1,1};
        SmartPointer<int> SmartIntArrayPointer2(array2,3);
        cout << "SmartIntArrayPointer2 = ";
        for(int i=0;i<SmartIntArrayPointer2.getSize();i++){
            cout<<SmartIntArrayPointer2.getValue(i)<<" ";
        }
        cout<< endl;

        cout << "Setting value of SmartIntArrayPointer2 at index 1 to 5" << endl;
        SmartIntArrayPointer2.setValue(5,1);
        cout << "SmartIntArrayPointer2 = ";
        for(int i=0;i<SmartIntArrayPointer2.getSize();i++){
            cout<<SmartIntArrayPointer2.getValue(i)<<" ";
        }
        cout<< endl;

        cout << "Creating a SmartArrayPointer of type float with 1.1, 1.2, 1.3" << endl;
        float farray1[3]={1.1,1.2,1.3};
        SmartPointer<float> SmartFloatArrayPointer1(farray1,3);
        cout << "SmartIntArrayPointer1 = ";
        for(int i=0;i<SmartFloatArrayPointer1.getSize();i++){
            cout<<SmartFloatArrayPointer1.getValue(i)<<" ";
        }
        cout<< endl;

        cout << "Creating a SmartArrayPointer of type float with 2.1, 2.2, 2.3" << endl;
        float farray2[3]={2.1,2.2,2.3};
        SmartPointer<float> SmartFloatArrayPointer2(farray2,3);
        cout << "SmartIntArrayPointer2 = ";
        for(int i=0;i<SmartFloatArrayPointer2.getSize();i++){
            cout<<SmartFloatArrayPointer2.getValue(i)<<" ";
        }
        cout<< endl;
       
        
        cout << "Creating a SmartArrayPointer of type float with 3.5,4.5" << endl;
        float farray3[3]={3.5,4.5};
        SmartPointer<float> SmartFloatArrayPointer3(farray3,2);
        cout << "SmartIntArrayPointer3 = ";
        for(int i=0;i<SmartFloatArrayPointer3.getSize();i++){
            cout<<SmartFloatArrayPointer3.getValue(i)<<" ";
        }
        cout<< endl;


        //test length exception catching
        try{
            cout << "SmartFloatPointer1 + SmartFloatPointer3 = "<<endl;
            SmartPointer<float> SmartFloatArrayPointer4 = SmartFloatArrayPointer1 + SmartFloatArrayPointer3;
            
            for(int i=0;i<SmartFloatArrayPointer4.getSize();i++){
                cout<<SmartFloatArrayPointer4.getValue(i)<<" ";
            }
            cout<< endl;

        }catch(notEqual& e){
            cout<< e.what()<<endl;
        }


        SmartPointer<float> SmartFloatArrayPointer4 = SmartFloatArrayPointer1 + SmartFloatArrayPointer2;
        cout << "SmartFloatPointer1 + SmartFloatPointer2 = " ;
        for(int i=0;i<SmartFloatArrayPointer4.getSize();i++){
            cout<<SmartFloatArrayPointer4.getValue(i)<<" ";
        }
        cout<< endl;

        SmartPointer<float> SmartFloatArrayPointer5 = SmartFloatArrayPointer2 - SmartFloatArrayPointer1;
        cout << "SmartFloatPointer1 - SmartFloatPointer2 = " ;
        for(int i=0;i<SmartFloatArrayPointer5.getSize();i++){
            cout<<SmartFloatArrayPointer5.getValue(i)<<" ";
        }
        cout<< endl;

        SmartPointer<float> SmartFloatArrayPointer6 = SmartFloatArrayPointer1 * SmartFloatArrayPointer2;
        cout << "SmartFloatPointer1 * SmartFloatPointer2 = " ;
        for(int i=0;i<SmartFloatArrayPointer6.getSize();i++){
            cout<<SmartFloatArrayPointer6.getValue(i)<<" ";
        }
        cout<< endl;

        
    }catch(RunOutMemory& e){
        cout<< e.what()<<endl;
    }

    
    
}