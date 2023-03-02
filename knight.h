#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"


bool isMountain(int* ar, const int& size, int& mtx, short& mti);
bool isPrime(const int& n);
void increasePrime(int& n);
int decrease_Fibo(const int& n);
int sum_of_max(const int& n);
pair<short, short> index_min_max(int* ar, const int& size, bool last);
pair<int, short> index_first_secondMax(int* ar, const int& size);

enum Shape {Tiny, Frog, Human};
enum Pos {Arthur, Lancelot, Normal};
enum File {Mush = 0, Ascle, Merlin};

struct State{
    Shape s;
    short time; // time = -1 means that time is infinity
};

struct Knight{
    int HP, MaxHP, PrevHP;
    short level, prelevel;
    short remedy;
    short maidenkiss;
    short phoenixdown;
    struct State state;
    Pos position;
    short rescue;

    void init(const int& _HP, const short& _level,
              const short& _remedy, const short& _maidenkiss,
              const short& _phoenixdown){
        HP = _HP;
        MaxHP = _HP;
        level = _level;
        remedy = _remedy;
        maidenkiss = _maidenkiss;
        phoenixdown = _phoenixdown;
        state = {Shape::Human, -1};
        rescue = -1;

        if(MaxHP == 999) position = Pos::Arthur;
        else if(isPrime(MaxHP)) position = Pos::Lancelot;
        else position = Pos::Normal;
        return;
    }
};

struct BaseDamage{
    constexpr static float MadBear = 1;
    constexpr static float Bandit = 1.5;
    constexpr static float LordLupin = 4.5;
    constexpr static float Elf = 7.5;
    constexpr static float Troll = 9.5;
}; 

void processString(string& res);
void preprocess_file(const char* fname, string& lknight, string& levents, string& lfile);
void initKnight(Knight& k, const string& lknight);
void updateShape(Knight& k);	
void update(Knight& k);
bool updateHP(Knight& k);
bool Event0(Knight& k);
bool Event1_5(const short& event, const short& idx_event, Knight& k);
bool Event6(const short& idx_event, Knight& k);
bool Event7(const short& idx_event, Knight& k);
bool Event11(Knight& k);
bool Event12(Knight& k);
bool Event13(const string& s, Knight& k);
bool Event15_17(const short& event, Knight& k);
bool Event19(Knight& k);
short returnHP(const string& s);
bool Event18(Knight& k);
bool Event99(Knight& k);
void journey(Knight& k, const string& levents);



void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);




#endif // __KNIGHT_H__