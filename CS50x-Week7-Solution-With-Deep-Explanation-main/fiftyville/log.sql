-- Retrieve all records from the crime_scene_reports table for the specified date and location
SELECT *  -- Select all columns from the table
FROM crime_scene_reports  -- Specify the table to query
-- Filter results to include only reports from July 28, 2023, at Humphrey Street
WHERE year=2023 AND month=7 AND day=28 AND street='Humphrey Street';
/*
  Explanation:
  - `SELECT *`: The asterisk (*) means to select all columns available in the table.
  - `FROM crime_scene_reports`: Indicates the table from which to fetch the data.
  - `WHERE`: Applies conditions to filter the rows returned by the query.
  - `year=2023 AND month=7 AND day=28 AND street='Humphrey Street'`: Specifies the conditions that rows must meet to be included in the results. Each condition is combined using the `AND` operator.
*/

-- Retrieve all interviews conducted on July 28, 2023
SELECT *  -- Select all columns from the table
FROM interviews  -- Specify the table to query
-- Filter results to include only interviews from July 28, 2023
WHERE year=2023 AND month=7 AND day=28;
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM interviews`: Specifies the table to query.
  - `WHERE year=2023 AND month=7 AND day=28`: Filters the results to only include records from the specified date.
*/

-- Retrieve bakery security log entries for July 28, 2023, specifically for the time range when vehicles exited
SELECT *  -- Select all columns from the table
FROM bakery_security_logs  -- Specify the table to query
-- Filter for logs from July 28, 2023, with activity 'exit' starting from 10:15 AM onwards
WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND activity='exit'
-- Order results by minute to analyze the sequence of exits
ORDER BY minute;
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM bakery_security_logs`: Indicates the table from which to fetch data.
  - `WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND activity='exit'`: Filters records to include only those with the specified conditions. `minute>=15` restricts the time to 10:15 AM and later. `activity='exit'` ensures that only exit activities are included.
  - `ORDER BY minute`: Sorts the results by the minute column to arrange the entries in chronological order.
*/

-- Retrieve information about individuals associated with specific license plates recorded in the bakery security logs
SELECT *  -- Select all columns from the table
FROM people  -- Specify the table to query
-- Filter to include only those whose license plates are found in the specified bakery security logs
WHERE license_plate IN (
    SELECT license_plate  -- Subquery to retrieve license plates from security logs
    FROM bakery_security_logs
    WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND activity='exit'
);
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM people`: Indicates the table to query.
  - `WHERE license_plate IN (...)`: Filters the results to include only those whose license plates match those in the subquery.
  - Subquery (`SELECT license_plate FROM bakery_security_logs ...`): Retrieves license plates from the bakery security logs based on specified conditions.
*/

-- Retrieve phone call records of individuals who match certain criteria
SELECT caller  -- Select the caller column from the phone_calls table
FROM phone_calls  -- Specify the table to query
WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
-- Filter callers who match phone numbers of people identified from the previous query
AND (
    caller IN (
        SELECT phone_number  -- Subquery to retrieve phone numbers from people
        FROM people
        WHERE license_plate IN (
            SELECT license_plate  -- Subquery to retrieve license plates from bakery security logs
            FROM bakery_security_logs
            WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = 'exit'
        )
    )
);
/*
  Explanation:
  - `SELECT caller`: Retrieves the caller column from the table.
  - `FROM phone_calls`: Specifies the table to query.
  - `WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60`: Filters phone call records to only include those from July 28, 2023, with a duration of 60 seconds or less.
  - `AND (caller IN (...))`: Further filters results to include only those callers whose phone numbers are found in the subquery.
  - Subquery (`SELECT phone_number FROM people ...`): Retrieves phone numbers of people associated with license plates observed exiting the bakery.
*/

-- Retrieve ATM transaction records for withdrawals made on July 28, 2023, at a specific location
SELECT *  -- Select all columns from the table
FROM atm_transactions  -- Specify the table to query
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street'  -- Filter for transactions at Leggett Street
AND transaction_type = 'withdraw';  -- Filter for withdrawal transactions
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM atm_transactions`: Indicates the table to query.
  - `WHERE year = 2023 AND month = 7 AND day = 28`: Filters records to include only those from the specified date.
  - `AND atm_location = 'Leggett Street'`: Further filters results to include only transactions that occurred at Leggett Street.
  - `AND transaction_type = 'withdraw'`: Ensures that only withdrawal transactions are included.
*/

