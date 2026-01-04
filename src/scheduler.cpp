#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cassert>
#include <random>
#include <algorithm>
#include <chrono>
#include <climits>
#include <set>
#include <map>
#include <iomanip>
#include <cstdio>
#include <stdexcept>
#include <tuple>
#include <string>
#include <cstring>
#ifdef _WIN32
    #include <windows.h> // For Windows DLL support
#endif

using namespace std;

#define DLL_VERSION "3.0.10"     //FORMAT: (Major Version Number, Minor Version Number, Backup Idx Number)
#define DLL_COMPILATION_DATE "09/05/2025"

#define ll long long
#define ld long double
#define F first
#define S second
#define pb push_back
#define ins insert
#define sz(x) (ll)x.size()
#define inf 1000000000

typedef vector <ll> vi;
typedef pair <ll,ll> ii;
typedef vector <ii> vii;

template<typename T>void printArr(T *arr,ll l,ll m=0){if(m==1){for(ll i=0;i<l;i++)cout<<arr[i]<<" ";cout<<endl;}else{cout<<endl;for(ll i=0;i<l;i++)cout<<i<<": "<<arr[i]<<endl;}}
#define printArr2D(arr,n,m)cout<<endl;for(ll i=0;i<n;i++){for(ll j=0;j<m;j++)cout<<arr[i][j]<<" ";cout<<endl;}cout<<endl;
template<typename T>void printVct(vector<T> v,ll m=0){if(m==1){for(ll i=0;i<sz(v);i++)cout<<v[i]<<" ";cout<<endl;}else{cout<<endl;for(ll i=0; i<sz(v);i++)cout<<i<<": "<<v[i]<<endl;}}
template<typename T>void printVct2D(vector<vector<T> >v){cout<<endl;for(ll i=0;i<sz(v);i++){cout<<i<<": ";for(ll j=0;j<sz(v[i]);j++)cout<<v[i][j]<<" ";cout<<endl;}}
template<typename T>void printVctPair(vector<T> v,ll m=0){if(m==1){for(ll i=0;i<sz(v);i++)cout<<v[i].F<<":"<<v[i].S<<" ";cout<<endl;}else{cout<<endl;for(ll i=0;i<sz(v);i++)cout<<i<<":  "<<v[i].F<<" : "<<v[i].S<<endl;}}
template<typename T>void printVctPair2D(vector<vector<T> >v){cout<<endl;for(ll i=0;i<sz(v);i++){cout<<i<<": ";for(ll j=0;j<sz(v[i]);j++)cout<<v[i][j].F<<":"<<v[i][j].S<<" ";cout<<endl;}}
template<typename T>void printVctPair3(vector<T> v,ll m=0){cout<<endl;for(ll i=0;i<sz(v);i++)cout<<i<<": ("<<v[i].F<<" : "<<v[i].S.F<<" : "<<v[i].S.S<<")"<<endl;}
template<typename T1,typename T2>void printMap(map<T1,T2>mp){cout<<endl;for(typename map<T1,T2>::iterator it=mp.begin();it!=mp.end();it++)cout<<it->F<<" -> "<<it->S<<endl;}
template<typename T>void printSet(set<T>st,ll m=0){typename set<T>::iterator it;if(m){for(it=st.begin();it!=st.end();it++)cout<<*it<<" ";cout<<endl;}else{cout<<endl;for(it=st.begin();it!=st.end();it++)cout<<*it<<endl;}}
void check(ll n){cout<<"CHECKPOINT "<<n<<"\n\n";}
#define dbg(x) cout<<#x<<":"<<x<<endl
#define dbg2(x,y) cout<<#x<<":"<<x<<"  "<<#y<<":"<<y<<endl
#define dbg3(x,y,z) cout<<#x<<":"<<x<<"  "<<#y<<":"<<y<<"  "<<#z<<":"<<z<<endl
#define dbg4(x,y,z,w) cout<<#x<<":"<<x<<"  "<<#y<<":"<<y<<"  "<<#z<<":"<<z<<"  "<<#w<<":"<<w<<endl
#define dbg5(x,y,z,w,v) cout<<#x<<":"<<x<<"  "<<#y<<":"<<y<<"  "<<#z<<":"<<z<<"  "<<#w<<":"<<w<<"  "<<#v<<":"<<v<<endl
#define dbg6(x,y,z,w,v,u) cout<<#x<<":"<<x<<"  "<<#y<<":"<<y<<"  "<<#z<<":"<<z<<"  "<<#w<<":"<<w<<"  "<<#v<<":"<<v<<"  "<<#u<<":"<<u<<endl
#define dbgp(x) cout<<#x<<":("<<x.F<<" "<<x.S<<")"<<endl
#define dbgp2(x,y) cout<<#x<<":("<<x.F<<","<<x.S<<")  "<<#y<<":("<<y.F<<","<<y.S<<")"<<endl
#define dbgt(x) cout<<#x<<":("<<x.F<<" "<<x.S.F<<" "<<x.S.S<<")"<<endl
#define dbgt2(x,y) cout<<#x<<":("<<x.F<<" "<<x.S.F<<" "<<x.S.S<<")  "<<#y<<":("<<y.F<<" "<<y.S.F<<" "<<y.S.S<<")"<<endl

#ifdef _WIN32
    #define RESET_TEXT ""
    #define BOLD_TEXT ""
    #define YELLOW_TEXT ""
    #define RED_TEXT ""
    #define GREEN_TEXT ""
    #define BLUE_TEXT ""
    #define PURPLE_TEXT ""
    #define CYAN_TEXT ""
    #define GREY_TEXT ""
#else
    #define RESET_TEXT "\x1b[0m"
    #define BOLD_TEXT "\x1b[1m"
    #define YELLOW_TEXT "\x1b[33m"
    #define RED_TEXT "\x1b[31m"
    #define GREEN_TEXT "\x1b[32m"
    #define BLUE_TEXT "\x1b[34m"
    #define PURPLE_TEXT "\x1b[35m"
    #define CYAN_TEXT "\x1b[36m"
    #define GREY_TEXT "\x1b[30m"
#endif

