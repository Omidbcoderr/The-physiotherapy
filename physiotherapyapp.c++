#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

// Structure to hold exercise information
struct Exercise {
    string name;
    string description;
    string reps;
};

// Database of exercises by body part
map<string, vector<Exercise>> exerciseDatabase = {
    {"neck", {
        {"Neck Stretch", "Gently tilt your head to one side, bringing your ear toward your shoulder. Hold for 15-30 seconds.", "3-5 per side"},
        {"Chin Tucks", "Gently tuck your chin toward your chest without bending your neck. Hold for 5 seconds.", "10 repetitions"}
    }},
    {"shoulder", {
        {"Pendulum Exercise", "Lean forward with one arm hanging down. Swing the arm gently in small circles.", "10 circles each direction"},
        {"Shoulder Blade Squeeze", "Sit or stand with arms at sides. Squeeze shoulder blades together. Hold for 5 seconds.", "10 repetitions"}
    }},
    {"back", {
        {"Cat-Cow Stretch", "On hands and knees, alternate between arching your back upward and dipping it downward.", "10 cycles"},
        {"Pelvic Tilts", "Lie on back with knees bent. Tighten abdominal muscles and press lower back into floor.", "10 repetitions"}
    }},
    {"knee", {
        {"Straight Leg Raises", "Lie on back with one leg bent and one straight. Lift straight leg to height of bent knee.", "10 per leg"},
        {"Seated Knee Extensions", "Sit in chair with feet flat. Slowly extend one leg straight out in front. Hold for 5 seconds.", "10 per leg"}
    }}
};

// Function to display loading animation
void showLoadingAnimation(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        cout << "Analyzing your symptoms";
        for (int j = 0; j < 3; ++j) {
            cout << ".";
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        cout << "\r" << string(20, ' ') << "\r"; // Clear line
    }
    cout << endl;
}

// Function to convert string to lowercase
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
              [](unsigned char c){ return tolower(c); });
    return lowerStr;
}

// Function to analyze symptoms and generate recommendations
void analyzeSymptoms(const string& bodyPart, int painLevel, const string& symptoms, const string& duration) {
    // Simulate AI processing
    showLoadingAnimation(3);
    
    string condition;
    string severity;
    vector<string> recommendations;
    
    // Determine condition based on body part and symptoms
    string lowerSymptoms = toLower(symptoms);
    
    if (bodyPart == "neck") {
        if (lowerSymptoms.find("stiff") != string::npos || lowerSymptoms.find("hard to move") != string::npos) {
            condition = "Neck stiffness or possible cervical strain";
            severity = painLevel > 7 ? "moderate" : "mild";
        } else if ((lowerSymptoms.find("pain") != string::npos) && (lowerSymptoms.find("radiate") != string::npos)) {
            condition = "Possible cervical radiculopathy";
            severity = painLevel > 8 ? "severe" : "moderate";
        } else {
            condition = "General neck discomfort";
            severity = "mild";
        }
        
        recommendations = {
            "Apply heat or ice for 15-20 minutes several times a day",
            "Practice gentle neck stretches",
            "Maintain good posture"
        };
        
        if (painLevel > 6) {
            recommendations.push_back("Consider over-the-counter pain relief as needed");
        }
    } 
    else if (bodyPart == "back") {
        if ((lowerSymptoms.find("sharp") != string::npos) && (lowerSymptoms.find("sudden") != string::npos)) {
            condition = "Possible acute back strain";
            severity = painLevel > 6 ? "moderate" : "mild";
        } else if ((lowerSymptoms.find("radiate") != string::npos) && (lowerSymptoms.find("leg") != string::npos)) {
            condition = "Possible sciatica or nerve involvement";
            severity = painLevel > 7 ? "severe" : (painLevel > 5 ? "moderate" : "mild");
        } else {
            condition = "General back discomfort";
            severity = "mild";
        }
        
        recommendations = {
            "Practice gentle back stretches and core strengthening",
            "Modify activities that aggravate pain",
            "Use proper lifting techniques"
        };
        
        if (painLevel > 5) {
            recommendations.push_back("Consider alternating heat and ice therapy");
        }
    }
    else {
        condition = bodyPart + " discomfort";
        if (painLevel > 8 && duration == "chronic") {
            severity = "severe";
        } else if (painLevel > 7) {
            severity = "moderate";
        } else {
            severity = "mild";
        }
        
        recommendations = {
            "Practice gentle range of motion exercises",
            "Apply heat or ice as needed",
            "Modify activities that aggravate symptoms"
        };
        
        if (painLevel > 6) {
            recommendations.push_back("Consider over-the-counter pain relief as needed");
        }
    }
    
    // Add duration consideration
    if (duration == "chronic" && painLevel > 4) {
        condition += " (chronic)";
        if (severity == "mild") severity = "moderate";
    }
    
    // Display results
    cout << "\n=== PROFESSIONAL ASSESSMENT ===" << endl;
    cout << "Condition: " << condition << endl;
    cout << "Severity: " << severity << endl;
    cout << "Pain level: " << painLevel << "/10" << endl;
    cout << "Duration: " << duration << endl;
    
    cout << "\n=== RECOMMENDATIONS ===" << endl;
    for (const auto& rec : recommendations) {
        cout << "- " << rec << endl;
    }
    
    if (severity == "moderate") {
        cout << "\nNOTE: Moderate condition detected. If symptoms persist for more than 2 weeks, consult a physiotherapist." << endl;
    } else if (severity == "severe") {
        cout << "\nWARNING: Severe condition detected. We recommend consulting a physiotherapist or doctor as soon as possible." << endl;
    }
}

// Function to display exercises for a body part
void displayExercises(const string& bodyPart) {
    cout << "\n=== EXERCISE RECOMMENDATIONS ===" << endl;
    
    if (exerciseDatabase.find(bodyPart) == exerciseDatabase.end()) {
        cout << "No specific exercises found for this body part. General mobility exercises are recommended." << endl;
        return;
    }
    
    const vector<Exercise>& exercises = exerciseDatabase[bodyPart];
    for (size_t i = 0; i < exercises.size(); ++i) {
        cout << "\nExercise " << (i + 1) << ": " << exercises[i].name << endl;
        cout << "Description: " << exercises[i].description << endl;
        cout << "Repetitions: " << exercises[i].reps << endl;
    }
}

int main() {
    cout << "=== PHYSIOAI ADVISOR ===" << endl;
    cout << "Professional physiotherapy advice system\n" << endl;
    
    // Get user input
    string bodyPart;
    cout << "Select affected body part (neck, shoulder, back, knee, etc.): ";
    getline(cin, bodyPart);
    
    int painLevel;
    cout << "Enter pain level (1-10): ";
    cin >> painLevel;
    cin.ignore(); // Ignore newline character
    
    string symptoms;
    cout << "Describe your symptoms in detail:\n";
    getline(cin, symptoms);
    
    string duration;
    cout << "Duration of symptoms (acute <2w, subacute 2-6w, chronic >6w): ";
    getline(cin, duration);
    
    // Analyze symptoms
    analyzeSymptoms(toLower(bodyPart), painLevel, symptoms, toLower(duration));
    
    // Show exercises
    displayExercises(toLower(bodyPart));
    
    cout << "\n=== IMPORTANT NOTICE ===" << endl;
    cout << "This application provides general information only and is not a substitute\n"
         << "for professional medical advice. Always consult a qualified healthcare\n"
         << "provider for proper diagnosis and treatment." << endl;
    
    return 0;
}