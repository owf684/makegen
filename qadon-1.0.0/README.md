# How to USE

## Adding to Project
|step| Action                                            |
-----|---------------------------------------------------|
|1   |download source files                              |
|2   |place source files into your project               |
|3   |add the include directive like so include "qadon.h"|


## Qadon File Format

The format of a qadon is similar to a json. All the data members live inside the curly braces { ... }
The data members are seperated with new lines. No commas are necessary. The extension of the file doesn't matter either. 
```
{
 key_1 : value_1
 key_2 : value_2
 key_3 : value_3
 key_n : value_n
}
```


## Creating a Qadon
```
#include "qadon.h"

int main()
{
  // define your qadon
  qadon myQadon;

  // add data memebrs
  myQadon["Hello"] = "World";
  myQadon["This"] = "is easy!";
  myQadon["What"] = " do you think?";

  // accesing data members
  std::string data = myQadon["Hello"]

  // printing all key,data pairs
  myQadon.print();

  // Write qadon to file
  myQadon.write("new.qadon");

  // Readon qadon file
  qadon read("new.qadon")

  return 0;
}
```
## Limitations
The qadon data members are currently limited to strings only. I think I can easily have a mix typed qadon by using templates. That will probably come in version v0.2.0.
