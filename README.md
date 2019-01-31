# dictionaryConverter
Change dct format to bnf format

use guide
1. Copy the pronunciation list you want to add from Excel and save it as .txt
2. $ make(= gcc -C dictionaryConverter.c)
3. $ dictionaryConverter.exe input.txt enu(Country identifier : ena, eng, enu ...)
4. $ ls -> check output.dct file 
5. Run DictionaryEditor.exe -> Language model set -> User Dictionary Editor > Open User Dictionary -> output.txt import
6. Put focus on the key you want to generate a phonetic symbol and click Generate Transcription(AutoCopy To Entry check) -> Save User Dictionary
8. $ dictionaryConverter.exe output.dct -> ls -> check final.dct file