void printVct(vi &v){
    for (ll i=0; i<sz(v); i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int int_representation_of_float(float float_val){
    int int_val;
    memcpy(&int_val, &float_val, sizeof(float)); // Copy float bits into int
    return int_val;
}

float float_representation_of_int(int int_val){
    float float_val;
    memcpy(&float_val, &int_val, sizeof(int)); // Copy float bits into int
    return float_val;
}

int coordinate_to_number(const int i, const int j, const int J){
    return (i * J + j);
}

// --------------------------------------- RANDOM GENERATOR TEMPLATE ---------------------------------------

class RandomGenerator{
private:
    static const ll N = 200000;
    mt19937 rng;

    void applyTreeIndexOffset(vii &edges, ll index_offset){
        for (ll i = 0; i<sz(edges); i++){
            edges[i].F += index_offset;
            edges[i].S += index_offset;
        }
    }

public:
    RandomGenerator(){
        rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    }

    //------VALUES------

    ll getNum(ll l, ll r){	// l<=x<=r
        if (l > r){ cout<<endl<<"ERROR: RandomGenerator.genNum: Invalid Input (l: "<<l<<" r:"<<r<<")"<<endl; return LLONG_MIN;};
        return ((rng() % (abs(r-l)+1)) + l);
    }

    //------ARRAYS------

    vi getArr(ll n, ll l, ll r){
        if (l > r || n < 0 || n > N) { cout<<"ERROR: RandomGenerator.genArr: Invalid Input (n:"<<n<<" l:"<<l<<" r:"<<r<<")"<<endl; return vi();}
        vi ans(n);
        for (ll i =0; i<n; i++)
            ans[i] = getNum(l,r);
        return ans;
    }

    vi getPermutation(ll n, ll index_offset = 0){
        if (n < 0) { cout<<"ERROR: RandomGenerator.getPermutation: Invalid Input (n:"<<n<<" index_offset:"<<index_offset<<")"<<endl; return vi();}
        vi v(n);
        for (ll i=0; i<n; i++) v[i] = i + index_offset;
        shuffle(v.begin(), v.end(), rng);
        return v;
    }
};

RandomGenerator rnd;
   
// --------------------------------------- ERROR HANDLING & DEBUGGING --------------------------------------

#define SUCCESS_ENABLED 1
#define LOG_ENABLED 1
#define WARNING_ENABLED 1
#define ERROR_ENABLED 1

//Unity Debug Support
#define UNITY_LOG 1
#define UNITY_WARNING 2
#define UNITY_ERROR 3

typedef void(*DbgFuncCallBack)(const char* message, int message_type, int size);
static DbgFuncCallBack dbgCallbackInstance = nullptr;
bool running_in_unity = false;

class debug{
private:

    template<typename T> void print_message(const string message_type, const string text_format, const string s1, const T num1, const string s2, const T num2, const string s3, const T num3){
        cout<<text_format;

        //"bullet-point" VS "message_type" logic
        if (message_type == "•"){
            cout<<" "<<message_type<<" ";
        }
        else{
            cout<<message_type<<": ";
        }

        //print
        if (num1 == -inf) cout<<s1<<endl;
        else if (num2 == -inf) cout<<s1<<" "<<num1<<endl;
        else if (num3 == -inf) cout<<s1<<" "<<num1<<"  "<<s2<<" "<<num2<<endl;
        else cout<<s1<<" "<<num1<<"  "<<s2<<" "<<num2<<"  "<<s3<<" "<<num3<<endl;
        cout<<RESET_TEXT;
        cout.flush();
    }

    template<typename T> void print_unity_message(const int message_unity_type, const string s1, const T num1, const string s2, const T num2, const string s3, const T num3){
        if (dbgCallbackInstance == nullptr){   //SHOULD BE IMPOSSIBLE => ERROR => SOMETHING WENT WRONG WITH COMMUNICATION?
            if (ERROR_ENABLED){
                print_message("ERROR: ", RED_TEXT, "print_unity_message() : callbackInstance is NULL => Something went wrong with communication", -inf, "", -inf, "", -inf);
            }
            return;    
        } 
        
        string mes = s1;
        if (num1 != -inf){
            mes += " ";
            mes += to_string(num1);
        }
        if (num2 != -inf){
            mes += " ";
            mes += s2;
            mes += to_string(num2);
        }
        if (num3 != -inf){
            mes += " ";
            mes += s3;
            mes += to_string(num3);
        }

        const char* c_mes = mes.c_str();
        // dbg3(c_mes, message_unity_type, mes.size());
        dbgCallbackInstance(c_mes, static_cast<int>(message_unity_type), static_cast<int>(mes.size()));
    }

public: 
    ll log_decimal_places = 2;
    debug(){
        cout<<fixed<<setprecision(log_decimal_places);
    }
    void setPrecision(ll p = 2){
        log_decimal_places = p;
        cout<<fixed<<setprecision(log_decimal_places);
    }
    void new_line(ll x = 1){
        for (ll i = 0; i < x; i++){
            cout<<"\n";
        }
    }
    template<typename T = ll> void success(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!SUCCESS_ENABLED) return;
        if (!running_in_unity) print_message("LOG", GREEN_TEXT, s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_LOG, s1, num1, s2, num2, s3, num3);
    }
    template<typename T = ll> void log(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!LOG_ENABLED) return;
        if (!running_in_unity) print_message("LOG", BLUE_TEXT, s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_LOG, s1, num1, s2, num2, s3, num3);
    }
    template<typename T = ll> void bullet_log(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!LOG_ENABLED) return;
        if (!running_in_unity) print_message("•", BLUE_TEXT, s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_LOG, " • " + s1, num1, s2, num2, s3, num3);
    }
    template<typename T = ll> void warning(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!WARNING_ENABLED) return;
        if (!running_in_unity) print_message("WARNING", YELLOW_TEXT, s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_WARNING, s1, num1, s2, num2, s3, num3);
    }
    template<typename T = ll> void error(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!ERROR_ENABLED) return;
        if (!running_in_unity) print_message("ERROR", RED_TEXT, s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_ERROR, s1, num1, s2, num2, s3, num3);
    }
    template<typename T = ll> void fatal_error(string s1, T num1 = -inf, string s2 = "", T num2 = -inf, string s3 = "", T num3 = -inf){
        if (!ERROR_ENABLED) return;
        string text_format = RED_TEXT; text_format += BOLD_TEXT;
        if (!running_in_unity) print_message("* FATAL ERROR", text_format , s1, num1, s2, num2, s3, num3);
        else print_unity_message(UNITY_ERROR, s1, num1, s2, num2, s3, num3);
        throw runtime_error("Called dbg.fatal_error()");
    }
    template<typename T = ll> void vector1D(string s, const vector<T> &v){
        if (!LOG_ENABLED) return;
        if (!running_in_unity){
            cout<<BLUE_TEXT<<"LOG: "<<s;
            for (ll i =0; i<sz(v); i++) cout<<v[i]<<" ";
            cout<<RESET_TEXT<<endl;
        }
        else{
            string dbg_string = s;
            dbg_string += ": \n";
            for (ll i =0; i<sz(v); i++){
                dbg_string += to_string(v[i]);
                dbg_string += " ";
            }
            log(dbg_string);
        }
    }
    void vector2D(string s, const vector <vi> v, bool colorOnesGreen = false){
        if (!running_in_unity){
            cout<<endl<<BOLD_TEXT<<s<<": "<<RESET_TEXT<<endl;
            cout<<BOLD_TEXT<<BLUE_TEXT<<"  ";
            for (ll j =0; j<sz(v[0]); j++){
                cout<<j%10<<" ";
            }
            cout<<RESET_TEXT<<endl;
            for (ll i =0; i<sz(v); i++){
                cout<<BLUE_TEXT<<BOLD_TEXT<<i%10<<" "<<RESET_TEXT;
                for (ll j =0; j<sz(v[i]); j++){
                    if (colorOnesGreen && v[i][j] == 1) cout<<PURPLE_TEXT;
                    cout<<v[i][j]<<" "<<RESET_TEXT;
                }
                cout<<endl;
            }
            cout<<endl;
        }
        else{
            string dbg_string = s;
            dbg_string += ": \n";
            for (ll i =0; i<sz(v); i++){
                dbg_string += to_string(i);
                dbg_string += ": ";
                for (ll j = 0; j<sz(v[i]); j++){
                    dbg_string += to_string(v[i][j]);
                    dbg_string += " ";
                }
                dbg_string += "\n";
            }
            log(dbg_string);
        }

    }
};
debug dbg;

// ------------------------------------- DLL DIRECT DATA TRANSMISSION --------------------------------------

typedef void(*sendValFuncCallBack)(int val, const char* key, int key_size);
static sendValFuncCallBack sendIntCallBackInstance = nullptr, sendFloatCallBackInstance = nullptr, sendBoolCallBackInstance = nullptr;
typedef void(*sendStringFuncCallBack)(const char* mes, int mes_size, const char* key, int key_size);
static sendStringFuncCallBack sendStringCallBackInstance = nullptr;

class direct_data_transmission{
    private:
    bool direct_data_transmission_initialized = false;
    public:
    void sendInt(int val, string key){
        if (sendIntCallBackInstance == nullptr){
            dbg.warning("direct_data_transmission(): sendInt(): sendIntCallBackInstance is NULL => (Failed to send data)");
            return;
        }
        const char* c_key = key.c_str();
        sendIntCallBackInstance(static_cast<int>(val), c_key, static_cast<int>(key.size()));
    }
    void sendBool(bool val, string key){
        if (sendBoolCallBackInstance == nullptr){
            dbg.warning("direct_data_transmission(): sendBool(): sendBoolCallBackInstance is NULL => (Failed to send data)");
            return;
        }
        int int_val = val;
        const char* c_key = key.c_str();
        sendBoolCallBackInstance(static_cast<int>(int_val), c_key, static_cast<int>(key.size()));
    }
    void sendFloat(float val, string key){
        if (sendFloatCallBackInstance == nullptr){
            dbg.warning("direct_data_transmission(): sendFloat(): sendFloatCallBackInstance is NULL => (Failed to send data)");
            return;
        }
        const char* c_key = key.c_str();
        int floatBits = int_representation_of_float(val);
        sendFloatCallBackInstance(static_cast<int>(floatBits), c_key, static_cast<int>(key.size()));
    }
    void sendString(string mes, string key){
        if (sendStringCallBackInstance == nullptr){
            dbg.warning("direct_data_transmission(): sendString(): sendStringCallBackInstance is NULL => (Failed to send data)");
            return;
        }
        const char* c_mes = mes.c_str();
        const char* c_key = key.c_str();
        sendStringCallBackInstance(c_mes, static_cast<int>(mes.size()), c_key, static_cast<int>(key.size()));
    }
};
direct_data_transmission ddt;

// --------------------------------------------- MAIN PROGRAM ----------------------------------------------

//Definitions
#define RED 0
#define ORANGE 4
#define WHITE 1
#define LIGHT_GREEN 3
#define GREEN 2

#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6
#define SUNDAY 7

#define NUMBER_OF_SUBUNITS 3

#define SETTINGS_ARRAY_SIZE 26

class ConstantSettingsClass {
    private:
        vi settingsVector;

        const ll MAX_MONDAYS;
        const ll MAX_TUESDAYS;
        const ll MAX_WEDNESDAYS;
        const ll MAX_THURSDAYS;
        const ll MAX_FRIDAYS;
        const ll MAX_SATURDAYS;
        const ll MAX_SUNDAYS;

        const ll MIN_SUBUNIT_LBO;
        const ll MIN_SUBUNIT_LAT;
        const ll MIN_SUBUNIT_LD;

