# C-Advance-finals

- [X] 12/27 (Wed.): Ray 完成 API <br>
- [ ] 1/3   (Wed.): 大家完成各自的部分 <br>
- [ ] 1/6   (Sat.): 完成 function 串接與 dump <br>
- [ ] 1/8   (Mon.): 完成錄影


# Doc
- function : get 
    - Get the file from in-memory filesystem.
    - And dump the file to the `dump` folder.
- function : put
    - put the local file into the in-memory filesystem.
- function : rmdir 
    - recursivly del the node under specific folder node.

# How to test
- We use google test suite to do the unit test ([How install gtest on your computer](https://github.com/google/googletest/blob/main/googletest/README.md))
- use command `make run_test` will compile the whole project and run the test program
