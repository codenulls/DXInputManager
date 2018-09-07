#pragma once
#include <Windows.h>

struct handle_data 
{
    unsigned long process_id;
    HWND window_handle;
};

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam);
BOOL IsMainWindow(HWND handle);

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    handle_data& data = *(handle_data*)lParam;
    unsigned long process_id = 0;
    GetWindowThreadProcessId(handle, &process_id);
    if (data.process_id != process_id || !IsMainWindow(handle))
        return TRUE;
    data.window_handle = handle;
    return FALSE;
}

BOOL IsMainWindow(HWND handle)
{
    return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

HWND FindMainWindow()
{
    handle_data data;
    data.process_id = GetCurrentProcessId();
    data.window_handle = 0;
    EnumWindows(EnumWindowsCallback, (LPARAM)&data);
    return data.window_handle;
}