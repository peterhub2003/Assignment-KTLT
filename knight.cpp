#include "knight.h"

/* Utility Functions */
bool isMountain(int* ar, const int& size, int& mtx, short& mti){
    //mtx: value of peek and mti: index of peek
    if(size == 1) {mtx = ar[0]; mti = 0; return true;}

    bool isFlip = false;
    for(int i = 0; i < size - 1; ++i){
        if(ar[i] == ar[i+1] || (ar[i] < ar[i+1] && isFlip)) return false;
        if(ar[i] > ar[i+1] && !isFlip) {mtx = ar[i]; mti = i; isFlip = true;}
    }
    if(!isFlip){
        if(ar[0] > ar[size - 1]) {mtx = ar[0], mti = 0;}
        else {mtx = ar[size - 1]; mti = size - 1;}
    }

    return true;
}

bool isPrime(const int& n){ 
    if(n <= 1) return false;
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) return false;
    return true;
}

void increasePrime(int& n){
    ++n;
    while(!isPrime(n)) {++n;}
    return;
}

int decrease_Fibo(const int& n){
    if(n == 1 || n == 2) return 1;
    int a = 1, b = 2;
    while(b <= n){
        if(b == n) return a;
        int temp = b;
        b = a + b;
        a = temp;
    }
    return a;
}

int sum_of_max(const int& n){
    try{
        if(n > 45) 
            throw invalid_argument("n is greater than the numbers of odd_2_digits number");
    }
    catch (const std::exception& e) {cout << e.what() << endl; return -1;}
    int start = 11 + (45 - n) * 2;
    int sum = ((99 - start) /2 + 1)*(99 + start) /2;
    return sum;
}

pair<short, short> index_min_max(int* ar, const int& size, bool last){
    //if last == true, get the last index otherwise get the first index
    short idx_min = 0, idx_max = 0;
    for(int i = 1; i < size; ++i){
        if(last){
            if(ar[i] <= ar[idx_min]) idx_min = i;
            if(ar[i] >= ar[idx_max]) idx_max = i;
        }
        else{
            if(ar[i] < ar[idx_min]) idx_min = i;
            if(ar[i] > ar[idx_max]) idx_max = i;
        }   
    }
    return make_pair(idx_max, idx_min);
}

pair<int, short> index_first_secondMax(int* ar, const int& size){
    if(size < 2) return make_pair(-5, -7);
    if(size == 2){
        if(ar[0] < ar[1]) return make_pair(ar[0], 0);
        else if(ar[0] > ar[1]) return make_pair(ar[1], 1);
        else return make_pair(-5, -7);
    }
    if(ar[0] == ar[1] && ar[1] == ar[2]) return make_pair(-5, -7);
    
    short secMax = 0, idxMax = 0 ;
    for(int i = 1; i < 3; ++i){
        if(ar[i] > ar[idxMax]) {
            secMax = idxMax;
            idxMax = i;
        }else if(ar[i] < ar[idxMax]){
            if(ar[i] > ar[secMax]) secMax = i;
            else if(ar[i] < ar[secMax]){
                if(secMax == idxMax) secMax = i;
            }
        }
    }

    return make_pair(ar[secMax], secMax);
}

void processString(string& res){
    while(res.length() > 0 && res.front() == ' ') res.erase(0, 1);
    while(res.length() > 0 && res.back() == ' ') res.pop_back();
    return;
}
/*=============================End Define Utility Function===================================== */
/*=============================================================================================*/
float ar[5] = {1, 1.5, 4.5, 7.5, 9.5};

//file_mush
int n2;
int* ar_mush;

//file_ascle
int r1, c1;
int** ar_ascle;

//file_merlin
int n9;
string* ar_merlin;

bool visited[3] = {false, false, false};
string file_name[3] ;
/*=============================================================================================*/
/*=============================================================================================*/

