#! /usr/bin/env python

import xlrd
import csv


book = xlrd.open_workbook("TileDataBase.xlsx", encoding_override="utf-8")
outname = "csv_GSU/Database_B{}"
for i in range(len(book.sheet_names())-1):
    sheet = book.sheet_by_index(i)
    name = outname.format(str(i+21)+".csv")
    csvWriter = csv.writer(open(name,"w"), delimiter = '\t')
    for row in range(sheet.nrows):
        csvWriter.writerow(list(x.encode('utf-8') if type(x) == type(u'') else x for x in sheet.row_values(row)))
