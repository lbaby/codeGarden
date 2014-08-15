
eto.py  
============
##insert an excel file into oracle database
## Usage:
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1 values (:a, :b , :c)"
### or 
###   eto.py excel=myexcel.xls db=user/passwd@db sql="insert into  table1(col1, col2, col3) values (:a, seq.nextval , 3)"
### 

#Notice
* The :a , :b  is reference of excel column with prefix ':'
* If you want to set fields with constant values , put them in value fields
* If you are insertting a date , please format it inside excel with date and make sure the target column of table is date too
* Function or string are not allowed in vlues section (may support  in next version)


