
eto.py  
============
###Insert an excel file into oracle database

### Usage:
	python3 eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1 values (:a, :b , :c)"
#### Or 
	python3 eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1(col1, col2, col3) values (:a, seq.nextval , 3)"

Python 2.x is also support with lame error message


### How to install dependent package 
*	pip install cx_Oracle
*	pip install sqlparse
*	pip install xlrd

#Info
* The :a , :b  is reference of excel column with prefix ':'
* If you want to set fields with constant values , put them in value fields
* If you are insertting a date , please format it inside excel with date and make sure the target column of table is date too
* Function or string are not allowed in vlues section (may support  in next version)


### License (GNU AGPLv3)

Copyright (c) 2014 Lbaby

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