        float SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT;

    public:
        const bool const_is_float[SETTINGS_ARRAY_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0};

        const ll DUTIES_PER_DAY;
        const ll MAX_PERSON_TOTAL;
        const ll MAX_PSK;

        const ll DUTY_TOTAL_BALANCE_ENABLED;
        const ll DUTY_PSK_BALANCE_ENABLED;
        const ll DUTY_PSK_VARIETY_BALANCE_ENABLED;
        const ll ORANGE_AVOIDANCE_ENABLED;
        const ll LIGHT_GREEN_PREFERENCE_ENABLED;
        const ll DUTY_SPREAD_ENABLED;

        const ll MIN_PEOPLE_FOR_SUBUNIT[NUMBER_OF_SUBUNITS];
        const ll MAX_FOR_DAY_TYPE[8];

        const ll SCHEDULE_INITIALIZATION_MAX_ATTEMPTS;
        const ll SCHEDULE_OPTIMIZATION_REPETITIONS;
        const ll SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS;

        const ll ATTEMPT_MIN_PERSON_TOTAL;
        const ll ATTEMPT_MIN_PSK; 

        const ll SA_MAX_TEMPERATURE;
        const ll SA_GEOMETRIC_COOLING_BASE_CONSTANT_INT;

        ConstantSettingsClass(int v[SETTINGS_ARRAY_SIZE]) : 
        DUTIES_PER_DAY(v[0]),
        MAX_MONDAYS(v[1]),
        MAX_TUESDAYS(v[2]),
        MAX_WEDNESDAYS(v[3]),
        MAX_THURSDAYS(v[4]),
        MAX_FRIDAYS (v[5]),
        MAX_SATURDAYS (v[6]),
        MAX_SUNDAYS (v[7]),
        MAX_PERSON_TOTAL(v[8]),
        MAX_PSK (v[9]),
        MIN_SUBUNIT_LBO(v[10]),
        MIN_SUBUNIT_LAT(v[11]),
        MIN_SUBUNIT_LD(v[12]),
        DUTY_TOTAL_BALANCE_ENABLED (v[13]),
        DUTY_PSK_BALANCE_ENABLED (v[14]),
        DUTY_PSK_VARIETY_BALANCE_ENABLED (v[15]),
        ORANGE_AVOIDANCE_ENABLED (v[16]),
        LIGHT_GREEN_PREFERENCE_ENABLED (v[17]),
        DUTY_SPREAD_ENABLED (v[18]),
        SCHEDULE_INITIALIZATION_MAX_ATTEMPTS(v[19]),
        SCHEDULE_OPTIMIZATION_REPETITIONS(v[20]),
        SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS(v[21]),
        SA_MAX_TEMPERATURE(v[22]),
        SA_GEOMETRIC_COOLING_BASE_CONSTANT_INT(v[23]),
        ATTEMPT_MIN_PERSON_TOTAL(v[24]),
        ATTEMPT_MIN_PSK(v[25]),
        MIN_PEOPLE_FOR_SUBUNIT{MIN_SUBUNIT_LBO, MIN_SUBUNIT_LAT, MIN_SUBUNIT_LD},
        MAX_FOR_DAY_TYPE{-1, MAX_MONDAYS, MAX_TUESDAYS, MAX_WEDNESDAYS, MAX_THURSDAYS, MAX_FRIDAYS, MAX_SATURDAYS, MAX_SUNDAYS}
        { 
            //init settingsVector
            settingsVector.resize(SETTINGS_ARRAY_SIZE);
            for (ll i = 0; i < SETTINGS_ARRAY_SIZE; i++){
                settingsVector[i] = v[i];
            }
            
            //init SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT
            SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT = float_representation_of_int(SA_GEOMETRIC_COOLING_BASE_CONSTANT_INT);
        }

        void dbgSettings(){
            dbg.vector1D("ConstantsSettings: ", settingsVector);
        }

        vi getSettingsVector(){
            return settingsVector;
        }

        float get_SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT(){
            return SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT;
        }

        /*
        settings format:
        0. Duties Per Day

        1. Max Mondays
        2. Max Tuesdays
        3. Max Wednsedays
        4. Max Thursdays
        5. Max Fridays
        6. Max Saturdays
        7. Max Sundays

        8. Max Person Total
        9. Max PSK
        10. MIN_SUBUNIT_LBO
        11. MIN_SUBUNIT_LAT
        12. MIN_SUBUNIT_LD

        13. DUTY_TOTAL_BALANCE_ENABLED
        14. DUTY_PSK_BALANCE_ENABLED
        15. DUTY_PSK_VARIETY_BALANCE_ENABLED
        16. ORANGE_AVOIDANCE_ENABLED
        17. LIGHT_GREEN_PREFERENCE_ENABLED
        18. DUTY_SPREAD_ENABLED

        19. Schedule Initialization Max Attempts
        20. Schedule Optimization Repetitions
        21. Schedule Neighbour Finding Max Attempts
        22. SA Max Temperature (Initial Temperature)
        23. SA Geometric Cooling Base Constant (constant "a")

        24. Min Total Duties
        25. Min Psk
        */
};  
ConstantSettingsClass* ConstantSettings = nullptr;

class RunStatsClass{
    public:

    //initialization stats
    ll initialization_failed_attempts = -1;
    ll max_day_reached = -1;
    bool successful_initialization = false;

    //optimization stats
    ll optimization_reps = 0;
    ll max_neighbour_finding_failed_attempts = -1;
    ld avg_neighbour_finding_failed_attempts = -1;
    bool successfully_found_all_neighbours = false;

    //evaluation stats
    bool SA_fixed_parameters_are_fully_met = false;
    ld initial_penalty = -1;
    ld final_penalty = -1;
    
    //time stats
    ld schedule_initialization_duration = -1;
    ld schedule_optimization_duration = -1;
    ld full_duration = -1;

    //helper stats (not sent)
    long long total_neighbour_finding_failed_attempts = 0;

    void resetStats(){
        initialization_failed_attempts = -1;
        max_day_reached = -1;
        successful_initialization = false;
        optimization_reps = 0;
        max_neighbour_finding_failed_attempts = -1;
        avg_neighbour_finding_failed_attempts = -1;
        successfully_found_all_neighbours = false;
        SA_fixed_parameters_are_fully_met = false;
        initial_penalty = -1;
        final_penalty = -1;
        schedule_initialization_duration = -1;
        schedule_optimization_duration = -1;
        full_duration = -1;
        total_neighbour_finding_failed_attempts = 0;
    }

    void logEssentialStats(){
        dbg.setPrecision(2);
        dbg.new_line(2);
        dbg.log(" ------- CURRENT RUN STATS -------");

        dbg.new_line();
        dbg.log("Program Essential Stats");
        dbg.bullet_log("initialization_failed_attempts:",initialization_failed_attempts);
        dbg.bullet_log("initial_penalty:",initial_penalty);
        dbg.bullet_log("final_penalty:",final_penalty);

        dbg.setPrecision(5);
        dbg.new_line();
        dbg.log("Time Stats");
        dbg.bullet_log("schedule_initialization_duration:",schedule_initialization_duration);
        dbg.bullet_log("schedule_optimization_duration:",schedule_optimization_duration);
        dbg.bullet_log("full_duration:",full_duration);
        dbg.new_line(2);

        dbg.setPrecision();
    }

    void logAllStats(){
        dbg.setPrecision(2);
        dbg.new_line(2);
        dbg.log(" ------- CURRENT RUN STATS -------");

        dbg.new_line();
        dbg.log("Initialization Stats");
        dbg.bullet_log("initialization_failed_attempts:",initialization_failed_attempts);
        dbg.bullet_log("max_day_reached:",max_day_reached);
        dbg.bullet_log("successful_initialization:",(int)successful_initialization);

        dbg.new_line();
        dbg.log("Optimization Stats");
        dbg.bullet_log("optimization_reps:",optimization_reps);
        dbg.bullet_log("max_neighbour_finding_failed_attempts:",max_neighbour_finding_failed_attempts);
        dbg.bullet_log("avg_neighbour_finding_failed_attempts:",avg_neighbour_finding_failed_attempts);
        dbg.bullet_log("successfully_found_all_neighbours:",(int)successfully_found_all_neighbours);

        dbg.new_line();
        dbg.log("Evaluation Stats");
        dbg.bullet_log("SA_fixed_parameters_are_fully_met:",(int)SA_fixed_parameters_are_fully_met);
        dbg.bullet_log("initial_penalty:",initial_penalty);
        dbg.bullet_log("final_penalty:",final_penalty);

        dbg.setPrecision(5);
        dbg.new_line();
        dbg.log("Time Stats");
        dbg.bullet_log("schedule_initialization_duration:",schedule_initialization_duration);
        dbg.bullet_log("schedule_optimization_duration:",schedule_optimization_duration);
        dbg.bullet_log("full_duration:",full_duration);
        dbg.new_line(2);

        dbg.setPrecision();
    }

