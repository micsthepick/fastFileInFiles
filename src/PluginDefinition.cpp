//this file is part of the FastFindInFiles plugin for notepad++
//Copyright (C) 2024 Michael Pannekoek
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "fff.h"

#include "resource.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

HANDLE g_hModule = NULL; // Global variable to store the module handle

// Initialize your plugin data here
// It will be called while plugin loading
void pluginInit(HANDLE hModule)
{
    g_hModule = hModule; // Store the module handle
}


//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, TEXT("Find In Files (fast)"), showFindInFilesDialog, NULL, false);
    setCommand(1, TEXT("About"), helloDlg, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void helloDlg()
{
    ::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("FindInFilesFast finds strings fast."), MB_OK);
}


void showFindInFilesDialog() {
    if (g_hModule == NULL) {
        // Handle the error, g_hModule is not initialized
        ::MessageBox(NULL, TEXT("Plugin module handle is null."), TEXT("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    if (nppData._nppHandle == NULL) {
        // Handle the error, nppData._nppHandle is not initialized
        ::MessageBox(NULL, TEXT("Notepad++ main window handle is null."), TEXT("Error"), MB_OK | MB_ICONERROR);
        return;
    }

    ::DialogBox((HINSTANCE)g_hModule, MAKEINTRESOURCE(IDD_FINDINFILESFAST_DIALOG), nppData._nppHandle, FindInFilesDlgProc);
}

std::string ConvertTCHARToString(const TCHAR* tcharString) {
    std::string convertedString;
#ifdef UNICODE
    std::wstring wString(tcharString);
    convertedString.assign(wString.begin(), wString.end());
#else
    convertedString = tcharString;
#endif
    return convertedString;
}


INT_PTR CALLBACK FindInFilesDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM) {
    switch (message) {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK) {
                TCHAR path[MAX_PATH];
                TCHAR searchString[MAX_PATH];
                TCHAR filters[MAX_PATH];

                GetDlgItemText(hDlg, IDC_PATH_EDIT, path, MAX_PATH);
                GetDlgItemText(hDlg, IDC_SEARCHSTRING_EDIT, searchString, MAX_PATH);
                GetDlgItemText(hDlg, IDC_FILTERS_EDIT, filters, MAX_PATH);

                // Convert from TCHAR to std::string (if necessary)
                std::string pathStr, searchStringStr, filtersStr;
                #ifdef UNICODE
                std::wstring wPath(path), wSearchString(searchString), wFilters(filters);
                pathStr = ConvertTCHARToString(path);
                searchStringStr = ConvertTCHARToString(searchString);
                filtersStr = ConvertTCHARToString(filters);
                #else
                pathStr = path;
                searchStringStr = searchString;
                filtersStr = filters;
                #endif

                EndDialog(hDlg, IDOK);

                // Call your search function here
                findInFilesFast(pathStr, searchStringStr, filtersStr);
                return (INT_PTR)TRUE;
            }
            else if (LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, IDCANCEL);
                return (INT_PTR)TRUE;
            }
            break;
    }
    return (INT_PTR)FALSE;
}
