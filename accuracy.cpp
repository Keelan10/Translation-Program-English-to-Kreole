//NAME:CANNOO Keelan
//Student ID: 2012638
//Programme: BSc (Hons) Computer Science L1, Group A
//Module: Computer Programming, ICT 1017Y
//DATE: 28 MAY 2021
//Sentence accuracy: 0.1 %
//Word accuracy: 21 %
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Comparator
{
    private:
        //vector variable of type string to store the manually sentences and sentences which program has translated
        vector <string> manuallyTranslated;
        vector <string> programTranslated;

    public:
        Comparator(vector <string> mT, vector <string> pT);
        //break into words
        vector <string> getWords(string sentence);

        //compare the two vectors and display percentage similarity for sentences
        void SentenceAccuracy();
        //compare the two vectors and display percentage similarity for words
        void WordAccuracy();

};
Comparator::Comparator(vector <string> mT, vector <string> pT)
{
    manuallyTranslated=mT;
    programTranslated=pT;
}
vector <string> Comparator::getWords(string sentence)
{
    vector <string> words;
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
void Comparator::SentenceAccuracy()
{
    //variable to store manually translated words from sentence
    vector <string> manualWords;
    vector <string> programWords;

    bool correct=true;
    int counter=0;
    //comparing sentence
    for (int i=0;i<manuallyTranslated.size();i++)
    {
        manualWords=getWords(manuallyTranslated[i]);
        programWords=getWords(programTranslated[i]);
        correct=true;

        //if number of words don't match, it means sentences are different!
        if (manualWords.size()!=programWords.size())
            continue;

        //comparing words of a sentence
        for (int j=0;j<manualWords.size();j++){
            if (manualWords[j]!=programWords[j]){
                correct=false;
                break;
            }
        }

        if (correct==true){
            counter++;
            for (int l=0;l<manualWords.size();l++)
            {
                cout<<manualWords[l];
                if (l==manualWords.size()-1)
                    cout<<"."<<endl;
                else
                    cout<<" ";
            }
        }
    }
    cout<<counter<<" out of "<<programTranslated.size()<<" sentences accurate"<<endl ;
    cout<<"Sentence Accuracy (%): "<<(100.0*counter/manuallyTranslated.size())<<endl;
}
void Comparator::WordAccuracy()
{
    //variable to store manually translated words from sentence
    vector <string> manualWords;
    vector <string> programWords;

    int counter=0;
    int tot=0;
    int loopcounter=0;
    //comparing sentence
    for (int i=0;i<manuallyTranslated.size();i++)
    {
        manualWords=getWords(manuallyTranslated[i]);
        programWords=getWords(programTranslated[i]);
        //the size of the sentence having the lesser number of words is used for the loop counter so that index is not out of range
        if (manualWords.size()<programWords.size())
            loopcounter=manualWords.size();
        else
            loopcounter=programWords.size();

        //comparing words of a sentence
        for (int j=0;j<loopcounter;j++){
            tot++;
            if (manualWords[j]==programWords[j])
                counter++;
        }
    }
    cout<< "Word Accuracy (%): "<< (100.0*counter/tot)<<endl;
}

int main()
{
    //vector variables to store all the sentences from the dataset
    vector<string> manualSentences;
    vector<string> ProgramSentences;

    //temporary string variable to store each sentence from the dataset
    string sentenceFromFile;

    //load sentences from translated (by program) file into vector
        ifstream infile("Translated.txt");
    while (!infile.eof())
    {
        getline(infile,sentenceFromFile);
        ProgramSentences.push_back(sentenceFromFile);
    }
    infile.close();
    //load sentences from manually translated file into a vector
    ifstream infile1("1000_KM_A_110521_Test.txt");
    while (!infile1.eof())
    {
        getline(infile1,sentenceFromFile);
        manualSentences.push_back(sentenceFromFile);
    }
    infile1.close();

    Comparator optimus(manualSentences,ProgramSentences);
    optimus.SentenceAccuracy();
    optimus.WordAccuracy();


}