    void sendAllStats(){
        ddt.sendInt(initialization_failed_attempts,"initialization_failed_attempts");
        ddt.sendInt(max_day_reached,"max_day_reached");
        ddt.sendBool(successful_initialization,"successful_initialization");

        ddt.sendInt(optimization_reps,"optimization_reps");
        ddt.sendInt(max_neighbour_finding_failed_attempts,"max_neighbour_finding_failed_attempts");
        ddt.sendFloat(avg_neighbour_finding_failed_attempts,"avg_neighbour_finding_failed_attempts");
        ddt.sendBool(successfully_found_all_neighbours,"successfully_found_all_neighbours");

        ddt.sendBool(SA_fixed_parameters_are_fully_met, "SA_fixed_parameters_are_fully_met");
        ddt.sendFloat(initial_penalty,"initial_penalty");
        ddt.sendFloat(final_penalty,"final_penalty");

        ddt.sendFloat(schedule_initialization_duration,"schedule_initialization_duration");
        ddt.sendFloat(schedule_optimization_duration,"schedule_optimization_duration");
        ddt.sendFloat(full_duration,"full_duration");
    }
};
RunStatsClass runStats;

//global user input data (WARNING: DO NOT EDIT AFTER INITIALIZATION)
ll days, people, first_day_type;                //input
vi day_type;                                    //calculated
vector <string> day_type_word;                  //calculated

vector <vi> user_restrictions;                  //input

vector <vi> user_people_day_type_duty_total;    //input
vi user_people_duty_total;                      //calculated
vi user_people_psk_duty_total;                  //calculated

ld ideal_people_duty_total;                     //calculated
ld ideal_people_psk_duty_total;                 //calculated
vector <ld> ideal_people_day_type_duty_total;

vi user_person_subunit;

//------------------------------------------------------------------

struct schedule{
    vi total_psk, total_duties;
    vector <vi> total_for_day_type;
    vector <vi> current_restrictions; //no consecutive, if thursday no psk, no red, 100% green
    vector <vi> res;
    vector <vi> day_total_subunit_duties; //total subunit duties currently in 'res' for each day
    schedule(){
        res.assign(people, vi(days));
        current_restrictions = user_restrictions;
        total_psk.assign(people, 0);
        total_for_day_type.assign(people, vi(SUNDAY+1, 0));
        total_duties.assign(people, 0);
        day_total_subunit_duties.assign(days, vi(NUMBER_OF_SUBUNITS,0));
    }

    void print_current_restrictions(){
        cout<<endl<<BOLD_TEXT<<"Current Restrictions:"<<RESET_TEXT<<endl;
        dbg.vector2D("current_restrictinos", current_restrictions);
    }

    void print_shedule(string s = ""){
        if (s == "") s += "Schedule";
        else s += " Schedule";
        dbg.vector2D(s, res, true);
    }
};

struct subunit_data_structure{
    ll total_remaining, total_restrictions_remaining;
    ll restrictions[NUMBER_OF_SUBUNITS];

    subunit_data_structure(){
        total_remaining = ConstantSettings->DUTIES_PER_DAY;
        total_restrictions_remaining = 0;
        for (ll subunit = 0; subunit < NUMBER_OF_SUBUNITS; subunit++){
            total_restrictions_remaining += ConstantSettings->MIN_PEOPLE_FOR_SUBUNIT[subunit];
            restrictions[subunit] = ConstantSettings->MIN_PEOPLE_FOR_SUBUNIT[subunit];
        }
    };

    bool can_add(ll subunit){
        return (total_restrictions_remaining - restrictions[subunit] < total_remaining);
    }

    void add(ll subunit){
        if (!can_add(subunit)) dbg.error("error");
        total_remaining--;
        if (restrictions[subunit]){
            restrictions[subunit]--;
            total_restrictions_remaining--;
        }
    }

    void print(){
        dbg2(total_remaining, total_restrictions_remaining);
        printArr(restrictions, NUMBER_OF_SUBUNITS, 1);
    }
};

void validate_program_settings(){
    //range checks
    if (ConstantSettings->DUTIES_PER_DAY <= 0){
        dbg.fatal_error("validate_program_settings() - Too small DUTIES_PER_DAY: ", ConstantSettings->DUTIES_PER_DAY);  
    }
    if (ConstantSettings->MAX_PERSON_TOTAL <= 0){
        dbg.fatal_error("validate_program_settings() - Too small MAX_PERSON_TOTAL: ", ConstantSettings->MAX_PERSON_TOTAL);  
    }
    if (ConstantSettings->MAX_PSK < 0){
        dbg.fatal_error("validate_program_settings() - Invalid MAX_PSK: ", ConstantSettings->MAX_PSK);  
    }
    if (ConstantSettings->SCHEDULE_INITIALIZATION_MAX_ATTEMPTS <= 0){
        dbg.fatal_error("validate_program_settings() - Too small SCHEDULE_INITIALIZATION_MAX_ATTEMPTS: ", ConstantSettings->SCHEDULE_INITIALIZATION_MAX_ATTEMPTS);  
    }
    if (ConstantSettings->SCHEDULE_OPTIMIZATION_REPETITIONS < 0){
        dbg.fatal_error("validate_program_settings() - Too small SCHEDULE_OPTIMIZATION_REPETITIONS: ", ConstantSettings->SCHEDULE_OPTIMIZATION_REPETITIONS);  
    }
    if (ConstantSettings->SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS <= 0){
        dbg.fatal_error("validate_program_settings() - Too small SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS: ", ConstantSettings->SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS);  
    }

    //bool format checks
    if (ConstantSettings->DUTY_TOTAL_BALANCE_ENABLED != 0 && ConstantSettings->DUTY_TOTAL_BALANCE_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid DUTY_TOTAL_BALANCE_ENABLED: ", ConstantSettings->DUTY_TOTAL_BALANCE_ENABLED);  
    }
    if (ConstantSettings->DUTY_PSK_BALANCE_ENABLED != 0 && ConstantSettings->DUTY_PSK_BALANCE_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid DUTY_PSK_BALANCE_ENABLED: ", ConstantSettings->DUTY_PSK_BALANCE_ENABLED);  
    }
    if (ConstantSettings->DUTY_PSK_VARIETY_BALANCE_ENABLED != 0 && ConstantSettings->DUTY_PSK_VARIETY_BALANCE_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid DUTY_PSK_VARIETY_BALANCE_ENABLED: ", ConstantSettings->DUTY_PSK_VARIETY_BALANCE_ENABLED);  
    }
    if (ConstantSettings->ORANGE_AVOIDANCE_ENABLED != 0 && ConstantSettings->ORANGE_AVOIDANCE_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid ORANGE_AVOIDANCE_ENABLED: ", ConstantSettings->ORANGE_AVOIDANCE_ENABLED);  
    }
    if (ConstantSettings->LIGHT_GREEN_PREFERENCE_ENABLED != 0 && ConstantSettings->LIGHT_GREEN_PREFERENCE_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid LIGHT_GREEN_PREFERENCE_ENABLED: ", ConstantSettings->LIGHT_GREEN_PREFERENCE_ENABLED);  
    }
    if (ConstantSettings->DUTY_SPREAD_ENABLED != 0 && ConstantSettings->DUTY_SPREAD_ENABLED != 1){
        dbg.fatal_error("validate_program_settings() - Invalid DUTY_SPREAD_ENABLED: ", ConstantSettings->DUTY_SPREAD_ENABLED);  
    }

    //other checks
    subunit_data_structure subunit_data;
    if (subunit_data.total_restrictions_remaining > ConstantSettings->DUTIES_PER_DAY){
        dbg.fatal_error("validate_program_settings() - Invalid total number of subunit restrictions");
    }

    //min > max checks
    if (ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL > ConstantSettings->MAX_PERSON_TOTAL){
        dbg.fatal_error("validate_program_settings() - MIN > MAX total duties");
    }
    if (ConstantSettings->ATTEMPT_MIN_PSK > ConstantSettings->MAX_PSK){
        dbg.fatal_error("validate_program_settings() - MIN > MAX psk duties");
    }
}