//=========================PREPROCESS FILE AND INIT KNIGHT=========================================
void preprocess_file(const char* fname, string& lknight, string& levents, string& lfile){
    FILE* inp = freopen(fname, "r", stdin);
    if(inp){
        getline(cin, lknight);
        getline(cin, levents);
        getline(cin, lfile);
    }

    processString(lknight);
    processString(levents);
    processString(lfile);

    stringstream ss(lfile);
    int i = 0;
    while(ss.good() && i < 3){
        getline(ss, file_name[i], ',');
        ++i;
    }
        
    cin.clear();
    for(int i = 0; i < 3; ++i){
        if(file_name[i].length() == 0) continue;
        freopen(file_name[i].c_str() , "r", inp);
        if(i == 0){
            cin >> n2;
            string line; cin >> line;
            processString(line); 
            stringstream ss(line);

            ar_mush = new int[n2];
            for(int i = 0; i < n2; ++i){
                string s; getline(ss, s, ',');
                ar_mush[i] = stoi(s);
            }   
        }
        else if(i == 1){
            cin >> r1 >> c1;
            ar_ascle = new int*[r1];
            for(int i = 0; i < r1; ++i){
                ar_ascle[i] = new int[c1];
                for(int j = 0; j < c1; ++j)
                    cin >> ar_ascle[i][j];
            }
        }
        else{
            cin >> n9;
            ar_merlin = new string[n9];
            for(int i = 0; i < n9; cin >> ar_merlin[i], ++i);
        }
        cin.clear();
    }

    fclose(inp);
}

void initKnight(Knight& k, const string& lknight){
    stringstream ss(lknight);
    int _HP;
    short _level, _remedy, _maidenkiss, _phoenixdown;
    ss >> _HP >> _level >> _remedy >> _maidenkiss >> _phoenixdown;
    k.init(_HP, _level, _remedy, _maidenkiss, _phoenixdown);

    return;
}

//================================================================================//
//===========================UPDATE FUNCTION======================================//
void updateShape(Knight& k){
    if(k.state.s == Shape::Tiny){
        if(k.state.time == 0 || k.remedy >= 1){
            if(k.remedy >= 1) {k.remedy -= 1;}
            k.HP *= 5; k.HP = (k.HP > k.MaxHP) ? k.MaxHP :k.HP;
            k.state = {Shape::Human, -1};
        }
        else k.state.time -= 1;
    }else{
        if(k.state.time == 0 || k.maidenkiss >= 1){
            if(k.maidenkiss >=1){ k.maidenkiss -= 1;}
            k.level = k.prelevel;
            k.state = {Shape::Human, -1};
        }
        else k.state.time -= 1;
    }
    
    if(k.state.time == 0) updateShape(k);
    return;
}


void update(Knight& k){
    if(k.state.s != Shape::Human) updateShape(k);
    return;
}

//using when HP <= 0. return false if not have phoenixdown
bool updateHP(Knight& k){
    if(k.phoenixdown == 0) {
        k.rescue = 0; 
        return false; //return false means that no rescue
    }
    else {
        k.HP = k.MaxHP;     
        k.phoenixdown -= 1;
        if(k.state.s == Shape::Frog) {k.level = k.prelevel;}
        k.state = {Shape::Human, -1};
    }  
    return true;
}
//=====================================================================================
//================================EVENT FUNCTION=======================================
/*                     If The returned result of function is true, 
                It means that knight w

    return true;ill go on otherwise knight will stop
*/ 
bool Event0(Knight& k){
    k.rescue = 1;
    update(k);
    return true;
}
bool Event1_5(const short& event, const short& idx_event, Knight& k){
    if(k.position != Pos::Normal){
        if(k.level < 10) k.level += 1;
        return true;
    } 

    short levelO = (idx_event > 6) ? (idx_event%10 > 5?idx_event%10:5): (idx_event%10);
    if(k.level < 10){
        if(k.level  > levelO) ++k.level;
        else if(k.level < levelO){
            short damage = ar[event - 1] * 10 * levelO;
            k.HP -= (int)damage;
        }
    }

    if(k.HP <= 0){
        bool c = updateHP(k);
        if(!c) {return false;}
    }

    update(k);
    return true;
}

