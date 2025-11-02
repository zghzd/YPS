# 开发一个用于YPS的扩展包  
### 先决条件  
- YPS应用程序  
- 文本编辑器  

### 开始之前  
- 决定你的扩展包的名称和开发者名称  
- 建立一个空文件夹，以你的扩展包名称为名字  
- 在文件夹下建立`<packagename>.pack.yps`文件，其中，\<packagename\>与文件夹名称相同  
- 准备你需要的其他自定义文件，将它们一同放在文件夹内  

### 开发
#### \<packagename\>.pack.yps文件  
- 使用文本编辑器打开`<packagename>.pack.yps`文件，并在第一行写入`YPS_PACK`  
- 之后，在第二行写入`<developer>|<packagename>`，其中，\<developer\>是开发者名称，\<packagename\>是你的扩展包名称  
- 之后，在后面行中写入以下的任意一个或多个内容，注意替换一些预留值：  
`arguments-><arguments>`让YPS将参数传递给此包的可执行文件  
`packageID-><ID>`指定此包的ID  
`load_exec-><filename>`让YPS加载名称为filename的可执行文件  

[示例文件](example.pack.yps)  

#### 字符限制  
用户自定义文本中（developer、packagename），不得出现以下的任意字符：
`-` `>` `/` `\` `[` `]` `<` `{` `}` `+` `=` `*`