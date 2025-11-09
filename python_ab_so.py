import sys
import os
from capstone import *
from elftools.elf.elffile import ELFFile

def detect_architecture(elf_file):
    machine = elf_file.header.e_machine
    print(f"机器码: {machine} (类型: {type(machine)})")
    
    arch_map = {
        'EM_ARM': (CS_ARCH_ARM, CS_MODE_ARM),
        'EM_AARCH64': (CS_ARCH_ARM64, CS_MODE_ARM),
        
        'EM_386': (CS_ARCH_X86, CS_MODE_32),
        'EM_X86_64': (CS_ARCH_X86, CS_MODE_64),
        
        'EM_MIPS': (CS_ARCH_MIPS, CS_MODE_MIPS32),
        'EM_MIPS_RS3_LE': (CS_ARCH_MIPS, CS_MODE_MIPS64),
        
        'EM_PPC': (CS_ARCH_PPC, CS_MODE_32),
        'EM_PPC64': (CS_ARCH_PPC, CS_MODE_64),
        
        'EM_SPARC': (CS_ARCH_SPARC, CS_MODE_BIG_ENDIAN),
    }
    
    result = arch_map.get(machine, (None, None))
    print(f"映射结果: {result}")
    return result

def disassemble_so(input_file, output_dir):
    with open(input_file, 'rb') as f:
        elf = ELFFile(f)
        arch, mode = detect_architecture(elf)
        
        if arch is None:
            print(f"不支持的架构: {elf.header.e_machine}")
            return False
        
        print(f"使用架构: arch={arch}, mode={mode}")
        
        if not isinstance(arch, int) or not isinstance(mode, int):
            return False
        
        try:
            md = Cs(arch, mode)
            
            os.makedirs(output_dir, exist_ok=True)
            
            base_name = os.path.splitext(os.path.basename(input_file))[0]
            output_file = os.path.join(output_dir, f"{base_name}_disassembled.asm")
            
            with open(output_file, 'w', encoding='utf-8') as out_f:
                for section in elf.iter_sections():
                    if section.header.sh_flags & 0x4:
                        out_f.write(f"\n; Section: {section.name}\n")
                        out_f.write(f"; Address: 0x{section.header.sh_addr:x}\n")
                        out_f.write(f"; Size: 0x{section.header.sh_size:x}\n")
                        out_f.write("=" * 50 + "\n")
                        
                        code = section.data()
                        address = section.header.sh_addr
                        
                        disasm_count = 0
                        for insn in md.disasm(code, address):
                            out_f.write(f"0x{insn.address:08x}:\t{insn.mnemonic}\t{insn.op_str}\n")
                            disasm_count += 1
                        
                        print(f"反汇编了 {disasm_count} 条指令在段 {section.name}")
            
            print(f"反汇编完成: {output_file}")
            return True
            
        except Exception as e:
            print(f"Capstone 初始化失败: {e}")
            return False

def main():
    if len(sys.argv) != 3:
        sys.exit(1)
    
    input_file = sys.argv[1]
    output_dir = sys.argv[2]
    
    if not os.path.exists(input_file):
        sys.exit(1)
    
    success = disassemble_so(input_file, output_dir)
    sys.exit(0 if success else 1)

if __name__ == "__main__":
    main()