bool Event6(const short& idx_event, Knight& k){
    if(k.state.s == Shape::Human) 
    {
        short levelO = (idx_event > 6) ? (idx_event%10 > 5?idx_event%10:5): (idx_event%10);
        if(k.level > levelO || k.position != Pos::Normal) {
            k.level += 2;
            if(k.level > 10) k.level = 10;
        }
        else if(k.level < levelO){
            if(k.remedy >= 1) {
                --k.remedy; 
            }
            else{
                k.state = {Shape::Tiny, 3};    
                if(k.HP < 5) k.HP = 1;
                else{   
                    k.HP = k.HP /5;     
                }
            }
        }
    }
    else update(k);

    return true;
}

bool Event7(const short& idx_event, Knight& k){
    if(k.state.s == Shape::Human){
        short levelO = (idx_event > 6) ? (idx_event%10 > 5?idx_event%10:5): (idx_event%10);
        if(k.level > levelO || k.position != Pos::Normal) {
            k.level += 2;
            if(k.level > 10) k.level = 10;
        }
        else if (k.level < levelO)
        {
            if(k.maidenkiss >= 1) {
                --k.maidenkiss;
            }
            else{
                k.prelevel = k.level;
                k.level = 1;
                k.state = {Shape::Frog, 3};
            }
        }
    }
    else update(k);
    return true;
}


bool Event11(Knight& k){
    short n1 = ((k.level + k.phoenixdown) % 5 + 1) * 3;
    short s1 = sum_of_max(n1);
    k.HP += (s1%100);

    if(k.HP < k.MaxHP) 
    {
        increasePrime(k.HP);
        if(k.HP > k.MaxHP) k.HP = k.MaxHP;
    }else k.HP = k.MaxHP;
    update(k);
    return true;
}

bool Event12(Knight& k){
    if(k.HP > 1) {k.HP = decrease_Fibo(k.HP);}
    update(k);
    return true;
}

// MUSH_GHOST
bool Event13(const string& s, Knight& k){
    for(int i = 2; i < (int)s.length(); ++i){
        short type = s[i] - '0';
        if(type == 1){
            short maxi, mini;
            maxi = index_min_max(ar_mush, n2, true).first;
            mini = index_min_max(ar_mush, n2, true).second;
            //cout << "Type 1:  " << "maxi: " << maxi <<  " mini:  " << mini << endl; 
            k.HP -= (maxi + mini);
        }
        else if(type == 2){
            int mtx = -2; short mti = -3;
            if(isMountain(ar_mush, n2, mtx, mti)){
                k.HP -= (mtx + mti);
            }
            else{
                mtx = -2; mti = -3;
                k.HP -= (mtx + mti);
            }
            // cout << "Type 2:  " << "mtx: " << mtx <<  " mti:  " << mti << endl; 
        }
        else if(type == 3){
            int* ar = new int[n2];
            for(int i = 0; i < n2; ++i){
                if(ar_mush[i] < 0){
                    ar[i] = (-17 * ar_mush[i] + 9) % 257;
                }
                else ar[i] = (17 * ar_mush[i] + 9) % 257;
            }
            
            short maxi2 = index_min_max(ar, n2, false).first;
            short mini2 = index_min_max(ar, n2, false).second;
            k.HP -= (maxi2 + mini2);
            //cout << "Type 3:  " << "maxi2: " << maxi2 <<  " mini2:  " << mini2 << endl; 
            delete ar;
        }
        else if(type == 4){
            int* ar = new int[n2];
            for(int i = 0; i < n2; ++i){
                if(ar_mush[i] < 0){
                    ar[i] = (-17 * ar_mush[i] + 9) % 257;
                }
                else ar[i] = (17 * ar_mush[i] + 9) % 257;
            }

            int max2_3x   = index_first_secondMax(ar, n2).first;
            short max2_3i = index_first_secondMax(ar, n2).second;
            k.HP -=(max2_3x + max2_3i);
            //scout << "Type 4:  " << "max2_3x: " << max2_3x <<  " max2_3i:  " << max2_3i << endl; 
            delete ar;
        }
        if(k.HP > k.MaxHP) k.HP = k.MaxHP;
        if(k.HP <= 0) {
            bool c = updateHP(k);
            if(!c)  {return false;}
        }
    }
    update(k);
    return true;
}