-- Retrieve phone call records of callers related to ATM transactions and their connections
SELECT receiver, caller  -- Select both receiver and caller columns from the phone_calls table
FROM phone_calls  -- Specify the table to query
WHERE year=2023 AND month=7 AND day=28 AND duration<=60
AND caller IN (
    SELECT phone_number  -- Subquery to retrieve phone numbers linked to ATM transactions
    FROM people
    WHERE id IN (
        SELECT person_id  -- Subquery to retrieve person IDs from bank accounts
        FROM bank_accounts
        WHERE account_number IN (
            SELECT account_number  -- Subquery to retrieve account numbers from ATM transactions
            FROM atm_transactions
            WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
        )
    )
    AND phone_number IN (
        SELECT caller  -- Subquery to retrieve callers with specific phone numbers
        FROM phone_calls
        WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
        AND caller IN (
            SELECT phone_number  -- Subquery to retrieve phone numbers associated with bakery security logs
            FROM people
            WHERE license_plate IN (
                SELECT license_plate  -- Subquery to retrieve license plates from bakery security logs
                FROM bakery_security_logs
                WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = 'exit'
            )
        )
    )
    AND license_plate IN (
        SELECT license_plate  -- Subquery to retrieve license plates from bakery security logs
        FROM bakery_security_logs
        WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 AND activity = 'exit'
    )
);
/*
  Explanation:
  - `SELECT receiver, caller`: Retrieves both receiver and caller columns from the table.
  - `FROM phone_calls`: Specifies the table to query.
  - `WHERE year=2023 AND month=7 AND day=28 AND duration<=60`: Filters phone calls to include those from July 28, 2023, with a duration of 60 seconds or less.
  - `AND caller IN (...)`: Further filters results to include only those callers whose phone numbers are found in the subquery.
  - Subqueries:
    - The innermost subquery retrieves account numbers from ATM transactions.
    - The middle subquery retrieves person IDs from bank accounts associated with those account numbers.
    - The outer subquery retrieves phone numbers linked to those people.
    - Additional subqueries further filter phone numbers based on bakery security logs and license plates.
*/

-- Retrieve passenger records for specific passport numbers
SELECT *  -- Select all columns from the table
FROM passengers  -- Specify the table to query
WHERE passport_number=3592750733 OR passport_number=5773159633;
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM passengers`: Indicates the table to query.
  - `WHERE passport_number=3592750733 OR passport_number=5773159633`: Filters records to include only those with the specified passport numbers. The `OR` operator is used to include records that match either passport number.
*/

-- Retrieve flight details for a specific passenger based on their passport number
SELECT *  -- Select all columns from the table
FROM flights  -- Specify the table to query
WHERE id IN (
    SELECT flight_id  -- Subquery to retrieve flight IDs from passengers
    FROM passengers
    WHERE passport_number=5773159633
);
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM flights`: Specifies the table to query.
  - `WHERE id IN (...)`: Filters results to include only flights with IDs found in the subquery.
  - Subquery (`SELECT flight_id FROM passengers WHERE passport_number=5773159633`): Retrieves flight IDs associated with the specified passport number.
*/

-- Retrieve flight details for another specific passenger based on their passport number
SELECT *  -- Select all columns from the table
FROM flights  -- Specify the table to query
WHERE id IN (
    SELECT flight_id  -- Subquery to retrieve flight IDs from passengers
    FROM passengers
    WHERE passport_number=3592750733
);
/*
  Explanation:
  - `SELECT *`: Retrieves all columns from the table.
  - `FROM flights`: Specifies the table to query.
  - `WHERE id IN (...)`: Filters results to include only flights with IDs found in the subquery.
  - Subquery (`SELECT flight_id FROM passengers WHERE passport_number=3592750733`): Retrieves flight IDs associated with the specified passport number.
*/

-- Retrieve the destination city for a specific flight
SELECT city  -- Select the city column from the airports table
FROM airports  -- Specify the table to query
WHERE id IN (
    SELECT destination_airport_id  -- Subquery to retrieve destination airport IDs from flights
    FROM flights
    WHERE id IN (
        SELECT flight_id  -- Subquery to retrieve flight IDs from passengers
        FROM passengers
        WHERE passport_number=5773159633
    )
);
/*
  Explanation:
  - `SELECT city`: Retrieves the city column from the table.
  - `FROM airports`: Specifies the table to query.
  - `WHERE id IN (...)`: Filters results to include only airports with IDs found in the subquery.
  - Subquery (`SELECT destination_airport_id FROM flights WHERE id IN (...)`): Retrieves destination airport IDs for flights associated with the specified passport number.
  - Inner Subquery (`SELECT flight_id FROM passengers WHERE passport_number=5773159633`): Retrieves flight IDs associated with the specified passport number.
*/
