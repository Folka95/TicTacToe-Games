#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H
#include <bits/stdc++.h>
using namespace std;


/**
 # Currently supported functions (all of them loop till they get a valid input)

    * string readLine();
        - This read a non-empty full line.

    * int readInt();
        - Read 32bit integer.

    * int readLongLong();
        - Read 64bit integer.

    * long long readRangeChoice(long long l, long long r)
        - Read at most 64bit integer in the range [l,r] (inclusive)

    * string readRangeChoice(string l, string r)
        - Read a string in the range [l,r] (inclusive) (as strings also)

    * long long readExactChoice(vector< long long > choices)
        - Read at most 64bit integer from some choices

    * string readExactChoice(vector< string > choices)
        - Read a string from some choices

    * string readStringWithCharactersRange(char l1, char r1,char l2 = 0, char r2 = 0,char l3 = 0, char r3 = 0)
        - Read a string contains only character from the ranges [l1 , r1], up to 3 ranges

    * string readStringWithCharacters(vector< char > all)
        - Read a string contains only character from the given vector

    * string readStringWithOUTCharactersRange(char l1, char r1,char l2 = 0, char r2 = 0,char l3 = 0, char r3 = 0)
        - Read a string does not contain any character from the ranges [l1 , r1], up to 3 ranges

    * string readStringWithOUTCharacters(vector< char > all)
        - Read a string does not contain any character from the given vector

    * string getFileName(string extension)
         - Read an exist file name with extension in argument

 # Use example

   * string x = readLine();

   * int y = readRangeChoice(1 , 8);

   * string z = readExactChoice({"a" , "bb" , "this is a choice" , "folka"});

 # Other features

   * void setDeletingLeadingAndEndingSpaces(bool DeleteLeadingAndEndingSpaces)
     - By default set to 'false', you can set it to true to clear the given
       input from the leading and ending spaces.

   * void setStrictOnLetterCase(bool StrictOnLetterCase)
     - By default set to 'true', you can set it to false to allow the any alpha
       compare does not depend on the letter case ('f' = 'F')
**/



class inputValidator{
#define inRange(x,l,r) (l <= x && x <= r)
private:
    const string _undefinedString = " f7$ Qm!x2W8vR #jT1bY5N ";
    const pair< string , string > _intRange = { to_string(INT_MIN) , to_string(INT_MAX) };
    const pair< string , string > _longlongRange = { to_string(LLONG_MIN) , to_string(LLONG_MAX) };
    bool strictOnSpaces = true;
    bool strictOnLetterCase = true;
    /// Clear input and output buffers
    void clearIO()
    {
        cout.flush();
    }

    string stringFormat(string s)
    {
        if(!strictOnSpaces)
            _removeLeadingEndingSpaces(s);
        if(!strictOnLetterCase)
            for(auto &c : s)
                c = tolower(c);
        return s;
    }


    /// Check if that is a part of larger container
    bool isPartOf(auto &check, auto &parent)
    {
        for(auto &child : parent)
        {
            if(check == child)
                return true;
        }
        return false;
    }

    /// Remove leading and ending spaces
    void _removeLeadingEndingSpaces(string &s)
    {
        for(int step = 0; step <= 1; step++)
        {
            while(s.size() && s.back() == ' ')
            {
                s.pop_back();
            }
            reverse(s.begin() ,s.end());
        }
    }

    void removeLeadingZeroes(string &s)
    {
        reverse(s.begin() ,s.end());
        while(s.size() > 1 && s.back() == '0')
        {
            s.pop_back();
        }
        reverse(s.begin() ,s.end());
    }

    void invalidInputWarning(auto err)
    {
        cout << "Invalid input '" << err << "'. please, Enter again:";
    }

    /// Read line
    string _getline()
    {
        string s;
        getline(cin , s);
        if(!strictOnSpaces)
        {
            _removeLeadingEndingSpaces(s);
        }
        while(s.empty())
        {
            clearIO();
            invalidInputWarning(s);
            getline(cin , s);
            if(!strictOnSpaces)
            {
                _removeLeadingEndingSpaces(s);
            }
        }
        if(!strictOnLetterCase)
        {
            for(auto &c : s)
            {
                tolower(c);
            }
        }
        return s;
    }

    /// Check if the string can be a number or not
    bool _isStringNumber(string s)
    {
        if(s[0] == '-')
        {
            s.erase(0 , 1);
        }
        bool valid = (!s.empty());
        bool noDotsFound = false;
        for(auto &d : s)
        {
            valid &= inRange(d , '0' , '9') || (d == '.' && !noDotsFound);
            noDotsFound |= d == '.';
        }
        return valid;
    }

    /// Get an string in costume range
    bool _isStringInNeededRange(const pair< string , string > range, string s)
    {
        string l = range.first;
        string r = range.second;
        // true means +
        // false means -
        bool lSign = (l[0] != '-');
        bool rSign = (r[0] != '-');
        bool sSign = (s[0] != '-');
        if(!(lSign <= sSign && sSign <= rSign))
            return false;
        if(lSign != sSign)
        {
            l = "0";
        }
        else if(rSign != sSign)
        {
            r = "0";
        }
        else if(!lSign && !rSign && !sSign)
        {
            l.erase(0 , 1);
            r.erase(0 , 1);
            s.erase(0 , 1);
        }
        removeLeadingZeroes(s);
        if(s.size() > l.size() || (s.size() == l.size() && s >= l))
        {
            if(s.size() < r.size() || (s.size() == r.size() && s <= r))
            {
                return true;
            }
        }
        return false;
    }

