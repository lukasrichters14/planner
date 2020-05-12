import datetime
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

# If modifying these scopes, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/calendar.readonly']


def is_leap_year(year):
    """
    Determines if the given year is a leap year.
    :param year: [int] the year.
    :return: [bool] True if year is a leap year, False otherwise.
    """
    if (year % 4 == 0 and year % 100 != 0) or year % 400 == 0:
        return True

    return False


def get_max_time(now):
    """
    Safely calculates the time two weeks from now.
    :param now: [datetime] the current time.
    :return: [string] the properly formatted string for the date two weeks from now.
    """
    SPECIAL_MONTHS = (1, 3, 5, 7, 8, 10, 12)   # Months with 31 days.
    day = now.day
    month = now.month
    year = now.year

    # Two weeks from now (includes the whole 14th day).
    day += 15

    # Make sure date is valid.
    # February.
    if month == 2:
        if is_leap_year(year):
            if day > 29:
                month += 1
                day -= 29
        else:
            if day > 28:
                month += 1
                day -= 28

    elif month in SPECIAL_MONTHS:
        if day > 31:
            # New year.
            if month == 12:
                year += 1
                month = 1
            else:
                month += 1
            day -= 31
    else:
        if day > 30:
            day -= 30
            month += 1

    return datetime.datetime(year, month, day).isoformat() + 'Z'


def main():
    # Retrieve credentials of the user.
    # Code from: https://developers.google.com/calendar/quickstart/python
    creds = None
    # The file token.pickle stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    service = build('calendar', 'v3', credentials=creds)

    # Call the Calendar API
    now = datetime.datetime.utcnow()
    # Max time is two weeks from now.
    max_time = get_max_time(now)
    print(max_time)
    now = now.isoformat() + 'Z'  # 'Z' indicates UTC time
    print('Getting the upcoming 10 events')
    events_result = service.events().list(calendarId='primary', timeMin=now,
                                          timeMax=max_time, singleEvents=True,
                                          orderBy='startTime').execute()
    events = events_result.get('items', [])

    if not events:
        print('No upcoming events found.')
    for event in events:
        # start = event['start'].get('dateTime', event['start'].get('date'))
        print(event['summary'])


if __name__ == '__main__':
    main()
