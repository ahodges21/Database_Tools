#! /usr/bin/env python

import xlrd
import csv

inputfile = open("xlsx_input.txt","r")
path = "csv_Uni/{}_{}"



for line in inputfile:
    book = xlrd.open_workbook(line.replace("\n",""))
    for j in range(1,len(book.sheet_names())):
        sheet = book.sheet_by_index(j)
        target = path.format(line[-20:-6],"sheet" + str(j) +".csv")
        print target
        csvWriter = csv.writer(open(target,"w"), delimiter = '\t')
        for k in range(sheet.nrows):
            csvWriter.writerow(sheet.row_values(k))
            
                