    /// Read an 32bit integer
    int _readInt()
    {
        string num = _getline();
        while(!_isStringNumber(num) || !_isStringInNeededRange(_intRange , num))
        {
            invalidInputWarning(num);
            num = _getline();
        }
        return stoi(num);
    }

    /// Read an 64bit integer
    long long _readLongLong()
    {
        string num = _getline();
        while(!_isStringNumber(num) || !_isStringInNeededRange(_longlongRange , num))
        {
            invalidInputWarning(num);
            num = _getline();
        }
        return stoll(num);
    }


public:
    /// Setters
    void setDeletingLeadingAndEndingSpaces(bool DeleteLeadingAndEndingSpaces)
    {
        strictOnSpaces = !DeleteLeadingAndEndingSpaces;
    }
    void setStrictOnLetterCase(bool StrictOnLetterCase)
    {
        strictOnLetterCase = StrictOnLetterCase;
    }

    /// get the full line
    string readLine()
    {
        return _getline();
    }

    /// get an integer
    int readInt()
    {
        return _readInt();
    }
    long long readLongLong()
    {
        return _readLongLong();
    }

    /// get choice in range from integer l to integer r
    long long readRangeChoice(long long l, long long r)
    {
        long long input = readLongLong();
        while(!inRange(input , l , r)){
            clearIO();
            invalidInputWarning(input);
            input = readLongLong();
        }
        return input;
    }

    /// get choice in range from string l to string r
    string readRangeChoice(string l, string r)
    {
        string input = readLine();
        while(!inRange(input , l , r)){
            clearIO();
            invalidInputWarning(input);
            input = readLine();
        }
        return input;
    }

    /// get exact integer choice
    long long readExactChoice(vector< long long > choices)
    {
        long long input = readLongLong();
        while(!isPartOf(input , choices)){
            clearIO();
            invalidInputWarning(input);
            input = readLongLong();
        }
        return input;
    }

    /// get exact string choice
    string readExactChoice(vector< string > choices)
    {
        for(auto &s : choices)
            stringFormat(s);
        string input = stringFormat(readLine());
        while(!isPartOf(input , choices)){
            clearIO();
            invalidInputWarning(input);
            input = stringFormat(readLine());
        }
        return input;
    }

    /// get string consist of some characters form l to r
    string readStringWithCharactersRange(char l1, char r1,char l2 = 0, char r2 = 0,char l3 = 0, char r3 = 0,char l4 = 0, char r4 = 0)
    {
        set< char > chars;
        while(l1 <= r1)
            chars.insert(l1++);
        while(l2 <= r2)
            chars.insert(l2++);
        while(l3 <= r3)
            chars.insert(l3++);
        while(l4 <= r4)
            chars.insert(l4++);
        chars.erase(char(0));
        return readStringWithCharacters(vector< char > (chars.begin() , chars.end()));
    }

    /// get string consist of some characters form the given set of characters
    string readStringWithCharacters(vector< char > all)
    {
        set< char > chars(all.begin() , all.end());
        string input = readLine();
        do{
            bool valid = true;
            for(auto &c : input)
            {
                valid &= isPartOf(c , all);
            }
            if(valid)
                break;
            clearIO();
            invalidInputWarning(input);
            input = readLine();
        }while(true);
        return input;
    }

    /// get string does not contain any characters form l to r
    string readStringWithOUTCharactersRange(char l1, char r1,char l2 = 0, char r2 = 0,char l3 = 0, char r3 = 0,char l4 = 0, char r4 = 0)
    {
        set< char > chars;
        while(l1 <= r1)
            chars.insert(l1++);
        while(l2 <= r2)
            chars.insert(l2++);
        while(l3 <= r3)
            chars.insert(l3++);
        while(l4 <= r4)
            chars.insert(l4++);
        chars.erase(char(0));
        return readStringWithCharacters(vector< char > (chars.begin() , chars.end()));
    }

    /// get string does not contain any characters form the given set of characters
    string readStringWithOUTCharacters(vector< char > all)
    {
        set< char > chars(all.begin() , all.end());
        string input = readLine();
        do{
            bool notValid = false;
            for(auto &c : input)
            {
                notValid |= isPartOf(c , all);
            }
            if(!notValid)
                break;
            clearIO();
            invalidInputWarning(input);
            input = readLine();
        }while(true);
        return input;
    }

    /// get a valid exists file name with given extension
    string getFileName(string extension)
    {
        auto exist = [](string filename) -> bool {
            ifstream file(filename.c_str());
            return (file.good());
        };
        string filename = readLine();
        while(true)
        {
            if(exist(filename))
            {
                if(filename.size() > extension.size() + 2 && filename.substr(filename.size() - extension.size()) == extension)
                {
                    break;
                }
            }
            else
            {
                filename += "." + extension;
                if(exist(filename))
                    break;
            }
            cout << "File does not exist. Enter a valid exist name :";
            filename = readLine();

        }
        return filename;
    }


};


#endif // INPUTVALIDATOR_H

