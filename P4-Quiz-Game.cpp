#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Question {
    string question;
    string options[4];
    char correctOption;
};

struct Player {
    string name;
    int score;
};

vector<Question> questions;
vector<Player> scoreboard;

void addQuestion() {
    Question q;
    cout << "Enter question: ";
    cin.ignore();
    getline(cin, q.question);

    for (int i = 0; i < 4; i++) {
        cout << "Enter option " << char('A' + i) << ": ";
        getline(cin, q.options[i]);
    }

    cout << "Enter correct option (A, B, C, D): ";
    cin >> q.correctOption;
    q.correctOption = toupper(q.correctOption);
    
    questions.push_back(q);
    cout << "Question added successfully!\n";
}

void removeQuestion() {
    if (questions.empty()) {
        cout << "No questions available to remove!\n";
        return;
    }

    int index;
    cout << "Enter question index to remove (1 to " << questions.size() << "): ";
    cin >> index;

    if (index < 1 || index > questions.size()) {
        cout << "Invalid index!\n";
        return;
    }

    questions.erase(questions.begin() + index - 1);
    cout << "Question removed successfully!\n";
}

void displayQuestions() {
    if (questions.empty()) {
        cout << "No questions available!\n";
        return;
    }

    cout << "\nList of Questions:\n";
    for (size_t i = 0; i < questions.size(); i++) {
        cout << i + 1 << ". " << questions[i].question << endl;
    }
}

void displayScoreboard() {
    if (scoreboard.empty()) {
        cout << "No scores recorded!\n";
        return;
    }

    cout << "\nScoreboard:\n";
    cout << setw(15) << left << "Player" << setw(10) << "Score" << endl;
    cout << string(25, '-') << endl;

    for (const auto &p : scoreboard)
        cout << setw(15) << left << p.name << setw(10) << p.score << endl;
}

void playQuiz() {
    if (questions.size() < 5) {
        cout << "Not enough questions to start the quiz! Add more questions.\n";
        return;
    }

    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int score = 0;
    srand(time(0));

    for (int i = 0; i < 5; i++) {
        int qIndex = rand() % questions.size();
        cout << "\n" << questions[qIndex].question << endl;

        for (int j = 0; j < 4; j++)
            cout << char('A' + j) << ". " << questions[qIndex].options[j] << endl;

        char answer;
        cout << "Your answer: ";
        cin >> answer;
        answer = toupper(answer);

        if (answer == questions[qIndex].correctOption) {
            cout << "Correct!\n";
            score += 10;
        } else {
            cout << "Wrong! The correct answer was " << questions[qIndex].correctOption << ".\n";
        }
    }

    cout << "Quiz Over! " << playerName << " scored: " << score << endl;

    scoreboard.push_back({playerName, score});
}

int main() {
    int choice;
    while (true) {
        cout << "\n1. Play Quiz\n2. Add Question\n3. Remove Question\n4. View Questions\n5. View Scoreboard\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: playQuiz(); break;
            case 2: addQuestion(); break;
            case 3: removeQuestion(); break;
            case 4: displayQuestions(); break;
            case 5: displayScoreboard(); break;
            case 6: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
