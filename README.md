# Library-Managment-System
ESE 224 Final Project for Fall 2022.  

# to anyone that might play around with the code
The system works off of textfiles for storage as well as json.

If you want to make your own set of logins, and books, the following need to be done:  
1. New User data needs to be formatted EXACTLY as the current "student.txt".
2. "student.txt" holds all login information and is what the system uses to check auth. Later on in program it works off a json object. 
3. New book data needs to be formatted EXACTLY as the current "book.txt".
4. "book.txt" holds all login information and is what the system uses to check auth. Later on in program it works off a json object. 
5. At no point should a user of the program touch the .json files. These will be maanaged automatically so dont feel the need/desire to wok onto them!


A sample set of login info would look like:
```
[0, 1, and 2 all indicate privledges to the system. 0 is a Student, 1 is a Teacher, 2 is a Librarian]
2	Westery	HereTree	
0 Mike qwerty
1 Alfonozo 6735109
```

A sample set of book info would look like:
```
[Information for books is stored in order as: ISBN TITLE AUTHOR GENRE NUMBEROFCOPIES]
16278279832   How_to_tie_your_shoes Rigel_Oakfeild Tutorials  2
```
 
# compile instructions
```zsh
cd /path-to-dir/  # Linux or macOS
cd \path-to-dir\  # Windows
```
then,
```zsh
sh make.sh         # Linux or macOS
./make.bat         # Windows (PowerShell)
make.bat           # Windows (Command Prompt)
```
finally,
```zsh
./main             # Linux or macOS
./main.exe         # Windows (PowerShell)
main.exe           # Windows (Command Prompt)
```
