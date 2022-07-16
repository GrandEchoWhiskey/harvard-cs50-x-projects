[<- Back to course](../README.md)

<p align="center"><a href="https://cs50.harvard.edu/x/2022">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/course/harvard100.png" /><br>
</a></p>
<h1 align="center">CS50's Introduction to Computing Science<br><br>Volume</h1>

<p align="center"><a href="#">
  <img src="https://github.com/GrandEchoWhiskey/grandechowhiskey/blob/main/icons/programming/c.png" />
</a></p>

### Background:
WAV files are a common file format for representing audio. WAV files store audio as a sequence of “samples”: numbers that represent the value of some audio signal at a particular point in time. WAV files begin with a 44-byte “header” that contains information about the file itself, including the size of the file, the number of samples per second, and the size of each sample. After the header, the WAV file contains a sequence of samples, each a single 2-byte (16-bit) integer representing the audio signal at a particular point in time.

Scaling each sample value by a given factor has the effect of changing the volume of the audio. Multiplying each sample value by 2.0, for example, will have the effect of doubling the volume of the origin audio. Multiplying each sample by 0.5, meanwhile, will have the effect of cutting the volume in half.

### Getting Started:
Export this directory using SVN.
```
svn export https://github.com/GrandEchoWhiskey/harvard-cs50-x-projects/trunk/lab-4-volume
```
Change directory
```
cd lab-4-volume
```
Compile the program. (Optional)
```
make volume
```
Now run the binary file
```
./volume INPUT.wav OUTPUT.wav 2.0
```