void validate_user_restrictions(vector <vi> &v){
    //scan user restrictions for clear invalid cases
    //=> format check

    //CHECK 1: (check constants)
    if (first_day_type < 0 || first_day_type > 6){
        dbg.fatal_error("validate_user_restrictions() - invalid user input - 'first_day_type' out of range");
    }
    if (people < ConstantSettings->DUTIES_PER_DAY){
        dbg.fatal_error("validate_user_restrictions() - Too few people");
    }

    //CHECK 2: GREEN VS SUBUNIT RESTRICTIONS
    for (ll day = 0; day<days; day++){
        subunit_data_structure subunit_data;
        for (ll person = 0; person < people; person++){
            if (v[person][day] == GREEN){
                if (subunit_data.can_add(user_person_subunit[person])){
                    subunit_data.add(user_person_subunit[person]);
                }
                else{
                    dbg.fatal_error("validate_user_restrictions() - Failed GREEN VS SUBUNIT RESTRICTIONS check");
                    break;
                }
            }
        }
    }

    //CHECK 3: MAX GREEN AND MAX RED IN A DAY
    for (ll day = 0; day<days; day++){
        ll red_cnt = 0, green_cnt = 0;
        for (ll person = 0; person < people; person++){
            if (v[person][day] == GREEN){
                green_cnt++;
            }
            else if (v[person][day] == RED){
                red_cnt++;
            }
        }
        if (green_cnt > ConstantSettings->DUTIES_PER_DAY){
            dbg.fatal_error("validate_user_restrictions() - Too many GREEN people in a single day");
        }
        else if (people - red_cnt < ConstantSettings->DUTIES_PER_DAY){
            dbg.fatal_error("validate_user_restrictions() - Too many RED people for a single day");
        }
    }

    //CHECK 4: MAX GREEN FOR EACH PERSON
    for (ll person = 0; person < people; person++){
        ll green_cnt = 0;
        for (ll day = 0; day < days; day++){
            if (v[person][day] == GREEN){
                green_cnt++;
            }
        }
        if (green_cnt > ConstantSettings->MAX_PERSON_TOTAL){
            dbg.fatal_error("validate_user_restrictions() - Too many GREEN days for a single person");
        }
    }
}

void initialisation(){
    //INITIALISATION 1: DAY TYPES
    day_type.resize(days);
    day_type_word.resize(days);
    ll cur_day_type = first_day_type;
    ll number_of_psk_days_in_month = 0;
    vi number_of_day_type_days_in_month(8,0);
    for (ll i =0; i<days; i++){
        switch (cur_day_type){
            case 0:
            day_type[i] = MONDAY;
            day_type_word[i] = "MONDAY";
            number_of_day_type_days_in_month[MONDAY]++;
            break;
            case 1:
            day_type[i] = TUESDAY;
            day_type_word[i] = "TUESDAY";
            number_of_day_type_days_in_month[TUESDAY]++;
            break;
            case 2:
            day_type[i] = WEDNESDAY;
            day_type_word[i] = "WEDNESDAY";
            number_of_day_type_days_in_month[WEDNESDAY]++;
            break;
            case 3:
            day_type[i] = THURSDAY;
            day_type_word[i] = "THURSDAY";
            number_of_day_type_days_in_month[THURSDAY]++;
            break;
            case 4:
            day_type[i] = FRIDAY;
            day_type_word[i] = "FRIDAY";
            number_of_psk_days_in_month++;
            number_of_day_type_days_in_month[FRIDAY]++;
            break;
            case 5:
            day_type[i] = SATURDAY;
            day_type_word[i] = "SATURDAY";
            number_of_psk_days_in_month++;
            number_of_day_type_days_in_month[SATURDAY]++;
            break;
            case 6: 
            day_type[i] = SUNDAY;
            day_type_word[i] = "SUNDAY";
            number_of_psk_days_in_month++;
            number_of_day_type_days_in_month[SUNDAY]++;
            break;
        }
        cur_day_type++;
        cur_day_type %= 7;
    }
    dbg.log("initialisation(): number_of_psk_days_in_month",number_of_psk_days_in_month);
    dbg.vector1D("initialisation(): day_type: ", day_type);
    
    //INITIALISATION 2: DUTY TOTALS
    user_people_psk_duty_total.assign(people, 0);
    user_people_duty_total.assign(people,0);
    ll total_people_duty_total = 0, total_people_psk_duty_total = 0;
    vi total_people_day_type_duty_total(8, 0);

    for (ll person =0; person<people; person++){
        for (ll d_type = MONDAY; d_type<=SUNDAY; d_type++){
            ll x = user_people_day_type_duty_total[person][d_type];
            total_people_day_type_duty_total[d_type] += x;
            total_people_duty_total += x;
            user_people_duty_total[person] += x;
            if (d_type >= FRIDAY){
                user_people_psk_duty_total[person] += x;
                total_people_psk_duty_total += x;
            }
        }
    }

    ll total_duties = total_people_duty_total + (ConstantSettings->DUTIES_PER_DAY * days);
    ideal_people_duty_total = ((ld)total_duties / (ld)people);

    ll total_psk_duties = total_people_psk_duty_total + (ConstantSettings->DUTIES_PER_DAY * number_of_psk_days_in_month);
    ideal_people_psk_duty_total = ((ld)total_psk_duties / (ld)people);

    ideal_people_day_type_duty_total.resize(8);
    for (ll d_type = MONDAY; d_type<=SUNDAY; d_type++){
        ll total_day_type_duties = total_people_day_type_duty_total[d_type] + (ConstantSettings->DUTIES_PER_DAY * number_of_day_type_days_in_month[d_type]);
        ideal_people_day_type_duty_total[d_type] = ((ld)total_day_type_duties / (ld)people);
    }

    dbg.log("initialisation(): ideal_people_duty_total:",ideal_people_duty_total,"ideal_people_psk_duty_total:",ideal_people_psk_duty_total);
    dbg.vector1D("initilisation(): ideal_people_day_type_duty_total: ", ideal_people_day_type_duty_total);
}

int add(const ll day, const ll person, schedule &s){
    //WARNING: Assuming that this person is not already added to this day. => pre-check this

    ll d_type = day_type[day];
    bool is_psk = (d_type >= FRIDAY);

    //CHECK 1: (consequtive check, thurday rule check, RED check)
    if (s.current_restrictions[person][day] == RED){
        return 1;
    }

    //CHECK 2: (max duties check)
    if (s.total_duties[person]+1 > ConstantSettings->MAX_PERSON_TOTAL){
        return 2;
    }

    //CHECK 3: (next day green check)
    if (day + 1 < days && (s.current_restrictions[person][day+1] == GREEN || s.res[person][day+1] == 1)){        //!! ALSO LOGIC FOR edit_add() => BE CAREFUL (=> condition after || )
        return 3;
    }

    //CHECK 4: (Day count check)
    if (s.total_for_day_type[person][d_type]+1 > ConstantSettings->MAX_FOR_DAY_TYPE[d_type]){
        return 4;
    }

    //CHECK 5: (Max PSK check)
    if (is_psk && s.total_psk[person]+1 > ConstantSettings->MAX_PSK){
        return 5;
    }

    //CHECK 6: (Thursday clear PSK check)
    if (d_type == THURSDAY){
        ll r = min(days-1, day + 3);
        for (ll k = day+1; k<=r; k++){
            if (s.current_restrictions[person][k] == GREEN || s.res[person][k] == 1){       //!! ALSO LOGIC FOR edit_add() => BE CAREFUL (=> condition after || )
                return 6;
            }
        }
    }

    //=> OK => UPDATE VALUES

    //UPDATE 1: (totals update)
    if (is_psk) s.total_psk[person]++;
    s.total_for_day_type[person][d_type]++;
    s.total_duties[person]++;
    s.day_total_subunit_duties[day][user_person_subunit[person]]++;

    //UPDATE 2: (consequtive rule update)
    if (day + 1 < days) s.current_restrictions[person][day+1] = RED;

    //UPDATE 3: (Thursday rule update)
    if (d_type == THURSDAY){
        ll r = min(days-1, day + 3);
        for (ll k = day+1; k<=r; k++){
            s.current_restrictions[person][k] = RED;
        }
    }

    return 0;
}

bool attempt_adding_day(const ll day, schedule &s){
    // dbg.log("attempt day: ", day);
    // dbg(day_type_word[day]);
    set <ll> cur_people;
    subunit_data_structure subunit_data;

    //add green
    for (ll person = 0; person<people; person++){
        if (s.current_restrictions[person][day] == GREEN){
            ll add_res = add(day,person,s);
            if (add_res == 0){
                cur_people.ins(person);
                subunit_data.add(user_person_subunit[person]);
                // dbg.log("attempt_adding_day() - add() (GREEN PERSON) succeeded");
            }
            else{
                // dbg.log("attempt_adding_day() - add() (GREEN PERSON) failed with code: ", add_res);
                return false;
            }
        }
    }

    //add the rest
    vi rand_perm = rnd.getPermutation(people);
    // sort(rand_perm.begin(), rand_perm.end());
    // printVct(rand_perm);
    for (ll j =0; j<people && sz(cur_people) < ConstantSettings->DUTIES_PER_DAY; j++){
        ll person = rand_perm[j];
        if (cur_people.find(person) != cur_people.end()) continue;
        if (!subunit_data.can_add(user_person_subunit[person])) continue; //* SUBUNIT CHECK
        ll add_res = add(day,person,s);
        if (add_res == 0){
            subunit_data.add(user_person_subunit[person]);
            cur_people.ins(person);
            // dbg.log("attempt_adding_day() - add() succeeded");
        }
        else{
            // dbg.log("attempt_adding_day() - add() failed with code: ", add_res);
        }
    }

    // cout<<"Added People: ";
    // printSet(cur_people,1);
    // subunit_data.print();

    if (sz(cur_people) < ConstantSettings->DUTIES_PER_DAY){
        // dbg.warning("Failed to add enough people. People Added: ", sz(cur_people));
        // cout<<endl;
        return false;
    }

    // dbg.success("added day: ", day);

    for (set <ll> :: iterator it = cur_people.begin(); it != cur_people.end(); it++){
        s.res[*it][day] = 1;
    }

    return true;
}

