// This will be the driving menu for making polygons and calculating their area.

#include "PolygonMenu.h"
#include <iostream>
#include <filesystem>
#include <fstream> // File stream for loading files from disk
#include <sstream> // String stream for simple processing of module scripts
#include <cctype> // Provides IsDigit(char) function
#include <algorithm> // Provides std::replace for strings

// Keyboard direct input
#include "KeyListener.h" // Handles keyboard input
#include <Windows.h>  // Windows API/library for keyboard input

using std::cout; using std::cin; using std::endl;

// Constructor
P::PolygonMenu::PolygonMenu()
{
	if (!P::PolygonMenu::LoadShapeModules()) return;

	// Get the size of ShapeData list
	size = ShapeModuleData.size();

	// If no modules were loaded, then quit program
	if (size == 0) return;

	P::PolygonMenu::SetupKeybindings();
	P::PolygonMenu::Main();
}

bool P::PolygonMenu::LoadShapeModules()
{
	namespace fs = std::filesystem;
	using std::string;
	
	// Get .exe path
	fs::path folder;
	std::string folderStr;
	//std::string folder2 = "Y:/Documents/Visual Studio Projects/Polygon/x64/Debug/Shapes"; // Placeholder
	wchar_t exepath[MAX_PATH];
	std::string exepathStr;
	GetModuleFileName(NULL, exepath, MAX_PATH);			// Returns a path with "\\" as separators. The file loading method doesn't accept those.
	exepathStr = WCharToNarrow(exepath);								
	std::replace(exepathStr.begin(), exepathStr.end(), '\\', '/');	// Replaces all occurences of "\\" with "/".
	folder = exepathStr;											// Convert to filesystem path string
	folder.remove_filename();										// Removes the name of this execute
	folderStr.assign(folder.string());								// Convert filesystem path string to standard string
	//folder.assign(fs::canonical(fs::current_path() / fs::path(argv[0]))); // Not used. Get the canonical path of argv[0], which is passed from int main()

	// Add Shapes folder name to our folder path
	folderStr += "Shapes";
	folder = folderStr;	// Don't forget to update value of folder as well

	// Check if Shapes folder exists
	if (!fs::exists(folder))
	{
		cout << "Error: Shapes folder was not found. Please add a folder named Shapes in the same folder as the program executable." << endl;
		return false;
	}

	// Prepare for handling files
	fs::directory_iterator iterator(folderStr); // Bug: Throws a runtime error when we don't check if Shapes folder exists before creating this object
	//fs::directory_iterator iterator(folder2); // Placeholder
	std::string filename;
	std::string target;
	std::ifstream file;
	std::string content;
	std::string line;

	// Iterate through all the files in the directory
	for (const fs::directory_entry& entry : iterator)
	{
		// Check if the entry is a regular file
		if (entry.is_regular_file())
		{
			// Get the file name
			filename = entry.path().filename().string();

			// Validate filename. It should start with "Polygon_" and end with ".txt"
			if (filename.find("Polygon_") != string::npos && filename.rfind(".txt") != string::npos)
			{
				cout << "LoadShapeModules: Found the following file with proper naming convention, and will be analyzed further: " << filename << endl;

				// Load this file
				// Make a complete target destination to open with path and filename
				target = folderStr + "/" + filename;
				file.open(target);
				if (file.is_open())
				{
					// Loop through the lines of code in this file to validate for saving into ShapeModuleData list
					ShapeModuleStruct ModuleData;
					int i = 0;
					int ValidatedCount = 0;
					std::string keyword;
					while (std::getline(file, line))
					{
						// Line counter
						++i;

						// Flag for successfully validating this line. Needs to be reset in the beginning of every iteration
						bool Validated;
						Validated = false;

						// Limit to 3 lines of code
						if (i > 3) break;

						// Find corresponding keyword depending on line number, and then add it to success count
						switch (i)
						{
						case 1:
							keyword = "Name: ";
							break;
						case 2:
							keyword = "Question: ";
							break;
						case 3:
							keyword = "Area: ";
							break;
						default:
							break;
						}
						if (line.find(keyword) != string::npos)
						{
							// Line 3 is expected to be area script, which needs further validation. Else just count as a success for now
							if (i == 3)
							{
								// Duplicate line string and substring it based on the length of current keyword
								std::string script = line.substr(keyword.length());

								// A temporary shape module data structure and user input string is needed for RunAreaScript
								ShapeModuleStruct module;
								module.Area = script;
								module.Name = ModuleData.Name;
								module.Question = ModuleData.Question;
								std::string userinput = "1 1 1 1";

								// Run a test of area script line. It returns -1 at failure
								if (RunAreaScript(&module, &userinput) != -1)
								{
									Validated = true;
								}
							}

							// Line 1 and 2 is Name or Question, doesn't need validation
							else Validated = true;

							// If current line is validated, add it to the corresponding entry in the data struct
							if (Validated)
							{
								ValidatedCount++;

								// Duplicate line string and substring it based on the length of current keyword
								std::string data = line.substr(keyword.length());

								// Save data to temporary structure until we have validated all lines
								switch (i)
								{
								case 1:
									ModuleData.Name = data;
									break;
								case 2:
									ModuleData.Question = data;
									break;
								case 3:
									ModuleData.Area = data;
									break;
								default:
									break;
								}
							}
						}

						// Keyword wasn't found in line at this point, throw error
						else cout << "Error: LoadShapeModules couldn't find keyword in file " << filename << " at line " << i << ". Expected keyword: " << keyword << endl;
					}

					// Finally, add data entry into module data list
					// According to our design of script format, it should have found 3 correct lines.
					if (ValidatedCount == 3) ShapeModuleData.push_back(ModuleData);
				}
				else
				{
					cout << "Error: LoadShapeModules failed opening following file: " << filename << endl;
				}

				// When done reading file, it needs to be closed, or else any sequent open-attempts will not do anything
				file.close();
			}
			else
			{
				cout << "LoadShapeModules: Following file will not be opened due to unproper naming convention: " << filename << ". Please put Polygon_ in front of filename" << endl;
			}
		}
	}
	return true;
}

