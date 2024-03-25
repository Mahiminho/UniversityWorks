// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

extern "C" __declspec(dllexport) void wordAcounter(string input) {
    istringstream iss(input);
    vector<string> aWords;
    vector<int> aCount;
    string token;
    bool found;

    while (iss >> token) {
        found = false;
        for (int i = 0; i < aWords.size(); i++) {
            if (token == aWords[i]) {
                aCount[i]++;
                found = true;
                break;
            }
        }

        if (!found) {
            aWords.push_back(token);
            aCount.push_back(1);
        }
    }

    cout << "Words\tCount" << endl;
    for (int i = 0; i < aWords.size(); i++) {
        if (aWords[i][0] == 'a' || aWords[i][0] == 'A')
            cout << aWords[i] << "\t" << aCount[i] << endl;
    }
}

//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//                     )
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//    case DLL_THREAD_ATTACH:
//    case DLL_THREAD_DETACH:
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}

