//����Ȩ���������������������/��Ŀ/�洢�⣬���ǲ����ļ�������ȷ˵����
/*
Copyright 2025 �

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
    std::string copyright = "� �ĳ���\nCopyright (c) 2025 �\nLicensed under the Apache License, Version 2.0\n";
    //���������ʹ��/�����˿��ŵ�Դ���룬�����·�copyright_2д���ַ���(ע��ʹ��\n���з�)��Ӧ�������������ݺͿ�������Ϣ��ͬʱ�����Ը���ver��
    std::string ver = "0.2.1\n";
    std::string copyright_2 = "";
    return (copyright + "�汾:" + ver + copyright_2);
}