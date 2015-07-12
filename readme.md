#sdes

/*  
    Copyright (C) 2013 Jason Giancono (jasongiancono@gmail.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

This was a task for an assignment in a cryptography unit in my undergraduate computer science degree. This was written in 2013. It is the implementation of S-DES, a simplified version of DES used to explain cryptography concepts. More on S-DES can be found [here](mercury.webster.edu/aleshunas/COSC%205130/G-SDES.pdf).

    USAGE: sdes <FLAG> <input filename> <output filename> <seed(base2)> 
    FLAGS:	-d: decrypt
            -e: encrypt