bool Event15_17(const short& event, Knight& k){
    if(event == 15) {if(k.remedy < 99) {++k.remedy;}}
    else if(event == 16) {if(k.maidenkiss < 99) {++k.maidenkiss;}}
    else if(event == 17) {if(k.phoenixdown < 99) {++k.phoenixdown;}}

    update(k);
    return true;
}

bool Event19(Knight& k){
    //If visit Event 19, knight will skip
    if(visited[File::Ascle] == true) {update(k); return true;}
    
    int count;
    for(int i = 0; i < r1; ++i){
        count = 0;
        for(int j = 0; j < c1; ++j)
        {
            if(16 <= ar_ascle[i][j] && ar_ascle[i][j] <= 18){
                if(ar_ascle[i][j] == 16){
                    if(k.remedy < 99) ++k.remedy;
                }
                else if(ar_ascle[i][j] == 17){
                    if(k.maidenkiss < 99) ++k.maidenkiss;
                }else{
                    if(k.phoenixdown < 99) ++k.phoenixdown;
                }
                ++count;
            }
            if(count >= 3) break;
        }
    }
    visited[File::Ascle] = true;
    update(k);
    
    return true;
}

//Utility function for Event 18
short returnHP(const string& s){
    string pivot = "merlin";
    if(s.find("Merlin") != std::string::npos || s.find("merlin") != std::string::npos) return 3; 
    for(int i = 0; i < (int)pivot.length(); ++i){
        if(s.find(pivot[i]) == std::string::npos && s.find(pivot[i] - 32) == std::string::npos) return 0;
    }

    return 2;
}

bool Event18(Knight& k){
    //If visit Event 18, knight will skip
    if(visited[File::Merlin] == true) {update(k); return true;}

    for(int i = 0; i < n9; ++i)
        k.HP += returnHP(ar_merlin[i]);
    if(k.HP > k.MaxHP) k.HP = k.MaxHP;
    visited[File::Merlin] = true;
    update(k);

    return true;
}

bool Event99(Knight& k){
    if (k.position == Pos::Arthur ||
       (k.position == Pos::Lancelot && k.level >= 8) ||
       (k.position == Pos::Normal && k.level == 10))
    {
        k.level = 10;
        update(k);
    }
    else{
       k.rescue = 0;
       update(k);
       return false;
    }
    return true;
}

void journey(Knight& k, const string& levents)
{
    stringstream ss(levents);

    bool Continue;
    string eve; ss >> eve;
    int idx_event = 1;
    while(eve.length() !=  0){
        if(eve.compare("13") == 0 || eve.length() >= 3){
            Continue = Event13(eve, k);
        }else
        {
            int id = stoi(eve); 
            if(id == 0) {Event0(k); display(k.HP, k.level, k.remedy, k.maidenkiss, k.phoenixdown, k.rescue); return;}
            else if(1 <= id &&  id <= 5){
                Continue =Event1_5(id, idx_event, k);
            }
            else if (id == 6){               
                Continue = Event6(idx_event, k);
            }
            else if (id == 7){
                Continue = Event7(idx_event, k);
            }
            else if (id == 11){
                Continue = Event11(k);
            }
            else if (id == 12){
                Continue = Event12(k);
            }   
            else if (15 <= id && id <= 17){
                Continue = Event15_17(id, k);
            }
            else if(id == 18){
                Continue = Event18(k);
            }
            else if(id == 19){
                Continue = Event19(k);
            }
            else if(id == 99){
                Continue = Event99(k);
            }
            //else throw 
        }
        if(!Continue) {display(k.HP, k.level, k.remedy, k.maidenkiss, k.phoenixdown, k.rescue); return;}
        if(!(ss >> eve)) {k.rescue = 1; display(k.HP, k.level, k.remedy, k.maidenkiss, k.phoenixdown, k.rescue); return;}
        display(k.HP, k.level, k.remedy, k.maidenkiss, k.phoenixdown, k.rescue);
        ++idx_event;
    }
    return;
}
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    Knight k;
    string lknight, levents, lfile;
    preprocess_file(file_input.c_str(), lknight, levents, lfile);
    initKnight(k, lknight);
    journey(k, levents);

    return;
}

/*======================================END EVENT========================================*/