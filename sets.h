#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//set class and associated methods
class sets {
    public:
        sets();
        sets(vector<int> list);
        //print cout << 'our set';
        //isIN a^S (S is our set, a is an int)
        //add S+=a 
        //* intersection
        //+ Union
        //- Difference
        //< proper subset
        //<= subset
        //isEmpty !S true if empty
        //subset
        int size();
    private:
        vector<int> set;

    friend ostream & operator<<(ostream &out, const sets &obj)
    {
        out << "The set contains: ";
        for(int n : obj.set)
        {
            out << n << " ";
        }

        return out;
    }

    friend bool operator^(int y, sets &x)
    {
        for(int n: x.set)
        {
            if(n == y)
            {
                return true;
            }
        }

        return false;
    }

    friend void operator+=(sets &x, int y)
    {
        for(int n: x.set)
        {
            if(n == y)
            {
                return;
            }
        }
        x.set.push_back(y);
    }

    friend sets operator*(sets &x, sets &y)
    {
        sets res;

        for(int n: x.set)
        {
            for(int m: y.set)
            {
                if(n == m)
                {
                    res += n;
                }
            }
        }

        return res;
    }

    friend sets operator+(sets &x, sets &y)
    {
        sets res;

        for(int n: x.set)
        {
            res += n;
        }
        
        for(int m: y.set)
        {
            res += m;
        }

        return res;
    }

    friend sets operator-(sets &x, sets &y)
    {
        sets res;

        for(int n: x.set)
        {
            int val = 0;
            for(int m: y.set)
            {
                if(n == m)
                {
                    val = 1;
                }
            }

            if(val == 0)
            {
                res += n;
            }
        }

        return res;
    }

    friend bool operator<(sets &x, sets &y)
    {
        for(int n: x.set)
        {
            int found = 0;
            for(int m: y.set)
            {
                if(n == m)
                {
                    found = 1;
                }
            }

            if(found == 0)
            {
                return false;
            }
        }

        vector<int> a = x.set;
        vector<int> b = y.set;
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if(a != b)
        {
            return true;
        }

        return false;
    }

    friend bool operator<=(sets &x, sets &y)
    {
        for(int n: x.set)
        {
            int found = 0;
            for(int m: y.set)
            {
                if(n == m)
                {
                    found = 1;
                }
            }

            if(found == 0)
            {
                return false;
            }
        }

        return true;
    }

    friend bool operator!(sets &x)
    {
        int size = x.set.size();

        if(size == 0)
        {
            return true;
        }
        return false;
    }

};

sets::sets()
{
    
}

sets::sets(vector<int> list)
{
    set = list;
}

int sets::size()
{
    return set.size();
}