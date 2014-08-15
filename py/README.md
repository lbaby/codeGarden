
eto.py  
============
##insert an excel file into oracle database
## Usage:
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1 values (:a, :b , :c)"
#### or
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1 values (:a, 'x' , :c)"
#### or
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1 values (:a, seq.nextval , :c)"
#### or 
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1(col1, col2, col3) values (:a, seq.nextval , :c)"
###  
