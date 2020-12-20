# Project: Process and Resource Manager
>Name: Yingchen Zhou<br>
>ID: 55879895<br><br>

## How to run the project
>I'm using Visual Studio to program and run the project. <br>
After executing the project, you need to enter the test file name <strong>with document type</strong>. The project will read your file and generate an output file named "<strong>output.txt</strong>" at the end.

## Shell Specs
#### <strong>in</strong><br>
>Restore the system to its initial state.

#### <strong>cr\<p></strong><br>
>Invoke function create(), which creates a new process at the priority level \<p>;<br> 
\<p> can be 1 or 2 (0 is reserved for init process)

#### <strong>de\<i></strong><br>
>Invoke the function destroy(), which destroy the process identified by the PCB index \<i>, and all of its descendants

#### <strong>rq \<r> \<n> </strong><br>
>Invoke the function request(), which requests \<n> units of resource \<r>;<p>
\<r> can be 0, 1, 2, or 3;<p>
>>>\<n> = 1 for \<r>= 0 and \<r>=1<p>
>>>\<n> = 2 for \<r> = 2<p>
>>>\<n> = 3 for \<r> = 3.<p>

#### <strong>rl \<r> \<n></strong><br>
>Invoke the function release(), which release the resource \<r>;<br>
>>\<r> can be 0, 1, 2, or 3; <br>
>>\<n> gives the number of units to be released

#### <strong>to</strong><br>
>Invoke the function timeout().<p>

## Output
For each input command, output the index of the process running next
>><p>output only a single integer, separated from the previous integer by a blank space</p>
>><p>output no other additional information</p>
If an error occurs, output -1 instead of the process index and ignore the command
>><p>the next command will be “in” to start a new test sequence</p>
Start a new line for each “in” command