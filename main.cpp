
// ========================================================================
// Name  : Leoul Tilahun                                                 //
// Title : InfixToPostfix                                                //
// To    : Dr. NG                                                        //
// Date  : April 1st, 2019                                               //
// ========================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include "Stack.h"

using namespace std;

const string BASE_ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int BASE = 36;

string getInfix();
string getPostFix();
int getUserChoice();
void printOpening();
bool is_Operand(char item);
bool is_Operator(char item);
int getPrecidence(char item);
int toBase10(char postFixChar);
bool checkUserChoice(string userInput);
string toAnotherBase(int finalOutput);
string evaluatePostfix(string postFixExp);
bool checkPostfixExpress(string userInput);
bool checkInfixExpression(string userInput);
string infixToPostfix(string infixExpression);
bool checkBalancedParathesis(string userInput);
string removeChar(string userInput, char removedChar);
bool checkPrecidence (char firstChar, char secondChar);
int performOperation(char givenOperator, int number1, int number2);

int main()
{
    int userChoice;
    string postfixExp, infixExp, finalResult;

    printOpening();
    userChoice = getUserChoice();

    if (userChoice == 1)
    {
        infixExp = getInfix();
        postfixExp = infixToPostfix(infixExp);
        cout << endl << " Postfix: " << postfixExp << endl;
    }
    else if (userChoice == 2)
    {
        postfixExp = getPostFix();
        finalResult = evaluatePostfix(postfixExp);
        cout << endl << " Evaluated:" << finalResult << endl;
    }
    else
    {
        infixExp = getInfix();
        postfixExp = infixToPostfix(infixExp);
        cout << endl << " Postfix: " << postfixExp << endl;
        finalResult = evaluatePostfix(postfixExp);
        cout << endl << " Evaluated: " << finalResult << endl;
    }


}

//==========================================================================//
//             Removes Character from the given input                       //
//==========================================================================//

string removeChar(string userInput, char removedChar)
{
    string finalString = "";

    for (int i = 0; i < userInput.length(); i++)
    {
        if(userInput[i] != removedChar)
        {
            finalString += userInput[i];
        }
    }
    return finalString;
}

//==========================================================================//
//              Checks if the given character is Operand                    //
//==========================================================================//

bool is_Operand(char item)
{
    bool result;
    result = false;

    for (int i = 0; i < BASE; i++)
    {
        if (item == BASE_ALPHABET[i])
        {
            result = true;
        }
    }

    return result;
}

//==========================================================================//
//              Checks if the given character is Operator                   //
//==========================================================================//

bool is_Operator(char item)
{
    bool result;
    result = false;

    if (item == '+' ||
        item == '-' ||
        item == '*' ||
        item == '/' )
    {
        result = true;
    }

    return result;
}

//==========================================================================//
//             returns the precidence of the opreators                      //
//==========================================================================//

int getPrecidence(char item)
{
    int precidence;

	switch(item)
	{
        case '+':
        case '-':
            precidence = 1;
            break ;
        case '*':
        case '/':
            precidence = 2;
            break ;
        default:
            precidence = -1;
	}
	return precidence;
}

//==========================================================================//
//             checks the precidence of the opreators                       //
//==========================================================================//

bool checkPrecidence (char firstChar, char secondChar)
{
    return (getPrecidence(firstChar) >= getPrecidence(secondChar)? true : false);
}

//==========================================================================//
//          gets an infix statement and changes it to postfix               //
//==========================================================================//

