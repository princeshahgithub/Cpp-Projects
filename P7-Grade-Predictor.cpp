#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

struct DataPoint {
    double studyHours;
    double attendance;
    double assignments;
    double grade;
};

vector<DataPoint> dataset = {
    {2, 80, 70, 50}, {3, 85, 75, 55}, {4, 90, 80, 60}, 
    {5, 95, 85, 65}, {6, 98, 90, 70}, {7, 100, 95, 75}, 
    {8, 100, 98, 80}, {9, 100, 100, 85}, {10, 100, 100, 90}, 
    {11, 100, 100, 95}
};

double theta0 = 0, theta1 = 0, theta2 = 0, theta3 = 0;
double learningRate = 0.0001;
int iterations = 5000;

double minHours = 2, maxHours = 11;
double minAttendance = 80, maxAttendance = 100;
double minAssignments = 70, maxAssignments = 100;
double minGrade = 50, maxGrade = 95;

double normalize(double value, double minVal, double maxVal) {
    return (value - minVal) / (maxVal - minVal);
}

double denormalize(double value, double minVal, double maxVal) {
    return value * (maxVal - minVal) + minVal;
}

double predict(double hours, double attendance, double assignments) {
    double normHours = normalize(hours, minHours, maxHours);
    double normAttendance = normalize(attendance, minAttendance, maxAttendance);
    double normAssignments = normalize(assignments, minAssignments, maxAssignments);

    double normResult = theta0 + theta1 * normHours + theta2 * normAttendance + theta3 * normAssignments;
    return denormalize(normResult, minGrade, maxGrade);
}

double computeCost() {
    double cost = 0;
    int m = dataset.size();
    for (const auto& data : dataset) {
        double normHours = normalize(data.studyHours, minHours, maxHours);
        double normAttendance = normalize(data.attendance, minAttendance, maxAttendance);
        double normAssignments = normalize(data.assignments, minAssignments, maxAssignments);
        double normGrade = normalize(data.grade, minGrade, maxGrade);

        double prediction = theta0 + theta1 * normHours + theta2 * normAttendance + theta3 * normAssignments;
        cost += pow((prediction - normGrade), 2);
    }
    return cost / (2 * m);
}

void trainModel() {
    int m = dataset.size();

    for (int iter = 0; iter < iterations; iter++) {
        double sumError0 = 0, sumError1 = 0, sumError2 = 0, sumError3 = 0;
        for (const auto& data : dataset) {
            double normHours = normalize(data.studyHours, minHours, maxHours);
            double normAttendance = normalize(data.attendance, minAttendance, maxAttendance);
            double normAssignments = normalize(data.assignments, minAssignments, maxAssignments);
            double normGrade = normalize(data.grade, minGrade, maxGrade);

            double prediction = theta0 + theta1 * normHours + theta2 * normAttendance + theta3 * normAssignments;
            sumError0 += (prediction - normGrade);
            sumError1 += (prediction - normGrade) * normHours;
            sumError2 += (prediction - normGrade) * normAttendance;
            sumError3 += (prediction - normGrade) * normAssignments;
        }

        theta0 -= learningRate * (sumError0 / m);
        theta1 -= learningRate * (sumError1 / m);
        theta2 -= learningRate * (sumError2 / m);
        theta3 -= learningRate * (sumError3 / m);

        if (iter % 1000 == 0) {
            cout << "Iteration " << iter << " | Cost: " << computeCost() << endl;
        }
    }
    cout << "Training Complete! Final Cost: " << computeCost() << endl;
}

void testModel() {
    double hours, attendance, assignments;
    cout << "Enter study hours: ";
    cin >> hours;
    cout << "Enter attendance percentage: ";
    cin >> attendance;
    cout << "Enter assignment completion percentage: ";
    cin >> assignments;

    double predictedGrade = predict(hours, attendance, assignments);
    cout << "Predicted Grade: " << predictedGrade << endl;
}

void saveModel() {
    ofstream file("model.txt");
    if (!file) return;
    file << theta0 << " " << theta1 << " " << theta2 << " " << theta3;
    file.close();
}

void loadModel() {
    ifstream file("model.txt");
    if (!file) {
        cout << "No saved model found. Training a new one...\n";
        trainModel();
        saveModel();
        return;
    }
    file >> theta0 >> theta1 >> theta2 >> theta3;
    file.close();
    cout << "Model loaded successfully!\n";
}

int main() {
    loadModel();
    int choice;
    while (true) {
        cout << "\n1. Predict Grade\n2. Train Model Again\n3. Save Model\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: testModel(); break;
            case 2: trainModel(); saveModel(); break;
            case 3: saveModel(); break;
            case 4: return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}
