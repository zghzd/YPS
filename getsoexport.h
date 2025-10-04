#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include "log.h"
#pragma pack(push, 1)
struct Elf64_Ehdr {
    unsigned char e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
};

struct Elf64_Shdr {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
};

struct Elf64_Sym {
    uint32_t st_name;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t st_shndx;
    uint64_t st_value;
    uint64_t st_size;
};
#pragma pack(pop)

std::vector<std::string> GetSoExports(const std::string& file_path, std::string my_date) {
    my_log(my_date + ".log", "D", "0000-0001", "so文件导出函数遍历", "遍历" + file_path + "文件的函数");
    std::vector<std::string> exports;
    std::ifstream f(file_path, std::ios::binary);
    if (!f) return exports;

    Elf64_Ehdr ehdr;
    f.read(reinterpret_cast<char*>(&ehdr), sizeof(ehdr));
    if (f.gcount() != sizeof(ehdr)) return exports;
    if (std::memcmp(ehdr.e_ident, "\x7f""ELF", 4) != 0) return exports;

    f.seekg(ehdr.e_shoff, std::ios::beg);
    std::vector<Elf64_Shdr> shdrs(ehdr.e_shnum);
    f.read(reinterpret_cast<char*>(shdrs.data()), ehdr.e_shnum * sizeof(Elf64_Shdr));
    int dynsym_idx = -1, dynstr_idx = -1;
    f.seekg(shdrs[ehdr.e_shstrndx].sh_offset, std::ios::beg);
    std::vector<char> shstrtab(shdrs[ehdr.e_shstrndx].sh_size);
    f.read(shstrtab.data(), shstrtab.size());

    for (size_t i = 0; i < shdrs.size(); ++i) {
        std::string secname = shstrtab.data() + shdrs[i].sh_name;
        if (secname == ".dynsym") dynsym_idx = (int)i;
        else if (secname == ".dynstr") dynstr_idx = (int)i;
    }
    if (dynsym_idx == -1 || dynstr_idx == -1) return exports;
    f.seekg(shdrs[dynstr_idx].sh_offset, std::ios::beg);
    std::vector<char> dynstr(shdrs[dynstr_idx].sh_size);
    f.read(dynstr.data(), dynstr.size());
    size_t nsyms = shdrs[dynsym_idx].sh_size / sizeof(Elf64_Sym);
    f.seekg(shdrs[dynsym_idx].sh_offset, std::ios::beg);
    std::vector<Elf64_Sym> dynsyms(nsyms);
    f.read(reinterpret_cast<char*>(dynsyms.data()), nsyms * sizeof(Elf64_Sym));
    for (size_t i = 0; i < nsyms; ++i) {
        uint8_t bind = dynsyms[i].st_info >> 4;
        uint8_t type = dynsyms[i].st_info & 0xF;
        if ((bind == 1 || bind == 2) && type == 2) {
            std::string name = dynstr.data() + dynsyms[i].st_name;
            if (!name.empty()) exports.push_back(name);
        }
    }
    my_log(my_date + ".log", "D", "0000-0001", "so文件导出函数遍历", "完成遍历" + file_path + "文件");
    return exports;
}