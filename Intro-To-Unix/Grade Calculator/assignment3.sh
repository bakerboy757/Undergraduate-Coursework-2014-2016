#Tyler Kelly
#COP3353
#Assignment 3
#3/25/15

#!/bin/sh

#copy files 

cp -r ~vastola/ufiles/file[12] $PWD
cp -r ~vastola/ufiles/grades $PWD
cp -r ~vastola/ufiles/t[12] $PWD
touch output.txt
touch myprocess.txt

#Grades program
chmod 700  grades
echo "******************* Grades test 1 *******************" >> output.txt
grades < t1 >> output.txt
echo "******************* Grades test 2 *******************" >> output.txt
grades < t2 >> output.txt

#permissions
chmod 644 file1
chmod 644 file2

#diff command
echo "******************* diff test 1 *******************" >> output.txt
diff file1 file2 >> output.txt
echo "******************* diff test 2 *******************" >> output.txt
diff -w file1 file2 >> output.txt
echo "******************* diff test 3 *******************" >> output.txt
diff -iw file1 file2 >> output.txt

#grep command
echo "******************* grep test 1 *******************" >> output.txt
grep -in the file1 >> output.txt
echo "******************* grep test 2 *******************" >> output.txt
grep -n ^The file1 >> output.txt
echo "******************* grep test 3 *******************" >> output.txt
grep -nw who file1 >> output.txt

#process command   
echo "******************* Process command 1 *******************" >> myprocess.txt
ps -ef >> myprocess.txt
echo "******************* Process command 2 *******************" >> myprocess.txt
ps -ef|grep root >> myprocess.txt

#final directory listing
echo "******************* Directory listing  *******************" >> output.txt 
ls -l >> output.txt 

#Create Archive
mkdir archive
tar -cvf myTar.tar file1 file2 grades output.txt myprocess.txt
mv myTar.tar archive
cd archive
gzip myTar.tar 



