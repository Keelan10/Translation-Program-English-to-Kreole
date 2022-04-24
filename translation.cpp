//NAME:CANNOO Keelan
//Student ID: 2012638
//Programme: BSc (Hons) Computer Science L1, Group A
//Module: Computer Programming, ICT 1017Y
//DATE: 28 MAY 2021
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
class Dictionary
{
    private:
    //creating an empty vector of pairs. First element is English word and second one is the Kreol translation
    vector<pair<string,string> > dictionary;

    public:
        Dictionary(vector <string> mappings);
        //store only the mapping with the highest frequency for each English word into dictionary vector
        void setDictionary(vector <string> mappings);
        vector<pair<string,string> > getDictionary();
        void displayDictionary();
        string translateWord(string s);
        vector <string> getWords(string sentence);
        vector <string> translateWordsOfSentence(string s);
};
Dictionary::Dictionary(vector <string> mappings)
{
    setDictionary(mappings);
}
void Dictionary::setDictionary(vector <string> mappings)
{
    //to determine whether first or second word of mapping
    int counter=0;
    //temporary variables to store first and second elements of pairs
    string first,second;

    //codes to get the words for each mapping
    for (int i=0;i<mappings.size();i++)
    {
        string currentWord;
        currentWord.clear();
        counter=0;

        for (int j=0;j<(mappings[i]).size();j++)
        {
            if(((mappings[i])[j] == ' ' || (mappings[i])[j] == ':') && currentWord.size()!=0)
            {
                if (counter==0)
                    first=currentWord;

                else if (counter==1){
                    second=currentWord;

                    //see if highest frequency mapping for word is already present in dictionary
                    bool found;
                    found=false;
                    for (int k=0;k<dictionary.size();k++)
                    {
                        if (first==dictionary[k].first)
                            found=true;
                    }
                    //add it to dictionary if it does not exist yet and read next mapping
                    if (found==false)
                        dictionary.push_back(make_pair(first,second));
                    break;
                }
                currentWord.clear();
                counter++;
            }
            else
                currentWord += tolower(mappings[i][j]);
        }
    }
}
void Dictionary::displayDictionary()
{
    for (int i=0;i<dictionary.size();i++)
        cout<<dictionary[i].first<<" "<<dictionary[i].second<<endl;
}
vector<pair<string,string> > Dictionary::getDictionary()
{
     return dictionary;
};
string Dictionary::translateWord(string s)
{
    bool found=false;
    //if word exists in dictionary, fetch the kreol word. Otherwise return the english word itself
    for (int i=0;i<dictionary.size();i++)
    {
        if (s==dictionary[i].first){
            return dictionary[i].second;
            found=true;
            break;
        }
    }
    if (found==false)
        return s;
}
vector <string> Dictionary::getWords(string sentence)
{
    vector <string> words;
    string currentWord;
    words.clear();
    //extracting the words and converting them into lowercase
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
vector <string> Dictionary::translateWordsOfSentence(string s)
{
    vector <string> words;
    vector <string> translatedWords;
    words=getWords(s);
    translatedWords.clear();
    //store each translated word of a sentence into a vector
    for (int i=0;i<words.size();i++)
    {
        translatedWords.push_back(translateWord(words[i]));
    }
    return translatedWords;
}
int main()
{
    //temporary string variable to store each sentence
    string sentenceFromFile;
    //vector variables to store the individual mappings and their frequencies
    vector <string> mapping;

    //codes to load the sentences dataset from a text file into a vector
    ifstream infile1 ("Mapping.txt");
    while (!infile1.eof())
    {
        getline(infile1,sentenceFromFile);
        mapping.push_back(sentenceFromFile);
    }
    infile1.close();
    //creating dictionary
    Dictionary englishToKreol(mapping);
    //englishToKreol.displayDictionary();

    //translating a word
    //cout<<englishToKreol.translateWord("she");

    //codes to load the sentences dataset from a text file into a vector
    ifstream infile2 ("1000_English_A_110521_Test.txt");
    //vector variables to store the English sentences
    vector <string> englishsentences;
    while (!infile2.eof())
    {
        getline(infile2,sentenceFromFile);
        englishsentences.push_back(sentenceFromFile);
    }
    infile2.close();

    //translate english sentences
    ofstream fout("Translated.txt");
    vector <string> translatedwords;
    for (int i=0;i<englishsentences.size();i++)
    {
        translatedwords.clear();
        translatedwords=englishToKreol.translateWordsOfSentence(englishsentences[i]);
        //writing the translated sentences to a file
        for (int j=0;j<translatedwords.size();j++)
        {
            fout<<translatedwords[j];
            if (j==translatedwords.size()-1){
                fout<<".";
                if (i!=englishsentences.size()-1)
                    fout<<endl;
            }
            else
                fout<<" ";


        }

    }
}
