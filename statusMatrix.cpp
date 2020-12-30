#include <iostream>
#include <vector>
#include <iomanip>
#include <time.h>

using namespace std;
int col = 4;
int row = 1;
vector<vector<int>> vec(row , {0, 0});
int medicineID, amount, day, user;
string medicine[5] = {"Acyclovir - 0, ", "Codeine - 1, ","Diclofenac - 2, ","Getitinib - 3, ","Hydroxyurea - 4"};
float priceTab[5] = {0.72, 0.7, 1.09, 271.37, 0.78};
int stored [5] = {80000, 300000, 150000, 10000, 40000};
vector<int> days;

//array including all the mistakes
    int mistakes[5];
    int lost[5];
    float percent[5];

void printmedication( vector<vector<int>> vec){
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            cout << vec[i][j] << " ";
        }
        cout<< endl;
    }
};

void inventory(int medicineID, int amount){
    stored[medicineID] -= amount;
};

vector<vector<int>> addrow(vector<vector<int>> vec, string cont){
    vector<int> add{};
    while (cont.compare("y") == 0){
        cout << "Medication: ";
        cin >> medicineID;
        cout << "Amount: ";
        cin >> amount;
        cout << "Day: ";
        cin >> day; 
        cout << "Patient: ";
        cin >> user;
        add.push_back(medicineID);
        add.push_back(amount);
        add.push_back(day);
        days.push_back(day);
        add.push_back(user);

        vec.push_back(add);
        inventory(medicineID, amount);
        printmedication(vec);
        add.pop_back(); add.pop_back(); add.pop_back(); add.pop_back();
        row += 1;
        cout << "Continue? (y/n)";
        cin >> cont;
    };
    if(cont.compare("n") == 0){return vec;};
    return vec;
};


void missing(){
    
    copy(begin(stored), end(stored), begin(mistakes));
    for (int z = 0; z < (sizeof(mistakes)/sizeof(*mistakes)); z++){
        int gone = rand() % 1000;
        lost[z] = gone;
        mistakes[z] -= gone;
        percent[z] = (float(stored[z]) - float(mistakes[z]))/float(mistakes[z]);
        cout << setprecision(3) << fixed << percent[z] << " ";
    };
    
};

int trustlevel(){
    float max = 0.0;
    int level[5] = {0, 1, 2, 3, 4};
    for (int i = 0; i < (sizeof(level)/sizeof(*level)); i++){
        if(max <= percent[i]){max = percent[i];};
    };
    if (max == 0){return 4;}
    else if (max <= 0.05){return 3;}
    else if (max <= 0.10){return 2;}
    else if (max <= 0.15){return 1;}
    else if (max > 0.15){return 0;}
    return 15;
};

int restock(vector<vector<int>> total){
//determine when to restock by recognizing patterns and projecting when more is needed.- ML application. 
//use slope (best line fit) to find when to buy. y = mx + b
    //missing / in stock
    int entry;
    cout << "Which entry needs restock calculation? ";
    cin  >> entry;
    int set = days[entry - 1];
    int setMed = total[entry - 1][0];
    int sum = 0;
    int count;

    //cout<<days.size();
    for (int i = 0; i < days.size(); i++)
        {  

            if (days[i] == set && total[i][0] == setMed){
                sum += total[i][1];
            };
        };
    cout << sum << endl;
    int when = 0.75 * stored[setMed];
    cout << when<< endl;
    count = when / sum;
    cout << "How many days will pass before restock needed: " << count;
    cout << endl;
    return count;
};
//plot time as x variable and storage as time goes on



int budget(){

};

int main() {
    for (int z = 0; z < (sizeof(medicine)/sizeof(*medicine)); z++){cout << medicine[z];};

    string cont = "y";
    cout << "\n";
    cout << "Medication: ";
    cin >> medicineID;
    cout << "Amount: ";
    cin >> amount;
    cout << "Day: ";
    cin >> day; 
    cout << "Patient: ";
    cin >> user;
    days.push_back(day);
    inventory(medicineID, amount);

    vector<vector<int>> vec( row , {medicineID, amount, day, user});
    printmedication(vec);
    row += 1;
    cout << "Continue? (y/n) ";
    cin >> cont;
    vector<vector<int>> total = addrow(vec, cont);
    srand(time(0)); //uses current time to seed the random number gen
    
    missing();
    cout << "\n" << "Expected Storage: " ;
    for (int z = 0; z < (sizeof(stored)/sizeof(*stored)); z++){
        cout << stored[z] << " ";
    };
    cout << "\n" << "Actual: " ;
    for (int z = 0; z < (sizeof(mistakes)/sizeof(*mistakes)); z++){
        cout << mistakes[z] << " ";
    };
    cout << "\n" << "Lost: " ;
    for (int i = 0; i < (sizeof(lost)/sizeof(*lost)); i++){
        cout << lost[i] << " ";
    };
    cout << " \n";
    cout << "Trust level: " << trustlevel() << endl;
    restock(total);
    printmedication(total);

    return 0;
}