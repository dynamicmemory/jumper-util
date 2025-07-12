#JUMPER

The idea is instead of having to use **cd** to navigate between directories, I 
can just use "jmp <directory name>" and land straight in it. That's the basic 
idea atleast, which language to write it in and if I ever use it or find it useful
is a whole other question i'll answer shortly.

Current working version is written in python, I ideally would like to rewrite in C 
or assembly as python is very slow to scour an entire machines file system.

To test this out all you need to do:
- place the proto.py file somewhere in your machine you wish to store it 
- add the zsh script code to your .zshrc or .bash file
- change the file path in between the <> of this line dest=$(python <~/projects/jumper/proto.py> "$1")
  to the file path of where ever you saved the .py script
- Create a .jmp_list in your home directory and fill it with any directories you want quick access too 
- source .zshrc or .bash to refresh your script 

now you should be able to use: 'jmp desired_directory' and you should jump straight to it if it exists.
If multiple directories share the same name, you will be prompted to choose one by selecing its number.
If you type this: 'jmp do<tab>' with the tab representing an actual tab, it will try to auto complete from '
an item it matches from your jump list, if there are multiple, it will show you multiple.

Thats it, very basic, but a very handy tool for me. Now that I got a basic version up, ill get 
around to rewritting in a faster language to really speed up jmping around your file system.
