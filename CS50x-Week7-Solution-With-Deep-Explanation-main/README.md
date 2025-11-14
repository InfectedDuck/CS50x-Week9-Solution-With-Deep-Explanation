# README

### ⭐️ **Star this repository! It really motivates me to make better explanations and produce more work!!** ⭐️

## Overview

This repository contains various SQL queries used for different data retrieval tasks. The queries are organized by their functionality and purpose, providing insights into how to extract and manipulate data from a database.

## SQL Queries

### Query to Retrieve Crime Scene Reports

```sql
SELECT *
FROM crime_scene_reports
WHERE year=2023 AND month=7 AND day=28 AND street='Humphrey Street';

```

#### Purpose

This query fetches all crime scene reports from a specific date and location. It helps in understanding the context and details of the crime scene.

#### Key Points

- Filters data based on year, month, day, and street.
- Useful for gathering preliminary information about the crime.


### Query to Retrieve Interviews
```sql
SELECT *
FROM interviews
WHERE year=2023 AND month=7 AND day=28;
```
#### Purpose

This query obtains all interviews conducted on a specific date, which can provide insights into witness statements and other critical information.

#### Key Points

- Helps in gathering evidence related to transactions, parking, and calls.
- Useful for understanding witness accounts and potential leads.

### 3. Query to Retrieve Bakery Security Logs
```sql
SELECT *
FROM bakery_security_logs
WHERE year=2023 AND month=7 AND day=28 AND  hour=10 AND minute>=15 AND activity='exit'
ORDER BY minute;
```

#### Purpose

This query retrieves security logs for a specific time window, focusing on exit activities. It helps in analyzing movements and possible suspects.

#### Key Points

- Filters logs based on date, time, and activity.
- Orders results by minute to track exact exit times.

### Query to Retrieve People with Specific License Plates
```sql
SELECT *
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year=2023 AND month=7 AND day=28 AND hour=10 AND minute>=15 AND activity='exit');
```
#### Purpose

This query identifies individuals associated with specific license plates found in the security logs.

#### Key Points

- Uses subqueries to filter people based on license plates from the logs.
- Helps in identifying potential suspects or witnesses.

### Query to Retrieve Callers with Short Call Durations
```sql
SELECT caller
FROM phone_calls
WHERE year = 2023
AND month = 7
AND day = 28
AND duration <= 60
AND (
    caller IN (
        SELECT phone_number
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND activity = 'exit'
        )
    )
);
```

#### Purpose

This query retrieves phone numbers of callers who made brief calls on the day of the crime. It helps in identifying possible suspects.

#### Key Points

- Filters calls based on duration and date.
- Uses subqueries to cross-reference phone numbers and license plates.

### Query to Retrieve People with Specific Phone Numbers
```sql
SELECT *
FROM people
WHERE phone_number IN (
    SELECT phone_number
    FROM phone_calls
    WHERE phone_number IN (
        SELECT phone_number
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE year = 2023
            AND month = 7
            AND day = 28
            AND hour = 10
            AND minute >= 15
            AND activity = 'exit'
        )
    )
);
```
#### Purpose

This query helps in identifying individuals who have phone numbers linked to the license plates from the security logs.

#### Key Points

- Uses multiple subqueries to filter and cross-reference phone numbers.
- Aids in connecting people based on phone numbers and license plates.

### Query to Retrieve Titles of Movies Released in 2008
```sql
SELECT title
FROM movies
WHERE year=2008;
```
#### Purpose

This query retrieves the titles of movies released in a specific year, in this case, 2008.

#### Key Points

- Filters movies based on the year of release.
- Provides a list of movie titles for the specified year.

### Query to Retrieve Distinct Names of People Who Directed High-Rated Movies
```sql
SELECT DISTINCT people.name
FROM directors
JOIN people ON directors.person_id=people.id
WHERE movie_id IN (
    SELECT id
    FROM movies
    JOIN ratings ON ratings.movie_id=movies.id
    WHERE ratings.rating>=9.0
);
```
#### Purpose

This query identifies the names of directors who have directed movies with high ratings.

#### Key Points

- Uses DISTINCT to avoid duplicate names.
- Joins multiple tables to filter based on movie ratings.

### Query to Retrieve Top 5 Movies Starring Chadwick Boseman
```sql
SELECT movies.title
FROM stars
JOIN movies ON movies.id=stars.movie_id
JOIN people ON people.id=stars.person_id
JOIN ratings ON ratings.movie_id=stars.movie_id
WHERE people.name='Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;
```

#### Purpose

This query retrieves the top 5 movies featuring Chadwick Boseman, based on their ratings.

#### Key Points

- Joins tables to gather data on movies, stars, and ratings.
- Orders results by rating and limits the output to the top 5 movies.

