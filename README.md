fsrv
====

**fsrv** is a high performance static file server written in C. It is very minimalistic and lightweight.

Installation
------------
````
$ git clone https://github.com/vivekn/fsrv.git
$ cd fsrv
$ make
````
Then add this directory to your PATH.

Usage
----
````
fsrv-pf <static_files_directory> <port>
````

Eg: 
````
fsrv-pf /var/www/public 80
````


----

Author: Vivek Narayanan < vivek_n@me.com >

LICENSE: BSD