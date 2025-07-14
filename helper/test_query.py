import requests

# Replace with your Space-Track credentials
USERNAME = 'nelsongoosman@gmail.com'
PASSWORD = '!NjpZGV3S23hjqa'

LOGIN_URL = 'https://www.space-track.org/ajaxauth/login'
# Request all active GP objects with PERIGEE < 2000 (i.e., LEO)
QUERY_URL = 'https://www.space-track.org/basicspacedata/query/class/gp/EPOCH/>now-1/MEAN_MOTION/>11.25/ECCENTRICITY/<0.25/orderby/NORAD_CAT_ID desc/format/tle'

def fetch_leo_sats():
    session = requests.Session()

    # Log in
    login_response = session.post(LOGIN_URL, data={
        'identity': USERNAME,
        'password': PASSWORD
    })

    if login_response.status_code != 200:
        print("Login failed:", login_response.status_code, login_response.text)
        return

    # Fetch LEO satellites
    response = session.get(QUERY_URL)
    if response.status_code == 200:
        tle_data = response.text.strip()
        
        # Count TLE entities (each TLE consists of 3 lines: name + 2 data lines)
        if tle_data:
            lines = tle_data.split('\n')
            # Filter out empty lines
            non_empty_lines = [line for line in lines if line.strip()]
            tle_count = len(non_empty_lines) // 2
            
            
            # Get byte count as it would be in C (including null terminator)
            tle_bytes = len(tle_data.encode('utf-8'))
            tle_bytes_with_null = tle_bytes + 1  # Add 1 for null terminator in C
            tle_kb = tle_bytes / 1024
            tle_kb_with_null = tle_bytes_with_null / 1024
            
            print(f"TLE string size: {tle_kb:.2f} KB")
            print(f"TLE string size (C-style): {tle_kb_with_null:.2f} KB")
            print(f"Successfully retrieved {tle_count} TLE entities")
            print(f"Total lines received: {len(non_empty_lines)}")
            print(f"TLE string bytes: {tle_bytes} bytes")
            print(tle_data[:1000])
        else:
            print("No TLE data received (empty response)")
    else:
        print("Failed to fetch LEO satellites:", response.status_code, response.text)

if __name__ == "__main__":
    fetch_leo_sats()
