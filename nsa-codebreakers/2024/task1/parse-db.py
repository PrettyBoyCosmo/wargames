#!/usr/bin/python3

"""
Title:          parse-db.py
Description:    parse database from NSA-CB Task1
Author:         bluecosmo
Version:        1.0
"""

# imports
import xml.etree.ElementTree as ET
import sys

# get cmd line arguments
def arg(index):
    try:
        return sys.argv[index]

    except IndexError:
        print("[!] ERROR: run `main.py <file.xml>`")
        exit(1)

# main code
def main():

    # NAMESPACES used in the XML
    NAMESPACES = {
        'office': 'urn:oasis:names:tc:opendocument:xmlns:office:1.0',
        'table': 'urn:oasis:names:tc:opendocument:xmlns:table:1.0',
        'text': 'urn:oasis:names:tc:opendocument:xmlns:text:1.0'
    }

    # open xml
    xml_file = arg(1)
    tree = ET.parse(xml_file)
    root = tree.getroot()
    rows = root.findall('.//table:table-row', NAMESPACES)

    # iterate rows
    for row in rows:
        cells = row.findall('table:table-cell', NAMESPACES)

        # filter cells
        if len(cells) >= 10:
            organization = cells[0].find('text:p', NAMESPACES).text
            address = cells[1].find('text:p', NAMESPACES).text
            person1 = cells[2].find('text:p', NAMESPACES).text
            person1_number = cells[3].find('text:p', NAMESPACES).text
            person1_email = cells[4].find('text:p', NAMESPACES).text
            person2 = cells[5].find('text:p', NAMESPACES).text
            person2_number = cells[6].find('text:p', NAMESPACES).text
            person2_email = cells[7].find('text:p', NAMESPACES).text
            order_id = cells[8].find('text:p', NAMESPACES).text
            date = cells[9].find('text:p', NAMESPACES).text

            # stage 1
            # print(f"Organization: {organization}")
            # print(f"Address: {address}")
            # print(f"Person 1: {person1}, Number: {person1_number}, Email: {person1_email}")
            # print(f"Person 2: {person2}, Number: {person2_number}, Email: {person2_email}")
            # print(f"Order ID: {order_id}, Date: {date}")
            # print("-" * 40) # border

            # stage 2
            # print(f"Organization: {organization}", end=" ")
            # print(f"Address: {address}", end=" ")
            # print(f"Person 1: {person1}, Number: {person1_number}, Email: {person1_email}", end=" ")
            # print(f"Person 2: {person2}, Number: {person2_number}, Email: {person2_email}")

            # stage 3
            if (address == "28754 Michelle Street, Port Bradleytown, IA 90919"):
                print(f"Organization: {organization}")
                print(f"Address: {address}")
                print(f"Person 1: {person1}, Number: {person1_number}, Email: {person1_email}")
                print(f"Person 2: {person2}, Number: {person2_number}, Email: {person2_email}")
                print(f"Order ID: {order_id}, Date: {date}")

# run main()
if __name__ == "__main__":
    main()
