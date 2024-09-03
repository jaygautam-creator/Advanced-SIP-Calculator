#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Function to calculate the future value of a SIP (Systematic Investment Plan)
double calculateSIP(double monthlyInvestment, double annualRate, int years) {
    double monthlyRate = annualRate / 12 / 100;
    int months = years * 12;
    double futureValue = monthlyInvestment * (pow(1 + monthlyRate, months) - 1) * (1 + monthlyRate) / monthlyRate;
    return futureValue;
}

// Function to convert a number to words (Indian numbering system)
string convertToWords(long long num) {
    const string unitsArr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    const string teensArr[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    const string tensArr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
    const string placeValuesArr[] = {"", "Thousand", "Lakh", "Crore"};

    vector<string> units(unitsArr, unitsArr + 10);
    vector<string> teens(teensArr, teensArr + 10);
    vector<string> tens(tensArr, tensArr + 10);
    vector<string> placeValues(placeValuesArr, placeValuesArr + 4);

    if (num == 0) return "Zero";

    string words = "";

    if (num >= 10000000) {
        words += convertToWords(num / 10000000) + " Crore ";
        num %= 10000000;
    }

    if (num >= 100000) {
        words += convertToWords(num / 100000) + " Lakh ";
        num %= 100000;
    }

    if (num >= 1000) {
        words += convertToWords(num / 1000) + " Thousand ";
        num %= 1000;
    }

    if (num >= 100) {
        words += units[num / 100] + " Hundred ";
        num %= 100;
    }

    if (num >= 20) {
        words += tens[num / 10] + " ";
        num %= 10;
    } else if (num >= 10) {
        words += teens[num - 10] + " ";
        num = 0;
    }

    if (num > 0) {
        words += units[num] + " ";
    }

    // Remove trailing spaces
    while (!words.empty() && words.back() == ' ') {
        words.pop_back();
    }

    return words;
}

// Function to calculate inflation-adjusted value
double calculateInflationAdjustedValue(double futureValue, double inflationRate, int years) {
    double inflationAdjustedValue = futureValue / pow(1 + inflationRate / 100, years);
    return inflationAdjustedValue;
}

int main() {
    double monthlyInvestment, annualRate, inflationRate;
    int years;

    // Input Section
    cout << "Enter your monthly investment amount: ";
    cin >> monthlyInvestment;

    cout << "Enter the expected annual rate of return (in %): ";
    cin >> annualRate;

    cout << "Enter the investment period (in years): ";
    cin >> years;

    cout << "Enter the expected annual inflation rate (in %): ";
    cin >> inflationRate;

    // Calculation Section
    double futureValue = calculateSIP(monthlyInvestment, annualRate, years);
    int months = years * 12;
    double totalInvested = monthlyInvestment * months;
    double profit = futureValue - totalInvested;
    double profitPercentage = (profit / totalInvested) * 100;
    double inflationAdjustedValue = calculateInflationAdjustedValue(futureValue, inflationRate, years);

    // Output Section
    cout << fixed << setprecision(0); 
    
    cout << "Total amount invested: " << totalInvested << endl;
    cout << "In words: " << convertToWords(static_cast<long long>(totalInvested)) << endl;
    
    cout << "Profit amount: " << profit << endl;
    cout << "In words: " << convertToWords(static_cast<long long>(profit)) << endl;
    
    cout << "Profit percentage: " << fixed << setprecision(2) << profitPercentage << "%" << endl;
    
    cout << "The future value of your SIP is: " << futureValue << endl;
    cout << "In words: " << convertToWords(static_cast<long long>(futureValue)) << endl;

    cout << "Inflation-adjusted future value: " << fixed << setprecision(0) << inflationAdjustedValue << endl;
    cout << "In words: " << convertToWords(static_cast<long long>(inflationAdjustedValue)) << endl;

    return 0;
}