void P::PolygonMenu::SetupKeybindings()
{
	// Setup the collection of Virtual Keys for asking user for trying again
	P::PolygonMenu::KeyBindings_TryAgain.push_back('Y');
	P::PolygonMenu::KeyBindings_TryAgain.push_back('N');

	// Prepare key bindings for choosing shape in a list
	// Check if size is valid
	if (size > 9)
	{
		cout << "Warning: ShapeModuleData list is too big. The program will only use the first 9 loaded modules" << endl;
		return;
	}
	if (size <= 0)
	{
		cout << "Error: ShapeModuleData list is empty, or has an invalid size" << endl;
		return;
	}

	// Propagate key-binding list
	// Will only bind the first 9 loaded modules
	for (int i = 0; i <= size-1 && i < 8; i++)
	{
		// Keyboard button char value is '1', and numerical value is 49. We count from there
		KeyBindings_ShapeList.push_back(49 + i);
	}
}

void P::PolygonMenu::Main()
{
	P::PolygonMenu::AskForShape();
	P::PolygonMenu::RunChosenShape();

	// Ask for doing it again.
	cout << "Do you want to make a new shape? (Y/N)" << endl;

	// Listen for key presses.
	P::KeyListener KeyListener;
	int Key = 0;
	Key = KeyListener.ListenForKeys(&(P::PolygonMenu::KeyBindings_TryAgain));
	
	// But 'N' will continue towards program end
	if (Key == 'Y') {
		P::PolygonMenu::Main();
	}
}

void P::PolygonMenu::AskForShape()
{
	// This is a while-loop for asking until the user input is valid
	bool ShapeIsValid = false;
	bool FirstIteration = true;
	while (!ShapeIsValid)
	{
		// Display the question.
		// The first line of the question is different after the user input has been invalid.
		if (FirstIteration)
		{
			cout << "Please choose a shape:" << endl;
			FirstIteration = false;
		}
		else
		{
			cout << "The pressed key is not valid. Please try again:" << endl;
		}

		// Display the list of shapes to choose from
		for (int i = 0; i <= size - 1; i++)
		{
			// Format: #. Name
			cout << i + 1 << ". " << ShapeModuleData.at(i).Name << endl;
		}

		// Listen for user key input
		P::KeyListener KeyListener;
		int Key = 0;
		Key = KeyListener.ListenForKeys(&KeyBindings_ShapeList);

		// Check if returned pressed key is valid
		// char numerical values for 1-9 are 49-58
		if (Key >= '1' && Key - 49 <= size - 1)
		{
			ShapeIsValid = true;

			// char and int offset
			ChosenModuleIndex = static_cast<size_t>(Key - 49);
		}
	}
}

void P::PolygonMenu::RunChosenShape()
{
	ShapeModuleStruct Data;
	std::string Word;
	std::string UserInput;

	// Get values
	Data = ShapeModuleData.at(ChosenModuleIndex);

	// Display question
	cout << Data.Question << endl;

	// Receive user input. The design of this application will let the user enter whitespaces, so std::getline works better than std::cin
	std::getline(cin, UserInput);

	if (IsWholeNumber(&UserInput))
	{
		int result = RunAreaScript(&Data, &UserInput);
		if (result >= 0)
		{
			cout << "The area of the " << Data.Name << " is: " << result << endl;
		}
		// At this point, RunAreaScript returned -1 for error
		else cout << "The chosen shape " << Data.Name << " has stumbled upon an error. You may try another shape or try fixing the corresponding module file" << endl;
	}
	else
	{
		cout << "Invalid input. Please try again:" << endl;
		RunChosenShape();
	}
}

