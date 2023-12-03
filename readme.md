# How To Run The Spell Checker!

> [!NOTE]
> Ensure that all dependencies are installed
>    - make
>    - cmake (3.11 or Higher required)
>    - g++

### Building 
First run the cmake! 3.11 or Higher is required
This should be ran in the build directory (spellcheck)
`cmake .` 

Following this you need to run the generated make file
'make'

Then build the program
`./proj5.x dictionary.txt inFile.txt outFile.txt`
If you would like to build the myspell program instead do not add any arguments
`./proj5.x`

Following this you will be prompted with a UI interface...

If none of that is working it may be an issue with the caching of cmake. try running.

```bash
rm -rf extracredit_pt2/_deps/ftxui-subbuild
cmake -B .
cmake --build .
```
If needed replace `.` with the build directory (spellcheck by default)


### How This Was Implemented
I used the ftxui library from github. https://arthursonzogni.github.io/FTXUI

### How My Algorithm is Superior
With my implementation I have implemented the default method (character substition), which loops through the word changing each letter individually, as well as my improved methods. The improved 
methods work as follows:

- Deletion - removes 1 character from each position to see if it is in the dictionary
- Insertion - adds 1 character from each position to see if it is in the dictionary
- Swapping - swapps characters to see if they are in the dictionary

```cpp
// -------- Default Way -------- //
for(char j = 'a'; j <= 'z'; j++){
    tempWord = word;
    tempWord[i] = j;
    if(dictionary.contains(tempWord)){
        similarWords.push_back(tempWord);
    }
}
// --------------------------- //


// -------- Additions -------- //
// Character deletion
tempWord = word.substr(0, i) + word.substr(i + 1);
if(dictionary.contains(tempWord)){
    similarWords.push_back(tempWord);
}

// Character insertion
for(char j = 'a'; j <= 'z'; j++){
    tempWord = word.substr(0, i) + j + word.substr(i);
    if(dictionary.contains(tempWord)){
        similarWords.push_back(tempWord);
    }
}

// Character swapping
for(int i = 0; i < length - 1; i++){
    tempWord = word;
    swap(tempWord[i], tempWord[i + 1]);
    if(dictionary.contains(tempWord)){
        similarWords.push_back(tempWord);
    }
}
```

