#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    int randomNumber = rand() % 100 + 1;
    int userGuess = 0;

    cout << "Guess the number (between 1 and 100): "<<endl<<"Enter Your No : ";

    while (userGuess != randomNumber) {
        cin >> userGuess;

        if (userGuess > randomNumber) {
           cout << "Too high! Try again: ";
        } else if (userGuess < randomNumber) {
            cout << "Too low! Try again: ";
        } else {
            cout << "Congratulations! You guessed the correct number!" << endl;
        }
    }

    return 0;
}
