#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
using std::cout;
using std::cin;
using std::string;
using std::rand;
using std::ifstream;
using std::vector;
using std::endl;

string filename =  "questions.txt";
bool err = false;

std::string readLine(int line) {
   std::ifstream in(filename);

   std::string s;
   s.reserve(10);    

   for(int i = 0; i < line; ++i)
       std::getline(in, s);

   std::getline(in,s);
   return s; 
}

class Question {
    private:
        string question;
        vector<string> answers;
        int correct;
    public:
        Question(int l) {
            string line = readLine(l);
            std::istringstream iss(line);
            string s;
            for(int i = 0; getline(iss, s, '|'); i++) {
                switch(i) {
                    case 0:
                        question = s;
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                        answers.push_back(s);
                        break;
                    default:
                        cout << "Something went wrong while loading the questions.";
                        err = true;
                        break;
                }
            }
        }

        string getQuestion() {
            return question;
        }
        vector<string> getAnswers() {
            int random = 1+(rand() % 3);
            string c = answers.at(0);
            correct = random;
            vector<string> possible;
            for(int i = 0; i < 4; i++) {
                if(i < random) {
                    possible.push_back(answers.at(i+1));                    
                } else if(i == random) {
                    possible.push_back(c);                    
                } else {
                    possible.push_back(answers.at(i-1));                    
                }
            }
            return possible;
        }
        
        bool valid(int ans) {
            if(ans == correct) return true;
            return false;
        }
};

int main() {
    srand(time(0));
    
    vector<Question> questions;
    ifstream file(filename);
    string tmp;
    int i = 0;
    while (getline(file, tmp)) {
        Question q(i);
        questions.push_back(q);
        i++;
    }
    if(err) return 1;

    int answered = 0;
    for(int j = 0; j < questions.size(); j++) {
        cout << questions.at(j).getQuestion() << " [" << j+1 << "/" << questions.size() << "]\n";
        vector<string> a = questions.at(j).getAnswers();
        for(int i = 1; i < a.size()+1; i++) {
            cout << "[" << i << "] " << a.at(i-1) << endl;
        }
        int answer;
        cout << "> ";
        cin >> answer;
        bool correct = questions.at(j).valid(answer-1);
        if(correct) {
            cout << "Poprawna odpowiedz!\n";
            answered++;
        }
        else {
            cout << "Zla odpowiedz! Przegrywasz.\n";
            break;
        }
    }
    cout << "Koniec gry!\nPoprawne odpowiedzi: " << answered << "/" << questions.size() << endl;
}