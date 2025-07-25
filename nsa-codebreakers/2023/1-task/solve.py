#!/usr/bin/env python3
# task 1
# created by : C0SM0

# imports
import sqlite3
from datetime import datetime, timedelta

# constants
sql_file = sqlite3.connect('database.db')
cursor = sql_file.cursor()

# checks if degrees are 1/100th of each other
def degree_calculator(input_latitude, input_longitude):

    # coordinate constants
    signal_latitude = 26.37105
    signal_longitude = -83.88421
    tolerance = 1 / 100

    # coordinate differences (using absolute values)
    latitude_difference = abs(signal_latitude - input_latitude)
    longitude_difference = abs(signal_longitude - input_longitude)

    return latitude_difference <= tolerance and longitude_difference <= tolerance

# checks if time is within 10 mins of ea/o
def timestamp_calculator(input_date, input_time):
    
    # timestamp cosntants
    signal_date = '02/04/2023'
    signal_time = '19:10:18'
    time_format = '%H:%M:%S'

    # format time values and get difference
    formatted_signal_time = datetime.strptime(signal_time, time_format)
    formatted_input_time = datetime.strptime(input_time, time_format)

    time_difference = abs(formatted_signal_time - formatted_input_time)

    return (input_date == signal_date) or (time_difference <= timedelta(minutes=10))

# parse location table
cursor.execute('SELECT * FROM location')
locations = cursor.fetchall()
possible_coordinate_ids = []

# get coordiantes within 1/100th of a degree
for location in locations:
    id = location[0]
    latitude = float(location[1])
    longitude = float(location[2])

    if degree_calculator(latitude, longitude):
        print(longitude, latitude)
        possible_coordinate_ids.append(id)

# parse timestamp table
cursor.execute('SELECT * FROM timestamp')
timestamps = cursor.fetchall()
possible_timestamp_ids = []

# get timestamps no greater than 10 minutes of each other
for timestamp in timestamps:
    id = timestamp[0]
    time = timestamp[1]
    date = timestamp[2]

    if timestamp_calculator(date, time):
        possible_timestamp_ids.append(id)

# get shared values from the possible timestamps and coordiantes
print(set(possible_coordinate_ids) & set(possible_timestamp_ids))