bool initialize_schedule(schedule &s){
    const ll failed_attempts_timeout = ConstantSettings->SCHEDULE_INITIALIZATION_MAX_ATTEMPTS;
    const ll init_day_attempt_limit = 2;

    schedule max_day_reached_schedule;  //used to return the max day reached schedule in case of failure

    vector <schedule> s_memory(days);
    s_memory[0] = s;
    
    vi attempt_left(days,init_day_attempt_limit);
    attempt_left[0] = -1;

    ll failed_attempts = 0, day = 0, max_day_reached = -1;
    bool last_attempt_succeeded = false;
    while (failed_attempts < failed_attempts_timeout && day < days && day >= 0){
        if (max_day_reached < day-1){
            max_day_reached = day-1;
            max_day_reached_schedule = s;
        }
        s_memory[day] = s;
        last_attempt_succeeded = attempt_adding_day(day, s);
        if (last_attempt_succeeded){
            attempt_left[day]--;
            day++;
        }
        else{
            failed_attempts++;
            if (!day) break;
            attempt_left[day] = init_day_attempt_limit;
            day--;
            while (!attempt_left[day]){
                attempt_left[day] = init_day_attempt_limit;
                day--;
            }
            s = s_memory[day];
        }
    }
    max_day_reached = max(max_day_reached, day-1);

    //in case of failure return max day reached schedule
    if (failed_attempts >= failed_attempts_timeout){
        for (ll day = max_day_reached+1; day < days; day++){
            for (ll person = 0; person < people; person++){
                max_day_reached_schedule.res[person][day] = 2;
            }
        }
        s = max_day_reached_schedule;
    }

    runStats.initialization_failed_attempts = failed_attempts;
    runStats.max_day_reached = max_day_reached;

    return last_attempt_succeeded;
}

int edit_remove(const ll day, const ll person, schedule &s, bool subunit_check){
    ll d_type = day_type[day];
    bool is_psk = (d_type >= FRIDAY);

    //CHECK 1: Green Check
    if (s.current_restrictions[person][day] == GREEN){
        return 1;
    }

    //CHECK 2: SUBUNIT Min Check
    if (subunit_check && s.day_total_subunit_duties[day][user_person_subunit[person]]-1 < ConstantSettings->MIN_PEOPLE_FOR_SUBUNIT[user_person_subunit[person]]){
        return 2;
    }

    //OK => MAKE CHANGE
    //UPDATE 1: (reverse totals update)
    if (is_psk) s.total_psk[person]--;
    s.total_for_day_type[person][d_type]--;
    s.total_duties[person]--;
    s.day_total_subunit_duties[day][user_person_subunit[person]]--;

    //UPDATE 2: (reverse consequtive rule update => make equal to user input)
    if (day + 1 < days) s.current_restrictions[person][day + 1] = user_restrictions[person][day + 1];

    //UPDATE 3: (reverse Thursday rule update => make equal to user input)
    if (d_type == THURSDAY){
        ll r = min(days-1, day + 3);
        for (ll k = day+1; k<=r; k++){
            s.current_restrictions[person][k] = user_restrictions[person][k];
        }
    }

    return 0;
}

tuple <schedule, bool> find_neighbour(schedule s){
    const ll failed_attempts_timeout = ConstantSettings->SCHEDULE_NEIGHBOUR_FINDING_MAX_ATTEMPTS;
    ll failed_attempts = 0;
    schedule res_s;

    while (failed_attempts < failed_attempts_timeout){
        ll day = rnd.getNum(0, days-1);
        res_s = s;

        // pick a random person on duty and a random person with no duty: O(people) => POSSIBLE OPTIMIZATION
        vi p = rnd.getPermutation(people);
        ll no_duty_person = -1, duty_person = -1;
        for (ll i = 0; i<sz(p) && (no_duty_person == -1 || duty_person == -1); i++){
            ll person = p[i];
            if (duty_person == -1 && res_s.res[person][day]){
                duty_person = person;
            }
            if (no_duty_person == -1 && !res_s.res[person][day]){
                no_duty_person = person;
            }
        }
        bool people_from_same_subunit = (user_person_subunit[duty_person] == user_person_subunit[no_duty_person]);

        // dbg.log("Attempt swap: Day:",day,"Add:",no_duty_person,"Remove:",duty_person);

        //attempt the swap
        ll res_remove = edit_remove(day, duty_person, res_s, !people_from_same_subunit);
        ll res_add = add(day, no_duty_person, res_s);
        // dbg2(res_remove, res_add);
        if (res_add == 0 && res_remove == 0){
            res_s.res[duty_person][day] = 0;
            res_s.res[no_duty_person][day] = 1;
            break;
        }
        failed_attempts++;
    }

    //update runStats
    runStats.max_neighbour_finding_failed_attempts = max(runStats.max_neighbour_finding_failed_attempts, failed_attempts);
    runStats.total_neighbour_finding_failed_attempts += failed_attempts;

    //handle neighbour finding failure
    if (failed_attempts >= failed_attempts_timeout){
        dbg.warning("Failed to find neighbour! Failed Attempts: ", failed_attempts);
        return make_tuple(s,false);
    }
    else{
        // dbg.success("Found neighbour! Failed Attempts: ", failed_attempts);
    }

    return make_tuple(res_s,true);
}

ld linear_progress_calc(ld input_bottom, ld input_top, ld output_bottom, ld output_top, ld val){
    ld dif_input = input_top - input_bottom;
    ld dif_output = output_top - output_bottom;
    return output_bottom + (((val - input_bottom) / dif_input) * dif_output);
}

ld progressive_dif_to_penalty_convertion(ld dif){
    ld cur;
    if (dif < 0) dif *= (ld)-1;
    if (dif >= (ld)5){      //5 - inf => 100
        cur = 100;
    }
    else if (dif >= (ld)4){     //4-5 => 60-100
        cur = linear_progress_calc(4, 5, 60, 100, dif);
    }
    else if (dif >= (ld)3){     //3-4 => 30-60
        cur = linear_progress_calc(3, 4, 30, 60, dif);
    }
    else if (dif >= (ld)2){     //2-3 => 10-30
        cur = linear_progress_calc(2, 3, 10, 30, dif);
    }
    else if (dif >= (ld)1){     //1-2 => 2-10
        cur = linear_progress_calc(1, 2, 2, 10, dif);
    }
    else if (dif >= (ld)0.5){     //0.5-1 => 0.5-2
        cur = linear_progress_calc(0.5, 1, 0.5, 2, dif);
    }
    else{      //0-0.5  => 0-0.5
        cur = linear_progress_calc(0, 0.5, 0, 0.5, dif);
    }
    return cur;
}

