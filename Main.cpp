#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
using namespace std;

void CallProcedure(string pName) {
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());
    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();
    delete[] procname;
}
int callIntFunc(string proc, string param) {
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());
    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());
    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    Py_Initialize();
    pName = PyUnicode_FromString((char*)"PythonCode");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc)) {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else {
        PyErr_Print();
    }
    Py_DECREF(pValue);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    delete[] procname;
    delete[] paramval;
    return _PyLong_AsInt(presult);
}
int callIntFunc(string proc, int param) {
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());
    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    Py_Initialize();
    pName = PyUnicode_FromString((char*)"PythonCode");
    pModule = PyImport_Import(pName);
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc)) {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else {
        PyErr_Print();
    }
    Py_DECREF(pValue);
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    delete[] procname;
    return _PyLong_AsInt(presult);
}
void Menu() {
    bool program = true;
    bool input;
    int choice;
    string grocery_Type;
    do {
        cout << endl;
        cout << "******************************************************************************" << endl;
        cout << "*****                                                                   ******" << endl;
        cout << "*****             What Would You Like To Do?                            ******" << endl;
        cout << "*****    Choose From One Of The Following Options Below:                ******" << endl;
        cout << "*****                                                                   ******" << endl;
        cout << "******************************************************************************" << endl;
        cout << "*****                                                                   ******" << endl;
        cout << "***** 1. Print List of All Purchased Items and How Many Were Purchased  ******" << endl;
        cout << "***** 2. Print Total Amount Purchased of a Specific Item                ******" << endl;
        cout << "***** 3. Display Text Histogram                                         ******" << endl;
        cout << "***** 4. Exit The Program                                               ******" << endl;
        cout << "*****                                                                   ******" << endl;
        cout << "******************************************************************************" << endl;
        cout << endl;
        try {
            std::cin >> choice;
            cout << "******************************************************************************" << endl;
            cout << endl;
            while (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(256, 'n');
                cout << "Invalid Entry. Please Try Again." << endl;
                cout << "Please Enter: 1, 2, 3, or 4." << endl;
                std::cin >> choice;
                cout << "******************************************************************************" << endl;
                cout << endl;
            }
            if (choice >= 0) {
                input = true;
            }
            else { throw (choice); }
        }
        catch (...) {
            cout << "Invalid Input. Please Enter: 1, 2, 3, or 4." << endl;
        }
        if (choice == 1) {
            cout << endl;
            cout << "================================================================================" << endl;
            cout << "======                         Total Produce Purchased Today              ======" << endl;
            cout << "--------------------------------------------------------------------------------" << endl;
            cout << endl;
            //Reads the file in python.
            CallProcedure("read_File");
        }
        else if (choice == 2) {
            string userString;
            cout << "Please Enter The Product You Wish To Look Up: ";
            std::cin >> userString; //Grabs product the user wishes to look up
            int tot = callIntFunc("locate_Total_Product_Amount", userString);
            if (tot == -1) {
                cout << "This Item Could Not Be Located. Please Check Spelling and Make Sure Your Input Is Correct." << endl;
            }
            else {
                cout << "There Were A Total Of " << tot << " " << userString << " Sold Today." << endl;
            }
        }
        else if (choice == 3) {
            CallProcedure("read_AND_Write_File");
        }
        else { program = false; }

    } while (program == true);
}
int main() {
    CallProcedure("printsomething");
    cout << callIntFunc("PrintMe", "Corner Grocer") << endl;
    cout << callIntFunc("SquareValue", 2);
    //calls menu for main functionality of the program
    Menu();
    //Message when user exits program
    cout << endl;
    cout << "******************************************************************************" << endl;
    cout << "**********                      Exit The Program                    **********" << endl;
    cout << "******************************************************************************" << endl;
    return 0;
}