### Query to Retrieve Movies Featuring Both Bradley Cooper and Jennifer Lawrence
```sql
SELECT movies.title
FROM stars
JOIN movies ON movies.id=stars.movie_id
JOIN people ON people.id=stars.person_id
WHERE stars.movie_id IN (
    SELECT movie_id
    FROM stars
    JOIN people ON people.id=stars.person_id
    WHERE people.name='Bradley Cooper'
)
AND stars.movie_id IN (
    SELECT movie_id
    FROM stars
    JOIN people ON people.id=stars.person_id
    WHERE people.name='Jennifer Lawrence'
);
```
#### Purpose

This query finds movies that feature both Bradley Cooper and Jennifer Lawrence.

#### Key Points

- Uses subqueries to filter movies featuring specific actors.
- Joins multiple tables to gather required information.

### Query to Retrieve Names of Co-Stars of Kevin Bacon
```sql
SELECT name
FROM people
WHERE id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id = (
            SELECT id
            FROM people
            WHERE name = 'Kevin Bacon' AND birth = 1958
        )
    )
) AND name != 'Kevin Bacon';
```
### Query to Retrieve Names of Co-Stars of Kevin Bacon

#### Purpose

This query identifies individuals who have acted in movies with Kevin Bacon, excluding Kevin Bacon himself.

#### Key Points

- Uses multiple subqueries to filter and find co-stars.
- Excludes Kevin Bacon from the results.

### Query to Retrieve Birth Year of Emma Stone
```sql
SELECT birth
FROM people
WHERE name='Emma Stone';
```
#### Purpose

This query retrieves the birth year of Emma Stone from the database.

#### Key Points

- Filters the people table based on the name.
- Provides birth information for the specified individual.

### Query to Retrieve Movie Titles Released in or After 2018
```sql
SELECT title
FROM movies
WHERE year>=2018
ORDER BY title;
```
#### Purpose

This query retrieves movie titles released in or after 2018 and orders them alphabetically.

#### Key Points

- Filters movies based on the release year.
- Orders the results by title for easy browsing.

### Query to Count Movies with a Rating of 10.0
```sql
SELECT COUNT(movie_id)
FROM ratings
WHERE rating=10.0;
```
#### Purpose

This query counts the number of movies that have received a perfect rating of 10.0.

#### Key Points

- Uses COUNT to tally the number of qualifying movies.
- Filters ratings to find perfect scores.

### Query to Retrieve Titles of Movies with "Harry Potter"
```sql
SELECT title, year
FROM movies
WHERE title LIKE "%Harry Potter%"
ORDER BY year;
```
#### Purpose

This query retrieves movie titles containing "Harry Potter" and orders them by the release year.

#### Key Points

- Uses the LIKE operator to filter titles.
- Orders the results by year for chronological viewing.

### Query to Retrieve Names of People with Common Licenses
```sql
SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM people
    GROUP BY license_plate
    HAVING COUNT(*) > 1
);
```
#### Purpose

This query identifies people with license plates that appear in multiple records.

#### Key Points

- Uses GROUP BY and HAVING to filter common license plates.
- Helps in finding individuals with multiple records.

### Query to Retrieve Movie Ratings Above Average
```sql
SELECT title
FROM movies
JOIN ratings ON movies.id=ratings.movie_id
GROUP BY title
HAVING AVG(rating) > (
    SELECT AVG(rating)
    FROM ratings
);
```
### Query to Retrieve Movie Ratings Above Average

#### Purpose

This query retrieves movie titles with ratings above the average rating.

#### Key Points

- Uses AVG to calculate the average rating and filter movies above this threshold.
- Joins movies and ratings tables for comprehensive data.

### Query to Retrieve Most Recent Movies
```sql
SELECT title, year
FROM movies
ORDER BY year DESC
LIMIT 10;
```
#### Purpose

This query retrieves the titles of the most recent movies, up to a specified limit, ordered by release year.

#### Key Points

- Orders results by year in descending order.
- Limits the output to the top 10 most recent movies.

<table>
  <tr>
    <td><img src="images/CS50x_logo.png" alt="CS50 Logo" width="800" height="300"></td>
    <td>
      <h3>Credits to CS50x</h3>
      <p>This project was inspired by and developed as part of the CS50x course offered by Harvard University. CS50x is Harvard University's introduction to the intellectual enterprises of computer science and the art of programming for majors and non-majors alike, with or without prior programming experience.</p>
      <ul>
        <li><strong>Course:</strong> CS50x: Introduction to Computer Science</li>
        <li><strong>Institution:</strong> Harvard University</li>
        <li><strong>Instructor:</strong> David J. Malan</li>
        <li><strong>Website:</strong> <a href="https://cs50.harvard.edu/x/2024/">CS50x Official Site</a></li>
      </ul>
      <p>Thank you to the CS50x team for providing such a comprehensive and engaging introduction to computer science.</p>
    </td>
  </tr>
</table>
