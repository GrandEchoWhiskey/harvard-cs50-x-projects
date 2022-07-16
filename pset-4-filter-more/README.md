[<- Back to course](../README.md)

<p align="center"><a href="https://cs50.harvard.edu/x/2022">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/course/harvard100.png" /><br>
</a></p>
<h1 align="center">CS50's Introduction to Computing Science<br><br>Filter (More)</h1>

<p align="center"><a href="#">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/programming/c.png" />
</a></p>

### Background:
What does it even mean to filter an image? You can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image. Here we can find such filters as grayscale, relfection, blur or edge highlighting.

### Getting Started:
Export this directory using SVN.
```
svn export https://github.com/GrandEchoWhiskey/harvard-cs50-x-projects/trunk/pset-4-filter-more
```
Change directory
```
cd pset-4-filter-more
```
Compile the program. (Optional)
```
make filter
```
Now run the binary file
```
./filter TYPE INFILE.bmp OUTFILE.bmp
```

Types:
* `-g` -> black-white
* `-r` -> reflect (horizontally)
* `-b` -> box-blur
* `-e` -> highlight edges
