// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include<lbpch.h>
#include "framework.h"
#include<iostream>
#include<filesystem>

void entry();

extern "C" {
    _declspec(dllexport) void onPostInit() {
        std::ios::sync_with_stdio(false);
        entry();
    }
}

LIAPI string GetDataPath(const string& myname) {
    using namespace std::filesystem;
    create_directory("data");
    return "data/" + myname;
}
