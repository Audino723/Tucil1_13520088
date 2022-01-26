#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

void readFile(vector<vector<char>> *puzzles, vector<vector<char>> *words, int *m, int *n)
{
    ifstream inFile;
    char readChar;
    bool isNewLine;
    int i;

    //Opening directory
    string fileName;
    cout << "Input filename : ";
    cin >> fileName;
    inFile.open("puzzles\\" + fileName);

    //Error handling
    if (!inFile) {
        cerr << "Can't find the specified file";
        exit(1);
    }

    //Read puzzles per char
    while (inFile.get(readChar)) {
        if (readChar == '\n')
        {
            if (isNewLine)
            {
                break;
            }
            (*puzzles).push_back({});
            isNewLine = true;
            i++;
            (*n)++;
        }
        else if (readChar != ' ')
        {
            (*puzzles)[i].push_back(readChar);
            (*m)++;
            isNewLine = false;
        }
    }
    //Read words per char
    i = 0;
    isNewLine = false;
    while (inFile.get(readChar)) {
        if (readChar == '\n')
        {   
            (*words).push_back({});
            i++;
        }
        else if (readChar != ' ')
        {
            (*words)[i].push_back(readChar);
        }
    }
    inFile.close();
}

void tesShowFile(vector<vector<char>> puzzles, vector<vector<char>> words, int m, int n)
{
    //Keperluan testing di awal
    cout << "Size n : " << n << endl;
    cout << "Size m : " << m << endl << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << puzzles[i][j];
        }   
        cout << endl;
    }

    cout << endl;
    for (int i = 0; i < words.size(); i++)
    {
        cout << i + 1 << ". ";
        for (int j = 0; j < words[i].size(); j++)
        {
            cout << words[i][j];
        }   
        cout << endl;
    }
}

bool validDirection(int i, int j, int wordSize, int direction, int m, int n)
{   
    /*
        1-8 menunjukkan arah, 
        dimulai dari 1 (atas), 2 (atas kanan), ..., 8 (atas kiri). -> perputaran searah jarum jam
    */

   switch(direction) {
    case 1:
        if (i - wordSize + 1 >= 0)
        {
            return true;
        }
        break;    
    case 2:
        if (i - wordSize + 1 >= 0 && j + wordSize <= m)
        {
            return true;
        }
        break;    
    case 3:
        if (j + wordSize <= m)
        {
            return true;
        }
        break;    
    case 4:
        if (j + wordSize <= m && i + wordSize <= n)
        {
            return true;
        }
        break;    
    case 5:
        if (i + wordSize <= n)
        {
            return true;
        }
        break;    
    case 6:
        if (i + wordSize <= n && j - wordSize + 1 >= 0)
        {
            return true;
        }
        break;    
    case 7:
        if (j - wordSize + 1 >= 0)
        {
            return true;
        }
        break;    
    case 8:
        if (j - wordSize + 1 >= 0 && i - wordSize + 1 >= 0)
        {
            return true;
        }        
        break;
    }
    return false;
}

bool validWord(vector<vector<char>> puzzles, vector<char> word, int wordSize, int i, int j, int direction, int *numComp)
{
    int verMove = 0, horMove = 0;

    //Configuring move direction
    switch(direction) {
        case 1:
            verMove = -1;
            break;
        case 2:
            verMove = -1;
            horMove = 1;
            break;
        case 3:
            horMove = 1;
            break;
        case 4:
            verMove = 1;
            horMove = 1;
            break;
        case 5:
            verMove = 1;
            break;
        case 6:
            verMove = 1;
            horMove = -1;
            break;
        case 7:
            horMove = -1;
            break;
        case 8:
            verMove = -1;
            horMove = -1;
            break;
        }
    
    //Checking the puzzles per char
    int iCheck = i + verMove;
    int jCheck = j + horMove;
    bool isFound = true;
    for(int k = 1; k < wordSize; k++)
    {
        *numComp+=1;
        //---COMPARING---
        if (puzzles[iCheck][jCheck] != word[k])
        {
            isFound = false;
            break;
        }

        iCheck += verMove;
        jCheck += horMove;
    }
    return isFound;
}