string infixToPostfix(string infixExpression)
{
    Stack <char> operatorStack;
    string finalPostfix = "";

    for (int i = 0; i < infixExpression.length(); i++)
    {
        if (is_Operand(infixExpression[i]))
        {
            finalPostfix += infixExpression[i];
        }

        else if (is_Operator(infixExpression[i]))
        {
            while (!operatorStack.is_Empty() &&
                    (infixExpression[i] != '(') &&
                    checkPrecidence(operatorStack.top(), infixExpression[i]))
            {
                finalPostfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(infixExpression[i]);
        }

        else if (infixExpression[i] == '(')
        {
            operatorStack.push(infixExpression[i]);
        }

        else if (infixExpression[i] == ')')
        {
            while ( !operatorStack.is_Empty() &&
                    (operatorStack.top() != '('))
            {
                finalPostfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
    }
    while (!operatorStack.is_Empty())
    {
        finalPostfix += operatorStack.top();
        operatorStack.pop();
    }

    return finalPostfix;
}

//==========================================================================//
//       gets a postfix expression then returns an evaluation               //
//==========================================================================//

string evaluatePostfix(string postFixExp)
{
    Stack<int> value;
    int finalOutput = 0;
    int firstChar;
    int secondChar;

    for (int i = 0; i < postFixExp.length(); i++)
    {
        if (is_Operand(postFixExp[i]))
        {
            if (!value.is_Full())
            {
                value.push(toBase10(postFixExp[i]));
            }
        }
        else if (is_Operator(postFixExp[i]))
        {
            firstChar = value.top();
            value.pop();
            secondChar = value.top();
            value.pop();
            finalOutput = performOperation(postFixExp[i], secondChar, firstChar);
            value.push(finalOutput);

        }
    }
    if (postFixExp.length() == 1)
    {
        finalOutput += toBase10(postFixExp[0]);
    }

    return toAnotherBase(finalOutput);
}

//==========================================================================//
//      Gets a Base 36 char and changes it to the base 10                   //
//==========================================================================//

int toBase10(char postFixChar)
{
    int base10 = 0;

    if (postFixChar >= '0' &&
        postFixChar <= '9')
    {
        base10 = postFixChar - '0';
    }
    else
    {
        base10 = (postFixChar - 'A') + 10;
    }

    return  base10;
}

//==========================================================================//
//      Gets a Base 10 and changes to a string with the given BASE form     //
//==========================================================================//
string toAnotherBase(int finalOutput)
{
    string toOtherBase = "";
    bool foundNegative = false;
    int tempQuotient;
    int passed;

    if (finalOutput < 0)
    {
        foundNegative = true;
        finalOutput *= -1;
    }

    tempQuotient = finalOutput / BASE;
    passed = finalOutput % BASE;
    toOtherBase = toOtherBase + BASE_ALPHABET[passed];

    while (tempQuotient != 0)
    {
        passed = tempQuotient % BASE;
        toOtherBase = BASE_ALPHABET[passed] + toOtherBase;
        tempQuotient = tempQuotient / BASE;
    }

    if (foundNegative)
    {
        toOtherBase = '-' + toOtherBase;
    }

    return toOtherBase;
}

//==========================================================================//
//      Gets an opreator and with two numbers and returns the result        //
//      of the two numbers when the operator applied                        //
//==========================================================================//

int performOperation(char givenOperator, int number1, int number2)
{
    int finalResult;

    switch (givenOperator)
    {
        case '+':
            finalResult = number1 + number2;
            break;
        case '-':
            finalResult = number1 - number2;
            break;
        case '*':
            finalResult = number1 * number2;
            break;
        case '/':
            finalResult = number1 / number2;
            break;
    }

    return finalResult;
}

//==========================================================================//
//                  Prints the opening statement                            //
//==========================================================================//

void printOpening()
{
    cout << endl;
    cout << " The program can do:" << endl;
    cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " 1) read in an infix expression and convert it into postfix form " << endl;
    cout << " 2) read in a postfix expression and evaluate the postfix expression " << endl;
    cout << " 3) read in an infix expression, convert it to postfix form, and then evaluate it." << endl;
    cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
}

//==========================================================================//
//      Checks if the given infix expression has a balanced parenthesis      //
//==========================================================================//

bool checkBalancedParathesis(string userInput)
{
    bool isBalanced = true;
    int numOfOpenPara, numOfClosedPara;

    numOfClosedPara = 0;
    numOfOpenPara = 0;
    for (int i = 0; i < userInput.length(); i++)
    {
        if (userInput[i] == '(')
        {
            numOfOpenPara++;
        }
        if (userInput[i] == ')')
        {
            numOfClosedPara++;
        }
        if (numOfClosedPara > numOfClosedPara)
        {
            isBalanced = false;
        }
    }

    if (numOfOpenPara != numOfClosedPara)
    {
        isBalanced = false;
    }
    return isBalanced;
}

//==========================================================================//
//      gets the user choice for the selection given on the opening         //
//      statement.                                                          //
//==========================================================================//

int getUserChoice()
{
    string userInput;

    cout << endl << " Enter your choice ( 1, 2, or 3): ";
    getline(cin, userInput);
    userInput = removeChar(userInput, ' ');

    while (checkUserChoice(userInput))
    {
        cout << " Error!!! Enter your choice ( 1, 2, or 3): ";
        getline(cin, userInput);
        userInput = removeChar(userInput, ' ');
    }

    return stoi(userInput);
}

//==========================================================================//
//      Checks if the user input is correct for the choices                 //
//==========================================================================//

bool checkUserChoice(string userInput)
{
    bool inCorrect = false;

    if (userInput.length() != 1)
    {
        inCorrect = true;
    }

    if (userInput[0] < '1' || userInput[0] > '3')
    {
        inCorrect = true;
    }
    return inCorrect;
}

//==========================================================================//
//      Checks if the user input for the infix is correct                   //
//==========================================================================//

bool checkInfixExpression(string userInput)
{
    bool isCorrect = true;
    int numOfOperand = 0;
    int numOfOperator = 0;
    int difference = 0;

    for (int i = 0; i < userInput.length(); i++)
    {
        if (is_Operand(userInput[i]))
        {
            numOfOperand++;
        }

        else if (is_Operator(userInput[i]))
        {
            numOfOperator++;
        }

        else if (userInput[i] == '(')
        {
            if (i != 0)
            {
                if (!is_Operator(userInput[i - 1]) &&
                    userInput[i - 1] != '(')
                {
                    isCorrect = false;
                }
            }

            if (!is_Operand(userInput[i + 1]) &&
                userInput[i + 1] != '(')
            {
                isCorrect = false;
            }
        }

        else if (userInput[i] == ')')
        {
            if (i != userInput.length() - 1)
            {
                if (!is_Operator(userInput[i + 1]) &&
                    userInput[i + 1] != ')')
                {
                    isCorrect = false;
                }
            }

            if (!is_Operand(userInput[i - 1]) &&
                userInput[i - 1] != ')')
            {
                isCorrect = false;
            }
        }

        else
        {
            isCorrect = false;
        }

        difference = numOfOperand - numOfOperator;

        if (difference != 0 && difference != 1)
        {
            isCorrect = false;
        }
    }

    difference = numOfOperand - numOfOperator;

    if (difference != 1)
    {
        isCorrect = false;
    }

    return isCorrect;
}

//==========================================================================//
//        Checks if the user input for the Postfix is correct               //
//==========================================================================//

bool checkPostfixExpress(string userInput)
{
    bool isCorrect = true;
    int numOfOperand = 0;
    int numOfOperator = 0;
    int difference = 0;

    for (int i = 0; i < userInput.length(); i++)
    {
        if (is_Operand(userInput[i]))
        {
            numOfOperand++;
        }
        else if (is_Operator(userInput[i]))
        {
            numOfOperator++;
        }
        else
        {
            isCorrect = false;
        }

        if (numOfOperand <= numOfOperator)
        {
            isCorrect = false;
        }
    }

    difference = numOfOperand - numOfOperator;

    if (difference != 1)
    {
        isCorrect = false;
    }

    return isCorrect;

}

//==========================================================================//
//                    Gets the infix character                              //
//==========================================================================//

string getInfix()
{
    string userInput;

    cout << " Enter an infix expression: ";
    getline(cin, userInput);

    while ( userInput.length() == 0 ||
            !checkBalancedParathesis(userInput) ||
            !checkInfixExpression(userInput))
    {
        cout << " Error!!! Enter an infix expression: ";
        getline(cin, userInput);
    }
    return userInput;
}

//==========================================================================//
//                  Gets the Postfix character                              //
//==========================================================================//

string getPostFix()
{
    string userInput;

    cout << " Enter an postfix expression: ";
    getline(cin, userInput);

    while ( userInput.length() == 0 ||
            !checkPostfixExpress(userInput))
    {
        cout << " Error!!! Enter an postfix expression: ";
        getline(cin, userInput);
    }
    return userInput;
}