ld calculate_schedule_penalty(const schedule &s){
    ld ans = 0;

    ld duty_total_balance_penalty = 0;  //out of 100
    ld duty_psk_balance_penalty = 0;    //out of 100
    ld duty_psk_variety_penalty = 0;    //out of 100

    ld orange_penalty = 0;          //fixed penalty (+1 for each violation)
    ld light_green_penalty = 0;     //fixed penalty (+1 for each violation)

    ld duty_spread_penalty = 0;     //out of 10

    ld min_total_person_duties_penalty = 0;     //out of 4000
    ld min_psk_duties_penalty = 0;              //out of 4000

    /*
    Plan 1:
    calculate ideal number for every person 
    => calc difference from real
    => use a function (probably not linear => fixed with cases or exponential => probably firxed with cases)
    */

    /*
    Plan 2:
    • Use exponential functions for each balancing parameter and normalize so that the output is always between 0 and 1 (adjust local weights)
    • Use multiplication factor on the final answer (adjust relative weights)
    */
    if (ConstantSettings->DUTY_TOTAL_BALANCE_ENABLED){
        for (ll person = 0; person < people; person++){
            ld dif = (ld)s.total_duties[person] + (ld)user_people_duty_total[person] - ideal_people_duty_total, cur = -1;
            duty_total_balance_penalty += progressive_dif_to_penalty_convertion(dif);
        }
    }

    if (ConstantSettings->DUTY_PSK_BALANCE_ENABLED){
        for (ll person = 0; person < people; person++){
            ld dif = (ld)s.total_psk[person] + (ld)user_people_psk_duty_total[person] - ideal_people_psk_duty_total;
            duty_total_balance_penalty += progressive_dif_to_penalty_convertion(dif);
        }
    }

    if (ConstantSettings->DUTY_PSK_VARIETY_BALANCE_ENABLED){
        for (ll person = 0; person < people; person++){
            for (ll d_type = FRIDAY; d_type <= SUNDAY; d_type++){
                ld dif = (ld)s.total_for_day_type[person][d_type] + (ld)user_people_day_type_duty_total[person][d_type] - ideal_people_day_type_duty_total[d_type];
                duty_psk_variety_penalty += progressive_dif_to_penalty_convertion(dif);
            }
        }
    }

    if (ConstantSettings->ORANGE_AVOIDANCE_ENABLED){
        for (ll person = 0; person < people; person++){
            for (ll day = 0; day < days; day++){
                if (user_restrictions[person][day] == ORANGE && s.res[person][day]){
                    orange_penalty++;
                }
            }
        }
    }

    if (ConstantSettings->LIGHT_GREEN_PREFERENCE_ENABLED){
        for (ll person = 0; person < people; person++){
            for (ll day = 0; day < days; day++){
                if (user_restrictions[person][day] == LIGHT_GREEN && !s.res[person][day]){
                    light_green_penalty++;
                }
            }
        }
    }
    
    if(ConstantSettings->DUTY_SPREAD_ENABLED){
        for (ll person = 0; person < people; person++){
            for (ll day = 0; day < days; day++){
                if (s.res[person][day]){
                    ld cur = 0;
                    //check 2 days away:
                    if ((day + 2 < days && s.res[person][day+2]) || (day - 2 >= 0 && s.res[person][day-2])){
                        cur = 10;
                    }
                    //check 3 days away:
                    else if ((day + 3 < days && s.res[person][day+3]) || (day - 3 >= 0 && s.res[person][day-3])){
                        cur = 3;
                    }
                    //check 4 days away:
                    else if ((day + 4 < days && s.res[person][day+4]) || (day - 4 >= 0 && s.res[person][day-4])){
                        cur = 1;
                    }
                    duty_spread_penalty += cur;
                }
            }
        }
    }

    if(ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL > 0){
        for (ll person = 0; person < people; person++){
            if(s.total_duties[person] < ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL){
                ll dif = ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL - s.total_duties[person];
                if (dif == 1){
                    min_total_person_duties_penalty += 400;
                }
                else if (dif == 2){
                    min_total_person_duties_penalty += 1000;
                }
                else if (dif == 3){
                    min_total_person_duties_penalty += 2000;
                }
                else{
                    min_total_person_duties_penalty += 3000;
                }
            }
        }
    }

    if(ConstantSettings->ATTEMPT_MIN_PSK > 0){
        for (ll person = 0; person < people; person++){
            if(s.total_psk[person] < ConstantSettings->ATTEMPT_MIN_PSK){
                ll dif = ConstantSettings->ATTEMPT_MIN_PSK - s.total_psk[person];
                if (dif == 1){
                    min_psk_duties_penalty += 400;
                }
                else if (dif == 2){
                    min_psk_duties_penalty += 1000;
                }
                else if (dif == 3){
                    min_psk_duties_penalty += 2000;
                }
                else{
                    min_psk_duties_penalty += 3000;
                }
            }
        }
    }

    ans = duty_total_balance_penalty * 2 + duty_psk_balance_penalty * 2 + duty_psk_variety_penalty * 0.2 + orange_penalty * 60 + light_green_penalty * 60 + duty_spread_penalty * 1.5 + min_total_person_duties_penalty + min_psk_duties_penalty;
    return ans;
}

bool check_if_sa_fixed_parameters_are_met(schedule &s){
    bool ok = true;
    if(ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL > 0){
        for (ll person = 0; person < people; person++){
            if(s.total_duties[person] < ConstantSettings->ATTEMPT_MIN_PERSON_TOTAL){
                dbg.warning("check_if_sa_fixed_parameters_are_met(): total failed: person:", person, "total duties: ", s.total_duties[person]);
                ok = false;
            }
        }
    }
    if(ConstantSettings->ATTEMPT_MIN_PSK > 0){
        for (ll person = 0; person < people; person++){
            if(s.total_psk[person] < ConstantSettings->ATTEMPT_MIN_PSK){
                dbg.warning("check_if_sa_fixed_parameters_are_met(): psk failed: person:", person, "psk duties: ", s.total_psk[person]);
                ok = false;
            }
        }
    }
    return ok;
}

ld linear_cooling_schedule(const ld time, const ld repetitions, const ld max_temperature){
    return max_temperature - (time * max_temperature / repetitions);
}

ld geometric_cooling_schedule(const ld time, const ld a, const ld max_temperature){
    return max_temperature * powl(a, time);
}

schedule simulated_annealing(schedule current_schedule){
    const ll repetitions = ConstantSettings->SCHEDULE_OPTIMIZATION_REPETITIONS;
    ld current_penalty = calculate_schedule_penalty(current_schedule);
    schedule neighbour_schedule;
    const ld e = 2.71828182846;
    ll i;
    for (i =0; i<repetitions; i++){
        bool found_neighbour;
        tie(neighbour_schedule, found_neighbour) = find_neighbour(current_schedule);
        if (!found_neighbour){
            dbg.warning("Terminated SA at repetition =",i);
            break;
        }

        ld neighbour_penalty = calculate_schedule_penalty(neighbour_schedule);
        if (neighbour_penalty <= current_penalty){
            current_penalty = neighbour_penalty;
            current_schedule = neighbour_schedule;
        }
        else{
            ld Temperature = geometric_cooling_schedule(i, ConstantSettings->get_SA_GEOMETRIC_COOLING_BASE_CONSTANT_FLOAT(), ConstantSettings->SA_MAX_TEMPERATURE);   //(i, 0.9999, 2500);
            ld Delta_E = neighbour_penalty - current_penalty;
            ld P_accept = powl(e, -Delta_E / Temperature);
            ld r = (ld)rnd.getNum(0,10) / (ld)10;
            if (r < P_accept){
                current_penalty = neighbour_penalty;
                current_schedule = neighbour_schedule;
            }
        }
    }

    //update runStats
    runStats.optimization_reps = i;
    runStats.successfully_found_all_neighbours = (i == repetitions);
    runStats.avg_neighbour_finding_failed_attempts = ((ld)runStats.total_neighbour_finding_failed_attempts / ((ld)(runStats.optimization_reps + (i < repetitions))));

    return current_schedule;
}

schedule local_search(schedule current_schedule, const ll repetitions){
    ld current_penalty = calculate_schedule_penalty(current_schedule);
    for (ll i =0; i<repetitions; i++){
        bool found_neighbour;
        schedule neighbour_schedule;
        tie(neighbour_schedule,found_neighbour) = find_neighbour(current_schedule);
        if (!found_neighbour) break;
        ld neighbour_penalty = calculate_schedule_penalty(neighbour_schedule);
        if (neighbour_penalty < current_penalty){
            current_penalty = neighbour_penalty;
            current_schedule = neighbour_schedule;
        }
    }
    cout<<"local_search: "<<endl;
    current_schedule.print_shedule();
    dbg(current_penalty);
    return current_schedule;
}