void showAnswer(int n, int m, int direction, vector<char> word, int i, int j, int wordSize)
{
    int verMove = 0, horMove = 0;
    switch(direction) {
        case 1:
            verMove = -1;
            break;
        case 2:
            verMove = -1;
            horMove = 1;
            break;
        case 3:
            horMove = 1;
            break;
        case 4:
            verMove = 1;
            horMove = 1;
            break;
        case 5:
            verMove = 1;
            break;
        case 6:
            verMove = 1;
            horMove = -1;
            break;
        case 7:
            horMove = -1;
            break;
        case 8:
            verMove = -1;
            horMove = -1;
            break;
        }

    int iCheck, jCheck;
    int temp;
    int iMag, jMag;

    //Print the word
    for (int iPrint = 0; iPrint < wordSize; iPrint++)
    {
        cout << word[iPrint];
    }
    cout << endl;
    for (int iPrint = 0; iPrint < n; iPrint++)
    {
        iCheck = iPrint - i;
        iMag = iCheck * verMove; //Magnitude of vertical and horizontal movement
        for (int jPrint = 0; jPrint < m; jPrint++)
        {
            jCheck = jPrint - j;
            jMag = jCheck * horMove;

            if (jMag >= 0 && jMag < wordSize && iMag >= 0 && iMag < wordSize )
            {
                //Print kanan-kiri
                if (verMove == 0 && iCheck == 0)
                {
                    temp = jCheck/horMove;
                    cout << word[temp] << ' ';
                }
                //Print Atas-bawah
                else if (horMove == 0 && jCheck == 0)
                {
                    temp = iCheck/verMove;
                    cout << word[temp] << ' ';
                }
                //Print Diagonal
                else if (verMove != 0 && horMove !=0 && iMag == jMag)
                {
                    temp = iCheck/verMove;
                    cout << word[temp] << ' ';
                }
                else
                {
                    cout << "- ";
                }
            }
            else
            {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    vector<vector<char>> puzzles {{}}, words {{}};
    vector<char> word;
    int m = 0, n = 0;
    bool isFound;
    int found = 0;

    //Read Config File
    readFile(&puzzles, &words, &m, &n);
    
    //Readjusting  m and n
    m = (m/n);

    //Greedy Algorithm
    auto start = high_resolution_clock::now();
    
    //Iterates per word
    int i, j;
    int direction, wordIndex = 0, wordSize, wordsSize = words.size();
    int numComp = 0;

    while(wordIndex < wordsSize)
    {
        isFound = false;
        i = 0;
        word = words[wordIndex];
        wordSize = word.size();
        //iterates per char in puzzle
        while (i < n && !isFound)
        {
            j = 0;
            while(j < m && !isFound)
            {
                //Check the first alphabet
                //---COMPARING---
                numComp += 1;
                if (word[0] != puzzles[i][j])
                {
                    j++; //skipping
                    continue;
                }
                //Validating direction
                for (int direction = 1; direction <= 8; direction ++)
                {
                    //cout << i << " " << j << " " << direction << puzzles[i][j-1] << endl;

                    if(validDirection(i, j, wordSize, direction, m, n))
                    {   
                        //Check if word correct
                        isFound = validWord(puzzles, word, wordSize, i, j, direction, &numComp);

                        if (isFound)
                        {
                            found ++;
                            showAnswer(n, m, direction, word, i , j, wordSize);
                            break;
                        }
                    }
                }
                j++;
            }
            i++;
        }
        //cout << "Comprar : " << numComp << endl;
        wordIndex ++;
    }   

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start) / 1000;
    cout << duration.count() << " ms" << endl; 
    cout << "No. of Comparison : " << numComp << endl;   
    cout << "Found : " << found << "/" << wordsSize << endl;
    while(getchar());

    return 0;
}