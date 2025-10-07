//（版权声明适用于整个解决方案/项目/存储库，除非部分文件中有明确说明）
/*
Copyright 2025 翊

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <iostream>
std::string copyright() {
    std::string copyright = "翊 的程序\nCopyright (c) 2025 翊\nLicensed under the Apache License, Version 2.0\n";
    //如果第三者使用/更改了开放的源代码，请在下方copyright_2写入字符串(注意使用\n换行符)。应当包含更改内容和开发者信息，同时，可以更改ver。
    std::string ver = "0.2.1\n";
    std::string copyright_2 = "";
    return (copyright + "版本:" + ver + copyright_2);
}