int P::PolygonMenu::RunAreaScript(ShapeModuleStruct* Module, std::string* UserInput)
{
	// Validate pointers
	{
		bool error = false;
		if (Module == nullptr)
		{
			cout << "Error: RunAreaScript function received a null pointer to Module" << endl;
			error = true;
		}
		if (UserInput == nullptr)
		{
			cout << "Error: RunAreaScript function received a null pointer to UserInput" << endl;
			error = true;
		}
		if (error) return -1;
	}

	// Validate user input
	{
		std::stringstream ss(*UserInput);
		std::string word;

		while (ss >> word)
		{
			if (!IsWholeNumber(&word))
			{
				cout << "Error: RunAreaScript function received UserInput with one or more invalid numbers" << endl;
				return -1;
			}
		}
	}

	// Declare variables
	// Using string stream for simple processing of scripts
	int Buffer = 0;
	std::stringstream ScriptStream(Module->Area);
	std::stringstream UserInputStream(*UserInput);
	std::string word;
	std::string userword;

	// Iterate through every word of the script
	// Word counter and pending flags
	int i = 0;
	int UserValue = 0;

	while (ScriptStream >> word)
	{
		// Count words
		i++;

		if (i > 100)
		{
			cout << "Warning: Area script of shape " << Module->Name << " exceeded limit of 100 words. The program will return the current buffer value" << endl;
			return Buffer;
		}

		// Check for number
		if (IsWholeNumber(&word))
		{
			// Convert word string to int
			int num = std::stoi(word);

			// First word being a number is the starting buffer
			if (i == 1) Buffer = num;

			// Check if a math operation is pending
			else if (MathOperatorType != Null)
			{
				MathOperator(&Buffer, num);
				MathOperatorType = Null;
			}

			// After checking for all valid conditions, this number is unexpected and will be ignored 
			else cout << "Warning: Syntax error. Unexpected number in area script of module " << Module->Name << ", word #" << i << ". The program will ignore and continue." << endl;
		}

		// Check for parameter
		else if (word == "parameter")
		{
			// Parameter means that we will pick next number from user input
			// But make first that any one of the following conditions is met
			if (i == 1 || MathOperatorType != Null)
			{
				UserInputStream >> userword;
				UserValue = std::stoi(userword);
			}

			// First script word being parameter initiates the buffer from user input
			if (i == 1) Buffer = UserValue;

			// Check if a math operation is pending
			else if (MathOperatorType != Null)
			{
				MathOperator(&Buffer, UserValue);
				MathOperatorType = Null;
			}

			// After checking for all valid conditions, this parameter is unexpected and will be ignored 
			else cout << "Warning: Syntax error. Unexpected parameter in area script of module " << Module->Name << ", word #" << i << ". The program will ignore and continue." << endl;
		}

		// Check for Multiply or Divide command
		else if (word == "multiply") MathOperatorType = Multiply;
		else if (word == "divide") MathOperatorType = Divide;
		else if (word == "power") MathOperatorType = Power;

		// After checking for all valid word types without success, it's unidentified
		else cout << "Warning: Unidentified word in area script of module " << Module->Name << ", word #" << i << ". The program will ignore and continue." << endl;
	}

	// After iterating through all words of the area script, the value of the buffer should be the desired result of area
	return Buffer;
}

bool P::PolygonMenu::IsWholeNumber(std::string* string)
{
	// Iterates through every character of the string
	for (std::string::iterator it = string->begin(); it != string->end(); it++)
	{
		// Not a digit and not a space
		if (!std::isdigit(*it) && *it != ' ')
		{
			return false;
		}
	}
	return true;
}

void P::PolygonMenu::MathOperator(int* Buffer, int num)
{
	switch (MathOperatorType)
	{
	case Null:
		cout << "Warning: MathOperator: MathOperatorFlag is Null. The program will ignore this and continue." << endl;
		break;
	case Multiply:
		*Buffer *= num;
		break;
	case Divide:
		*Buffer /= num;
		break;
	case Power:
		for (int i = 1; i <= num - 1; i++)
			*Buffer *= *Buffer;
		break;
	default:
		break;
	}
}

std::string WCharToNarrow(const wchar_t* s)
{
	int len = WideCharToMultiByte(CP_ACP, 0, s, -1, NULL, 0, NULL, NULL);
	std::string str(len, '\0');
	WideCharToMultiByte(CP_ACP, 0, s, -1, &str[0], len, NULL, NULL);
	return str;
}