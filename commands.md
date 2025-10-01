# 指令参数表  
| 指令名称 | 运行参数 | 指令说明 | 参数说明 |
| --- | --- | --- | --- |
| filecompare | YPS.exe filecompare \<file1> \<file2> \[-o] | 以行为单位，比较两个文件的差异 | file1, file2是两个需要比较的文件名称,-o指定允许输出到文件 |
| getdllexport64 | YPS.exe getdllexport64 \<file1> \[-o] | 遍历一个64位dll文件的导出函数 | file1是dll文件的文件名,-o指定允许输出到文件 |
| getsoexport | YPS.exe getsoexport \<file1> \[-o] | 遍历一个so文件的导出函数 | file1是so文件的文件名,-o指定允许输出到文件 |
| entropy | YPS.exe entropy file1 | 对二进制文件求熵 | file1是文件的文件名 |
| smalifilesprocessing | YPS.exe smalifilesprocessing dir1 dir2 | 整理合并smali文件 | dir1是smali文件的目录,dir2是输出 |
