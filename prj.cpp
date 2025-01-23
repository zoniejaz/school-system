#include <iostream>
#include <string>

using namespace std;

// Constants for maximum number of users and lectures
const int MAX_USERS = 30; // Increased limit to accommodate more users
const int MAX_LECTURES = 30;  // Maximum lectures to store attendance

// User structure to hold user information
struct User {
    string name;
    string password;
    string role; // "admin", "teacher", or "student"
};

// Attendance structure to hold attendance information
struct Attendance {
    bool present[MAX_USERS][MAX_LECTURES]; // Attendance for up to 30 students for 30 lectures
    int totalLectures; // Total lectures of attendance marked
};

// Global arrays to hold users and attendance
User    users[MAX_USERS];
Attendance attendance;
int userCount = 0; // To keep track of registered users

// Function to register a user
void registerUser (string role) {
    if (userCount >= MAX_USERS) {
        cout << "User  limit reached!" << endl;
        return;
    }
    cout << "Enter name: ";
    cin >> users[userCount].name;
    cout << "Enter password: ";
    cin >> users[userCount].password;
    users[userCount].role = role;
    userCount++;
    cout << role << " registered successfully!" << endl;
}

// Function to mark attendance
void markAttendance() {
    // Check if there are any registered students
    bool hasStudents = false;
    for (int i = 0; i < userCount; i++) {
        if (users[i].role == "student") {
            hasStudents = true;
            break;
        }
    }

    if (!hasStudents) {
        cout << "No students registered. Cannot mark attendance." << endl;
        return;
    }

    cout << "Mark Attendance for Lectures:" << endl;
    for (int i = 0; i < userCount; i++) {
        if (users[i].role == "student") {
            cout << i + 1 << ". " << users[i].name << endl;
        }
    }

    // Mark attendance for the current lecture
    for (int i = 0; i < userCount; i++) {
        if (users[i].role == "student") {
            char status;
            cout << "Is " << users[i].name << " present for Lecture " << (attendance.totalLectures + 1) << "? (p for present, a for absent): ";
            cin >> status;
            if (status == 'p') {
                attendance.present[i][attendance.totalLectures] = true;
            } else {
                attendance.present[i][attendance.totalLectures] = false;
            }
        }
    }
    attendance.totalLectures++; // Increment the total lectures after marking attendance
}

// Function to view attendance for a student
void viewAttendance(int studentIndex) {
    cout << "Attendance for " << users[studentIndex].name << ":" << endl;
    int presentCount = 0;

    for (int lecture = 0; lecture < attendance.totalLectures; lecture++) {
        cout << "Lecture " << (lecture + 1) << ": " << (attendance.present[studentIndex][lecture] ? "Present" : "Absent") << endl;
        if (attendance.present[studentIndex][lecture]) {
            presentCount++;
        }
    }

    // Calculate and display attendance percentage
    double percentage = (static_cast<double>(presentCount) / attendance.totalLectures) * 100;
    cout << "Attendance Percentage: " << percentage << "%" << endl;
}

// Function to display all registered users and their attendance
void displayRegisteredUsers() {
    bool hasStudents = false;
    bool hasTeachers = false;

    cout << "\nRegistered Users:\n";
    for (int i = 0; i < userCount; i++) {
        cout << "Name: " << users[i].name << ", Role: " << users[i].role << ", Password: " << users[i].password << endl;
        if (users[i].role == "student") {
            hasStudents = true;
            // Display attendance for each student
            viewAttendance(i); // Call viewAttendance to show attendance details
        } else if (users[i].role == "teacher") {
            hasTeachers = true;
            // Display teacher details (no attendance tracking for teachers in this example)
            cout << "Teacher " << users[i].name << " has no attendance records." << endl;
        }
    }

    if (!hasStudents) {
        cout << " No students registered." << endl;
    }
    if (!hasTeachers) {
        cout << "No teachers registered." << endl;
    }
}

// Function to change password for a registered user
void changePassword() {
    string name, newPassword;
    cout << "Enter your name: ";
    cin >> name;

    for (int i = 0; i < userCount; i++) {
        if (users[i].name == name) {
            cout << "Enter new password: ";
            cin >> newPassword;
            users[i].password = newPassword;
            cout << "Password changed successfully!" << endl;
            return;
        }
    }
    cout << "User  not found. Please check the name and try again." << endl;
}

// Main function
int main() {
    int choice;
    string role, password;

    // Initialize attendance
    attendance.totalLectures = 0; // Start with 0 lectures of attendance

    while (true) {
        cout << "1. Register Admin" << endl;
        cout << "2. Register Teacher" << endl;
        cout << "3. Register Student" << endl;
        cout << "4. Sign In" << endl;
        cout << "5. Change Password" << endl; // New choice for changing password
        cout << "6. Display Registered Users" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        bool found = false; // Declare found here

        switch (choice) {
            case 1:
                registerUser ("admin");
                break;
            case 2:
                registerUser ("teacher");
                break;
            case 3:
                registerUser ("student"); // Allow students to register
                break;
            case 4:
                cout << "Enter role (admin/teacher/student): ";
                cin >> role;
                cout << "Enter password: ";
                cin >> password;

                // Check user credentials
                for (int i = 0; i < userCount; i++) {
                    if (users[i].role == role && users[i].password == password) {
                        found = true;
                        if (role == "admin") {
                            cout << "Admin access granted." << endl;
                            displayRegisteredUsers(); // Display all registered users for admin
                        } else if (role == "teacher") {
                            cout << "Teacher access granted." << endl;
                            markAttendance(); // Allow teacher to mark attendance
                        } else if (role == "student") {
                            viewAttendance(i); // Allow student to view their attendance
                        }
                        break;
                    }
                }

                if (!found) {
                    cout << "Invalid credentials. Please try again." << endl;
                }
                break;
            case 5:
                changePassword(); // Call the change password function
                break;
            case 6:
                displayRegisteredUsers(); // Display all registered users
                break;
            case 7:
                cout << "Exiting the system." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select again." << endl;
        }
    }
}