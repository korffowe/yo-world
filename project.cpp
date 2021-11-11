#include <iostream>
#include <cstring>
#include <string>
/*
               ∩
　　　　　　　＼＼
　　　　　　　／　 ）
⊂＼＿／￣￣￣　 ／
　＼＿／   ° ͜ʖ ° （
　　　）　　 　／⌒＼
　　／　 ＿＿＿／⌒＼⊃
　（　 ／
　　＼＼
      U
*/
//This function converts each individual digit in the input string in the first parameter to its integer
//value and finds the sum of all these values. It loops through the string and adjusts each digit's
//character value in the ASCII chart to its proper integer value.
int get_line_sum(std::string line)
{
    int sum = 0;
    int length = line.size();
    for (int i = 0; i < length; i++) //loops through each digit in the string
    {
        int add = line[i] - '0'; //subtracts '0' to change from ASCII value to integer
        sum += add;
    }
    return sum;
}

//This function converts a three digit cell given in the first parameter into one digit according
//to the rules in the second parameter. If the cell is found in the list of rules, the function returns
//the corresponding predefined value, and if the cell cannot be found the function returns 0.
char get_next_state(std::string cell, std::string rules)
{
    int index = rules.find(cell); //finds if the cell parameter is in the given rules list
    if (index >= 0)
    {
        return rules[index + 7]; //function returns the corresponding value for the cell
    }
    else
    {
        return '0'; //returns 0 if the cell cannot be found in the rules list
    }
}

//This function references an input line in the first parameter and updates it according to the set
//of rules referenced in the second parameter by utilizing the get_next_state function. This
//includes wrap around from the front and back ends of the line.
void update_line(std::string &line, std::string &rules)
{
    std::string updated;
    int indices = line.size() - 2;                                  //2 is subtracted to exclude the front and back wrap-around cells
    std::string front_cell = line[indices + 1] + line.substr(0, 2); //the front cell includes the last digit and the first two digits of the string
    updated += get_next_state(front_cell, rules);
    for (int i = 0; i < indices; i++) //loops through the string to convert each cell via get_next_state function
    {
        std::string cell = line.substr(i, 3); //collects the three digits that make up each cell
        updated += get_next_state(cell, rules);
    }
    std::string back_cell = line.substr(indices, indices + 1) + line[0]; //the back cell includes the last two digits and the first digit of the string
    updated += get_next_state(back_cell, rules);
    line = updated; //this replaces the original input line with the updated line
}

//This function creates a multiline string with a string and the sum of its digits found via the get_line_sum
//function on each line. The string is updated via the rules defined in the first parameter each line, and the
//number of lines is given in the second parameter. The original string is defined in the third parameter.
std::string run_cellular_automata(std::string rules, int line_num, std::string line)
{
    std::string multistring = "";
    for (int i = 0; i < line_num; i++) //loops through the update_line function the number of iterations requested
    {
        std::string sum = std::to_string(get_line_sum(line)); //simultaneously finds the sum of the line and converts the sum from an int to a string
        multistring += line + " sum = " + sum + "\n";         //outputs each line and its respective sum in the requested format
        update_line(line, rules);
    }
    return multistring;
}

int main()
{
    std::string rules;
    std::string in_line;
    while (std::getline(std::cin, in_line)) //loops through the input lines of the user until a period is input
    {
        if (in_line.find('.') != std::string::npos)
        {
            break; //exits loop if the period is found in the new line
        }
        else
        {
            rules += in_line; //adds the rule to the rule string and creates a newline each iteration
            rules += "\n";
        }
    }
    std::string num_of_lines;
    std::getline(std::cin, num_of_lines); //next input after the period is the number of iterations to output a line, followed by the original line
    std::string line;
    std::getline(std::cin, line);
    int line_num = std::stoi(num_of_lines); //converts the input string of number of lines to an integer for use in run_cellular_automata
    std::string output = run_cellular_automata(rules, line_num, line);
    std::cout << output;
    return 0;
}