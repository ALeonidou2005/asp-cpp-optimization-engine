#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <dlfcn.h>  // For dynamic library loading
using namespace std;

typedef vector <int> vi;
typedef pair <int,int> ii;
#define F first
#define S second

#define MONDAY 1
#define SUNDAY 7

//---------------------------------------DLL DEFINITIONS--------------------------------------------
typedef void (*schedulerFunc)(int, int, int, int*, int*, int*, int*, int*);

typedef void(*DbgFuncCallBack)(const char* message, int message_type, int size);
static DbgFuncCallBack dbgCallbackInstance = nullptr;

typedef void (*runningInUnityFunc)(DbgFuncCallBack);

typedef void (*testDbgFunc)(int);

typedef void(*sendValFuncCallBack)(int val, const char* key, int key_size);
static sendValFuncCallBack sendIntCallBackInstance = nullptr, sendFloatCallBackInstance = nullptr, sendBoolCallBackInstance = nullptr;
typedef void(*sendStringFuncCallBack)(const char* mes, int mes_size, const char* key, int key_size);

typedef void (*initialize_direct_data_transmission_Func)(sendValFuncCallBack, sendValFuncCallBack, sendValFuncCallBack, sendStringFuncCallBack);
void receiveInt(int val, const char* c_key, int key_size) {
    string key(c_key, key_size);
    cout << "receiveInt() Callback" << endl;
    cout << "Val: " << val << endl;
    cout << "Key: " << key << endl;
    cout << "Key Size: " << key_size << endl;
    cout<<endl;
}
void receiveBool(int val, const char* c_key, int key_size) {
    string key(c_key, key_size);
    bool bool_val = (val != 0);
    cout << "receiveBool() Callback" << endl;
    cout << "Val: " << val << endl;
    cout << "Key: " << key << endl;
    cout << "Key Size: " << key_size << endl;
    cout<<endl;
}
void receiveFloat(int floatBits, const char* c_key, int key_size) {
    string key(c_key, key_size);
    if (sizeof(float) != sizeof(int)){
        cout<<endl<<"ERROR: Cannot Convert Float - (Incompatible variable sizes => int to float)"<<endl;
        return;
    }
    float val;
    memcpy(&val, &floatBits, sizeof(int)); // Copy float bits into int
    cout << setprecision(5) << "receiveFloat() Callback" << endl;
    cout << "Val: " << val << endl;
    cout << "Key: " << key << endl;
    cout << "Key Size: " << key_size << endl;
    cout<<endl;
}
void receiveString(const char* c_mes, int mes_size, const char* c_key, int key_size) {
    string mes(c_mes, mes_size);
    string key(c_key, key_size);
    cout << "receiveString() Callback" << endl;
    cout << "Mes: " << mes << endl;
    cout << "Mes Size: " << mes_size << endl;
    cout << "Key: " << key << endl;
    cout << "Key Size: " << key_size << endl;
    cout<<endl;
}
//----------------------------------------------------------------------------------------------------

int coordinate_to_number(const int i, const int j, const int J){
    return (i * J + j);
}

int int_representation_of_float(float float_val){
    int int_val;
    memcpy(&int_val, &float_val, sizeof(float)); // Copy float bits into int
    return int_val;
}

float float_representation_of_float(int int_val){
    float float_val;
    memcpy(&float_val, &int_val, sizeof(int)); // Copy float bits into int
    return float_val;
}

int main(const int argc, const char *argv[]){
//LINK DLL
    void* handle = dlopen("./scheduler.dylib", RTLD_LAZY);
    if (!handle){
        cout<<endl<<"ERROR: test.cpp - Failed to load library: "<< dlerror()<<endl;
        return 1;
    }
    schedulerFunc run_scheduler = (schedulerFunc)dlsym(handle, "run_scheduler");
    if (!run_scheduler){
        cout<<endl<<"ERROR: test.cpp - Failed to find function: "<<dlerror()<<endl;
        return 1;
    }
    runningInUnityFunc runningInUnity = (runningInUnityFunc)dlsym(handle, "runningInUnity");
    if (!runningInUnity){
        cout<<endl<<"ERROR: test.cpp - Failed to find function: "<<dlerror()<<endl;
        return 1;
    }
    testDbgFunc testDbg = (testDbgFunc)dlsym(handle, "testDebugFunction");
    if (!testDbg){
        cout<<endl<<"ERROR: test.cpp - Failed to find function: "<<dlerror()<<endl;
        return 1;
    }
    initialize_direct_data_transmission_Func initialize_direct_data_transmission = (initialize_direct_data_transmission_Func)dlsym(handle, "initialize_direct_data_transmission");
    if (!initialize_direct_data_transmission){
        cout<<endl<<"ERROR: test.cpp - Failed to find function: "<<dlerror()<<endl;
        return 1;
    }

    testDbg(2);

    initialize_direct_data_transmission(receiveInt, receiveBool, receiveFloat, receiveString);

    // TEST UNITY => No Logs when uncommented
    // runningInUnity(callbackInstance);

//INPUT
    string input_file_name = "input1.txt";
    if (argc > 1){
        string argv1 = argv[1];
        input_file_name = "input" + argv1 + ".txt";
    }
    cout<<"Input File Name: "<<input_file_name<<endl;

    ifstream input_file;
    string input_source = "tests/" + input_file_name;
    input_file.open(input_source);
    
    if (!input_file.is_open()){
        cout<<"ERROR: test.cpp - Input File not found!";
        return 1;
    }

    int people, days, first_day_type;
    input_file>>people>>days>>first_day_type;

    int user_restrictions_C[people * days];
    int user_people_day_type_duty_total_C[people * (SUNDAY+1)];
    int user_person_subunit_C[people];
    int user_settings_C[26] = {4, 100,100,100,1,2,2,2, 6,3,0,0,0, 1,1,1,1,1,1, 2000000,200000,1000000,2500,int_representation_of_float(0.9999), 3,1};
    int output_res_C[people * days];

    //user_restrictions input
    for (int person =0; person<people; person++){
        for (int day =0; day<days; day++){
            input_file>>user_restrictions_C[coordinate_to_number(person, day, days)];
        }
    }
    //user_people_day_type_duty_total input
    for (int person =0; person<people; person++){
        for (int d_type = MONDAY; d_type<=SUNDAY; d_type++){
            input_file>>user_people_day_type_duty_total_C[coordinate_to_number(person, d_type-1, SUNDAY)];
        }
    }
    //user_person_subunit input
    for (int person = 0; person < people; person++){
        input_file>>user_person_subunit_C[person];
    }

//PROCESSING
    cout<<endl<<"------------------------ENTERED SCHEDULER.CPP------------------------"<<endl<<endl;
    run_scheduler(people, days, first_day_type, user_restrictions_C, user_people_day_type_duty_total_C, user_person_subunit_C, user_settings_C, output_res_C);
    cout<<endl<<"-------------------------EXITED SCHEDULER.CPP------------------------"<<endl;

//OUTPUT
    cout<<endl<<endl<<"test.cpp - OUTPUT"<<endl;
    for (int person =0; person<people; person++){
        cout<<person%10<<": ";
        for (int day =0; day<days; day++){
            cout<<output_res_C[coordinate_to_number(person, day, days)]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

//UNLINK DLL
    dlclose(handle);

    return 0;
}