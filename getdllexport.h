#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <stdexcept>
#include "log.h"
#pragma comment(lib, "Kernel32.lib")

DWORD RVAToOffset64(DWORD rva, IMAGE_NT_HEADERS64* ntHeaders) {
    IMAGE_SECTION_HEADER* section = IMAGE_FIRST_SECTION(ntHeaders);
    if (rva < section->VirtualAddress) return rva;
    for (int i = 0; i < ntHeaders->FileHeader.NumberOfSections; ++i, ++section) {
        DWORD sectionStartRVA = section->VirtualAddress;
        DWORD sectionEndRVA = section->VirtualAddress + std::max(section->Misc.VirtualSize, section->SizeOfRawData);
        if (rva >= sectionStartRVA && rva < sectionEndRVA) {
            return section->PointerToRawData + (rva - sectionStartRVA);
        }
    }
    return 0;
}

std::vector<std::string> GetDllExports64(const std::string& dllPath, std::string my_date) {
    std::vector<std::string> exportedFunctions;

    my_log(my_date + ".log", "D", "0000-0001", "dll�ļ�������������", "����" + dllPath + "�ļ�");
    HANDLE hFile = CreateFileA(dllPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "�޷���dll�ļ�");
        throw std::runtime_error("Failed to open DLL file.");
    }

    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
    if (!hMapping) {
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "�޷������ļ�ӳ��");
        throw std::runtime_error("Failed to create file mapping.");
    }

    BYTE* pBaseAddr = (BYTE*)MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);
    if (!pBaseAddr) {
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "�޷�ӳ���ļ���ͼ");
        throw std::runtime_error("Failed to map view of file.");
    }

    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)pBaseAddr;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "��ЧDOSǩ��");
        throw std::runtime_error("Invalid DOS signature.");
    }

    IMAGE_NT_HEADERS64* ntHeaders = (IMAGE_NT_HEADERS64*)(pBaseAddr + dosHeader->e_lfanew);
    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "��ЧNTǩ��");
        throw std::runtime_error("Invalid NT signature.");
    }
    if (ntHeaders->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "����64λDLL");
        throw std::runtime_error("Not support for PE32 (x86) DLL.");
    }

    IMAGE_DATA_DIRECTORY exportDirData = ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (exportDirData.VirtualAddress == 0) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "û�е�����");
        throw std::runtime_error("No export table.");
    }

    DWORD exportDirOffset = RVAToOffset64(exportDirData.VirtualAddress, ntHeaders);
    if (exportDirOffset == 0) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "RVAToOffsetʧ��:������");
        throw std::runtime_error("Failed to convert export directory RVA to file offset.");
    }

    IMAGE_EXPORT_DIRECTORY* exportDir = (IMAGE_EXPORT_DIRECTORY*)(pBaseAddr + exportDirOffset);

    DWORD namesOffset = RVAToOffset64(exportDir->AddressOfNames, ntHeaders);
    if (namesOffset == 0) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hMapping);
        CloseHandle(hFile);
        my_log(my_date + ".log", "E", "0001-0000", "dll������������", "RVAToOffsetʧ��:������������");
        throw std::runtime_error("Failed to convert AddressOfNames RVA to file offset.");
    }
    DWORD* nameRVAs = (DWORD*)(pBaseAddr + namesOffset);

    for (DWORD i = 0; i < exportDir->NumberOfNames; ++i) {
        DWORD funcNameRVA = nameRVAs[i];
        DWORD funcNameOffset = RVAToOffset64(funcNameRVA, ntHeaders);
        if (funcNameOffset == 0) continue;
        char* funcName = (char*)(pBaseAddr + funcNameOffset);
        exportedFunctions.emplace_back(funcName);
    }

    UnmapViewOfFile(pBaseAddr);
    CloseHandle(hMapping);
    CloseHandle(hFile);
    my_log(my_date + ".log", "D", "0000-0001", "dll�ļ�������������", "��ɱ���" + dllPath + "�ļ�");
    return exportedFunctions;
}