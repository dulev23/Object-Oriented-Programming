#include <iostream>
#include <cstring>
using namespace std;
int MAX = 50;
class List
{
private:
    int *broevi;
    int brojBroevi;
public:
    List()
    {
        broevi = nullptr;
        brojBroevi = 0;
    }
    List(const int *broevi1, int brojBroevi1)
    {
        broevi = new int[brojBroevi1];
        for(int i=0;i<brojBroevi1;i++)
        {
            broevi[i] = broevi1[i];
        }
        brojBroevi = brojBroevi1;
    }
    List(const List & l1) : List(l1.broevi, l1.brojBroevi)
    {}//copy-constructor

    List &operator=(const List &other)
    {
        if(this==&other)
        {
            return *this;
        }
        delete[] broevi;
        broevi = new int[other.brojBroevi];
        for(int i=0; i<other.brojBroevi; i++)
        {
            broevi[i] = other.broevi[i];
        }
        brojBroevi = other.brojBroevi;
        return *this;
    }

    void pecati()
    {
        cout<<brojBroevi<<": ";
        for(int i=0;i<brojBroevi;i++)
        {
            cout<<broevi[i]<<" ";
        }
        cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
    }

    int sum()
    {
        int s = 0;
        for(int i=0;i<brojBroevi;i++)
        {
            s+=broevi[i];
        }
        return s;
    }

    double average()
    {
        return (double)sum()/brojBroevi;
    }
    int getN()
    {
        return brojBroevi;
    }
};

class ListContainer
{
private:
    List *listi;
    int brElementi;
    int brObidi;
public:
    ListContainer()
    {
        listi = new List[MAX];
        brElementi = 0;
        brObidi = 0;
    };

    ListContainer(List *l1, int brElementi1, int brObidi1)
    {
        listi = new List[MAX];
        for(int i=0;i<brElementi;i++)
        {
            listi[i]=l1[i];
        }
        brElementi = brElementi1;
        brObidi = brObidi1;
    }

    ListContainer(const ListContainer & lc) : ListContainer(lc.listi, lc.brElementi, lc.brObidi)
    { }

    ListContainer &operator=(const ListContainer &other)
    {
        if(this==&other)
        {
            return *this;
        }
        delete[] listi;
        listi = new List[MAX];
        for(int i=0;i<other.brElementi;i++)
        {
            listi[i] = other.listi[i];
        }
        brElementi = other.brElementi;
        brObidi = other.brObidi;
        return *this;
    }

    void pecati()
    {
        if(brElementi == 0)
            cout<<"The list is empty"<<endl;
        else
        {
            for(int i=0;i<brElementi;i++)
            {
                cout<<"List number: "<<i+1<<" List info: ";
                listi[i].pecati();
            }
            cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
            cout<<"Successful attempts: "<<brElementi<<" Failed attempts: "<<brObidi-brElementi<<endl;
        }
    }
    int sum()
    {
        int s = 0;
        for(int i=0;i<brElementi;i++)
        {
            s+=listi[i].sum();
        }
        return s;
    }
    double average()
    {
        int a = 0;
        for(int i=0;i<brElementi;i++)
        {
            a+=listi[i].getN();
        }
        return (double)sum()/a;
    }
    void addNewList(List l1)
    {
        brObidi++;
        for(int i=0;i<brElementi;i++)
        {
            if(listi[i].sum()==l1.sum())
                return;
        }
        listi[brElementi] = l1;
        brElementi++;
    }
};

int main() {
	
	ListContainer lc;
	int N;	
	cin>>N;	
    
	for (int i=0;i<N;i++) {
		int n;
		int niza[100];
		
		cin>>n;
       
		for (int j=0;j<n;j++){
			cin>>niza[j];
            
		}
       
		List l=List(niza,n);
	
		lc.addNewList(l);
	}	
	
    
    int testCase;
    cin>>testCase;
    
    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.pecati();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.pecati();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();
        
    }
    else {
        lc.pecati();
    }
}
