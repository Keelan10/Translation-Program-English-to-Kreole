//NAME:CANNOO Keelan
//DATE: 28 MAY 2021
//Number of mappings: 38610
//Sentence accuracy: 0.1 %
//Word accuracy: 21 %
/*
WE CAN IMPROVE ACCURACY BY
1. Using a larger dataset for the mappings
2. Making sure the sentences of the dataset are well written. I noticed that among the sentences from line 500 to 1000
   over hundreds had no punctuation at the end of the sentence.
3. Aiming for simple sentences for the mapping will significantly increase accuracy
4. Implementing an algorithm for stemming and lemmatization
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

class Sentence
{
    private:
        //string variable to store one sentence
        string sentence;
        //vector of type string to store the words in a sentence
        vector<string> words;
    public:
        Sentence();
        Sentence(string s);
        string getSentence();
        void setSentence(string s);
        int getNumWords();
        vector <string> getWords();
        ~Sentence();
};

class Mapping
{
    private:
        //string variable to store one mapping
        string mapping;
        //integer variable to store number of times mapping occurs
        int frequency;
    public:
        Mapping();
        Mapping(string m);
        string getMapping();
        void setMapping(string m);
        int getFrequency();
        void setFrequency(int f);
        ~Mapping();
};
Sentence::Sentence(){}
Sentence::Sentence(string s)
{
    sentence=s;
}
string Sentence::getSentence()
{
    return sentence;
}
void Sentence::setSentence(string s)
{
    sentence=s;
}
//return number of words
int Sentence::getNumWords()
{

    string currentWord;
    vector<string> setOfWords;
    for(int i=0;i<sentence.length();i++)
    {
        if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'|| sentence[i] == ';'|| sentence[i] == ':'||sentence[i]==',')
        {
            if (currentWord.size()!=0)
                setOfWords.push_back(currentWord);
                currentWord.clear();
        }
    else
    {
        currentWord += sentence[i];
    }
    }

    return setOfWords.size();
}
//return words of a sentence
vector <string> Sentence::getWords()
{
    string currentWord;
    words.clear();

    for(int i=0;i<sentence.length();i++){
        if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '!' || sentence[i] == '?'|| sentence[i] == ','|| sentence[i] == ';'|| sentence[i] == ':')
        {
            if (currentWord.size()!=0)
                words.push_back(currentWord);
            currentWord.clear();
        }
        else
        {
            currentWord += tolower(sentence[i]);
        }
    }
    return words;
}
Sentence::~Sentence(){}

Mapping::Mapping(){}
Mapping::Mapping(string m)
{
    mapping=m;
    frequency=1;

}
string Mapping::getMapping()
{
    return mapping;
}
void Mapping::setMapping(string m)
{
    mapping=m;
}
int Mapping::getFrequency()
{
    return frequency;
}
void Mapping::setFrequency(int f)
{
    frequency=f;
}
Mapping::~Mapping(){}

//function to sort vector in descending order
bool sortByVal(const pair<string, int> &a, const pair<string, int> &b)
{
    return (a.second > b.second);
}
int main()
{

    //vector variables to store the individual words in one sentence
    vector<string> wordsFromEnglishSentence;
    vector<string> wordsFromKreolSentence;

    //vector variables to store all the sentences from the dataset
    vector<string> allEnglishSentences;
    vector<string> allKreolSentences;
    //temporary string variable to store each sentence from the dataset
    string sentenceFromFile;

    //codes to load the sentences dataset from a text file into a vector
    ifstream infile("1000_English_A_040521.txt");
    ifstream infile1("1000_KM_A_040521.txt");
    while(!infile.eof())
    {
        getline(infile,sentenceFromFile);
        allEnglishSentences.push_back(sentenceFromFile);
        getline(infile1,sentenceFromFile);
        allKreolSentences.push_back(sentenceFromFile);
    }
	infile.close();
    infile1.close();

    //creating a vector of objects of type sentence
    vector<Sentence> s(allEnglishSentences.size());
    vector<Sentence> s1(allKreolSentences.size());

    //assign each extracted sentence (from dataset) to one Sentence object
    for (int i=0;i<allEnglishSentences.size();i++)
    {
        s[i].setSentence(allEnglishSentences[i]);
        s1[i].setSentence(allKreolSentences[i]);
    }

    //creating a vector of objects of type mapping
    vector <Mapping> mapping;
    //string variable to store a mapping
    string value;
    int l=0;
    bool found=false;
    //assign each word of a sentence to a sentence object
    //for each sentence map each english word onto every kreol word
    for (int i=0; i<allEnglishSentences.size();i++)
    {
        wordsFromEnglishSentence=s[i].getWords();
        wordsFromKreolSentence=s1[i].getWords();
        for (int j=0; j<s[i].getNumWords();j++)
        {
            for (int k=0; k<s1[i].getNumWords();k++)
            {
                value=wordsFromEnglishSentence[j] +" " +wordsFromKreolSentence[k];
               l=0;
                //check if mapping already exists
                while (found==false && l<mapping.size())
                {
                    //if mapping exists, increment frequency
                    if (mapping[l].getMapping()==value)
                    {
                        found=true;
                        mapping[l].setFrequency(mapping[l].getFrequency()+1);
                    }
                    l++;
                }
                //else insert mapping into vector
                if (found==false)
                    mapping.push_back(Mapping(value));
                found=false;
            }
        }
    }
    //store the mappings and their frequencies in a map for easier processing
    map<string, int> mappings_frequencies;
    for (int i=0; i<mapping.size(); i++){
        mappings_frequencies.insert(pair<string,int>(mapping[i].getMapping(),mapping[i].getFrequency()));
    }
    //create a empty vector of pairs
    vector<pair<string,int> > vec;
    //create an iterator to the first element in map
    map<string, int> :: iterator it;
        //store the pairs in a vector
        for (it=mappings_frequencies.begin(); it!=mappings_frequencies.end(); it++)
        {
            vec.push_back(make_pair(it->first, it->second));
        }
        // sort the vector by increasing order of its pair's second value
        sort(vec.begin(), vec.end(), sortByVal);

    //writing the sorted mappings and their respective frequencies to mapping.txt
    ofstream fout ("Mapping.txt");
    for (int i = 0; i < vec.size(); i++){
            fout << vec[i].first << ": " <<vec[i].second<< endl;
    }
    fout.close();

    //display sorted mappings and their respective frequencies
    for (int i = 0; i < vec.size(); i++){
        cout << vec[i].first << ": " <<vec[i].second<< endl;
    }

}
