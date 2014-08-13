#!/usr/bin/env python
# -*- coding: utf-8 -*-
#author : lbaby   lsylny@gmail.com
""" Insert an excel file into oracle db
    usage:
    eto.py db=usr/passwd@db excel=my.xlsx
    sql="insert into table1 values(:A, :b :c, :AA, NULL)"
    Dependent package : xlrd, cx_Oracle, sqlparse
"""

import re
import sys
import xlrd
import datetime
import cx_Oracle
import sqlparse
import functools


def sql_executor(cursor, sql):
    #For closure imitation
    class bind_to_cursor:
        def __init__(self, cursor, sql):
            """
            Bind a sql(insert only) to cursor
            :type self: object
            :param cursor:  cx_oracle.cursor
            :param sql:  insert sql statement
            """
            self.sql = sql
            self.cursor = cursor
            self.psql = sqlparse.parse(sql)
            self.table_column_list_re = re.compile(r'^\s*(\w+)\s*(\(\s*((\w+\s*,\s*)*)(\w+)\s*\))?\s*$')
            self.insert_value_list_re = re.compile(r'^\s*\(\s*((([\w.]+|:\w+)\s*,\s*)*)([\w.]+|:\w+)\s*\)\s*$')
            self.parenthesis_re = re.compile(r'\((\s*[^\)]+)\)')
            self.table_and_values = self.get_table_values(self.psql[0].tokens)
            if len(self.table_and_values) != 2:
                raise RuntimeError("{0:s} \n is not an expected insert statement".format(sql))
            self.insert_data_type = list()  # [None, datetime.datetime, None, None ...]
            self.get_var_type()
            self.bind_vars = dict()  # { key : [excel_column, insert_data_type] }
            self.get_bind_vars()

        def get_var_type(self):
            """
            """
            query = 'select %s from %s where 1!=1'
            sql_fields = self.table_column_list_re.match(str(self.table_and_values[0])).groups()
            if sql_fields[1] is None:
                query_sql = query % ('*', sql_fields[0])
            else:
                query_sql = query % (sql_fields[2] + sql_fields[4], sql_fields[0])
            self.cursor.execute(query_sql)
            self.insert_data_type = [datetime.datetime
                                     if isinstance(t, cx_Oracle.DATETIME) else None
                                     for t in self.cursor.fetchvars]

        def get_bind_vars(self):
            """
            values (:A, :C, :e, :f)

            """
            values = self.parenthesis_re.match(str(self.table_and_values[1])).groups()[0]
            value_list = values.split(',')
            A_Z = 'abcdefghijklmnopqrstuvwxyz'.upper()
            i = 0
            #{ key : [parameter position(start with 0), excel_column] }
            for k in value_list:
                var_name_match = re.match('^\s*:\s*(\w+)\s*$', k)
                if var_name_match is not None:  # bind variable
                    j = var_name_match.groups()[0]
                    # A -> 0, Z->25 , Az -> 51
                    # value pair : [excel column, parameter position ]
                    self.bind_vars[j] = \
                        [i, functools.reduce(lambda x, y: x * 26 + A_Z.index(y.upper()) + 1, j, 0) - 1]
                i += 1

        def get_table_values(self, ptokens):
            """
            :rtype : list
            :param ptokens:  parsed sql tokens
            :return: insert  table (fields)?
            """
            insert_syntax = (
                ('Token.Keyword.DML', 'INSERT'),
                ('Token.Keyword', 'INTO'),
                (None, self.table_column_list_re),  # table1 or table1 (1,2,3)
                ('Token.Keyword', 'VALUES'),
                (None, self.insert_value_list_re))
            table_values = []
            j = 0
            i = 0
            while j < len(ptokens):
                if str(ptokens[j].ttype).startswith('Token.Text.Whitespace'):
                    j += 1
                    continue
                if insert_syntax[i][0] is not None:
                    if str(ptokens[j].ttype).startswith(insert_syntax[i][0]):
                        if str(ptokens[j]).upper() != insert_syntax[i][1]:
                            break  # SQL syntax error
                    else:
                        break
                else:
                    if insert_syntax[i][1].match(str(ptokens[j])) is not None:
                        table_values.append(ptokens[j])
                    else:
                        break
                j += 1
                i += 1
                if i == len(insert_syntax):
                    break
            return table_values

        def exec_using(self, row):
            key_values = dict()
            for k, v in self.bind_vars.items():
                data_type, excel_column = v[0], v[1]
                if self.insert_data_type[data_type] is not None:  # Excel Date format translate
                    try:
                        key_values[k] = xlrd.xldate.xldate_as_datetime(row[excel_column], 1)
                    except Exception as e:
                        raise RuntimeError('Can not convert ' + str(row[excel_column]) + ' into date: '
                                           + str(e) + ' you must format  this cell into date')
                else:  # or not any translation
                    key_values[k] = row[excel_column]
            self.cursor.execute(self.sql, key_values)

    #Return analysed sql executor
    return bind_to_cursor(cursor, sql).exec_using


def read_excel_by_row(excel):
    book = xlrd.open_workbook(excel)
    for n in range(book.nsheets):
        sheet = book.sheet_by_index(n)
        for r in range(sheet.nrows):
            yield sheet.row_values(r)


def parse_arg(arg):
    """
    argv['key1=v1', 'key2=v2']
    :param arg:
    """
    arg_re = re.compile(r'^([^=]+)=(.+)$')
    striped_args = [m.replace('\r', ' ').replace('\n', ' ') for m in arg]
    return {arg_re.match(m).group(1).upper(): arg_re.match(m).group(2) for m in striped_args}


if __name__ == '__main__':
    if len(sys.argv) != 4:
        raise RuntimeError('''
        usage:
            {0:s}  db=usr/passwd@db excel=all_data.xlsx  \
        sql="insert into aa values(:a, :b, :d, NULL)"
            '''.format(sys.argv[0]))
    argv = parse_arg(sys.argv[1:])
    db = cx_Oracle.connect(argv['DB'])
    cursor = db.cursor()
    exec_using = sql_executor(cursor, argv['SQL'])
    for each_row in read_excel_by_row(argv['EXCEL']):
        try:
            exec_using(each_row)
        except Exception as e:
            print(e, ':', each_row, file=sys.stderr)
    cursor.close()
    db.commit()