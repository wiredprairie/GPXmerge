# GPXMerge #
A very simple tool for merging GPX files (from devices like a Garmin eTrex 30 for example) into a single GPX file named "merged.gpx". 

I created this out of frustration that the GPS would create many small files that then were very frustrating to organize and manage inside of Adobe Lightroom. One file however is quite simple! 

## Usage ##
	GPXMerge - merges GPX files into a single file.
	GPXMERGE source-path
	  source-path         Specifies the folder to non-recursively search.
						  All files with the extension .GPX are merged
						  into a single GPX file named MERGED.GPX.
	Skips duplicate segments.



----------

Software licensed (with `dirent.h` and `pugixml.cpp` having their own license):

The MIT License (MIT)

Copyright (c) 2013 Wiredprairie.us

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.