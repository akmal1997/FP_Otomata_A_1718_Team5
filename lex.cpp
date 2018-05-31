#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    LexicalAnalyzer lexicalAnalyzer;
    ifstream myFile;

    lexicalAnalyzer.getFileName(myFile);
    lexicalAnalyzer.scanFile(myFile);

    return 0;
}

void LexicalAnalyzer::getFileName(ifstream &myFile)
{
    string fileName;

    cout << "Enter file name: ";

    while (true)
    {
        cin >> fileName;
        myFile.open(fileName);

        if (!myFile)
        {
            cout << "Invalid file name, Please enter a valid file name: ";
        }
        else
        {
            break;
        }
    }
}

void LexicalAnalyzer::scanFile(ifstream &myFile)
{
    string currentToken;
    string readLine;
    char lookahead;
    string myNumber = "";
    string myString = "";
    int tempX;

    while (getline(myFile, readLine))
    {
        for (int x = 0; x < readLine.length(); x++)
        {
            tempX = x;
            lookahead = readLine[x];

            token.push_back(readLine[x]);

            if (isWhiteSpace(lookahead))
            {
                token.pop_back();
                analyzeToken(token);
                token.clear();
            }

            else if (isSymbol(lookahead))
            {
                if (lookahead == '/' && readLine[x + 1] == '/')
                {
                    for (int i = x + 1; i < readLine.length(); i++)
                    {
                        token.push_back(readLine[i]);
                        x++;
                    }

                    for (int y = 0; y < token.size(); y++)
                    {
                        myString += token[y];
                    }
                    x++;

                    cout << "TOKEN:COMMENT           "
                         << myString << endl;
                    myString = "";
                    token.clear();
                    break;
                }
                else
                {
                    token.pop_back();
                    analyzeToken(token);
                    token.clear();
                    token.push_back(lookahead);
                    analyzeToken(token);
                    token.clear();
                }
            }

            else if (isdigit(lookahead) && !isalpha(readLine[x - 1]))
            {
                while (isdigit(readLine[x + 1]))
                {
                    token.push_back(readLine[x + 1]);
                    x++;
                }
                for (int y = 0; y < token.size(); y++)
                {
                    myNumber += token[y];
                }
                cout << "TOKEN:NUMBER            " << myNumber << endl;
                myNumber = "";
                token.clear();
            }

            else if (isComment(lookahead))
            {
                for (int i = x + 1; i < readLine.length(); i++)
                {
                    token.push_back(readLine[i]);
                    x++;
                }

                for (int y = 0; y < token.size(); y++)
                {
                    myString += token[y];
                }
                x++;

                cout << "TOKEN:COMMENT           "
                     << myString << endl;
                myString = "";
                token.clear();
                break;
            }

            else if (isString(lookahead))
            {
                token.pop_back();

                while (readLine[x + 1] != '"')
                {
                    token.push_back(readLine[x + 1]);
                    x++;
                }

                //tambahkan token (dalam vector) ke string untuk dicetak
                for (int y = 0; y < token.size(); y++)
                {
                    myString += token[y];
                }
                x++;

                cout << "TOKEN:STRING            "
                     << "\"" << myString << "\"" << endl;
                myString = "";
                token.clear();
            }

            //cek utk melihat karakter berikutnya adalah RELOP
            else if (isRelop(lookahead))
            {
                token.pop_back();

                //apakah karakter berikutnya valid RELOP
                if (isRelop(readLine[x + 1]))
                {
                    token.push_back(lookahead);
                    token.push_back(readLine[x + 1]);
                    x = x + 2;
                    analyzeToken(token);
                    token.clear();
                }

                //CEK APAKAH KARAKTER berikutnya assignment operator
                else if (isAssignOp(readLine[x]))
                {
                    //token.push_back(lookahead);
                    token.push_back(readLine[x]);
                    x = x + 1;
                    analyzeToken(token);
                    token.clear();
                }
                
                else if (lookahead == '<' || lookahead == '>')
                {
                    token.push_back(lookahead);
                    if(readLine[x+1] == '?' && readLine[x+2] == 'p' && readLine[x+3] == 'h' && readLine[x+4] == 'p')
                    {
                        token.push_back(readLine[x+1]);
                        token.push_back(readLine[x+2]);
                        token.push_back(readLine[x+3]);
                        token.push_back(readLine[x+4]);
                        x+=3;
                    }
                    analyzeToken(token);
                    x++;
                    token.clear();
                }
                //invalid token
                else
                {
                    analyzeToken(token);
                    cout << "TOKEN:ERROR             " << lookahead << endl;
                    token.clear();
                }
            }
        }
    }
}

