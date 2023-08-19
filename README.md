# C_library
C library for personal reference

## description for each file
* system.c: bash commands to perform useful system calls
* fcntl_flags.c: all the file descriptor flags
* errorchecked_heap.c: self-explanatory filename
* funcptr.c: function pointer
* **game_of_chance.c**: game to show the usage of the other files + other stuff
this is a multi-player game that writes to the /var directory.  
Therefore you need to run the following commands:  
  * `clang game_of_change.c -o game_of_chance` (compilation)  
  * `sudo chown root:root ./game_of_chance` (change ownership)  
  * `sudo chmod u+s ./game_of_chance` (set the setuid permission)  
  * `./game_of_chance` (run)  
