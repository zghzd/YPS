# YPS  
## 快速导航  
- [已知问题](known_issues.md)  
- [应用程序标准内部代码](codes.md)  
- [指令及参数表](commands.md)
## 已定义语句  
`issuesID`  
> 在[known_issues.md](known_issues.md)中定义  

`codeID`  
> 在[codes.md](_codes.md)中定义  
## 已知应用程序组件特性  
getdllexport64
> 只能遍历明确存在函数导出表的64位dll文件  
> 导出表不存在、文件损坏、dll文件为32位等情况，均会导致应用程序抛出异常并记录日志，之后，应用程序将崩溃  

getsoexport
> 只能遍历明确存在函数导出表的so文件  
> 导出表不存在、文件损坏等情况，均会导致应用程序抛出异常并记录日志，之后，应用程序将崩溃  

filecompare
> 如果文件不存在或读取失败，则视为文件为空文件  
> `+=`表示相对于第一文件，多出的行，`-=`相反。如果是更改的行，视为减少后增加。  