bool LexicalAnalyzer::isAssignOp(char ch)
{
    if (ch == '=')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah whitespace
bool LexicalAnalyzer::isWhiteSpace(char ch)
{
    if (ch == ' ' || ch == '\n' || ch == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah string ("" quotes)
bool LexicalAnalyzer::isString(char ch)
{
    if (ch == '"')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah simbol
bool LexicalAnalyzer::isSymbol(char ch)
{
    if (ch == '(' || ch == ')' || ch == ',' || ch == '{' || ch == '}' || ch == '+' ||
        ch == '-' || ch == '*' || ch == '/' || ch == '&' || ch == '!' || ch == '|' || ch == ';')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah skarakter RELOP
bool LexicalAnalyzer::isRelop(char ch)
{
    if (ch == '=' || ch == '!' || ch == '<' || ch == '>')
    {
        return true;
    }

    else
    {
        return false;
    }
}

//returns true jika argument adalah karakter RELOP
bool LexicalAnalyzer::isRelopString(string currentToken)
{
    if (currentToken == "==" || currentToken == "!=" || currentToken == "<" ||
        currentToken == ">" || currentToken == "<=" || currentToken == ">=")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah KEYWORD FUNCTION
bool LexicalAnalyzer::isFunction(string currentToken)
{
    if (currentToken == "function")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah KEYWORD if
bool LexicalAnalyzer::isIf(string currentToken)
{
    if (currentToken == "if")
    {
        return true;
    }
    else
    {
        return false;
    }

}

//returns true jika argument adalah simbol OR
bool LexicalAnalyzer::isOr(string currentToken)
{
    if (currentToken == "|")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah keyword ELSE
bool LexicalAnalyzer::isElse(string currentToken)
{
    if (currentToken == "else")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah simbol not
bool LexicalAnalyzer::isNot(string currentToken)
{
    if (currentToken == "!")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::isOpeningTag(string currentToken)
{
    if (currentToken == "<?php")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::isClosingTag(string currentToken)
{
    if (currentToken == "?>")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::isEcho(string currentToken)
{
    if (currentToken == "echo")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool LexicalAnalyzer::isDie(string currentToken)
{
    if (currentToken == "die")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah keyword RETURN
bool LexicalAnalyzer::isReturn(string currentToken)
{
    if (currentToken == "return")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah keyword var
bool LexicalAnalyzer::isVar(string currentToken)
{
    if (currentToken == "var")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah keyword while
bool LexicalAnalyzer::isWhile(string currentToken)
{
    if (currentToken == "while")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah ID
bool LexicalAnalyzer::isID(string currentToken)
{
    if ((isalnum(currentToken[0]) || (currentToken[0] == '$' && isalpha(currentToken[1]))) && currentToken != "if" && currentToken != "function" &&
        currentToken != "else" && currentToken != "return" && currentToken != "var" &&
        currentToken != "while" && currentToken != "echo" &&  currentToken != "die")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah kurung buka
bool LexicalAnalyzer::isParenL(string currentToken)
{
    if (currentToken == "(")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns truejika argument adalah kurung tutup
bool LexicalAnalyzer::isParenR(string currentToken)
{
    if (currentToken == ")")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah kurung kurawal buka
bool LexicalAnalyzer::isCurlL(string currentToken)
{
    if (currentToken == "{")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah kurung kurawal tutup
bool LexicalAnalyzer::isCurlR(string currentToken)
{
    if (currentToken == "}")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah semicolon
bool LexicalAnalyzer::isSemicolon(string currentToken)
{
    if (currentToken == ";")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah operasi pertambahan/pengurangan
bool LexicalAnalyzer::isAddOp(string currentToken)
{
    if (currentToken == "+" || currentToken == "-")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah operasi perkalian/pembagian
bool LexicalAnalyzer::isMulOp(string currentToken)
{
    if (currentToken == "/" || currentToken == "*")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah tanda koma
bool LexicalAnalyzer::isComma(string currentToken)
{
    if (currentToken == ",")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah simbol and
bool LexicalAnalyzer::isAnd(string currentToken)
{
    if (currentToken == "&")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah assignment operator
bool LexicalAnalyzer::isAssignmentOperator(string currentToken)
{
    if (currentToken == "=")
    {
        return true;
    }
    else
    {
        return false;
    }
}

//returns true jika argument adalah simbol komentar
bool LexicalAnalyzer::isComment(char ch)
{
    if (ch == '#')
    {
        return true;
    }
    else
    {
        return false;
    }
}
//tentukan jenis token pada argument
void LexicalAnalyzer::analyzeToken(vector<char> token)
{
    string currentToken;
    for (int x = 0; x < token.size(); x++)
    {
        currentToken += token[x];
    }

    //checks jika token merupakan fungsi
    if (isFunction(currentToken))
    {
        cout << "TOKEN:FUNCTION          " << currentToken << endl;
    }

    else if(isClosingTag(currentToken))
    {
        cout << "TOKEN:CLOSETAG          " << currentToken << endl;
    }

    else if(isOpeningTag(currentToken))
    {
        cout << "TOKEN:OPENTAG           " << currentToken << endl;
    }

    //jika token merupakan assignment operator
    else if (isAssignmentOperator(currentToken))
    {
        cout << "TOKEN:ASSIGNOP          " << currentToken << endl;
    }

    else if (isDie(currentToken))
    {
        cout << "TOKEN:DIE               " << currentToken << endl;
    }

    else if (isEcho(currentToken))
    {
        cout << "TOKEN:ECHo              " << currentToken << endl;
    }

    //jika token merupakan keyword if
    else if (isIf(currentToken))
    {
        cout << "TOKEN:IF                " << currentToken << endl;
    }

    //jika token merupakan keyword else
    else if (isElse(currentToken))
    {
        cout << "TOKEN:ELSE              " << currentToken << endl;
    }

    //jika token merupakan keyword return
    else if (isReturn(currentToken))
    {
        cout << "TOKEN:RETURN            " << currentToken << endl;
    }

    //jika token merupakan not
    else if (isNot(currentToken))
    {
        cout << "TOKEN:NOT               " << currentToken << endl;
    }

    //jika token merupakan or
    else if (isOr(currentToken))
    {
        cout << "TOKEN:OR                " << currentToken << endl;
    }

    //jika token merupakan var
    else if (isVar(currentToken))
    {
        cout << "TOKEN:VAR               " << currentToken << endl;
    }

    //jika token merupakan while
    else if (isWhile(currentToken))
    {
        cout << "TOKEN:WHILE             " << currentToken << endl;
    }

    //jika token merupakan semicolon
    else if (isSemicolon(currentToken))
    {
        cout << "TOKEN:SEMICOLON         " << currentToken << endl;
    }

    //jika token merupakan kurung buka
    else if (isParenL(currentToken))
    {
        cout << "TOKEN:PARENL            " << currentToken << endl;
    }

    //jika token merupakan kurung Tutup
    else if (isParenR(currentToken))
    {
        cout << "TOKEN:PARENR            " << currentToken << endl;
    }

    //jika token merupakan koma
    else if (isComma(currentToken))
    {
        cout << "TOKEN:COMMA             " << currentToken << endl;
    }

    //jika token merupakan kurung kurawal buka
    else if (isCurlL(currentToken))
    {
        cout << "TOKEN:CURLL             " << currentToken << endl;
    }

    //jika token merupakan kurung kurawal tutup
    else if (isCurlR(currentToken))
    {
        cout << "TOKEN:CURLR             " << currentToken << endl;
    }

    //jika token merupakan operasi pertambahan/pengurangan
    else if (isAddOp(currentToken))
    {
        cout << "TOKEN:ADDOP             " << currentToken << endl;
    }

    //jika token merupakan operasi perkalian/pembagian
    else if (isMulOp(currentToken))
    {
        cout << "TOKEN:MULOP             " << currentToken << endl;
    }

    //jika token merupakan and
    else if (isAnd(currentToken))
    {
        cout << "TOKEN:AND               " << currentToken << endl;
    }

    //jika token merupakan RELOP
    else if (isRelopString(currentToken))
    {
        cout << "TOKEN:RELOP             " << currentToken << endl;
    }

    //jika token merupakan ID
    else if (isID(currentToken))
    {
        cout << "TOKEN:ID                " << currentToken << endl;
    }
}
