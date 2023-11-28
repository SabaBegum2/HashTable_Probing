//
// Lab 6:�
// In this lab, we utilize the hashing methods with probing: Linear, Quadratic, double and open chaining probing.
// Simple hash function will be used: hashCode = x % SIZE

// Assignment:
// 1- Run the supplied code in your visual studio IDE
// 2- Add few more probing methods similar to the linear probing as described below�


// Already implemented:
// Linearhashing Probing and open chaining
//
// Implement the following probing methods:
// 1-Quadrating Hashing
// 2-Double Hashing
// 3-Cubic Hashing

// Each hashing method should have the following features (at least)
// 1- Insert
// 2- Remove
// 3- Find
// 4- Display

// Extra credit:
// 1-Add the load factor
//�
// Extra extra credit:
// Use the load factor to perform a re-hashing
// -Is cubic probing any better than quadratic?
// -Study of clustering induced by each method
//�
// Create a report highlighting the above topics featuring your run data.
//



#include <iostream>
#include <list>
using namespace std;


const int TABLE_SIZE = 19;  // The size of the hash table

// Hash functions (simple modulo-based hash)
int linearHash(int key) {
    return key % TABLE_SIZE;
}

int quadraticHash(int key) {
    return (key * key) % TABLE_SIZE;
}

// doubleHash functions (simple modulo-based hash)
int doubleHash(int key) {
    return (key * 2) % TABLE_SIZE;
}



class LinearProbingHashTable {
private:
    int table[TABLE_SIZE];

public:
    LinearProbingHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }

    void insert(int key) {
        int index = linearHash(key);
        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;  // Linear probing
        }
        table[index] = key;
    }

    bool find(int key) {
        int index = linearHash(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                return true;
            }
            index = (index + 1) % TABLE_SIZE;  // Linear probing
        }
        return false;
    }

    bool remove(int key) {
        int index = linearHash(key);
        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1;
                return true;
            }
            index = (index + 1) % TABLE_SIZE;  // Linear probing
        }
        return false;
    }


    void display() {
        cout << "\nLinear Probing Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (table[i] != -1) {
                cout << "[" << i << "] " << table[i] << endl;
            }
            else {
                cout << "[" << i << "] Empty" << endl;
            }
        }
    }
};




class OpenChainingHashTable {
private:
    list<int> table[TABLE_SIZE];

public:
    void insert(int key) {
        int index = linearHash(key);    // We can use any hash function, we are using the linear one to test
        table[index].push_back(key);    // Open chaining with linked lists
    }