void terminal_only_detailed_input_dbg(){
    cout<<BOLD_TEXT<<"ARMY SCHEDULER PROJECT DLL"<<RESET_TEXT<<endl;
    cout<<" • DLL Version: "<<DLL_VERSION<<endl;
    cout<<" • DLL Compilation Date: "<<DLL_COMPILATION_DATE<<endl;
    
    cout<<endl<<BOLD_TEXT<<"Input"<<RESET_TEXT<<endl<<"people:"<<people<<" days:"<<days<<" first_day_type:"<<first_day_type<<endl;
    for (ll i=0; i<people; i++){
        cout<<BOLD_TEXT<<i%10<<": "<<RESET_TEXT;
        for (ll j =0; j<days; j++){
            if (user_restrictions[i][j] == RED) cout<<RED_TEXT;
            else if (user_restrictions[i][j] == GREEN) cout<<GREEN_TEXT;
            else if (user_restrictions[i][j] == ORANGE) cout<<YELLOW_TEXT;
            else if (user_restrictions[i][j] == LIGHT_GREEN) cout<<CYAN_TEXT;
            cout<<user_restrictions[i][j]<<" ";
            cout<<RESET_TEXT;
        }
        cout<<endl;
    }
    cout<<BOLD_TEXT<<"   M T W T F S S"<<RESET_TEXT<<endl;
    for (ll i =0; i<people; i++){
        cout<<BOLD_TEXT<<i%10<<": "<<RESET_TEXT;
        for (ll j =MONDAY; j<=SUNDAY; j++){
            cout<<user_people_day_type_duty_total[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<BOLD_TEXT<<"People Subunit:"<<endl;
    for (ll person = 0; person <people; person++){
        cout<<person%10<<" ";
    }
    cout<<RESET_TEXT<<endl;
    for (ll person = 0; person <people; person++){
        cout<<user_person_subunit[person]<<" ";
    }
    cout<<endl;

    cout<<BOLD_TEXT<<"Settings:"<<endl;
    vi setting_vector = ConstantSettings->getSettingsVector();
    const ll spacing = 3;
    cout<<"|";
    for (ll i =0; i<sz(setting_vector); i++){
        string tmp = to_string(i);
        tmp += " ";
        while (sz(tmp) <= spacing) tmp += " ";
        tmp += "|";
        cout<<tmp;
    }
    cout<<RESET_TEXT<<endl<<"|";
    for (ll i =0; i<sz(setting_vector); i++){
        string tmp;
        if (ConstantSettings->const_is_float[i]) tmp = to_string(float_representation_of_int(setting_vector[i]));
        else tmp = to_string(setting_vector[i]);
        tmp += " ";
        while (sz(tmp) <= spacing) tmp += " ";
        tmp += "|";
        cout<<tmp;
    }
    cout<<endl<<endl;
}

vector <vi> main_program(){
    try{
    //DEBUG INPUT
        terminal_only_detailed_input_dbg();
        if (running_in_unity){
            dbg.vector2D("user_restrictions", user_restrictions);
            dbg.vector2D("user_people_day_type_duty_total", user_people_day_type_duty_total);
            dbg.vector1D("user_person_subunit: ",user_person_subunit);
            ConstantSettings->dbgSettings();
        }

    //INPUT VALIDATION CHECKS
        validate_program_settings();
        validate_user_restrictions(user_restrictions);

    //PRE-PROCESSING AND INITIALIZATION
        {
            //adjust user input for previous month 
            //=> check for thursday rule => TO DO USE SUGGESTION *
            //=> check for cononsequtive rule => TO DO USE SUGGESTION *
            //=> (adjust for max spread optional rule)?
            //SUGGESTION *: Also take the last duty of the previous month as input (when it was and what day_type it was)
        }
        initialisation();

    //SCHEDULE INITIALIZATION - FIXED PARAMETERS
        schedule initial_schedule;
        auto scheduleInitializationStartTime = std::chrono::high_resolution_clock::now();   //start initialization timer
        runStats.successful_initialization = initialize_schedule(initial_schedule);    //initialize schedule
        std::chrono::duration<double> scheduleInitializationDuration = (std::chrono::high_resolution_clock::now() - scheduleInitializationStartTime);   //calc initialization duration
        runStats.schedule_initialization_duration = scheduleInitializationDuration.count();     //store initialization duration in stats
        if (runStats.successful_initialization){
            dbg.success("main_program() - Shedule Initialized. \n=>Total Failed Attempts:",runStats.initialization_failed_attempts);
        }
        else{
            dbg.error("main_program() - Initialization Failed. \n=> Total Failed Attempts:",runStats.initialization_failed_attempts, "\n=> Max Day Reached:", runStats.max_day_reached);
            return initial_schedule.res;
        }
        initial_schedule.print_shedule("Initial");
        runStats.initial_penalty = calculate_schedule_penalty(initial_schedule);
        dbg.log("Initial Schedule Penalty: ", runStats.initial_penalty);

    //TMP DEBUGGING (REMOVE AFTER DONE)
        check_if_sa_fixed_parameters_are_met(initial_schedule);

    //SCHEDULE OPTIMIZATION - OPTIONAL PARAMETERS
        auto scheduleOptimizationStartTime = std::chrono::high_resolution_clock::now();    //start optimization timer
        schedule final_schedule = simulated_annealing(initial_schedule);
        std::chrono::duration<double> scheduleOptimizationDuration = (std::chrono::high_resolution_clock::now() - scheduleOptimizationStartTime);    //calc optimization duration
        runStats.schedule_optimization_duration = scheduleOptimizationDuration.count();     //store optimization duration in stats
        final_schedule.print_shedule("Final");
        runStats.final_penalty = calculate_schedule_penalty(final_schedule);
        dbg.log("Final Schedule Penalty: ", runStats.final_penalty);

    //STATS
        runStats.SA_fixed_parameters_are_fully_met = check_if_sa_fixed_parameters_are_met(final_schedule);

    //RETURN OUTPUT
        return final_schedule.res;
    }
    catch (const::exception &e){
        dbg.error(e.what());
        return vector <vi> (people, vi(days, 2));
    }
}

// --------------------------------------------- DLL PROGRAM ---------------------------------------------

// Define DLLExport and STDCALL macros for cross-platform export
#ifdef _WIN32
    #define DLLExport __declspec(dllexport)
    #define STDCALL __stdcall
#else
    #define DLLExport __attribute__((visibility("default")))
    #define STDCALL
#endif

extern "C" {
    //SEND DLL VERSION TO USER <<<<<<<<<<<<<<<<<<<<<<<<<<<< (also print it in the console in the beginning)

    DLLExport void STDCALL runningInUnity(DbgFuncCallBack cb) {
        running_in_unity = true;
        dbg(running_in_unity);
        dbgCallbackInstance = cb;
    }

    DLLExport void STDCALL testDebugFunction(int x) {
        cout<<"scheduler.cpp - Debug Testing:"<<endl;
        dbg.log("scehdyler.cpp - runningInUnity() - TEST LOG");
        dbg.warning("scehdyler.cpp - runningInUnity() - TEST WARNING");
        dbg.error("scehdyler.cpp - runningInUnity() - TEST ERROR");
        dbg.log("scehdyler.cpp - runningInUnity() - TEST NUMBER LOG", x);
        dbg.success("scehdyler.cpp - runningInUnity() - TEST SUCCESS");
        cout<<endl;
    }

    DLLExport void STDCALL initialize_direct_data_transmission(sendValFuncCallBack int_cb, sendValFuncCallBack bool_cb, sendValFuncCallBack float_cb, sendStringFuncCallBack string_cb) {
        if (int_cb == NULL || bool_cb == NULL || float_cb == NULL || string_cb == NULL){
            dbg.error("initialize_direct_data_transmission(): Failed to initialize. Callback function(s) are NULL!");
            return;
        }
        dbg.log("initialize_direct_data_transmission(): Initialized direct data transmission.");
        sendIntCallBackInstance = int_cb;
        sendBoolCallBackInstance = bool_cb;
        sendFloatCallBackInstance = float_cb;
        sendStringCallBackInstance = string_cb;
        
        //SEND DLL VERSION TO USER
        ddt.sendString(DLL_VERSION,"dll_version");
        ddt.sendString(DLL_COMPILATION_DATE, "dll_compilation_date");
    }
    
    DLLExport void STDCALL run_scheduler(int people_C, int days_C, int first_day_type_C, int* user_restrictions_C, int* user_people_day_type_duty_total_C, int* user_person_subunit_C, int* user_settings_C, int* output_res_C){
        //initialize
        people = people_C;
        days = days_C;
        first_day_type = first_day_type_C;
        
        user_restrictions.assign(people, vi(days,WHITE));
        user_people_day_type_duty_total.assign(people, vi(SUNDAY+1, 0));
        user_person_subunit.assign(people, 0);

        for (int person =0; person<people; person++){
            for (int day =0; day<days; day++){
                user_restrictions[person][day] = user_restrictions_C[coordinate_to_number(person, day, days)];
            }
        }
        for (int person =0; person<people; person++){
            for (int d_type = MONDAY; d_type<=SUNDAY; d_type++){
                user_people_day_type_duty_total[person][d_type] = user_people_day_type_duty_total_C[coordinate_to_number(person, d_type-1, SUNDAY)];
            }
        }
        for (int person = 0; person < people; person++){
            user_person_subunit[person] = user_person_subunit_C[person];
        }

        ConstantSettings = new ConstantSettingsClass(user_settings_C);
        
        //run
        runStats.resetStats();
        auto programStartTime = std::chrono::high_resolution_clock::now();   //start program timer
        vector <vi> output_res = main_program();    //run program
        std::chrono::duration<double> fullDuration = (std::chrono::high_resolution_clock::now() - programStartTime);    //calc program duration
        runStats.full_duration = fullDuration.count();  //store program duration

        //print & send runStats
        runStats.logEssentialStats();
        runStats.logAllStats();
        runStats.sendAllStats();

        //output
        for (int person =0; person<people; person++){
            for (int day =0; day<days; day++){
                output_res_C[coordinate_to_number(person, day, days)] = output_res[person][day];
            }
        }

        //cleanup
        delete ConstantSettings;
    }
}

/*
SUGGESTED SA SETTINGS:
=> Repetitions: 200,000 (increase for more exploitation)
=> a = 0.9999 (30,000 iterations for exploration)
=> Tmax = 2500 (to account for the two extra parameters)
*/