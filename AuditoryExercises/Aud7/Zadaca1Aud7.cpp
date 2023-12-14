#include<iostream>
#include<cstring>

using namespace std;

class TennisPlayer {
protected:
    char name[50];
    bool playsInLeague;
public:
    TennisPlayer(char *n = "", bool pIL = false) {
        strcpy(name, n);
        playsInLeague = pIL;
    }

    TennisPlayer(const TennisPlayer &t) {
        strcpy(name, t.name);
        playsInLeague = t.playsInLeague;
    }

    void print() {
        cout << "Tennis player: " << name << " " << (playsInLeague ? "plays in league" : "doesn't play in league")
             << endl;
    }

    friend ostream &operator<<(ostream &out, const TennisPlayer &tp) {
        return out << "Tennis player: " << tp.name << " "
                   << (tp.playsInLeague ? "plays in league" : "doesn't play in league");
    }
};

class RankedTennisPlayer : public TennisPlayer {
private:
    int rank;
public:
    RankedTennisPlayer(char *n = "", bool pIL = false, int rank = 100) : TennisPlayer(name, playsInLeague) {
        this->rank = rank;
    }

    RankedTennisPlayer(TennisPlayer &tp, int rank) : TennisPlayer(tp) {
        this->rank = rank;
    }

    RankedTennisPlayer(const RankedTennisPlayer &rtp) : TennisPlayer(rtp) {
        this->rank = rtp.rank;
    }

    friend ostream &operator<<(ostream &out, const RankedTennisPlayer &rtp) {
        out << "Ranked";
        TennisPlayer tmp(rtp);
        out << tmp << ", is ranked " << rtp.rank;
        return out;
    }

};

int main() {
    TennisPlayer tp("Roger Federer", true);
    cout << tp;
    RankedTennisPlayer rtp(tp, 1);
    cout << rtp;
    return 0;
}