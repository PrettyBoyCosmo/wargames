#!/usr/bin/env python3
# task 1
# created by : C0SM0

# imports
import sqlite3
from datetime import datetime, timedelta

# constants
sql_file_path = 'database.db'

# checks if degrees are 1/100th of each other
def degree_calculator(input_latitude, input_longitude):
    signal_latitude = 26.37105
    signal_longitude = -83.88421
    tolerance = 1 / 100
    latitude_difference = abs(signal_latitude - input_latitude)
    longitude_difference = abs(signal_longitude - input_longitude)
    return latitude_difference <= tolerance and longitude_difference <= tolerance

# checks if time is within 10 mins of each other
def timestamp_calculator(input_date, input_time):
    signal_date = '02/04/2023'
    signal_time = '19:10:18'
    time_format = '%H:%M:%S'
    formatted_signal_time = datetime.strptime(signal_time, time_format)
    formatted_input_time = datetime.strptime(input_time, time_format)
    time_difference = abs(formatted_signal_time - formatted_input_time)
    return input_date == signal_date or time_difference <= timedelta(minutes=10)

# Function to get IDs with matching coordinates and timestamps
def get_matching_ids():
    with sqlite3.connect(sql_file_path) as conn:
        cursor = conn.cursor()

        # Parse location table
        cursor.execute('SELECT id, latitude, longitude FROM location')
        possible_coordinate_ids = {
            location_id
            for location_id, latitude, longitude in cursor.fetchall()
            if degree_calculator(float(latitude), float(longitude))
        }

        # Parse timestamp table
        cursor.execute('SELECT id, time, date FROM timestamp')
        possible_timestamp_ids = {
            timestamp_id
            for timestamp_id, time, date in cursor.fetchall()
            if timestamp_calculator(date, time)
        }

    # Get shared values from the possible timestamps and coordinates
    return possible_coordinate_ids & possible_timestamp_ids

# Get and print the matching IDs
matching_ids = get_matching_ids()
print(matching_ids)

