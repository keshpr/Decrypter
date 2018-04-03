# Decrypter
Substitution cipher decoder

Made using C++. Project for "CS32: Introduction to Computer Science II" (course at UCLA)

Wrote the code in MyHash.h, Decrypter.cpp, Tokenizer.cpp, Translator.cpp, WordList.cpp and myTester.cpp
The rest of the code was provided by the professor.

A report describing the classes implemented is included, and present in the Decrypter folder gotten after
unzipping Decrypter.zip. 

To run, unzip the Decrypter.zip file. Open the Decrypter folder, and open Project4.vcxproj using Visual Studio. 
Select "Start Without Debugging" under the Debug dropdown menu. The code has been set up to decrypt a 
particular ciphertext. 

There are four example ciphertexts provided as the variables string1, ... , string4
in myTester.cpp (lines 31-34). The string to be decoded is set on line 127. It is currently set to
string1. To decode other ciphertexts, change the argument to decrypter.crack() from string1 to
any of the other available strings (string2 for example) or to any other ciphertext of your choosing 
(place double-quoted ciphertext within the parentheses of decrypter.crack()). Follow the aforementioned 
steps to get all possible decrypted texts for any ciphertext.
