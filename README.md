# todo_cpp
A CLI todo list using CPP.

This tool is for the nerds who wish not to leave their terminal windows to open up a new tab in their browser or an application to jolt down the few things they have to get done by the end of the day.
With this program you can quickly write down your todo list on the go right from your terminal.

# Installation
**Note**: First and foremost you should open `todo.h` and replace the variable `FILENAME` value with your `~/.todoc/tasks.txt` in absolute path (Will fix this soon).

For your installation you can run the `todoc_installer.sh` script
```
chmod +x todoc_installer.sh
./todoc_installer.sh
```
For updating run the `update.sh` script instead.
```
chmod +x update.sh
./update.sh
```

But soon enough a new installer will be created that would enable the program to be launched from anywhere within 
your shell.

# Usage
The program is to be executed as follows:
```
./todoc <option>
```
The todoc program currently have all of the functionalities given below.
```
help: To display help
show: Shows the top priority task
showall: Shows all of the tasks
push: Add a new task to the bottom of the list
  Usage: todoc push <item name>
pop: Delete the top priority task
insert: Insert a task to a specific position
  Usage: todoc insert <position> <item name>
delete: Delete a task from a specific position
  Usage: todoc delete <position>
clear: To delete all tasks from the list
insertfrom: To insert tasks from a specific filename
  Usage: todoc insertfrom <filename>
swap: To swap the priority of two tasks
  Usage: todoc swap <position1> <position2>
```

# Examples
To push a new task:
```
./todoc push 12 mile jogging
```
To push tasks from a file
```
./todoc insertfrom ~/Documents/newtasks.txt
```
Or you could couple up with bash for an even better experience.

You could insert multiple entries using a bash for loop
```
for i in {1..4}; do
  ./todoc push
done;
Finish todoc documentation
Go for a haircut
Finish studying ACN Module 3
Finish studying ACN Module 4
```
And you can check your tasks with `./todoc showall` which outputs:
```
1) Finish todoc documentation
2) Go to the barber
3) Finish ACN Module 3
4) Finish ACN Module 4
```
Or you can append the the nth line of a textfile by pipelining.

To append the 3rd line from a file `newtasks.txt`
```
sed '3q;d' newtasks.txt | ./todoc push
```
or
```
head -3 newtasks.txt | tail -1 | ./todoc push
```
Imagination is your limits.


**Note:** Inputting arguments through stream input is not enabled for all options. So, coupling of bash functionalities or usage of redirection operators 
may not work everywhere. This functionality will be improved in the future.

# Future updates
- A proper installer that helps to call todoc from anywhere within the terminal.
- Improve exception handling
- A way to sync with a text file in the web so that you don't have to carry your laptop everywhere.
- Improving stream input.
- A way to share/view todo lists with/of friends.
