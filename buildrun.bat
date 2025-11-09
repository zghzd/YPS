python -m PyInstaller --onefile --distpath "d:/yps/x64/bin/" --name abso.exe python_ab_so.py
python -m PyInstaller --onefile --distpath "d:/yps/x64/bin/" --name abaxml.exe python_ab_xml-android.py
7z a -tzip "D:\YPS\build and package\yps.zip" "D:\YPS\x64\bin\*" "D:\YPS\x64\Release\yps.exe" -y
