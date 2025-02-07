import json
import time
import math
from kafka import KafkaConsumer
from datetime import datetime

# Initialize Kafka Consumer
consumer = KafkaConsumer(
    'location-updates',
    bootstrap_servers='localhost:9092',
    auto_offset_reset='earliest',
    group_id='location-tracker-group',
    value_deserializer=lambda m: json.loads(m.decode('utf-8'))
)

def haversine(lat1, lon1, lat2, lon2):
    """
    Calculate the great circle distance between two points 
    on the Earth (specified in decimal degrees) using the haversine formula.
    """
    # Convert decimal degrees to radians
    lat1, lon1, lat2, lon2 = map(math.radians, [lat1, lon1, lat2, lon2])
    
    # Haversine formula
    dlat = lat2 - lat1 
    dlon = lon2 - lon1 
    a = math.sin(dlat / 2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2)**2
    c = 2 * math.asin(math.sqrt(a)) 
    r = 6371  # Radius of Earth in kilometers
    return c * r

total_distance = 0.0
prev_location = None
report_interval = 30  # seconds
last_report_time = time.time()

print("Starting consumer. Waiting for location updates...")
for message in consumer:
    data = message.value
    current_location = (data['latitude'], data['longitude'])
    
    if prev_location is not None:
        # Calculate distance between the previous and current location
        distance = haversine(prev_location[0], prev_location[1],
                             current_location[0], current_location[1])
        total_distance += distance
    prev_location = current_location

    # Check if it's time to generate a report
    if time.time() - last_report_time >= report_interval:
        report_time = datetime.utcnow().isoformat()
        print(f"[{report_time}] Total Distance Traveled: {total_distance:.4f} km")
        last_report_time = time.time()