    bool find(int key) {
        int index = linearHash(key); // You can use the same hash function here
        for (const int& value : table[index]) {
            if (value == key) {
                return true;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = linearHash(key); // We can use the same hash function here
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {//begins from the start of the table and goes till the end
            if (*it == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\nOpen Chaining Hash Table:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] ";
            for (const int& value : table[i]) {
                cout << value << " -> ";
            }
            cout << "nullptr" << endl;
        }
    }
};



class QuadraticProbingHashTable{
    //constructor 
    private:
        int table[TABLE_SIZE];
    public:
        QuadraticProbingHashTable(){
            for(int i=0;i<TABLE_SIZE;i++){
                table[i]=-1;//this is making a spot in the hash table availeble 
            }
        }
        void insert(int key){
            int index=quadraticHash(key);
            int i=0;
            while(table[(index + i*i) % TABLE_SIZE] != -1 && i<TABLE_SIZE){//while the slot is not empty
                i++;
            }
             table[(index + i*i) % TABLE_SIZE] = key;
        }

        bool find(int key){
            int index=quadraticHash(key);
            int i=0;
            while(table[(index + i*i) % TABLE_SIZE] != -1 && i<TABLE_SIZE){
                if(table[(index + i*i) % TABLE_SIZE] == key){
                    return true;
                }
                i++;
            }
            return false;

        }

        bool remove(int key){
            int index=quadraticHash(key);
            int i=0;
            while(table[(index + i*i) % TABLE_SIZE] != -1 && i<TABLE_SIZE){
                if(table[(index + i*i) % TABLE_SIZE] ==key){
                    table[(index + i*i) % TABLE_SIZE] = -1;
                    return true;
                }
                i++;
            }
            return false;
        }

        void display(){
            cout<<"\nquadratic hash table"<<endl;
            for(int i=0;i<TABLE_SIZE;i++){
                if(table[i] != -1){
                    cout<<"["<<i<<"]"<<table[i]<<endl;
                }
                else{
                    cout<<"["<<i<<"]"<<"empty"<<endl;
                }
            }
        }
        
};

//double hasing
class DoubleHashingHashTable {
private:
    int table[TABLE_SIZE];

public:
    DoubleHashingHashTable() {
        for(int i = 0; i < TABLE_SIZE; i++) {
            table[i] = -1;
        }
    }
    
    void insert(int key) {
        int index = linearHash(key);
        int secondaryHash = 1 + (key % (TABLE_SIZE - 1));
        int i = 0;
        while(table[(index + i * secondaryHash) % TABLE_SIZE] != -1 && i < TABLE_SIZE) {
            i++;
        }
        table[(index + i * secondaryHash) % TABLE_SIZE] = key;
    }
    bool find(int key){
        int index=linearHash(key);
        int secondaryHash=1+(key % (TABLE_SIZE - 1));
        int i=0;
        while(table[(index+i*secondaryHash)%TABLE_SIZE] != -1 && i<TABLE_SIZE){
            if(table[(index+i*secondaryHash)%TABLE_SIZE] == key){
                return true;
            }
            i++;
        }
        return false;
    }

    bool remove(int key){
        int index=linearHash(key);
        int secondaryHash=1+(key % (TABLE_SIZE - 1));
        int i=0;
        while(table[(index+i*secondaryHash)%TABLE_SIZE] != -1 && i<TABLE_SIZE){
            if(table[(index+i*secondaryHash)%TABLE_SIZE]==key){
                table[(index+i*secondaryHash)%TABLE_SIZE]=-1;
                return true;
            }
            i++;
        }
        return false;
    }

    void display(){
        cout<<"\nDouble hash table: "<<endl;
        for(int i=0;i<TABLE_SIZE;i++){
                if(table[i] != -1){
                    cout<<"["<<i<<"]"<<table[i]<<endl;
                }
                else{
                    cout<<"["<<i<<"]"<<"empty"<<endl;
                }
        }
    }
};


int main() 
{
    int keys[] = { 7, 17, 18, 27, 37, 47, 57, 67, 77, 87, 97 };

    LinearProbingHashTable      linearProbingTable;
    OpenChainingHashTable       openChainingTable;
    QuadraticProbingHashTable   quadraticProbingTable;
    DoubleHashingHashTable      doubleHashingTable;


    cout << "Inserting keys into hash tables..." << endl;

    for (int key : keys) 
    {
        linearProbingTable.insert(key);
        openChainingTable.insert(key);

        quadraticProbingTable.insert(key);
        doubleHashingTable.insert(key);
    }

    cout << "Displaying hash tables..." << endl;

    linearProbingTable.display();
    openChainingTable.display();

    quadraticProbingTable.display();
    doubleHashingTable.display();

    // Find and remove keys in the hash tables
    int keyToFind = 47;
    cout << "Searching for key " << keyToFind << " in hash tables:" << endl;
    cout << "Linear Probing: " << (linearProbingTable.find(keyToFind) ? "Found" : "Not Found") << endl;
    cout << "Open Chaining: " << (openChainingTable.find(keyToFind) ? "Found" : "Not Found") << endl;

    cout << "Quadratic Probing: " << (quadraticProbingTable.find(keyToFind) ? "Found" : "Not Found") << endl;
    cout << "Double Hashing: " << (doubleHashingTable.find(keyToFind) ? "Found" : "Not Found") << endl;

    int keyToDelete = 37;
    cout << "Removing key " << keyToDelete << " from hash tables:" << endl;
    cout << "Linear Probing: " << (linearProbingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;
    cout << "Open Chaining: " << (openChainingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;

    cout << "Quadratic Probing: " << (quadraticProbingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;
    cout << "Double Hashing: " << (doubleHashingTable.remove(keyToDelete) ? "Removed" : "Not Found") << endl;

    cout << "Displaying updated hash tables..." << endl;

    linearProbingTable.display();
    openChainingTable.display();

    quadraticProbingTable.display();
    doubleHashingTable.display();

    int numberOfKeys = sizeof(keys) / sizeof(keys[0]); // Calculate the number of keys inserted
    float loadFactor = static_cast<float>(numberOfKeys) / TABLE_SIZE; // Correct load factor calculation
    cout << "The load factor is " << loadFactor << endl;


    return 0;
}



