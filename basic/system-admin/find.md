Basic Examples
1. find . -name thisfile.txt

If you need to know how to find a file in Linux called thisfile.txt, it will look for it in current and sub-directories.

2. find /home -name *.jpg

Look for all .jpg files in the /home and directories below it.

3. find . -type f -empty

Look for an empty file inside the current directory.

4. find /home -user randomperson-mtime 6 -iname ".db"

Look for all .db files (ignoring text case) that have been changed in the preceding 6 days by a user called randomperson.

https://www.plesk.com/blog/various/find-files-in-linux-via-command-line/


-O2 filters by name and type of file before carrying on with more demanding filters to find a file in Linux. Level -O3 reorders all tests according to their relative expense and how likely they are to succeed.

-O1 – (Default) filter based on file name first
-O2 – File name first, then file-type
-O3 – Allow find to automatically re-order the search based on efficient use of resources and likelihood of success
-maxdepth X – Search this directory along with all sub-directories to a level of X
-iname – Search while ignoring text case.
-not – Only produce results that don’t match the test case
-type f – Look for files
-type d – Look for directories
Find Files by When They Were Modified
The Linux find command contains the ability to filter a directory hierarchy based on when the file was last modified:

find / -name "*jpg" -mtime 5

find /home/randomuser/ -name "*jpg" -mtime 4

The initial Linux find command pulls up a list of files in the whole system that end with the characters jpg and have been modified in the preceding 5 days. The next one filters randomuser’s home directory for files with names that end with the characters “conf” and have been modified in the preceding 4 days.

Use Grep to Find Files Based on Content
The find command in Linux is great but it can only filter the directory tree according to filename and meta data. To search files based on what they contain you’ll need a tool like grep. Take a look:

find . -type f -exec grep "forinstance" '{}' \; -print

This goes through every object in the current directory tree (.) that’s a file (-type f) and then runs grep ” forinstance ” for every file that matches, then prints them on the screen (-print). The curly braces ({}) are a placeholder for those results matched by the Linux find command. The {} go inside single quotes (‘) so that grep isn’t given a misshapen file name. The -exec command is ended with a semicolon (;), which also needs an escape (\;) so that it doesn’t end up being interpreted by the shell.

Before -exec was implemented, xargs would have been used to create the same kind of output:

find . -type f -print | xargs grep "forinstance"

How to Locate and Process Files Using the Find Command in Linux
The -exec option runs commands against every object that matches the find expression. Let’s see how that looks:

find . -name "rc.conf" -exec chmod o+r '{}' \;

This filters all objects in the current directory tree (.) for files named rc.conf and runs the chmod o+r command to alter file permissions of the results that find returns.

The root directory of the Linux is where the commands that -exec runs are executed. Use -execdir to execute the command you want in the directory where the match is sitting, because this might be more secure and improve performance under certain circumstances.

The -exec or -execdir options will continue to run on their own, but if you’d like to see prompts before they do anything, swap out -exec  -ok or -execdir for -okdir.

How To Manage Files Using Plesk?
Let’s say you have a website that’s all ready to go on your laptop/desktop and you’d like to use File Manager to upload it to the Plesk on Linux server:

On your machine, you’ll need to take the folder with all of your website’s files on it and add it to a compressed archive in one of the usual formats (ZIP, RAR, TAR, TGZ, or TAR.GZ).
In Plesk, go to Files, click the httpdocs folder to open it, click Upload, choose the archive file, and then click Open.
As soon as you’ve uploaded it, click in the checkbox you see alongside and then on Extract Files.
How to Edit Files in File Manager
File Manager lets you edit your website pages by default. To do this you can use:

An HTML editor or a “what-you-see-is-what-you-get” style of editor, which is a nice option because it adds the HTML tags for you. If you aren’t all that confident with HTML then this can be a helpful option.
Code editor. When you open HTML files with this one you’ll be presented with text where the HTML syntax is highlighted. If you’re comfortable with adding HTML tags yourself then code editor is for you.
Text editor. HTML files are opened as ordinary text with this one.
Your Plesk administrator may have already et up the Rich Editor extension, in which case you can use it for HTML file editing. Rich Editor works in a what-you-see-is-what-you-get fashion, just like Code Editor, although it’s better specced with features like a spellchecker for instance.

Here’s how to use File Manager to edit a file:

Put the cursor over the file and the line that corresponds with it will show a highlight.
Open the context menu for the file by clicking on it.
Click Edit in … Editor (this will vary depending on your chosen editor).
How to Change Permissions with File Manager
There are some web pages and files that you don’t necessarily want to share with the world, and that’s where altering their permissions settings can come in handy.

To achieve this, find the item you want to restrict Internet access for like this:

Place your cursor over it and wait for the highlight to appear as in the previous example.
Click on the file to open its context menu and do the same again on Change Permissions.
Make your change and then hit OK. If you’d like to find out more about how to look at and alter permissions in Setting File and Directory Access Permissions.
File Manager’s default approach is to change permissions in a non-recursive manner, so consequently, sub-files and directories don’t aren’t affected by the changed permissions of the higher-level directories they belong to. With Plesk for Linux, you can make File Manager modify permissions in a recursive manner, assuming that your Plesk administrator set up the Permissions Recursive extension and that you understand the octal notation of file permissions.

To enable recursive editing of access permissions:

Place the cursor over the directory and wait for the highlight.
Click to open its context menu and then again on Set Permissions Recursive.
Now you can edit them. “Folder Permissions” is talking about the higher-level directory and any of its associated sub-directories. “File Permissions” applies to sub-files in this instance.
When you’ve completed your permission amendments, click OK.
File Search in File Manager
You’ve got a little bit of latitude with file searches. You can have File Manager hunt for a specific bit of text either in the file name, in the content, or in both. You can choose how you want it to search for files by clicking on the icon that appears adjacent to your chosen search field, and then clicking on whichever type you prefer.