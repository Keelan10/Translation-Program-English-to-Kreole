# Translation Program English to Kreole
## Overview
This is a program to translate sentences from English to Kreole using a given dataset.

## How it works?
### Dataset
The file 1000_KM_A_040521.txt contains the kreole translation of the english sentences in 1000_English_A_040521.txt. Each line corresponds to a sentence.

### Mapping
The program mapping.cpp maps each english word of a sentence to all the words of its corresponding kreole translation. Associated with each mapping (english-kreole pair) is its frequency. After the operation is performed on all the sentences, the mappings are sorted in decreasing order of frequency and the result is written to a new file called Mapping.txt.

### Translation
Using the highest frequency mapping of each word, the program translation.cpp translates the sentences of 1000_English_A_110521_Test.txt (test data) to kreole and the result is written to Translated.txt. If a particular english word does not have a corresponding kreole word, the word remains the same.

### Accuracy
The program accuracy.cpp compares each sentence of Translated.txt with its actual kreole translation in 1000_KM_A_110521_Test.txt and the accuracy of the translation is determined. 

![Accuracy](https://user-images.githubusercontent.com/96436249/167915436-e56e11a9-cb80-4ce4-81f9-100990aa4f3e.png)
